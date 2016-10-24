/*
	@author: Zeeshan Sajid, Vance Piscitelli 
	@brief: This program allows the person to play air-hockey using opengl
	This program loads models using a function called objLoader, in which it also adds textures, furthermore, returning
	a trimesh for Bullet in order to create static shapes used for collision. From there, we loaded 5 objects, two paddles
	a puck, and a table. The table is static while the paddles are dynamic along with the puck, and they are used to play air-hockey

	Extra Credit:
	For extra credit, we have sound effects, a top 10 scores history, Text2D displayed, Game replay, 
	changeable puck shape with correct physics, changeable paddle shape, a simple and toggleable AI,
	and changeable names.

	Functionalties:
		Main Menu: Press spacebar to start the game, or right click start to start the game
		Top Scores: Press 9 to go and see top scores, or right click and click the menu option to go to TopScore
		
		Right-click:
			Brings up our menu: 
					-Start- Can start the game from the title menu, or unpause the game while playing
					-Stop- Pauses the game while playing, pieces do not move
					-Replay- If the game is won, meaning the max number of points is received, then 
					-Change paddle/Puck shape- This menu option allows the user to change their paddle/puck into a square
					if already a square, it changes back to circle
					-Show topScores- This menu option allows the user to go to the topScore menu if and only if they are on the
					title Screen
					-Reset board- This resets the board, meaning the pieces are moved back to its original positions, including the puck
					paddles, but the scores are not
					-quit- This quits the game, essentially top scores will be written to a file prior to exiting
	
		Keyboard:
				'WASD': The 'W' key moves the yellow paddle up
						The 'A' key moves the yellow paddle left
						The 'S' key moves the yellow paddle down
						The 'D' key moves the yellow paddle right
						The 'F' key stops the yellow paddle
						The 'G' key speeds up the yellow paddle

				'Arrow: Up key moves the red paddle up
				Keys'	Down key moves the red paddle down
						Right key moves the red paddle right
						Left key moves the red paddle left
						The '/' key speeds up the red paddle
						The '.' key stops the red paddle

				'9': Goes to the top Score menu
				'r': Goes back to the title menu at any point and resets the game
				' ': Goes to game screen
				'p': Option to change paddles to square through keybard
				';': Option to change pucks to square through keyboard
				'\': Disables ai or enables
				'1': Top-down view
				'2': Angled view
				'3': Angled view and follows puck
	
		Mouse controls:
				While holding down the left mouse button:
						If the mouse moves left, the red paddle moves left.
						If the mouse moves right, the red paddle moves right.
						If the mouse moves up, the red paddle moves up.
						If the mouse moves down, the red paddle moves down.

		Esc Key: Quits the game entirely

	Irrklang audio library:
		Overview:
		Irrklang is a cross platform sound library for C++, C# and all .NET languages, essentially,
	it is free for non-commercial, while there si a pro version that comes with more features than the free.
	Since this is not offered on GitHub it is much harder to attain it than by just doing sudo apt-get install lib
	
	Instructions for usage:
		1. To download, go to http://www.ambiera.com/irrklang/, and click download and download the zip file 
		Irrklang has available, and it will come in as a zip file
		2. Extract the zip file and run the hello world or any program to see if it works and is not corrupted
		3. From there, extract the folder specifically catered to your OS. Since this class is using Linux, grab
		linux-gcc-64, along with the include folder which will host most of the header files
		4. From there go into your makefile and add this line or equivalent file location:
		OPTS = -I"../src/include"  ../src/linux-gcc-64/libIrrKlang.so -pthread
		5. From there, add it to compiler flag just like you would with LIBS, something along the lines of this:
		$(CC) $(CXXFLAGS) ../src/shader.cpp ../src/main.cpp -o ../bin/Bullet $(LDFLAGS) $(LIBS) $(OPTS)
		6. Within your .cpp file or wherever you are running it, #include<irrKlang.h> and if you want to use the namespace you can just by doing using namespace irrKlang
		7. From there, the program should be compilable and you can start using irrKlang for a lot of different sound libraries.
*/

/*
shader.h contains <GL/glew.h> <GL/glut.h>  <iostream> <fstream> <string.h>
*/

#define GLM_FORCE_RADIANS 
#include <btBulletDynamicsCommon.h>
#include <GL/glew.h> // glew must be included before the main gl libs
#include <GL/glut.h> // doing otherwise causes compiler shouting
#include <iostream>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier
#include "shader.h"
#include <vector> // Stl library
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <Magick++.h> // Texture mapping library
#include <string.h> 
#include <fstream> // In and output stream
#include <math.h>
#include <irrKlang.h> // This is the sound library
using namespace irrklang; // This is so I don't have to use scope resolution operator each time for soundEngine

// This is a masking 
#define BIT(x) (1<<(x))

// These are enumeration for variables that will be explicitly used for only Bullet and its collision with other objects
enum collisiontypes
{
    COL_PLANE = BIT(1), //Collide with plane
    COL_PUCK = BIT(2), //Collide with cylinder
	COL_PADDLE = BIT(3), // Collision with paddle
	COL_TOP = BIT(5), // Collision with the table top
	COL_WALL = BIT(6), // Collision with sides of the table
	COL_MID = BIT(7), // Collision with middle of the table, COL_WALL and COL_MID can be combined 
  	COL_GOAL = BIT(8), // COL_GOAL, collision for the goal
};

// This is a struct to calculate the top scores within the game, has two member variables
struct game
{
	string winner; // The name of the winner 
	int matchesWon; // The amount of matches won by said user
};

/*
	Comparator function used by stl:: sort
	The function takes two of the game struct object from the topScores vector and compares the value of matches won for player and b
	@param: Two game object are passed from the stl call
	@pre:
	@post:
*/
bool compareByScore(game a, game b)
{
	return a.matchesWon > b.matchesWon;
}

int puckCollision = COL_PLANE | COL_PADDLE  | COL_TOP | COL_WALL;
int tableCollision = COL_PADDLE | COL_PUCK | COL_PLANE;
int groundCollision = COL_PADDLE |COL_PUCK  | COL_TOP;
int paddleCollision = COL_PUCK | COL_TOP | COL_PLANE | COL_PADDLE | COL_MID | COL_GOAL;
int wallCollision = COL_PUCK | COL_PADDLE | COL_PLANE;
int midCollision = COL_PADDLE;
int goalCollision = COL_PADDLE;

// Global sound stuff
ISoundEngine* engine = createIrrKlangDevice();

//--Data types
//This object will define the attributes of a vertex(position, color, etc...)
struct Vertex
{
	GLfloat position[3];
	GLfloat normals[3];
	GLfloat uv[2];
};

// These are the obj's
// This is for magick
GLuint *texture = NULL; // For texture, need to dynamically allocate
Magick::Blob *bigBlob = NULL;;

// This is the number of vertices that belong to each of the different objects
int boardVert = 0;
int puckVert = 0;
int paddle1Vert = 0;
int paddle2Vert = 0;
int wallVert = 0;
int goal1Vert = 0;
int goal2Vert = 0;
int square1Vert = 0;
int square2Vert = 0;
int squarePuckVert = 0;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // Won't be used at the moment.

//--Evil Global variables
int w = 1080, h = 720;// Window size
const int numModels = 10;
GLuint program;// The GLSL program handle
GLuint vbo_geometry[numModels];// VBO handle for our geometry
GLuint vbo_geoTemp;
int mStartX, mStartY = 0;
bool mousePressed = false;
bool* keyStates = new bool[256]; // whether or not each key is pressed
bool* keySpecialStates = new bool[256]; // for the special keys
bool pauseGame = false;
bool squarePaddles = false;
bool squarePuck = false;
bool aiEnabled = false;
int p1score = 0;
int p2Score = 0;
int maxScore = 7;
string player1Name;
string player2Name;
vector<game> topScores;

//uniform locations
GLint loc_mvpmat;// Location of the modelviewprojection matrix in the shader
GLint loc_model;

//attribute locations
GLint loc_position;
GLint loc_uv;
GLint loc_normal;

//transform matrices
glm::mat4 model[numModels];//obj->world each object should have its own model matrix, one for the board, one for the sphere, one for the cube, etc...
glm::mat4 view;//world->eye
glm::mat4 projection;//eye->clip
glm::mat4 mvp;//premultiplied modelviewprojection

glm::vec3 cameraPos; // location of the camera
glm::vec3 focusPos; // location of the point the camera is looking at
int modelToFocus = 4; // the number of the model for the camera to look at

// Title screen
int titleScreen = 1; // This will be used to tell if the game is on the title screen
int showTopScore = 0; // This will be used to tell if the user wants to see the top scores
int replayGame = 0;

