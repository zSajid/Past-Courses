/*
	@Authors: Zeeshan Sajid, Vance Piscitelli
	This program uses a class called shader.h that is the header file for the implementation called shader.cpp within the src folder in PA7. This is a small class that reads in the information from the txt file called shader.fs and shader.vs, in which it compiles the information within those files and then returns a integer of its location

	This program loads model using a function called objLoader, in which it also adds textures. For the model loader, we used assimp model loader to save the information from the file using a struct called vertex and essentially save all the positions that we needed. It needs to have values for each of the different type of coordinates. 
	In terms of texture, we utilized Magick++, which were installed on the ECC computers, and essentially we read in the uv textures from the assimp model and just map that image to that texture on those coordinates.

Functionalities:
	Right-click: 
			Brings up our menu:
						- Start rotation: As it sounds, it starts the rotation, if the rotation is already going, it does absolutely nothing
						- Stop rotation: Turns off rotation by turning DT off completely and not having it effect the planets
						- Toggle: This turns on the scaling for it, so from the start all the planets are based on the scale, so pluto will be super far away and etc, while untoggled they all look relative in distance.
						- Quit: Quits the game

	Keyboard:
			0 to 9 on the keyboard numberpad or numberline: 
					Essentially, it changes the camera to focus on the planet with good distancing so nothing gets clipped
			
			*: The asterisk is used to look at the moons, however, if you start from the sun, and use the asterisk, essentially you can go through every single thing in our solar system, from the planets to the moon, etc.

			+: This changes it to global view
	Esc key: Quits the program
*/

// The header files that are utilized for this program
#define GLM_FORCE_RADIANS 
#include <GL/glew.h> // glew must be included before the main gl libs
#include <GL/glut.h> // doing otherwise causes compiler shouting
#include <iostream>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> //Makes passing matrices to shaders easier
#include "shader.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <Magick++.h>

// Struct to get information from the model's .obj file
// Contains the position, the normal and uv, the position has xyz, so does the normal, however uv only has two for x and y
struct Vertex
{
	GLfloat position[3];
	GLfloat normals[3];
	GLfloat uv[2];
};


// The structure used to keep our data for the solar system, class was not used since private and public was not really necessary
struct solarObjects
{
	char identifier; // This will be to determine if it's planet or moon, not sure if it's necessary
	string myObjectName; // The name of the object, not sure if this is necessary either
	string myTextureName; // The name of the texture for the object
	int myPositionInArray = 0; // Position within the array 
	int myDaddy = 0; // THis says who the object orbits around, so for example, the planets dad is the sun
	float mySize = 0.0; // How big it is
	float myRot = 0.0; // Rotational velocity
	float myOrb = 0.0; // Orbital velocity
	float myDistance = 0.0;

	// not read in from file
	float oAngle = 0.0; // orbital angle
	float rAngle = 0.0; // rotational angle

	glm :: mat4 myModel; // This is the model matrix for how I look
	glm :: vec3 myVectorPosition; // This is my current position

};

// This is used for Magick++, it's essentialyl textures for each of the different textures that we use, and the big blob is where we store the data
GLuint *texture = NULL; // For texture, need to dynamically allocate
Magick::Blob *bigBlob = NULL;;

// This is the instantiation, a pointer in which we allocate 26 indices
solarObjects * sObjects;

// This is the thing that holds the models information like the vertex and stuff from loadObj
Vertex *obj;
Vertex *jupiterRings;
Vertex *saturnRings;
Vertex *uranusRings;
Vertex *neptuneRings;

// Global variables
int planetToFocus = 0; // What planet the camera looks at
int scaleValue = 0;	// How much things will be scaled
bool globalView = true; // This is to see the planet from top down to see how vast it is
bool toScale = true; // changes the scale of the solar system from being to accurate but not easily viewed
float height = 0.0; // height of the camera that can be changed with keyboard

// Number of objects and vertices for the different rings/ sphere objects
int numObjects = 25; 
int numVert = 0;
int jupiterVert = 0; // for the rings
int saturnVert = 0;
int uranusVert = 0;
int neptuneVert = 0;

// Spin and stop globals, essentially for stop rotation and start
int stopSpin = 0;

// Amazing globals, life savers
int w = 1080, h = 720;// Window size
GLuint program;// The GLSL program handle
GLuint vbo_geometry[6];// VBO handle for our geometry