// This stuff is for bullet
// Build the broadphase
btBroadphaseInterface *broadphase = NULL; // Not sure if i should initialize here yet or not

// Set up the collision and dispatcher
btDefaultCollisionConfiguration* collisionConfiguration = NULL;
btCollisionDispatcher* dispatcher = NULL;

// The actual physics solver
btSequentialImpulseConstraintSolver* solver = NULL;
 
// The world.
btDiscreteDynamicsWorld* dynamicsWorld = NULL;

// The rigid bodies that will be used for bullet
btRigidBody* groundRigidBody = NULL;
btRigidBody* paddle1Rb = NULL;
btRigidBody* paddle2Rb = NULL;
btRigidBody* puckRb = NULL;
btRigidBody* tableRb = NULL;
btRigidBody* wallRb = NULL;
btRigidBody* cubeRb = NULL;
btRigidBody* goal1Rb = NULL;
btRigidBody* goal2Rb = NULL;
btRigidBody* square1Rb = NULL;
btRigidBody* square2Rb = NULL;
btRigidBody* squarePuckRb = NULL;
btRigidBody* mPaddle1Rb = paddle1Rb; // points to either the first regular or square paddle
btRigidBody* mPaddle2Rb = paddle2Rb; // points to either the second regular or square paddle
btRigidBody* mPuckRb = puckRb; // points to either the regular puck or the square puck

// TriangleMeshes
btTriangleMesh *tableMesh = NULL;
btTriangleMesh *puckMesh = NULL;
btTriangleMesh *paddle1Mesh = NULL;
btTriangleMesh *paddle2Mesh = NULL;
btTriangleMesh *wallMesh = NULL;
btTriangleMesh *goal1Mesh = NULL;
btTriangleMesh *goal2Mesh = NULL;
btTriangleMesh *square1Mesh = NULL;
btTriangleMesh *square2Mesh = NULL;
btTriangleMesh *squarePuckMesh = NULL;

//--GLUT Callbacks
void render();
void update();
void reshape(int n_w, int n_h);
void keyboard(unsigned char key, int x_pos, int y_pos);
void keyReleased(unsigned char key, int x_pos, int y_pos);
void keySpecialReleased(int key, int x_pos, int y_pos);
void keyOps();
void processSpecialKeys(int key, int xx, int yy);
void specialKeyOps();
void mouseClicked(int button, int state, int x, int y);
void mouseMotion(int, int);
void movePaddle(int, int);

//--Resource management
bool initialize();
void cleanUp();

//--Random time things
float getDT();
std::chrono::time_point<std::chrono::high_resolution_clock> t1,t2;

// Menu options/ Controls
void menu(int id);

// Loaders
Vertex *objLoader(string imageFile, int &numVertices, btTriangleMesh *& sendBackMesh);

// updates the rigid bodies. called in update()
void updateRb(btRigidBody*, int);

/*
	Get information for uv textures that was collected from the objLoader and read it into and attach it
	@param: 
			String: name of the texture
			int: The place in the texture pointer
	@pre: Needs a good looking texture
	@post: Returns indirectly with a texture array
*/
void loadImage(string, int);

/*
	Reads in TopScores.txt, and places it into the vector known as topScores
	@param: NULL
	@pre: Nothing, if no topScores, it does nothing
	@post: Reads in topScores to a vector
*/
// Create a image object and then have it read it, create textures bind it, and then do other gibberish things
void loadImage(string, int);

// This reads in the scores from the .txt file most likely into a map
bool readInTopScores();

/*
	Writes to topSCores in a file, essentially used to record games won by player x
	@param: NULL
	@pre: Nothing, if no topScores, it writes out a file topScores
	@post: Reads out topScores
*/
void writeToTopScores();

// sets the velocity for a paddle, making sure its within valid range.
void addVelocity(int, float, float, float);

// swaps between regular and square paddles
void swapPaddles();

// swaps between regular and square puck
void swapPuck();

// decides what the AI should do
void calcAI();

// This is for changing paddle from menu
void changePaddleSub(int selection);