//uniform locations
GLint loc_mvpmat;// Location of the modelviewprojection matrix in the shader
GLint loc_model;

//attribute locations
GLint loc_position;
GLint loc_uv;
GLint loc_normal;

//transform matrices
glm::mat4 model;//obj->world each object should have its own model matrix
glm::mat4 view;//world->eye
glm::mat4 projection;//eye->clip
glm::mat4 mvp;//premultiplied modelviewprojection

//--GLUT Callbacks
void render();
void update();
void reshape(int n_w, int n_h);
void keyboard(unsigned char key, int x_pos, int y_pos);
void myMouse(int button, int state, int x, int y);
void processSpecialKeys(int key, int xx, int yy);

//--Resource management
bool initialize();
void cleanUp();

//--Random time things
float getDT();
std::chrono::time_point<std::chrono::high_resolution_clock> t1,t2;

//--Menu options/ Controls
void menu(int id);

//--Loaders
Vertex *objLoader(const char *imageFile, int &numVertices); // This is the loader
bool loadSolar();
void orbitPath(Vertex circle[360]); // This sets the vertex for the circle to make a full circle using cos and sin

//--Main
int main(int argc, char **argv)
{
	// Initialize Magick++ ?
	Magick::InitializeMagick(*argv);

	// Loads all the planet/moon information
	if(loadSolar())
	{
		cout << "Successfully loaded planets!" << endl;
	}
	else
	{
		cout << "Failed to load planets and other objects" << endl;
	}

    // Initialize glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    // Name and create the Window
    glutCreateWindow("PA7 - Solar System by Vance Piscitelli & Zeeshan Sajid");

	// Create the menu and attach the components
	glutCreateMenu(menu);
	glutAddMenuEntry("Start Rotation", 1);
	glutAddMenuEntry("Stop Rotation", 2);
	glutAddMenuEntry("Toggle Scale" , 3);
	glutAddMenuEntry("Quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    // Now that the window is created the GL context is fully set up
    // Because of that we can now initialize GLEW to prepare work with shaders
    GLenum status = glewInit();
    if(status != GLEW_OK)
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
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(myMouse);

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
    // Render the scene

    // clear the screen
    glClearColor(0.05, 0.05, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate textures
	glActiveTexture(GL_TEXTURE0);

	// If the global view is turned on using +, and then choose between scales, essentially give a top down view
	if(globalView)
	{
		// A couple of planets are visibile in the scaled top down view, it shows vastness of the solarsystem
		if(toScale)
		{
			view = glm::lookAt( glm::vec3( 	sObjects[planetToFocus].myVectorPosition.x -1, // eye location
											sObjects[planetToFocus].myVectorPosition.y + 8000,
											0),
								sObjects[planetToFocus].myVectorPosition, // focus point
		                    	glm::vec3(0.0, 1.0, 0.0)); // Up vector

		}

		// Otherwise, show the solar system from a much better view where all the planets are visible
		else
		{
			view = glm::lookAt( glm::vec3( 	sObjects[planetToFocus].myVectorPosition.x -1, // eye location
											sObjects[planetToFocus].myVectorPosition.y + 205,
											0),
								sObjects[planetToFocus].myVectorPosition, // focus point
		                    	glm::vec3(0.0, 1.0, 0.0)); // Up vector
		}	
	}
	
	// Otherwise, when the user is not in global view, let the user focus on the different planets 
	else
	{
		if(toScale)
		{
			if(planetToFocus == 0)
			{
				// This will focus on the planet to look at while scaled
				view = glm::lookAt( glm::vec3( 	scaleValue *sObjects[planetToFocus].myVectorPosition.x + (sObjects[planetToFocus].mySize +70), // x location
												(height), // need to adjust height for the different scale y location
												scaleValue *sObjects[planetToFocus].myVectorPosition.z + (sObjects[planetToFocus].mySize +80)), // Z location
									sObjects[planetToFocus].myVectorPosition, // focus point.
					           		glm::vec3(0.0, 1.0, 0.0)); // Up vector
			}
			else if(planetToFocus > 9)
			{
				// This will focus on the planet to look at while scaled
				view = glm::lookAt( glm::vec3( 	scaleValue *sObjects[planetToFocus].myVectorPosition.x + (sObjects[planetToFocus].mySize + 1), // x location
												(height/2), // need to adjust height for the different scale y location
												scaleValue *sObjects[planetToFocus].myVectorPosition.z + (sObjects[planetToFocus].mySize + 1)), // Z location
									sObjects[planetToFocus].myVectorPosition, // focus point.
						   			glm::vec3(0.0, 1.0, 0.0)); // Up vector
			}
			else
			{
				if(planetToFocus== 5) // This is for jupiter
				{
					view = glm::lookAt( glm::vec3( 	scaleValue *sObjects[planetToFocus].myVectorPosition.x + (sObjects[planetToFocus].mySize +14), // eye location
													(height), // need to adjust height for the different scale
													scaleValue *sObjects[planetToFocus].myVectorPosition.z + (sObjects[planetToFocus].mySize +15)),
										sObjects[planetToFocus].myVectorPosition, // focus point.
					           			glm::vec3(0.0, 1.0, 0.0)); // Up vector
				}
				else if( planetToFocus ==6)
				{
					view = glm::lookAt( glm::vec3( 	scaleValue *sObjects[planetToFocus].myVectorPosition.x + (sObjects[planetToFocus].mySize +14), // eye location
													(height), // need to adjust height for the different scale
													scaleValue *sObjects[planetToFocus].myVectorPosition.z + (sObjects[planetToFocus].mySize +15)),
										sObjects[planetToFocus].myVectorPosition, // focus point.
					           			glm::vec3(0.0, 1.0, 0.0)); // Up vector
				}
				else
				{
					// This will focus on the planet to look at while scaled
					view = glm::lookAt( glm::vec3( 	scaleValue *sObjects[planetToFocus].myVectorPosition.x + (sObjects[planetToFocus].mySize +7), // eye location
													(height), // need to adjust height for the different scale
													scaleValue *sObjects[planetToFocus].myVectorPosition.z + (sObjects[planetToFocus].mySize +8)),
										sObjects[planetToFocus].myVectorPosition, // focus point.
					           			glm::vec3(0.0, 1.0, 0.0)); // Up vector
				}	
			}

		}	
		else // If it's not to scale and not to global, then go to this one
		{
			if(planetToFocus == 0)
			{
				// This will focus on the planet to look at while not scaled properly
				view = glm::lookAt( glm::vec3( 	scaleValue *sObjects[planetToFocus].myVectorPosition.x + 3, // eye location
												height,
												scaleValue *sObjects[planetToFocus].myVectorPosition.z + 4),
				    				sObjects[planetToFocus].myVectorPosition, // focus point.
				               		glm::vec3(0.0, 1.0, 0.0)); // Up vector
			}
			else
			{
				// This will focus on the planet to look at while not scaled properly
				view = glm::lookAt( glm::vec3( scaleValue *sObjects[planetToFocus].myVectorPosition.x + 3, // eye location
												height,
												scaleValue *sObjects[planetToFocus].myVectorPosition.z + 4	),
				    				sObjects[planetToFocus].myVectorPosition, // focus point.
				               		glm::vec3(0.0, 1.0, 0.0)); // Up vector
			}		
		}
	}

	
	// Go through every single one of the solarObjects, including the skybox and render them onto the screen in one form or another
	for(int i = 0; i < numObjects; i++)
	{
		//premultiply the matrix for this example
		mvp = projection * view * sObjects[i].myModel;

		//enable the shader program
		glUseProgram(program);

		//upload the matrix to the shader
		glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));

		//set up the Vertex Buffer Object so it can be drawn
		glEnableVertexAttribArray(loc_position);
		glEnableVertexAttribArray(loc_uv);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[0]);
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

		if(sObjects[i].identifier == 'P' && i != 24)
		{
			// After binding the circle to the vertex for each and every x and y position in the 360 indices, then bind it, and creat a model matrix
			glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[1]);
		
			glm::mat4 orbitPosition;

			// Scale the model matrix, and since we aren't rotating or translating do not need to do the multiplication thingy
			if(toScale)
			{
				// Hardest part to figure out, essentially, the x and z positions are the part where we want the scale to grow
				orbitPosition = glm :: scale(glm :: mat4(1.0f), glm :: vec3(sObjects[i].myDistance   ,0 ,sObjects[i].myDistance ));
			}
			// Otherwise, use constant time
			else
			{
				orbitPosition = glm :: scale(glm :: mat4(1.0f), glm::vec3(	(12 * sObjects[i].myPositionInArray ),
																			0,
																			(12 * sObjects[i].myPositionInArray )));
			}

			//premultiply the matrix for this example
			mvp = projection * view * orbitPosition;

			//enable the shader program
			glUseProgram(program);

			//upload the matrix to the shader
			glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));

			//set up the Vertex Buffer Object so it can be drawn
			glEnableVertexAttribArray(loc_position);
			glEnableVertexAttribArray(loc_uv);

			//set pointers into the vbo for each of the attributes(position and color)

			//set pointers into the vbo for each of the attributes(position and color)
		   	glVertexAttribPointer(loc_position,//location of attribute
					              3,//number of elements
					              GL_FLOAT,//type
					              GL_FALSE,//normalized?
					              sizeof(Vertex),//stride
					              0);//offset

			// Map the texture to the vertex
			glBindTexture(GL_TEXTURE_2D, texture[6]);

		   	glVertexAttribPointer(loc_uv,
					              2,
					              GL_FLOAT,
					              GL_FALSE,
					              sizeof(Vertex),
					              (void*)offsetof(Vertex,uv));
		  	glDrawArrays(GL_LINE_LOOP, 0, 360);//mode, starting index, count */

			// This portions is for the rings for each of the planets that needed one
			// Essentially bind the buffer, create a model, translate, rotate, scale it, and then display it depending on whether or not it scaled, same as the planets but with different models
			if(i == 5)
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[2]);

				glm::mat4 ringModel;

				if(toScale)
				{
					ringModel = glm::translate(glm::mat4(1.0f), glm::vec3(sObjects[i].myVectorPosition[0],0,sObjects[i].myVectorPosition[2]));
					ringModel = glm::rotate(ringModel, sObjects[i].rAngle / 2, glm::vec3(0,1,0));
					ringModel = glm :: scale(ringModel, glm::vec3(12,0,12));
				}
				else
				{
					ringModel = glm::translate(glm::mat4(1.0f), glm::vec3(	12 * sObjects[i].myPositionInArray * sin(sObjects[i].oAngle), 
																			0, 
																			12 * sObjects[i].myPositionInArray * cos(sObjects[i].oAngle)));
					ringModel = glm::rotate(ringModel, sObjects[i].rAngle / 2, glm::vec3(0,1,0));
				}

				//premultiply the matrix for this example
				mvp = projection * view * ringModel;

				//enable the shader program
				glUseProgram(program);

				//upload the matrix to the shader
				glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));

				//set up the Vertex Buffer Object so it can be drawn
				glEnableVertexAttribArray(loc_position);
				glEnableVertexAttribArray(loc_uv);

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
			  	glDrawArrays(GL_TRIANGLES, 0, jupiterVert);//mode, starting index, count */
			}
			else if(i == 6)
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[3]);

				glm::mat4 ringModel;

				if(toScale)
				{
					ringModel = glm::translate(glm::mat4(1.0f), glm::vec3(sObjects[i].myVectorPosition[0],0,sObjects[i].myVectorPosition[2]));
					ringModel = glm::rotate(ringModel, sObjects[i].rAngle / 2, glm::vec3(0,1,0));
					ringModel = glm::scale(ringModel, glm::vec3(10,0,10));
				}
				else
				{
					ringModel = glm::translate(glm::mat4(1.0f), glm::vec3(	12 * sObjects[i].myPositionInArray * sin(sObjects[i].oAngle), 
																			0, 
																			12 * sObjects[i].myPositionInArray * cos(sObjects[i].oAngle)));
					ringModel = glm::rotate(ringModel, sObjects[i].rAngle / 2, glm::vec3(0,1,0));
				}

				//premultiply the matrix for this example
				mvp = projection * view * ringModel;

				//enable the shader program
				glUseProgram(program);

				//upload the matrix to the shader
				glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));

				//set up the Vertex Buffer Object so it can be drawn
				glEnableVertexAttribArray(loc_position);
				glEnableVertexAttribArray(loc_uv);

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
			  	glDrawArrays(GL_TRIANGLES, 0, saturnVert);//mode, starting index, count */
			}
			else if(i == 7)
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[4]);

				glm::mat4 ringModel;

				if(toScale)
				{
					ringModel = glm::translate(glm::mat4(1.0f), glm::vec3(sObjects[i].myVectorPosition[0],0,sObjects[i].myVectorPosition[2]));
					ringModel = glm::rotate(ringModel, sObjects[i].rAngle / 2, glm::vec3(0,0,1));
					ringModel = glm::scale(ringModel, glm::vec3(5,5,5));
				}
				else
				{
					ringModel = glm::translate(glm::mat4(1.0f), glm::vec3(	12 * sObjects[i].myPositionInArray * sin(sObjects[i].oAngle), 
																			0, 
																			12 * sObjects[i].myPositionInArray * cos(sObjects[i].oAngle)));
					ringModel = glm::rotate(ringModel, sObjects[i].rAngle / 2, glm::vec3(0,0,1));
				}

				//premultiply the matrix for this example
				mvp = projection * view * ringModel;

				//enable the shader program
				glUseProgram(program);

				//upload the matrix to the shader
				glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));

				//set up the Vertex Buffer Object so it can be drawn
				glEnableVertexAttribArray(loc_position);
				glEnableVertexAttribArray(loc_uv);

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
			  	glDrawArrays(GL_TRIANGLES, 0, uranusVert);//mode, starting index, count */
			}
			else if(i == 8)
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[5]);

				glm::mat4 ringModel;

				if(toScale)
				{
					ringModel = glm::translate(glm::mat4(1.0f), glm::vec3(sObjects[i].myVectorPosition[0],0,sObjects[i].myVectorPosition[2]));
					ringModel = glm::rotate(ringModel, sObjects[i].rAngle / 2, glm::vec3(0,1,0));
					ringModel = glm :: scale(ringModel, glm::vec3(4,0,4));
				}
				else
				{
					ringModel = glm::translate(glm::mat4(1.0f), glm::vec3(	12 * sObjects[i].myPositionInArray * sin(sObjects[i].oAngle), 
																			0, 
																			12 * sObjects[i].myPositionInArray * cos(sObjects[i].oAngle)));
					ringModel = glm::rotate(ringModel, sObjects[i].rAngle / 2, glm::vec3(0,1,0));
				}

				//premultiply the matrix for this example
				mvp = projection * view * ringModel;

				//enable the shader program
				glUseProgram(program);

				//upload the matrix to the shader
				glUniformMatrix4fv(loc_mvpmat, 1, GL_FALSE, glm::value_ptr(mvp));

				//set up the Vertex Buffer Object so it can be drawn
				glEnableVertexAttribArray(loc_position);
				glEnableVertexAttribArray(loc_uv);

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
			  	glDrawArrays(GL_TRIANGLES, 0, neptuneVert);//mode, starting index, count */
			}
			
		}

	}

    //clean up
    glDisableVertexAttribArray(loc_position);

    glDisableVertexAttribArray(loc_uv);  
                     
    //swap the buffers
    glutSwapBuffers();
	
}

void update()
{
    //total time
    float dt = getDT();// if you have anything moving, use dt.


	// If stop rotation, then turn dt off, so it doesn't get added each time
	if(stopSpin == 1)
	{
		dt = 0;
	}
	
	// Go through the list of objects in the solary system not including the sykbox
	for(int i = 0; i < numObjects-1; i++)
	{
		float oSpeed = (sObjects[3].myOrb/sObjects[i].myOrb) * 16;
		float rSpeed = (sObjects[3].myOrb/sObjects[i].myRot) * 16;

		// None of these if statements shouldn't really come true
		if(oSpeed != 0)
		{
			sObjects[i].oAngle += dt * M_PI / oSpeed;
		}
		else
		{
			cout << "Orbital. Div by 0 error" << endl;
		}

		if(rSpeed != 0)
		{
			sObjects[i].rAngle += dt * M_PI / rSpeed;
		}
		else
		{
			cout << "Rotational. Div by 0 error" << endl;
		}

		// calc what to orbit around
		GLfloat position[3];
		position[0] = sObjects[sObjects[i].myDaddy].myVectorPosition[0];
		position[1] = sObjects[sObjects[i].myDaddy].myVectorPosition[1];
		position[2] = sObjects[sObjects[i].myDaddy].myVectorPosition[2];

		// Base the position on the scale being turned on
		if(toScale)
		{
			sObjects[i].myVectorPosition[0] = position[0] + (sObjects[i].myDistance * sin(sObjects[i].oAngle));
			sObjects[i].myVectorPosition[1] = position[1] + (0.0); // could change to have tilt
			sObjects[i].myVectorPosition[2] = position[2] + (sObjects[i].myDistance * cos(sObjects[i].oAngle));
		}
		else
		{
			if(sObjects[i].identifier == 'M') // if its a moon
			{
				sObjects[i].myVectorPosition[0] = position[0] + (6 * sin(sObjects[i].oAngle));
				sObjects[i].myVectorPosition[1] = position[1] + (0.0); // could change to have tilt
				sObjects[i].myVectorPosition[2] = position[2] + (6 * cos(sObjects[i].oAngle));
			}
			else // if its not a moon
			{
				sObjects[i].myVectorPosition[0] =  (12 * sObjects[i].myPositionInArray * sin(sObjects[i].oAngle));
				sObjects[i].myVectorPosition[1] =  (0.0); // could change to have tilt
				sObjects[i].myVectorPosition[2] =  (12 * sObjects[i].myPositionInArray * cos(sObjects[i].oAngle));
			}
		}
	
		// Translate the model, then rotate it, and then scale it based on whether it's the scaled view or not
		sObjects[i].myModel = glm::translate( glm::mat4(1.0f), sObjects[i].myVectorPosition);

		sObjects[i].myModel = glm::rotate( sObjects[i].myModel, sObjects[i].rAngle, glm::vec3(0,1,0));

		if(toScale)
		{
			if(planetToFocus == 9) // a temp resize for pluto since it is small but only while being looked at
			{
				GLfloat scale = sObjects[i].mySize * 10;
				sObjects[i].myModel = glm::scale(sObjects[i].myModel, glm::vec3(scale, scale, scale));
			}
			else
			{
				// scale the object accordingly
				GLfloat scale = sObjects[i].mySize;
				sObjects[i].myModel = glm::scale(sObjects[i].myModel, glm::vec3(scale, scale, scale));
			}
		}
		else
		{
			
			if(sObjects[i].myPositionInArray == 0) // if its the sun
			{
				sObjects[i].myModel = glm::scale(sObjects[i].myModel, glm::vec3(5.0, 5.0, 5.0));
			}
			else if(sObjects[i].identifier == 'M') // if its a planet
			{	
				sObjects[i].myModel = glm::scale(sObjects[i].myModel, glm::vec3(0.5, 0.5, 0.5));
			}
		}
	}
	
	// for the skybox
	float skyScale = sObjects[9].myDistance + 3000;

	sObjects[24].myVectorPosition = glm ::vec3(0,0,-0);
	sObjects[24].myModel = glm::translate( glm::mat4(1.0f), sObjects[24].myVectorPosition);
	sObjects[24].myModel = glm::scale(sObjects[24].myModel, glm :: vec3( skyScale, skyScale, skyScale));

	// Update the state of the scene
	glutPostRedisplay();//call the display callback
}