//--Main
int main(int argc, char **argv)
{
	// Initialize Magick++
	Magick :: InitializeMagick(*argv);

	// If the arguments passed in when running bullet is greater than two, record the names
	if(argc > 2)
	{
		// Use the names passed in from the parameter
		player1Name = argv[1];
		player2Name = argv[2];
	}

	// Otherwise use default names
	else
	{
		player1Name = "Player1";
		player2Name = "Player2";
	}

	// Read in top scores from file if it exist
	readInTopScores();

    // Initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);

    // Name and create the Window
    glutCreateWindow("PA9 - Hockey by Vance Piscitelli & Zeeshan Sajid");

	// Create a menu but attach it
    int subMenuPaddle = glutCreateMenu(changePaddleSub);
    glutAddMenuEntry("Make paddle square or circle",1);
    glutAddMenuEntry("Make puck square or circle",2);

    // Create the main glut menu and attach it as a submenu
	glutCreateMenu(menu);
	glutAddMenuEntry("Start", 1);
	glutAddMenuEntry("Stop", 2);
	glutAddMenuEntry("Replay", 3);
	glutAddSubMenu("Change paddle/puck shape", subMenuPaddle);
	glutAddMenuEntry("Show top scores", 4);
	glutAddMenuEntry("Reset board", 5);
	glutAddMenuEntry("Quit", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    // Now that the window is created the GL context is fully set up
    // Because of that we can now initialize GLEW to prepare work with shaders
    GLenum status = glewInit();

    if( status != GLEW_OK)
    {
        std::cerr << "[F] GLEW NOT INITIALIZED: ";
        std::cerr << glewGetErrorString(status) << std::endl;
        return -1;
    }

    // Set all of the callbacks to GLUT that we need
    glutDisplayFunc(render);// Called when its time to display
    glutReshapeFunc(reshape);// Called if the window is resized
    glutIdleFunc(update);// Called if there is nothing else to do
    glutKeyboardFunc(keyboard);// Called if there is keyboard input
	glutKeyboardUpFunc(keyReleased);// Called when a key is released
	glutSpecialUpFunc(keySpecialReleased);// Called when a special key is released
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(mouseClicked);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(movePaddle);
	
	// hiding the cursor
	//glutSetCursor(GLUT_CURSOR_NONE);
	// Plays the song and loops it
	engine->play2D("../bin/breakout.wav", true);

	// Initialize all of our resources(shaders, geometry)	
	if(initialize())
    {
        t1 = std::chrono::high_resolution_clock::now();
        glutMainLoop();
	}

	cleanUp();
	return 0;
}

//--Implementations
void render()
{
	//clear the screen
	glClearColor(0.2, 0.2, 0.4, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(0);

	// Check to see if the game is on the title screen
	if(titleScreen == 1 && showTopScore == 0)
	{
	  	string start = "Press space to start game";
	  	glColor3f(1.0, 0.0, 0.0); 
	  	glRasterPos3f(-.3,.0,0);

		// If so render these two things onto the screen
		for(int i = 0; i < start.size(); i++)
		{    
	    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, start[i]);
		}

		// Rinse and repeat
		start = "Press '9' for top scores";
		glColor3f(1.0, 0.0, 0.0); 
		glRasterPos3f(-.3,-0.2,0);

	  	for(int i = 0; i < start.size(); i++)
		{    
	        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, start[i]);
		}
		pauseGame = 1;
	}


	// If not on the title screen, check to see if it is on the top 10 score board
	else if(showTopScore == 1 && titleScreen == 0)
		{
			char instructions[60];
			glColor3f(1.0, 0.0, 0.0); 
		  	glRasterPos3f(-.4,.9,0);

			sprintf(instructions, "Top 10 Scores, based on matches won");

			for(int i = 0; instructions[i] != '\0'; i++)
				{    
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, instructions[i]);

				}

			// Sort the top scores out using comparator function
			std :: sort(topScores.begin(), topScores.end(), compareByScore);

			// This places the rasterization
			float yvalue = 0.8;
			
			
			// Rasterize the top scores based on the topSCores in the vector
			if(topScores.size() < 10)
				{
				for(int i = 0; i < topScores.size(); i++)
					{
						if(!topScores[i].winner.empty() )
						{
							char buffer[40];
							sprintf(buffer, "%d. %s = %d" , i+1,  topScores[i].winner.c_str(), topScores[i].matchesWon);

							glColor4f(0,1,0, 1.0f);
							glRasterPos3f( -.2, yvalue, 0.0 );



							for(int i = 0; buffer[i] != '\0'; i++)
							{    
								glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

							}
											yvalue -= 0.08;
						}
					}
				}
			// Rinse and repeat
			else if(topScores.size() > 10)
			{
				for(int i = 0; i < 10; i++)
				{
					if(!topScores[i].winner.empty() )
					{
						char buffer[40];
						sprintf(buffer, "%d. %s = %d" , i+1, topScores[i].winner.c_str(), topScores[i].matchesWon);

						glColor4f(0,1,0, 1.0f);
						glRasterPos3f( -.2, yvalue, 0.0 );

						for(int i = 0; buffer[i] != '\0'; i++)
						{    
							glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

						}

						yvalue -= 0.08;
					}
				}
			}
			// Render some more instructions to the screen
			char Leaveinstructions[30];
			glColor3f(1.0, 0.0, 0.0); 
		  	glRasterPos3f(-.4,-.9,0);

			sprintf(Leaveinstructions, "Press home key to leave");

			for(int i = 0; Leaveinstructions[i] != '\0'; i++)
			{    
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Leaveinstructions[i]);
			}
			
		}

	// Otherwise check to see if it is actually playing the game itself.
	else if(showTopScore == 0 && titleScreen == 0)
	{
		// Display the scores by rasterizing them and using sprintf to take in the string as a c-style string, along with the score that they currently have
		if(p1score != maxScore && p2Score != maxScore)
		{
			char buffer[30];
			glColor4f(0,1,0, 1.0f);
			glRasterPos3f( -.9, .7, 0.0 );

			sprintf(buffer, "%s: %d", player1Name.c_str(), p1score);

			for(int i = 0; buffer[i] != '\0'; i++)
			{    
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, buffer[i]);

			}
			
			sprintf(buffer, "%s: %d", player2Name.c_str(), p2Score);
			glColor4f(0,1,0, 1.0f);
			glRasterPos3f( .5, .7, 0.0 );

			for(int  k = 0; buffer[k] != '\0'; k++ )
			{
				glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, buffer[k]);
			}
	  	}

		// Activate textures
		glUseProgram(program);

		glActiveTexture(GL_TEXTURE0);

		// Render the models to the screen after getting their rb counterparts
		for(int i = 0; i < numModels; i++)
		{
			//premultiply the matrix for this example
			mvp = projection * view * model[i];

			//enable the shader program

			//upload the matrix to the shader
			glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));

			//set up the Vertex Buffer Object so it can be drawn
			glEnableVertexAttribArray(loc_position);
			glEnableVertexAttribArray(loc_uv);

			int numVert = 0;

			switch(i)
			{
				case 0:
					numVert = boardVert;
					break;

				case 1:
					numVert = puckVert;
					break;

				case 2:
					numVert = paddle1Vert;
					break;

				case 3:
					numVert = paddle2Vert;
					break;

				case 4:
					numVert = wallVert;
					break;

				case 5:
					numVert = goal1Vert;
					break;

				case 6:
					numVert = goal2Vert;
					break;	

				case 7:
					numVert = square1Vert;
					break;

				case 8:
					numVert = square2Vert;
					break;	

				case 9:
					numVert = squarePuckVert;
					break;		
			}

			glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[i]);
			//set pointers into the vbo for each of the attributes(position and color)

			//set pointers into the vbo for each of the attributes(position and color)
		   	glVertexAttribPointer(loc_position,//location of attribute
					              3,//number of elements
					              GL_FLOAT,//type
					              GL_FALSE,//normalized?
					              sizeof(Vertex),//stride
					              0);//offset
			glBindTexture(GL_TEXTURE_2D, texture[i]);

		   	glVertexAttribPointer(loc_uv,
					              2,
					              GL_FLOAT,
					              GL_FALSE,
					              sizeof(Vertex),
					              (void*)offsetof(Vertex,uv));

			glDrawArrays(GL_TRIANGLES, 0, numVert);//mode, starting index, count
		}	

		//clean up
		glDisableVertexAttribArray(loc_position);

		glDisableVertexAttribArray(loc_uv);  

		// Check to see the winner and rasterize
		if(p1score == maxScore)
		{
			// Stop using the program
			glUseProgram(0);
			char buffer[30] ;

			// Rasterization process, use the name as the string and loop through for both the instructions and name
			glColor4f(1.0,1,0, 1.0f);
			glRasterPos3f( -.1, .8, 0.0 );

			sprintf(buffer, "%s won this match", player1Name.c_str());


			for(int  k = 0; buffer[k] != '\0'; k++ )
			{
				glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, buffer[k]);
			}
		  	
		  	pauseGame = 1;

			char winState[] = "Play again through menu or 'r' key to return to menu";

		  	glColor4f(1.0,1,0, 1.0f);
			glRasterPos3f( -.5, .5, 0.0 );


			for(int  k = 0; winState[k] != '\0'; k++ )
			{
				glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, winState[k]);
			}
		}          

		// Rinse and repeat
		else if(p2Score == maxScore)
		{
			glUseProgram(0);
			char buffer[30] ;
			glColor4f(1.0,1,0, 1.0f);
			glRasterPos3f( -.1, .8, 0.0 );

			sprintf(buffer, "%s won this match", player2Name.c_str());


			for(int  k = 0; buffer[k] != '\0'; k++ )
			{
				glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, buffer[k]);
			}
		  	pauseGame = 1;

			char winState[] = "Play again through menu or 'r' key to return to menu";


		  	glColor4f(1.0,1,0, 1.0f);
			glRasterPos3f( -.5, .5, 0.0 );


			for(int  k = 0; winState[k] != '\0'; k++ )
			{
				glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, winState[k]);
			}
		}		
	}        

	//swap the buffers
	glutSwapBuffers();
}

void update()
{
	// check for any key presses and handle them accordingly
	keyOps();
	specialKeyOps();

	// push the puck down
	mPuckRb->setLinearVelocity(btVector3(mPuckRb->getLinearVelocity().x(), -1, mPuckRb->getLinearVelocity().z()));
	mPaddle1Rb->setLinearVelocity(btVector3(mPaddle1Rb->getLinearVelocity().x(),-1, mPaddle1Rb->getLinearVelocity().z()));
	mPaddle2Rb->setLinearVelocity(btVector3(mPaddle2Rb->getLinearVelocity().x(),-1, mPaddle2Rb->getLinearVelocity().z()));

	// Check to see if ai is enabled
	if(aiEnabled)
	{
		calcAI();
	}

	// Make the camera look at a specific position
	view = glm::lookAt( cameraPos, //Eye Position
                    	focusPos, //Focus point
                    	glm::vec3(0.0, 1.0, 0.0)); //Positive Y is up

    // total time
    float dt = getDT();// if you have anything moving, use dt.
    static float angle = 0.0;

    // Check to see if paused, if so change dt to 0
    if(pauseGame == true)
    {
    	dt = 0; // Don't let dt effect everything
    }
	
    // Update physics world
    dynamicsWorld->stepSimulation(dt, 10);

    // This gets the position of the object
    btVector3 puckPosition = mPuckRb->getCenterOfMassPosition();

    // This checks if the puck is inside the goal area
    if(puckPosition.z() < -26)
    {
    	// If so increment the score
		p1score+=1;

		// This segment of code resets the puck if socred on player 2 side relative of course
		{
			btDefaultMotionState *shapeMotionState = NULL;
			shapeMotionState = new btDefaultMotionState(btTransform( 
						                             btQuaternion( 0, 0, 0, 1 ),
						                             btVector3( 0, 1, -3 ) ) );
			mPuckRb->setMotionState(shapeMotionState);
			mPuckRb->setLinearVelocity(btVector3(0,-1,0));

			engine->play2D("../bin/Scream Of Joy.wav", false);
		}
    }

    // Check the same for the opposite side
    else if(puckPosition.z() > 25)
    {
		p2Score+=1;

		// This segment of code resets the puck if socred on player 1 side relative of course
		{
			btDefaultMotionState *shapeMotionState = NULL;
			shapeMotionState = new btDefaultMotionState(btTransform( 
						                       btQuaternion( 0, 0, 0, 1 ),
						                       btVector3( 0, 1, 3 ) ) );
			mPuckRb->setMotionState(shapeMotionState);
			mPuckRb->setLinearVelocity(btVector3(0,-1,0));
			engine->play2D("../bin/Scream Of Joy.wav", false);
		}
    }  

    // First one to max score wins, then reset everything and ask the player if they want to replay
	if(replayGame == 1)
	{
		// If player does want to replay, reset everything starting with paddle, puck
		{
			btDefaultMotionState *shapeMotionState = NULL;		
  			shapeMotionState = new btDefaultMotionState(btTransform(
  														btQuaternion(0,0,0,1),
  														btVector3(0,1,-20)));
  			mPaddle1Rb ->setMotionState(shapeMotionState);
  		}

		{
			btDefaultMotionState *shapeMotionState = NULL;
      		shapeMotionState = new btDefaultMotionState(btTransform( 
                                           				btQuaternion( 0, 0, 0, 1 ),
                                           				btVector3( 0, 1, 0 ) ) );
      		mPuckRb->setMotionState(shapeMotionState);
      		mPuckRb->setLinearVelocity(btVector3(0,-1,0));
      	}

		{
			btDefaultMotionState *shapeMotionState = NULL;
  			shapeMotionState = new btDefaultMotionState(btTransform(
														btQuaternion(0,0,0,1),
  														btVector3(0,2,20)));
	
  			mPaddle2Rb->setMotionState(shapeMotionState);
		}

		// Reset the score
      	p1score = 0;
      	p2Score = 0;

      	// Check to see if title screen so no need to reset
      	if(titleScreen == false)
  		{
	      	replayGame = 0;
		}

		// Set the pause 
      	pauseGame = 0;
	}          

	// Update the Rbs and models
	updateRb(tableRb, 0);
	updateRb(mPuckRb, 1);
	updateRb(mPaddle1Rb, 2);
	updateRb(mPaddle2Rb, 3);

	// Update the state of the scene
	glutPostRedisplay();//call the display callback
}