void reshape(int n_w, int n_h)
{
    w = n_w;
    h = n_h;
    //Change the viewport to be correct
    glViewport( 0, 0, w, h);
    //Update the projection matrix as well
    //See the init function for an explaination
    projection = glm::perspective(45.0f, float(w)/float(h), 0.01f, 20000.0f);

}

void keyboard(unsigned char key, int x_pos, int y_pos)
{	
	// A whole lot of if checks
	// Checks if sun, then sets the default height for both scaled and unscaled
	if(planetToFocus == 0 && toScale)
	{
		height = 7;
	}
	else if(planetToFocus == 0 && !toScale)
	{
		height = 5;
	}

	// Otherwise, it is a planet so set the default height for the camera to position itself
	else if(planetToFocus !=0 && toScale)		
	{
		height = 1;
	}
	else	
	{
		height = 3;
	}

	// A switch statement that allows the user to explore our planet
    switch(key)
	{
		case 27:
			exit(0);
			break;

		case '0':
			planetToFocus = 0;
			scaleValue = 1;
			globalView = false;
			break;
		
		case '1':
			planetToFocus = 1;
			scaleValue = 1;
			globalView = false;

			break;
		
		case '2':
			planetToFocus = 2;
			scaleValue = 1;
			globalView = false;

			break;

		case '3':
			planetToFocus = 3;
			scaleValue = 1;
			globalView = false;		

			break;

		case '4':
			planetToFocus = 4;
			scaleValue = 1;
			globalView = false;
			break;

		case '5':
			planetToFocus = 5;
			scaleValue = 1;
			globalView = false;

			break;

		case '6':
			planetToFocus = 6;
			scaleValue = 1;
			globalView = false;

			break;

		case '7':
			planetToFocus = 7;
			scaleValue = 1;
			globalView = false;

			break;

		case '8':
			planetToFocus = 8;
			scaleValue = 1;
			globalView = false;

			break;

		case '9':
			planetToFocus = 9;
			scaleValue = 1;
			globalView = false;

			if(toScale)
			{
				height = 4;
			}

			break;

		case '+':
			planetToFocus = 0;
			scaleValue = 2;
			globalView = true;
			height = 0;
			break;

		case '*':
			scaleValue = 1;
			globalView  =false;
			if(planetToFocus ==23 )
			{
				planetToFocus = 0;
			}
			planetToFocus ++;
			break;				
	}
}


// Just initializing some stuff
bool initialize()
{
	// Variables
	shader frag_shade;
	shader vert_shade;

	// Generate buffer and bind the buffer to the data    
	// 6 4 for the rings, 1 for the orbital path, and another for the sphere
	glGenBuffers(6, vbo_geometry);

	// Create one sphere object	
	obj = objLoader("./bin/sphere.obj", numVert);
	
	// Bind that data to the first place in the array position
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVert, obj, GL_STATIC_DRAW);

	// Create ring object for jupiter
	jupiterRings = objLoader("./bin/jupiterRings.obj", jupiterVert);
	
	// Bind that ring data to the fourth place in the array position
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * jupiterVert, jupiterRings, GL_STATIC_DRAW);

	// Create ring object for saturn
	saturnRings = objLoader("./bin/saturnRings.obj", saturnVert);
	
	// Bind that ring data to the third place in the array position
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * saturnVert, saturnRings, GL_STATIC_DRAW);
	
	// Create ring object for uranus
	uranusRings = objLoader("./bin/uranusRings.obj", uranusVert);
	
	// Bind that ring data to the fifth place in the array position
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * uranusVert, uranusRings, GL_STATIC_DRAW);

	// Create ring object for neptune
	neptuneRings = objLoader("./bin/neptuneRings.obj", neptuneVert);

	// Bind that ring data to the sixth place in the array position
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * neptuneVert, neptuneRings, GL_STATIC_DRAW);

	// Allocate memory to the magick pointers
	texture = new GLuint[numObjects];
	bigBlob = new Magick :: Blob[numObjects];

	// Then generate those textures
	glGenTextures(numObjects, texture);

	// Loop through and read in the data and store it 
	for(int i = 0; i < numObjects; i++)
	{
		Magick :: Image image;

		image.read(sObjects[i].myTextureName);
		image.write(&bigBlob[i], "RGBA");

		// Active the textures that are binded
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.columns(), image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bigBlob[i].data());
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	// FOr the orbital line, look at orbitpath function or something in order to see how this is done
	Vertex circle[360];
	
	// Calculates each and every x and y position for the circle at planet. Another way would be to just have a radius and expand upon it, but didn't think about ti that way until later
    orbitPath(circle);

	// Bind it
	glBindBuffer(GL_ARRAY_BUFFER, vbo_geometry[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);
	
	// Shader stuff starts here
	program = glCreateProgram();

	// Get file name
	frag_shade.setShaderFileName("./bin/shader.fs");
	vert_shade.setShaderFileName("./bin/shader.vs");
	
	// Read it in
	vert_shade.readIn();
	frag_shade.readIn();
	
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
	
    //--Init the view and projection matrices
    //  if you will be having a moving camera the view matrix will need to more dynamic
    //  ...Like you should update it before you render more dynamic 
    //  for this project having them static will be fine
    view = glm::lookAt( glm::vec3(3.0, 20.0, -9.0), //Where the eye is located Eye Position //(3.0, 8.0, -16.0)
                        sObjects[0].myVectorPosition, //Focus point. Pointing at sun now //(0.0, 0.0, 2.0)
                        glm::vec3(0.0, 1.0, 0.0)); //Up vector

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
    glDeleteBuffers(5, vbo_geometry);

	delete[] bigBlob;
	delete[] texture;
	delete[] obj;
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

void menu(int id)
{
	switch(id)
	{
		case 1:
			stopSpin = 0;
			break;

		case 2:
			stopSpin = 1;
			break;

		case 3:
			toScale = !toScale;
			break;

		case 4:
			exit(0);
			break;

	}
}

Vertex *objLoader(const char *imageFile, int &numberOfVertices )
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

	if(!myScene)
	{
		cout << importer.GetErrorString() << endl;
		exit(1);
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

				out++;
			}
		}
			return outVertex;
	}	
}