// Resetting window size
void reshape(int n_w, int n_h)
{
    w = n_w;
    h = n_h;
    //Change the viewport to be correct
    glViewport( 0, 0, w, h);
    //Update the projection matrix as well
    //See the init function for an explaination
    projection = glm::perspective(45.6f, float(w)/float(h), 0.01f, 100.0f);

}

// Keyboard inputs used by keyOps
void keyboard(unsigned char key, int x_pos, int y_pos)
{
	keyStates[key] = true;
}

void keyReleased(unsigned char key, int x_pos, int y_pos)
{
	keyStates[key] = false;
}

void keySpecialReleased(int key, int x_pos, int y_pos)
{
	keySpecialStates[key] = false;
}

void keyOps()
{
    // Handle keyboard input
    if(keyStates[27])//ESC
    {
    	writeToTopScores();
    	cleanUp();
        exit(0);
    }
	
	// Add velocity in one direction based on wasd
	if(keyStates['w'] || keyStates['W'])
	{
		if(keyStates['g'] || keyStates['G'])
		{
			addVelocity(2, -16.0, 0.0, 0.0);
		}
		else
		{
			addVelocity(2, -8.0, 0.0, 0.0);
		}		
	}

	if(keyStates['a'] || keyStates['A'])
	{
		if(keyStates['g'] || keyStates['G'])
		{
			addVelocity(2, 0.0, 0.0, 16.0);
		}
		else
		{
			addVelocity(2, 0.0, 0.0, 8.0);
		}	
	}

	if(keyStates['s'] || keyStates['S'])
	{
		if(keyStates['g'] || keyStates['G'])
		{
			addVelocity(2, 16.0, 0.0, 0.0);
		}
		else
		{
			addVelocity(2, 8.0, 0.0, 0.0);
		}	
	}

	if(keyStates['d'] || keyStates['D'])
	{
		if(keyStates['g'] || keyStates['G'])
		{
			addVelocity(2, 0.0, 0.0, -16.0);
		}
		else
		{
			addVelocity(2, 0.0, 0.0, -8.0);
		}
	}

	if(keyStates['f'] || keyStates['F'])
	{
		// stops the 2nd paddle
		addVelocity(2, 0.0, 0.0, 0.0);
	}

	if(keyStates['.'] || keyStates['>'])
	{
		// stops the 1st paddle
		addVelocity(1, 0.0, 0.0, 0.0);
	}

	// makes one of the paddles move up. disabled for demo
	//if(keyStates['e'] || keyStates['E'])
	{
		//addVelocity(2, 0.0, 2.0, 0.0);
	}

	if(keyStates['i'] || keyStates['I'])
	{
		cameraPos[1] -= 0.8;
		keyStates['i'] = keyStates['I'] = false;
	}

	if(keyStates['k'] || keyStates['I'])
	{
		cameraPos[1] += 0.8;
		keyStates['k'] = keyStates['K'] = false;
	}

	if(keyStates['u'] || keyStates['I'])
	{
		cameraPos[0] += 0.8;
		keyStates['u'] = keyStates['U'] = false;
	}

	if(keyStates['j'] || keyStates['J'])
	{
		cameraPos[0] -= 0.8;
		keyStates['j'] = keyStates['J'] = false;
	}

	if(keyStates['o'] || keyStates['O'])
	{
		cameraPos[2] += 0.8;
		keyStates['o'] = keyStates['O'] = false;
	}

	if(keyStates['l'] || keyStates['L'])
	{
		cameraPos[2] -= 0.8;
		keyStates['l'] = keyStates['L'] = false;
	}

	// Top-down view
	if(keyStates['1'])
	{
		cameraPos[0] = 2.0;
		cameraPos[1] = 25.0;
		cameraPos[2] = 0.0;

		modelToFocus = 0; // board
	}

	// Angled view
	if(keyStates['2'])
	{
		cameraPos[0] = 20.0;
		cameraPos[1] = 15.0;
		cameraPos[2] = 0.0;

		modelToFocus = 0; // board	
	}

	// Angled view looking at paddle
	if(keyStates['3'])
	{
		cameraPos[0] = 20.0;
		cameraPos[1] = 15.0;
		cameraPos[2] = 0.0;

		modelToFocus = 1; // puck	
	}

	if(keyStates['4'])
	{
		//modelToFocus = 0; // board	
	}

	// Change paddles to square and vice versa
	if(keyStates['p'] || keyStates['P'])
	{
		squarePaddles = !squarePaddles;
		swapPaddles();

		// Vice versa for pucks
		if(squarePaddles)
		{
			mPaddle1Rb = square1Rb;

			{
			btDefaultMotionState *shapeMotionState = NULL;
			shapeMotionState = new btDefaultMotionState(btTransform( 
						                             btQuaternion( 0, 0, 0, 1 ),
						                             btVector3(	paddle1Rb->getCenterOfMassPosition().x(), 
																paddle1Rb->getCenterOfMassPosition().y() + 0.1, 
																paddle1Rb->getCenterOfMassPosition().z() ) ) );
			mPaddle1Rb->setMotionState(shapeMotionState);
			mPaddle1Rb->setLinearVelocity( btVector3(	paddle1Rb->getLinearVelocity().x(), 
														paddle1Rb->getLinearVelocity().y(), 
														paddle1Rb->getLinearVelocity().z() ) );
			}

			mPaddle2Rb = square2Rb;

			{
			btDefaultMotionState *shapeMotionState = NULL;
			shapeMotionState = new btDefaultMotionState(btTransform( 
						                             btQuaternion( 0, 0, 0, 1 ),
						                             btVector3(	paddle2Rb->getCenterOfMassPosition().x(), 
																paddle2Rb->getCenterOfMassPosition().y() + 0.1, 
																paddle2Rb->getCenterOfMassPosition().z() ) ) );
			mPaddle2Rb->setMotionState(shapeMotionState);
			mPaddle2Rb->setLinearVelocity( btVector3(	paddle2Rb->getLinearVelocity().x(), 
														paddle2Rb->getLinearVelocity().y(), 
														paddle2Rb->getLinearVelocity().z() ) );
			}
		}
		else
		{
			mPaddle1Rb = paddle1Rb;

			{
			btDefaultMotionState *shapeMotionState = NULL;
			shapeMotionState = new btDefaultMotionState(btTransform( 
						                             btQuaternion( 0, 0, 0, 1 ),
						                             btVector3(	square1Rb->getCenterOfMassPosition().x(), 
																square1Rb->getCenterOfMassPosition().y(), 
																square1Rb->getCenterOfMassPosition().z() ) ) );
			mPaddle1Rb->setMotionState(shapeMotionState);
			mPaddle1Rb->setLinearVelocity( btVector3(	square1Rb->getLinearVelocity().x(), 
														square1Rb->getLinearVelocity().y(), 
														square1Rb->getLinearVelocity().z() ) );
			}

			mPaddle2Rb = paddle2Rb;

			{
			btDefaultMotionState *shapeMotionState = NULL;
			shapeMotionState = new btDefaultMotionState(btTransform( 
						                             btQuaternion( 0, 0, 0, 1 ),
						                             btVector3(	square2Rb->getCenterOfMassPosition().x(), 
																square2Rb->getCenterOfMassPosition().y(), 
																square2Rb->getCenterOfMassPosition().z() ) ) );
			mPaddle2Rb->setMotionState(shapeMotionState);
			mPaddle2Rb->setLinearVelocity( btVector3(	square2Rb->getLinearVelocity().x(), 
														square2Rb->getLinearVelocity().y(), 
														square2Rb->getLinearVelocity().z() ) );
			}
		}

		keyStates['p'] = keyStates['P'] = false;
	}

	// Do the same thing for pucks
	if(keyStates[';'])
	{
		squarePuck = !squarePuck;
		swapPuck();

		// Vice versa for pucks
		if(squarePuck)
		{
			mPuckRb = squarePuckRb;

			{
			btDefaultMotionState *shapeMotionState = NULL;
			shapeMotionState = new btDefaultMotionState(btTransform( 
						                             btQuaternion( 0, 0, 0, 1 ),
						                             btVector3( puckRb->getCenterOfMassPosition().x(), 
																puckRb->getCenterOfMassPosition().y(), 
																puckRb->getCenterOfMassPosition().z() ) ) );
			mPuckRb->setMotionState(shapeMotionState);
			mPuckRb->setLinearVelocity( btVector3(	puckRb->getLinearVelocity().x(), 
													puckRb->getLinearVelocity().y(), 
													puckRb->getLinearVelocity().z() ) );
			}
		}
		else
		{
			mPuckRb = puckRb;

			{
			btDefaultMotionState *shapeMotionState = NULL;
			shapeMotionState = new btDefaultMotionState(btTransform( 
						                             btQuaternion( 0, 0, 0, 1 ),
						                             btVector3( squarePuckRb->getCenterOfMassPosition().x(), 
																squarePuckRb->getCenterOfMassPosition().y(), 
																squarePuckRb->getCenterOfMassPosition().z() ) ) );
			mPuckRb->setMotionState(shapeMotionState);
			mPuckRb->setLinearVelocity(	btVector3(	squarePuckRb->getLinearVelocity().x(), 
													squarePuckRb->getLinearVelocity().y(), 
													squarePuckRb->getLinearVelocity().z() ) );
			}		
		}

		keyStates[';'] = false;
	}

	// Enabling ai or disabling
	if(keyStates['\''])
	{
		aiEnabled = !aiEnabled;
		keyStates['\''] = false;
	}

	// Reset the game by going back to the title screen and checks to see if max score is available
	if(keyStates['r'] || keyStates['R'])
	{
		titleScreen = 1;
		showTopScore = 0;
		replayGame = 1;

		if(p1score >= maxScore)
		{
			game tmp;
			tmp.winner=player1Name;
			bool playerExist = false;

			for(int i = 0; i < topScores.size();i++)
			{
				if((player1Name == topScores[i].winner))
				{
					playerExist = true;
					topScores[i].matchesWon +=1;
				}

			}

			if(!playerExist)
			{
				tmp.matchesWon =1;
				topScores.push_back(tmp);
			}
		}
		else if(p2Score >= maxScore)
		{
			game tmp;
			tmp.winner=player2Name;
			bool playerExist = false;

			for(int i = 0; i < topScores.size();i++)
			{
				if(player2Name == topScores[i].winner)
				{
					playerExist = true;
					topScores[i].matchesWon +=1;

				}
			}

			if(!playerExist)
			{
				tmp.matchesWon =1;
				topScores.push_back(tmp);

			}
		}		
	}

	// Gets out of titlescreen and into the game screen
	if(keyStates[' '])
	{
		titleScreen = 0;
		pauseGame = 0;
	}

	// Go to top score
	else if(keyStates['9'])
	{
		if(titleScreen == 1 &&  showTopScore == 0)
		{
			showTopScore = 1;
			titleScreen = 0;
		}
	}
}