// Got the idea from this guy here, however, unlike him I didn't try to do it all in the render function
// https://www.opengl.org/discussion_boards/showthread.php/167955-drawing-a-smooth-circle

void orbitPath(Vertex circle[360])
{
	// Create a conversio
	float deg2Rad = 3.14/180;

	// Loop through till 360
	for(int i = 0; i <360; i++)
	{
		
		 float x = i * deg2Rad;

		 circle[i].uv[0] = 0.6;
		 circle[i].uv[1] = 0.6;

		// Parameteric equation y = r sin0 , and x = r cos 0, 0 = x 
		 circle[i].position[0] = 1.0 * cos(x);
		 circle[i].position[1] = 0.0;
		 circle[i].position[2] = 1.0 * sin(x);
	}
}

bool loadSolar()
{
	// Declare an ifstream
    ifstream fin ("./bin/solarSystem.txt");

	// Check if it's bad and could not be opened
	if(!fin.good())
	{
		return false;
	}
	
	// Otherwise, just loop through and read it into the allocated space
	else
	{
		sObjects = new solarObjects[numObjects];
		int i = 0;
		while(fin >> sObjects[i].identifier >> sObjects[i].myObjectName >> sObjects[i].myTextureName 
				  >> sObjects[i].myPositionInArray >> sObjects[i].myDaddy >> sObjects[i].mySize 
				  >> sObjects[i].myRot >> sObjects[i].myOrb >> sObjects[i].myDistance)
		{
			if(i != 0)
			{
				sObjects[i].myDistance += sObjects[sObjects[i].myDaddy].mySize + 1; // want to account for diameter of the sun for the planets				
			}

			i++;
		}


		fin.close(); // dont forget to close

		return true;
	}
}

void myMouse(int button, int state, int x, int y)
{
	// A whole lot of if statements
	// For scrolling and stuff for each of the sun and planets, makes sure that it doesn't clip
	if(button == 3)
	{
		if(toScale)
		{
			if(planetToFocus == 0)
			{
				if(height >0)
				{
					 height -= 0.5;
				}
			}
			else
			{
				if(planetToFocus == 9)	
				{
					if(height >4)
					{	
						height -= 0.5;
					}
				}
				else
				{
					if(height >1)
					{	
						height -= 0.5;
					}
				}
			}

		}
		else
		{
			if(planetToFocus == 0)
			{
				if(height >5)
				{
					 height -= 0.5;
				}
			}
			else
			{
				if(height >3)
				{	
					height -= 0.5;
				}
			}	
		}
	}

	// For scrolling up? Does the same except wise versa.
	else if(button == 4)
	{
		if(toScale)
		{
			if(planetToFocus == 0)
			{
				if(height < 15)
				{
					height += 0.5;
				}
			}
			else
			{
				if(height < 7)
				{	
					height += 0.5;
				}
			}
		}
		else
		{
			if(planetToFocus == 0)
			{
				if(height < 7)
				{
					height += 0.5;
				}
			}
			else
			{
				if(height < 15)
				{	
					height += 0.5;
				}
			}
		}
	}
}