bool initialize()
{
	// Variables
	shader frag_shade;
	shader vert_shade;

	// set all the keystates to false because if something magically starts
	// as true it can cause issues.
	for(int i = 0; i < 256; i++)
	{
		keyStates[i] = false;
	}

	// Different camera positions and focus points
	cameraPos[0] = 5.0;
	cameraPos[1] = 20.0;
	cameraPos[2] = 0.0;
	focusPos[0] = model[modelToFocus][0][0];
	focusPos[1] = model[modelToFocus][0][1];
	focusPos[2] = model[modelToFocus][0][2];

	// This starts loading the different objects 
	Vertex *boardObj = objLoader("table.obj", boardVert, tableMesh);
	Vertex *puckObj = objLoader("puck.obj", puckVert, puckMesh);
	Vertex *paddle1Obj = objLoader("paddle.obj", paddle1Vert, paddle1Mesh);
	Vertex *paddle2Obj = objLoader("paddle.obj", paddle2Vert, paddle2Mesh);
	Vertex *wallObj = objLoader("wall.obj", wallVert, wallMesh);
	Vertex *goal1Obj = objLoader("goal1.obj", goal1Vert, goal1Mesh);
	Vertex *goal2Obj = objLoader("goal2.obj", goal2Vert, goal2Mesh);
	Vertex *square1Obj = objLoader("square.obj", square1Vert, square1Mesh);
	Vertex *square2Obj = objLoader("square.obj", square2Vert, square2Mesh);
	Vertex *squarePuckObj = objLoader("squarep.obj", squarePuckVert, squarePuckMesh);

	// Generate buffers for all three of those objects 
	// Generate 1 buffer for each object
	glGenBuffers(numModels, &vbo_geometry[0]);

	// Start binding those buffers to those locations
	// Bind the board buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * boardVert, boardObj, GL_STATIC_DRAW);
	
	// Bind the puck
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * puckVert, puckObj, GL_STATIC_DRAW);

	// Bind the paddle
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * paddle1Vert, paddle1Obj, GL_STATIC_DRAW);

	// Bind the paddle
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * paddle2Vert, paddle2Obj, GL_STATIC_DRAW);

	// Bind the wall
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * wallVert, wallObj, GL_STATIC_DRAW);

	// Bind the first goal
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * goal1Vert, goal1Obj, GL_STATIC_DRAW);

	// Bind the second goal
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * goal2Vert, goal2Obj, GL_STATIC_DRAW);

	// Bind the first square paddle
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * square1Vert, square1Obj, GL_STATIC_DRAW);

	// Bind the second square paddle
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * square2Vert, square2Obj, GL_STATIC_DRAW);

	// Bind the square puck
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * squarePuckVert, squarePuckObj, GL_STATIC_DRAW);

	// Allocate memory for the magick pointers so they can get the textures
	texture = new GLuint[numModels];
	bigBlob = new Magick :: Blob[numModels];	

	// Generate spaces for those texture
	glGenTextures(numModels, texture);

	// Create a image object and then have it read it, create textures bind it, and then do a few other things
	loadImage("hockeytable.png", 0); // table
	loadImage("puck.jpg", 1); 
	loadImage("red.jpg", 2); // paddle1
	loadImage("yellow.jpg", 3); // paddle2
	loadImage("wood.jpg", 4); // wall around table
	loadImage("table.jpg", 5); // goal 1
	loadImage("table.jpg", 6); // goal 2
	loadImage("red.jpg", 7); // square1
	loadImage("yellow.jpg", 8); // square2
	loadImage("puck.jpg", 9); // square puck

	// Intialize bullet
	// Tells bullet how to check for collisions between bojects
	broadphase = new btDbvtBroadphase(); 
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new  btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-9.81,0));

	{
	// Create collision for the ground plane
	btCollisionShape *planeShape = new btStaticPlaneShape ( btVector3(0, 1, 0 ), -1 );
	btDefaultMotionState *groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,-1,0)));
	btScalar mass(0);
	btVector3 inertia(0,0,0);
	planeShape -> calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
                groundRigidBodyCI(0, groundMotionState, planeShape, inertia);;
    groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody, COL_PLANE,groundCollision );
	}

	// Create collisions for the top of the table itself
	{
	btCollisionShape *cube = new btBoxShape(btVector3(50, 0.4, 50));
	btDefaultMotionState *shapeMotionState = NULL;
	shapeMotionState = new btDefaultMotionState(btTransform(
												btQuaternion(0,0,0,1),
												btVector3(0,0,0)));
	btScalar mass(0);
	btVector3 inertia(0,0,0);
	cube->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( 0, shapeMotionState, cube, inertia ); 
	tableRb = new btRigidBody( shapeRigidBodyCI );
	tableRb->setRestitution( 0.0 );  
	dynamicsWorld->addRigidBody( tableRb, COL_TOP, tableCollision ); 	
	}

  	// This is for the wall around the table
   	{
	btCollisionShape *shape = new btBvhTriangleMeshShape(wallMesh, 
                                                                  true);
	btDefaultMotionState *shapeMotionState = NULL;
	shapeMotionState = new btDefaultMotionState(btTransform( 
		                                       	btQuaternion( 0, 0, 0, 1 ),
		                                       	btVector3( 0, 0, 0) ) );
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( 0, shapeMotionState, shape, btVector3( 0, 0, 0 ) ); 
	wallRb = new btRigidBody( shapeRigidBodyCI );
	dynamicsWorld->addRigidBody( wallRb,
		                       COL_TOP, 
		                       wallCollision );
	wallRb->setRestitution( 1.0);       
	}

	// This collision box is for the middle of the table so paddles do not get through
	{
	btCollisionShape *cube = new btBoxShape(btVector3(13, 15, 0.125));
	btDefaultMotionState *shapeMotionState = NULL;
	shapeMotionState = new btDefaultMotionState(btTransform(
												btQuaternion(0,0,0,1),
												btVector3(0,0,0)));
	btScalar mass(0);
	btVector3 inertia(0,0,0);
	cube ->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, cube, inertia ); 
	cubeRb = new btRigidBody( shapeRigidBodyCI );
	cubeRb->setRestitution( 1.0 );  
	dynamicsWorld->addRigidBody( cubeRb, COL_MID, midCollision );
	}	

	// This collision is for the goals for player 2 side which I think is the one on the right hand side
	{
	btCollisionShape *cube = new btBoxShape(btVector3(13, 3, 0.125));
	btDefaultMotionState *shapeMotionState = NULL;
	shapeMotionState = new btDefaultMotionState(btTransform(
		                btQuaternion(0,0,0,1),
		                btVector3(0,0,-25)));
	btScalar mass(0);
	btVector3 inertia(0,0,0);
	cube ->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, cube, inertia ); 
	cubeRb = new btRigidBody( shapeRigidBodyCI );
	cubeRb->setRestitution( 1.0 );  
	dynamicsWorld->addRigidBody( cubeRb, COL_MID, midCollision );
	}

	// This collision is for the goals for player 1 side which I think is the one on the left hand side
	{
	btCollisionShape *cube = new btBoxShape(btVector3(13, 3, 0.125));
	btDefaultMotionState *shapeMotionState = NULL;
	shapeMotionState = new btDefaultMotionState(btTransform(
		                btQuaternion(0,0,0,1),
		                btVector3(0,0,25)));
	btScalar mass(0);
	btVector3 inertia(0,0,0);
	cube ->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, cube, inertia ); 
	cubeRb = new btRigidBody( shapeRigidBodyCI );
	cubeRb->setRestitution( 1.0 );  
	dynamicsWorld->addRigidBody( cubeRb, COL_MID, midCollision );
	}

   	// This is for the first goal
   	{
	btCollisionShape *shape = new btBvhTriangleMeshShape(goal1Mesh, 
                                                                  true);
	btDefaultMotionState *shapeMotionState = NULL;
	shapeMotionState = new btDefaultMotionState( btTransform( 
		                                       btQuaternion( 0, 0, 0, 1 ),
		                                       btVector3( 0, 0, 0) ) );
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( 0, shapeMotionState, shape, btVector3( 0, 0, 0 ) ); 
	goal1Rb = new btRigidBody( shapeRigidBodyCI );
	dynamicsWorld->addRigidBody( goal1Rb,
		                       COL_GOAL, 
		                       goalCollision );       
	}

   	// This is for the second goal
   	{
	btCollisionShape *shape = new btBvhTriangleMeshShape(goal2Mesh, 
                                                                  true);
	btDefaultMotionState *shapeMotionState = NULL;
	shapeMotionState = new btDefaultMotionState( btTransform( 
		                                       btQuaternion( 0, 0, 0, 1 ),
		                                       btVector3( 0, 0, 0) ) );
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( 0, shapeMotionState, shape, btVector3( 0, 0, 0 ) ); 
	goal2Rb = new btRigidBody( shapeRigidBodyCI );
	dynamicsWorld->addRigidBody( goal2Rb,
		                       COL_GOAL, 
		                       goalCollision );       
	}

	{
	// Create collision for the puck object
  	btCollisionShape *shape = new btCylinderShape(btVector3(1.0,0.2,1.0));
  	btDefaultMotionState *shapeMotionState = NULL;
  	shapeMotionState = new btDefaultMotionState(btTransform(
  												btQuaternion(0,0,0,1),
  												btVector3(0,2,0)));
    btScalar mass(100);
    btVector3 inertia(0.0, 0.0, 0.0);
    shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, shape, inertia ); 
	puckRb = new btRigidBody( shapeRigidBodyCI );
	puckRb->setRestitution(0.8);
	puckRb->setFriction(0.01);  
	dynamicsWorld->addRigidBody( puckRb, COL_PUCK, puckCollision );
	}

	{
	// Create collision for the paddle1 object
  	btCollisionShape *shape = new btCylinderShape(btVector3(1.0,0.2,1.0));
  	btDefaultMotionState *shapeMotionState = NULL;
  	shapeMotionState = new btDefaultMotionState(btTransform(
  												btQuaternion(0,0,0,1),
  												btVector3(0,2,-20)));
    btScalar mass(200);
    btVector3 inertia(0,0,0);
    shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, shape, inertia ); 
	paddle1Rb = new btRigidBody( shapeRigidBodyCI );
	paddle1Rb->setRestitution( 0.0 );  
	dynamicsWorld->addRigidBody( paddle1Rb, COL_PADDLE, paddleCollision );
	}

	{
	// Create collision for the square1 object
  	btCollisionShape *shape = new btBoxShape(btVector3(2.0,0.2,2.0));
  	btDefaultMotionState *shapeMotionState = NULL;
  	shapeMotionState = new btDefaultMotionState(btTransform(
  												btQuaternion(0,0,0,1),
  												btVector3(0,-10,0)));
    btScalar mass(1);
    btVector3 inertia(0,0,0);
    shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, shape, inertia ); 
	square1Rb = new btRigidBody( shapeRigidBodyCI );
	square1Rb->setRestitution( 0.0 );  
	dynamicsWorld->addRigidBody( square1Rb, COL_PADDLE, paddleCollision );
	}

	{
	// Create collision for the paddle2 object
  	btCollisionShape *shape = new btCylinderShape(btVector3(1.0,0.2,1.0));
  	btDefaultMotionState *shapeMotionState = NULL;
  	shapeMotionState = new btDefaultMotionState(btTransform(
  												btQuaternion(0,0,0,1),
  												btVector3(0,2,20)));
    btScalar mass(200);
    btVector3 inertia(0,0,0);
    shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, shape, inertia ); 
	paddle2Rb = new btRigidBody( shapeRigidBodyCI );
	paddle2Rb->setRestitution( 0.0 );  
	dynamicsWorld->addRigidBody( paddle2Rb,  COL_PADDLE, paddleCollision);
	}

	{
	// Create collision for the square2 object
  	btCollisionShape *shape = new btBoxShape(btVector3(1.0,0.2,1.0));
  	btDefaultMotionState *shapeMotionState = NULL;
  	shapeMotionState = new btDefaultMotionState(btTransform(
  												btQuaternion(0,0,0,1),
  												btVector3(0,-10,0)));
    btScalar mass(1);
    btVector3 inertia(0,0,0);
    shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, shape, inertia ); 
	square2Rb = new btRigidBody( shapeRigidBodyCI );
	square2Rb->setRestitution( 0.0 );  
	dynamicsWorld->addRigidBody( square2Rb,  COL_PADDLE, paddleCollision);
	}

	{
	// Create collision for the square puck object
  	btCollisionShape *shape = new btBoxShape(btVector3(1.0,0.2,1.0));
  	btDefaultMotionState *shapeMotionState = NULL;
  	shapeMotionState = new btDefaultMotionState(btTransform(
  												btQuaternion(0,0,0,1),
  												btVector3(0,2,0)));
    btScalar mass(0.8);
    btVector3 inertia(0,0,0);
    shape->calculateLocalInertia(mass, inertia);
	btRigidBody::btRigidBodyConstructionInfo
	shapeRigidBodyCI( mass, shapeMotionState, shape, inertia );
	squarePuckRb = new btRigidBody( shapeRigidBodyCI );
	squarePuckRb->setRestitution(1.0);
	squarePuckRb->setFriction(0.001); 
	dynamicsWorld->addRigidBody( squarePuckRb,  COL_PUCK, puckCollision);
	}

	mPaddle1Rb = paddle1Rb;
	mPaddle2Rb = paddle2Rb;
	mPuckRb = puckRb;

	// Shader stuff starts here
	program = glCreateProgram();

	// Get file name
	vert_shade.setShaderFileName("./bin/shader.vs");
	frag_shade.setShaderFileName("./bin/shader.fs");

	// Read it in. if it fails, check other location
	if(!vert_shade.readIn())
	{
		vert_shade.setShaderFileName("shader.vs");
		vert_shade.readIn();
	}

	if(!frag_shade.readIn())
	{
		frag_shade.setShaderFileName("shader.fs");
		frag_shade.readIn();
	}

	// Assign it's position
	GLuint vertex_shader = vert_shade.shaderLoader( GL_VERTEX_SHADER );
	GLuint fragment_shader = frag_shade.shaderLoader( GL_FRAGMENT_SHADER) ;
	GLint shader_status; 

	// Attach the programs to the shaders
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    //check if everything linked ok
    glGetProgramiv(program, GL_LINK_STATUS, &shader_status);
    if(!shader_status)
    {
        std::cerr << "[F] THE SHADER PROGRAM FAILED TO LINK" << std::endl;
        return false;
    }

	// Then start getting the attribute variables from the vertex shader
    loc_position = glGetAttribLocation(program,
                    const_cast<const char*>("v_position"));
    if(loc_position == -1)
    {
        std::cerr << "[F] POSITION NOT FOUND" << std::endl;
        return false;
    }

    loc_uv = glGetAttribLocation(program,
                    const_cast<const char*>("v_texture"));
    if(loc_uv == -1)
    {
        std::cerr << "[F] UV_POSITION NOT FOUND" << std::endl;
        return false;
    } 
	
    loc_mvpmat = glGetUniformLocation(program, const_cast<const char*>("mvpMatrix"));
    if(loc_mvpmat == -1)
    {
        std::cerr << "[F] MVPMATRIX NOT FOUND" << std::endl;
        return false;
    }

    projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                   float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                   0.01f, //Distance to the near plane, normally a small value like this
                                   100.0f); //Distance to the far plane, 

    //enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //and its done
    return true;
}