void processSpecialKeys(int key, int xx, int yy)
{
	// Essentially just lets the planyer move the camera a tad bit up or down just to give it some interactability. No clipping problems thanks to the if statements
	switch(key)
	{
		case GLUT_KEY_UP:

			if(toScale)
			{
				if(planetToFocus == 0)
				{
					if(height >0)
					{
						 height -= 0.5;
					}
				}
				else
				{
					if(planetToFocus == 9)	
					{
						if(height >4)
						{	
							height -= 0.5;
						}
					}
				else
				{
					if(height >1)
					{	
						height -= 0.5;
					}
				}
			}
		}
		else
		{
			if(planetToFocus == 0)
			{
				if(height >5)
				{
					height -= 0.5;
				}
			}
			else
			{
				if(height >3)
				{	
					height -= 0.5;
				}
			}	
		}
		break;

		case GLUT_KEY_DOWN:
			if(toScale)
			{
				if(planetToFocus == 0)
				{
					if(height < 15)
					{
						height += 0.5;
					}
				}
				else
				{
					if(height < 7)
					{	
						height += 0.5;
					}
				}

			}
			else
			{
				if(planetToFocus == 0)
				{
					if(height < 7)
					{
						 height += 0.5;
					}
				}
				else
				{
					if(height < 15)
					{	
						height += 0.5;
					}
				}
			}
			break;
	}
}