void cleanUp()
{
    // Clean up, Clean up
    glDeleteProgram(program);
    glDeleteBuffers(numModels, vbo_geometry);

    // Rmemove Magick first
	delete []bigBlob;
	delete []texture;

	// Then go to the bullet stuff
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
    // Finally remove sound engine stuff
    engine->drop();
}

//returns the time delta
float getDT()
{
	float ret = 0;

	t2 = std::chrono::high_resolution_clock::now();
	ret = std::chrono::duration_cast< std::chrono::duration<float> >(t2-t1).count();
	t1 = std::chrono::high_resolution_clock::now();

	return ret;
}

// The menu
void menu(int id)
{
	switch(id)
	{
		// Starts the game if on title screen, other wise unpauses
		case 1:
			if(titleScreen == false)
			{
				pauseGame = false;
			}
			else if(titleScreen == true)
			{
				titleScreen = false;
			}
			break;

		// Pauses the game
		case 2:
			pauseGame = true;
			break;

		// Replays game so the only person that doesn't have to do is p1 and writes into topScores
		case 3:
			replayGame = 1;

			if(p1score >= maxScore)
			{
				game tmp;
				tmp.winner=player1Name;
				bool playerExist = false;

				for(int i = 0; i < topScores.size();i++)
				{
					if((player1Name == topScores[i].winner))
					{
						playerExist = true;
						topScores[i].matchesWon +=1;
					}
				}

				if(!playerExist)
				{
					tmp.matchesWon =1;
					topScores.push_back(tmp);
				}
			}
			else if(p2Score >= maxScore)
			{
				game tmp;
				tmp.winner=player2Name;
				bool playerExist = false;

				for(int i = 0; i < topScores.size();i++)
				{
					if(player2Name == topScores[i].winner)
					{
						playerExist = true;
						topScores[i].matchesWon +=1;
					}
				}

				if(!playerExist)
				{
					tmp.matchesWon =1;
					topScores.push_back(tmp);
				}
			}	
			break;

		// Show top scores if no keyboard
		case 4:
			if(titleScreen == 1 &&  showTopScore == 0)
				{
				showTopScore = 1;
				titleScreen = 0;
				}
			break;

		// Reset the board that includes the paddles puck but not the score
		case 5:
			{
				btDefaultMotionState *shapeMotionState = NULL;		
	  			shapeMotionState = new btDefaultMotionState(btTransform(
	  														btQuaternion(0,0,0,1),
	  														btVector3(0,1,-20)));
	  			mPaddle1Rb ->setMotionState(shapeMotionState);
	  		}

			{
				btDefaultMotionState *shapeMotionState = NULL;
	      		shapeMotionState = new btDefaultMotionState(btTransform( 
	                                           				btQuaternion( 0, 0, 0, 1 ),
	                                           				btVector3( 0, 1, 0 ) ) );
	      		mPuckRb->setMotionState(shapeMotionState);
	      		mPuckRb->setLinearVelocity(btVector3(0,-1,0));
	      	}

			{
				btDefaultMotionState *shapeMotionState = NULL;
	  			shapeMotionState = new btDefaultMotionState(btTransform(
															btQuaternion(0,0,0,1),
	  														btVector3(0,2,20)));
		
	  			mPaddle2Rb->setMotionState(shapeMotionState);
			}
			break;

		// When quitting, write to top scores, cleanup deallocate and exit completely
		case 6:
		    writeToTopScores();
			cleanUp();
			exit(0);
			break;
	}
}


Vertex *objLoader(string imageFile, int &numberOfVertices, btTriangleMesh *& sendBackMesh)
{
	/*
		aiMesh** mMeshes - contains a 2-dimensional array of object meshes
		aiTexture** mTextures - contains a 2-dimensional array of textures
		int mNumMeshes and mNumTextures - contain the number of the respective objects in the scene
	*/

	// Intialize Assimp
	Assimp :: Importer importer;

	// Triangles are my favorite
	const aiScene *myScene = importer.ReadFile(imageFile, aiProcess_Triangulate);

	// Create btVector3
	btVector3 triArray[3];

	// Allocate memory to sendBackMesh
	sendBackMesh = new btTriangleMesh();

	if(!myScene)
	{
		// if default location doesn't work, try adding bin in front
		string otherLoc = "./bin/";
		otherLoc.append(imageFile);

		myScene = importer.ReadFile(otherLoc, aiProcess_Triangulate);

		if(!myScene) // at this point both locations didn't work
		{
			cout << importer.GetErrorString() << endl;
			exit(1);
		}
	}

	// Check to see if there are any meshes in the scene; if there is, grab the first one
	if(myScene->mNumMeshes > 0)
	{
		aiMesh *mesh = myScene->mMeshes[0];// This grabs the mesh from the first scene
	
		// Check the number of vertices, each face is a triangle which has 3 vertices
		numberOfVertices = mesh->mNumFaces * 3;

		// Create a array
		Vertex *outVertex = new Vertex[numberOfVertices];

		int out= 0;
		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			// Get face reference in order to extract it's value
			const aiFace& face = mesh->mFaces[i];			
			for(int j = 0; j < 3; j++)
			{			
				if(mesh->HasPositions())
				{
					// First get the vertices from each of the faces
					aiVector3D position = mesh->mVertices[face.mIndices[j]];

					outVertex[out].position[0] = position.x;
					outVertex[out].position[1] = position.y;
					outVertex[out].position[2] = position.z;
			        triArray[j] = btVector3(position.x, position.y, position.z); 

				}

				if(mesh->HasNormals())
				{
					// Then get the normals from each of the faces
					aiVector3D normal = mesh->mNormals[face.mIndices[j]];
		
					outVertex[out].normals[0] = normal.x;
					outVertex[out].normals[0] = normal.y;
					outVertex[out].normals[0] = normal.z;
				}

				if(mesh->HasTextureCoords(0))
				{
					aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[j]];
					outVertex[out].uv[0] = uv.x;
					outVertex[out].uv[1] = uv.y;
				}

				// One day I will use the textures, but not today.
				out++;
			}
			sendBackMesh->addTriangle(triArray[0], triArray[1], triArray[2]); 
		}

		return outVertex;
	}	
}


void processSpecialKeys(int key, int xx, int yy)
{
	keySpecialStates[key] = true;
}

void specialKeyOps()
{
	if(keySpecialStates[GLUT_KEY_UP])
	{
		if(keyStates['/'])
		{
			addVelocity(1, -16.0, 0.0, 0.0);
		}
		else
		{
			addVelocity(1, -8.0, 0.0, 0.0);
		}
	}

	if(keySpecialStates[GLUT_KEY_LEFT])
	{
		if(keyStates['/'])
		{
			addVelocity(1, 0.0, 0.0, 16.0);
		}
		else
		{
			addVelocity(1, 0.0, 0.0, 8.0);
		}
	}

	if(keySpecialStates[GLUT_KEY_RIGHT])
	{
		if(keyStates['/'])
		{
			addVelocity(1, 0.0, 0.0, -16.0);
		}
		else
		{
			addVelocity(1, 0.0, 0.0, -8.0);
		}
	}

	if(keySpecialStates[GLUT_KEY_DOWN])
	{
		if(keyStates['/'])
		{
			addVelocity(1, 16.0, 0.0, 0.0);
		}
		else
		{
			addVelocity(1, 8.0, 0.0, 0.0);
		}
	}

	if(keySpecialStates[GLUT_KEY_HOME])
	{
		titleScreen = 1;
		showTopScore = 0;
	}
}

void mouseClicked(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mStartX = x;
			mStartY = y;
			mousePressed = true;
		}		
		else
		{
			mousePressed = false;
		}
	}
}

void mouseMotion(int x, int y)
{
	if (mousePressed)
	{
		paddle1Rb->activate();

		float xDif = (float)(x - mStartX) / 8;
		float yDif = (float)(y - mStartY) / 8;

		float xVel = paddle1Rb->getLinearVelocity().x() + yDif;
		float zVel = paddle1Rb->getLinearVelocity().z() - xDif;	
	
		if(xVel > 16.0)
		{
			xVel = 16.0;
		}
		else if(xVel < -16.0)
		{
			xVel = -16.0;
		}

		if(zVel > 16.0)
		{
			zVel = 16.0;
		}
		else if(zVel < -16.0)
		{
			zVel = -16.0;
		}



		
		paddle1Rb->setLinearVelocity(btVector3(	xVel,
												0,
												zVel));


mStartX = x;
mStartY = y;

	}
}

void movePaddle(int x, int y)
{
	//cout << "(" << x << "," << y << ")" << endl;
}

// Gets the position of the rigidbody and updates the model based on it
void updateRb(btRigidBody* body, int position)
{
    // This is for bullet
    btTransform trans;
    btScalar m[16];

    // Get the position of it in the world
	body->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(m);

    model[position] = glm::make_mat4(m);

    // Transform the model
	if(modelToFocus == position)
	{
		focusPos[0] = model[position][3][0];
		focusPos[1] = model[position][3][1];
		focusPos[2] = model[position][3][2];
	}	
}

// Read in png file into bigblob which is a data storage
void loadImage(string file, int t)
{
	Magick::Image image;

	// Exception handing if file is bad or does not exist
	try
	{
		image.read(file);
		image.write(&bigBlob[t], "RGBA");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[t]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.columns(), image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bigBlob[t].data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	// If Magick input is bad then quit nicely
	catch(Magick::ErrorBlob &error)
	{
		string otherLoc = "./bin/";
		otherLoc.append(file);

		image.read(otherLoc);
		image.write(&bigBlob[t], "RGBA");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[t]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.columns(), image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bigBlob[t].data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
}


// Read in top Scores from the file
bool readInTopScores()
{
	// File stream variable, open a variable called topSccores
	ifstream fin("topScores.txt");

	// If the file exist then read through it for the first 10 games
	if(fin.good())
	{
		while(!fin.eof())
		{
			game tmp;
			char junk;

			//fin >> win >> won;
			fin >> tmp.winner >>  tmp.matchesWon ;

			if(fin.peek())
			{

			}

			// Check to see if the string is null
			if(!tmp.winner.empty())
			{
				topScores.push_back(tmp);
			}
		}
	}
	// Close the filestream
	fin.close();
}


// Write the max scores to file
void writeToTopScores()
{
	// Open a file out stream with the name topScores
	ofstream fout("topScores.txt");

	// Check to see if opened successfully
	if(fout.good())

	{
		// Loop through write the data
		for(int i = 0; i < topScores.size(); i++)
		{
			fout << topScores[i].winner << " " << topScores[i].matchesWon << " " << endl;
		}	
	}

	// Otherwise quit
	else
	{
		cout << "Cannot open .txt file for some reason" << endl;
	}

	// Close fout stream
	fout.close();
}

void addVelocity(int paddleNum, float x, float y, float z)
{
	btRigidBody* paddle;

	if(paddleNum == 1)
	{
		paddle = mPaddle1Rb;
		//paddle = mPuckRb;
	}
	else
	{
		paddle = mPaddle2Rb;
	}

	paddle->activate();

	paddle->setLinearVelocity(btVector3(x,
										y,
										z));
}

// Swap out the paddles
void swapPaddles()
{
	vbo_geoTemp = vbo_geometry[2];
	vbo_geometry[2] =  vbo_geometry[7];
	vbo_geometry[7] =  vbo_geoTemp;

	vbo_geoTemp = vbo_geometry[3];
	vbo_geometry[3] =  vbo_geometry[8];
	vbo_geometry[8] =  vbo_geoTemp;
}

// Swap out the vbo 
void swapPuck()
{
	vbo_geoTemp = vbo_geometry[1];
	vbo_geometry[1] =  vbo_geometry[9];
	vbo_geometry[9] =  vbo_geoTemp;
}

// Calculates AI
void calcAI()
{
	bool puckOnOwnSide;
	bool puckMovingAway;

	int verticalPosDif;
	int horizontalPosDif;

	int puckAbove;
	int puckRight;

	int puckZSpeed;

	float distToPuck;
	
	puckZSpeed = mPuckRb->getLinearVelocity().z();
	
	// calculate which side puck is on
	if(mPuckRb->getCenterOfMassPosition().z() > 0.0)
	{
		puckOnOwnSide = true;
	}
	else
	{
		puckOnOwnSide = false;
	}

	// calculate if puck is moving away or not
	if(puckZSpeed < 0.0)
	{
		puckMovingAway = true;
	}
	else
	{
		puckMovingAway = false;
	}

	// calculate the difference in the vertical position of the puck and paddle
	verticalPosDif = mPaddle2Rb->getCenterOfMassPosition().x() - mPuckRb->getCenterOfMassPosition().x();

	// calculate the difference in the horizontal position of the puck and paddle
	horizontalPosDif = mPaddle2Rb->getCenterOfMassPosition().z() - mPuckRb->getCenterOfMassPosition().z();

	// calculate whether the puck is above, below, or aligned with the paddle
	if(verticalPosDif > 0.3)
	{
		puckAbove = 1;
	}
	else if(verticalPosDif < -0.3)
	{
		puckAbove = -1;
	}
	else
	{
		puckAbove = 0;
	}

	// calculate whether the puck is to the right, left, or aligned with the paddle
	if(horizontalPosDif > 0.3)
	{
		puckRight = 1;
	}
	else if(horizontalPosDif < -0.3)
	{
		puckRight = -1;
	}
	else
	{
		puckRight = 0;
	}

	// calculate distance from the puck
	distToPuck = hypot( ( mPuckRb->getCenterOfMassPosition().x() - mPaddle2Rb->getCenterOfMassPosition().x()), 
						( mPuckRb->getCenterOfMassPosition().z() - mPaddle2Rb->getCenterOfMassPosition().z()));

	// perform movements below

	if(puckAbove == 1)
	{
		addVelocity(2 , -6.0, 0.0, 0.0);
	}
	else if(puckAbove == -1)
	{
		addVelocity(2 , 6.0, 0.0, 0.0);
	}
	else
	{
		addVelocity(2, 0.0, 0.0, 0.0);
	}

	if(puckOnOwnSide)
	{
		if(puckRight == 1)
		{
			if(distToPuck < 2)
			{
				if(!puckMovingAway)
				{
					addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, -16.0);
				}
			}
			else if(distToPuck < 3)
			{
				addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, -14.0);
			}
			else
			{
				addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, -2.0);
			}
		}
		else
		{
			addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, 8.0);
		}
	}	
	else
	{
		if(puckMovingAway)
		{
			if(distToPuck > 20)
			{
				addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, -5.0);
			}
			else if(distToPuck > 10)
			{
				addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, -2.0);
			}
		    else
			{
				addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, 0.0);
			}
		}
		else
		{
			if(distToPuck > 20)
			{
				addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, 0.0);
			}
			else if(distToPuck > 10)
			{
				addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, 3.0);
			}
		    else
			{
				addVelocity(2 , mPaddle2Rb->getLinearVelocity().x(), 0.0, 7.0);
			}
		}	
	}
}

// This is menu option to change the paddle
void changePaddleSub(int selection)
{
	switch(selection)
	{
		// If first option, change square to circle or vice versa
		case 1:
			if(squarePaddles = !squarePaddles)
			{
				swapPaddles();
			}

			else if(squarePaddles == squarePaddles)
			{
				swapPaddles();
			}
			break;

		// Otherwise do the same for the puck
		case 2:
			if(squarePuck = !squarePuck)
			{
				swapPuck();
			}

			else if(squarePuck == squarePuck)
			{
				swapPuck();
			}	
			break;
	}
}




