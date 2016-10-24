// Header Files 
#include "formatted_console_io_V18.h"
#include <cmath>
#include <fstream>

using namespace std;

// Global Constants 

   // Box management
   const int DIFFICULTY_MIN_X = 15;
   const int DIFFICULTY_MIN_Y = 10;
   const int DIFFICULTY_MAX_X = 70;
   const int DIFFICULTY_MAX_Y = 14;
   const int MENU_MIN_X = 20;
   const int MENU_MIN_Y = 5;
   const int MENU_MAX_X = 60;
   const int MENU_MAX_Y = 20;
   const int NAME_MIN_X = 15;
   const int NAME_MIN_Y = 8;
   const int NAME_MAX_X = 70;
   const int NAME_MAX_Y = 14;
   const int INSTRUCTION_MIN_X = 14;
   const int INSTRUCTION_MIN_Y = 3;
   const int INSTRUCTION_MAX_X = 68;
   const int INSTRUCTION_MAX_Y = 18;
   const int EXTRA_INSTRUCTION_MIN_X = 14;
   const int EXTRA_INSTRUCTION_MIN_Y = 3;
   const int EXTRA_INSTRUCTION_MAX_X = 68;
   const int EXTRA_INSTRUCTION_MAX_Y = 22;
   const int SIDEBAR_MIN_X = 0;
   const int SIDEBAR_MIN_Y = 0;
   const int SIDEBAR_MAX_X = 16;
   const int SIDEBAR_MAX_Y = 24;
   const int GAME_ENDS_BOX_MIN_X = 2;
   const int GAME_ENDS_BOX_MIN_Y = 12;
   const int GAME_ENDS_BOX_MAX_X = 14;
   const int GAME_ENDS_BOX_MAX_Y = 23;

   // square boundaries
   const int WIDTH = 62;
   const int HEIGHT = 23;

   // clear screen for new map
   const int MAP_MIN_X = 18;
   const int MAP_MIN_Y = 1;
   const int MAP_MAX_X = 78;
   const int MAP_MAX_Y = 23;

   // numbers
   const int ONE = 49;
   const int TWO = 50;
   const int THREE = 51;
   const int FOUR = 52;

   // difficulties
   const int EASY = 5;
   const int MEDIUM = 3;
   const int HARD = 1;

   // instruction screen
   const int INSTRUCTION_TITLE_X = 39;
   const int INSTRUCTION_TITLE_Y = 4;

   // prompt management
   const int DIFFICULTY_TITLE_X = 30;
   const int DIFFICULTY_TITLE_Y = 11;
   const int DIFFICULTY_PROMPT_X = 20;
   const int DIFFICULTY_PROMPT_Y = 13;
   const int MENU_X_VALUE = 30;
   const int MENU_TITLE_Y = 8;
   const int MENU_UNDERLINE_Y = 9;
   const int MENU_DIFFICULTY_Y = 11;
   const int MENU_PLAY_GAME_Y = 12;
   const int MENU_SCORES_Y = 13;
   const int MENU_QUIT_Y = 14;
   const int MENU_PROMPT_Y = 16;
   const int NAME_PROMPT_X = 25;
   const int NAME_PROMPT_Y = 11;
   const int GAME_ENDS_TOP_X = 7;
   const int GAME_ENDS_TOP_Y = 17;
   const int GAME_ENDS_BOTTOM_X = 7;
   const int GAME_ENDS_BOTTOM_Y = 19;

   // splash screen
   const int ROGUE_X_VALUE = 17;
   const int ROGUE_FIRST_Y = 3;
   const int ROGUE_SECOND_Y = 4;
   const int ROGUE_THIRD_Y = 5;
   const int ROGUE_FOURTH_Y = 6;
   const int ROGUE_FIFTH_Y = 7;
   const int ROGUE_SIXTH_Y = 8;
   const int LIKE_X_VALUE = 25;
   const int LIKE_FIRST_Y = 11;
   const int LIKE_SECOND_Y = 12;
   const int LIKE_THIRD_Y = 13;
   const int LIKE_FOURTH_Y = 14;
   const int LIKE_FIFTH_Y = 15;
   const int LIKE_SIXTH_Y = 16;
   const int SUBTITLE_X = 20;
   const int SUBTITLT_Y = 20;
   const int CONTINUE_PROMPT_X = 28;
   const int CONTINUE_PROMPT_Y = 22;

   // symbol management
   const char NULL_CHAR = '\0';
   const short PLAYER = 42;
   const short WALL = 176;
   const short TREASURE = 232;
   const short CLOAK = 247;
   const short HOLE = 178;
   const short SPELL = 234;
   const short SWORD = 157;
   const short MONSTER = 206;
   const char BIG_D = 68;
   const char LITTLE_D = 100;
   const char BIG_P = 80;
   const char LITTLE_P = 112;
   const char BIG_S = 83;
   const char LITTLE_S = 115;
   const char BIG_Q = 81;
   const char LITTLE_Q = 113;
   const char BIG_U = 85;
   const char SPACE = ' ';
   const char MARKER_CHAR = '*';

   // array sizes
   const int NAME_SCORE_ROW_SIZE = 11;
   const int NAME_SCORE_COLUMN_SIZE = 30;
   const int MAP_ARRAY_COLUMN_SIZE = 90;
   const int MAP_ARRAY_ROW_SIZE = 50;
   const int MAX_NAME_SIZE = 25;

   // input management
   const int DEFAULT = -1;

// Function Prototypes 

/*
Name: displaySplashScreen
Process: shows the game title screen and waits for the user to input a keystroak
Function Input/Parameters: none
Function Output/Return: the character that the user put in (char)
Device Input: a letter to continue
Device Output/Monitor: the title screen
Dependencies: formatted console I/O
Developer: Reese Barton
*/
char displaySplashScreen();

/*
Name: instructionScreen
Process: displays the correct instruction screen for the user
Function Input/Parameters: the character that was input at the splash screen (char)
Function Output/Return: none
Device Input: any key to continue
Device Output/Monitor: the instruction screen
Dependencies: formatted console I/O
Developer: Zeeshan Sajid
*/
void displayInstructionScreen( char splashInput );

/*
Name: displayExtraInstructions();
Process: displays the extra credit version of the instructions
Function Input/Parameters: none
Function Output/Return: none
Device Input: any key to continue
Device Output/Monitor: the extra instruction screen
Dependencies: formatted console I/O
Developer: Zeeshan Sajid
*/
void secondaryInstructionScreen();

/*
Name: displayMenu
Process: displays the game menu on the screen
Function Input/Parameters: none
Function Output/Return: none
Device Input: none
Device Output/Monitor: the menu with white text and a blue background
Dependencies: formatted console I/O
Developer: Reese Barton
*/
void displayMenu();

/*
Name: setDifficulty
Process: displays a prompt to input a difficulty and obtains input from the user
Function Input/Parameters: none
Function Output/Return: the input wait time associated with the selected difficulty (int)
Device Input: the desired difficulty
Device Output/Monitor: the difficulty display prompt
Dependencies: formatted console I/O
Developer: Reese Barton
*/
int setDifficulty();

/*
Name: showTopScores
Process: displays the top 10 scores in order of highest score
Function Input/Parameters: 
Function Output/Return: none
Device Input: none
Device Output/Monitor: the top 10 scores scored
Dependencies: fstream I/O tools
Developer: Zeeshan Sajid
*/
bool showTopScore( char namesAndScores[][ NAME_SCORE_COLUMN_SIZE ], int &score, char arr[] );

/*
Name: swap
Process: swaps two values
Function Input/Parameters: the first and second values to be swapped (char)
Function Output/Return: none
Device Input: none
Device Output/Monitor: none
Dependencies: none
Developer: Zeeshan Sajid
*/
void swap( char one[], char other[] );

/*
Name: playGame
Process: displays and starts the game
Function Input/Parameters: ifstream opereator (ifstream)
                           the name array, splash input, and high, low, and mid level names (char)
                           the difficulty (int)
Function Output/Return: continuation flag (bool)
Device Input: direction of movement
Device Output/Monitor: the screen for the game and the side score bar
Dependencies: fstream I/O tools
Developer: Reese Barton and Zeeshan Sajid
*/
bool playGame( ifstream &fin, ofstream &fout, char name[], char splashInput, int difficulty,
                char highLevel[], char lowLevel[], char midLevel[], int &score );

/*
Name: enterNamePrompt
Process: prompts the user to enter his or her name and score
Function Input/Parameters: the array that will hold the names and scores (char)
Function Output/Return: none
Device Input: the desired name
Device Output/Monitor: the prompt for the name
Dependencies: formatted console I/O
Developer: Zeeshan Sajid
*/
void enterNamePrompt( char name[] );

/*
Name: move
Process: moves the player's character a disignated direction
Function Input/Parameters: the x and y positions and the direction in the x and y directions (int)
Function Output/Return: boolean of if it was moved (bool)
Device Input: none
Device Output/Monitor: the new location of the character
Dependencies: none
Developer: Reese Barton
*/
bool move( int &xPos, int &yPos, int xVect, int yVect );

/*
Name: displaySquare
Process: displays the edges of the map
Function Input/Parameters: the width and height of the square (int)
Function Output/Return: none
Device Input: none
Device Output/Monitor: a square boarder
Dependencies: none
Developer: Zeeshan Sajid
*/
void displaySquare( int width, int height );

/*
Name: checkForMaps
Process: checks if the map files are existant
Function Input/Parameters: ifstream operator (ifstream)
                           the arrays with the name of the file (char)
Function Output/Return: boolean flag indicating whether or not it was successful (bool)
Device Input: none
Device Output/Monitor: none
Dependencies: ifstream I/O tools
Developer: Reese Barton
*/
bool checkForMaps( ifstream &fin, char highLevel[], char lowLevel[], char midLevel[] );

/*
Name: displayErrorMessage
Process: if not all maps are existant, will display an error message and shut down the program
Function Input/Parameters: 
Function Output/Return: none
Device Input: 
Device Output/Monitor: the maps error message
Dependencies: 
Developer: Zeeshan Sajid
*/
void displayErrorMessage();

/*
Name: changeMaps
Process: changes the current map on the screen
Function Input/Parameters: ifstream operator (ifstream)
                           file name of the map (char)
                           the map array (short)
Function Output/Return: a letter indicating the current level (char)
Device Input: none
Device Output/Monitor: the correct map
Dependencies: ifstream I/O tools
Developer: Reese Barton
*/
char changeMap( ifstream &fin, char mapName[], short mapArr[][ MAP_ARRAY_COLUMN_SIZE ], char high[], char mid[] );

/*
Name: percentageGenerator
Process: generates a number between 1-100 and tests if it is within the accepted percent range
Function Input/Parameters: none
Function Output/Return: random number from 1-100
Device Input: none
Device Output/Monitor: none
Dependencies: cmath
Developer: Reese Barton
*/
int percentageGenerator();

/*
Name: displayOoccurances
Process: possibly displays monsters, spell, swords, cloaks, holes, and treasure 
Function Input/Parameters: the percent telling if one will occur (int)
                           the character input at the splash screen (char)
                           the map array (short)
Function Output/Return: none
Device Input: none
Device Output/Monitor: monsters, spell, swords, cloaks, holes, and/or treasure
Dependencies: none
Developer: ReeseBarton
*/
void displayOccurances( int percent, char splashValue, short mapArr[][ MAP_ARRAY_COLUMN_SIZE ], int xLoc, int yLoc );

/*
Name: sideCounter
Process: keeps the score and stats up to date
Function Input/Parameters: the splash screen input (char)
                           the current x and y location, the score, and the cloak, treasure, spell, and sword values (int)
                           the map array (short)
Function Output/Return: if the function can continue (bool)
Device Input: none
Device Output/Monitor: the current scores and number of items
Dependencies: none
Developer: Reese Barton
*/
bool sideCounter( char splashInput, int xValue, int yValue, short mapArr[][ MAP_ARRAY_COLUMN_SIZE ], int &score,
                  int &cloak, int &treasure, int &spell, int &sword );

/*
Name: findScore
Process: inputs scores and names from a text file and returns how many were found
Function Input/Parameters: fstream input operator (ifstream)
                           the array with the list of names and the current name (char)
                           the array with the scores and the current score (int)
Function Output/Return: the number of items input (int)
Device Input: none
Device Output/Monitor: none
Dependencies: none
Developer: Zeeshan Sajid
*/
int findScore(ifstream &fileIn, char playersArr[][ MAX_NAME_SIZE ], int arr[], int playerScore, char src[]);

/*
Name: clearCharArray
Process: fills a character array with null chars
Function Input/Parameter: the array to fill (char)
                          the size (int)
Function Output/Return: none
Device Input: none
Device Output/Monitor: none
Dependencies:none
Developer: Zeeshan Sajid
*/
void clearCharArray( char testArr[], int amount);

/*
Name: openTheScoreAndNames
Process: outputs the data to a file
Function Input/Parameters: fstream output operator (ofstream)
                           the array full of names (char)
                           the size and array with the scores (int)
Function Output/Return: none
Device Input: none
Device Output/Monitor: none
Dependencies: fstream I/O tools
Developer: Zeeshan Sajid
*/
void openTheScoreAndNames(ofstream &output, char playersArr[][ MAX_NAME_SIZE ], int arr[], int size);

/*
Name: bubbleSort
Process: sorts the high scores from greatest to least
Function Input/Parameters: the array containing the names (char)
                           the size and the array with the score (int)
Function Output/Return: none
Device Input: none
Device Output/Monitor: none
Dependencies: none
Developer: Zeeshan Sajid
*/
void bubbleSort( int arr[], int size, char src[][ MAX_NAME_SIZE ] );

/*
Name: clearIntArray
Process: fills an integer array with null characters
Function Input/Parameters: the array to be cleared and its size (int)
Function Output/Return: none
Device Input: none
Device Output/Monitor: none
Dependencies: none
Developer: Zeeshan Sajid
*/
void clearIntArray(int arr[], int size);

// Main Function 
int main()
   {
    // initialize program/function

       // initialize function/variables
       char splashInput;
       bool continueFlag = true;
       int userInput, difficulty = 5;
       int score = 0;
       char name[ MAX_NAME_SIZE ];
       char namesAndScores[ NAME_SCORE_ROW_SIZE ][ NAME_SCORE_COLUMN_SIZE ];
       char highLevel[ MAX_NAME_SIZE ] = "highlevel.txt";
       char lowLevel[ MAX_NAME_SIZE ] = "lowlevel.txt";
       char midLevel[ MAX_NAME_SIZE ] = "midlevel.txt";
       bool continueflag = true;
       ifstream fin;
       ofstream fout;
       int index;

       // preset name array
       for( index = 0; index < 11; index++ )
          {
           name[index] = NULL_CHAR;
          }

       // seed random generator
          // function: srand
          srand( time( NULL ) );

       // start curses
          // function: startCurses
          startCurses();

    // display splash screen
       // function: displaySplashScreen
       splashInput = displaySplashScreen();
       
    // display appropriate instructions screen
       // function: displayInsturctionScreen
       displayInstructionScreen( splashInput );
    
       // start loop
       do
          {
           // wait to get user input
              // function: waitForInput
              userInput = waitForInput( FIXED_WAIT );

           // depending on input, do task
           switch( userInput )
              {
               // set case for setting difficulty
                  // function: setDifficulty
                  case ONE:
                  case LITTLE_D:
                  case BIG_D:
                     difficulty = setDifficulty();
                     break;

               // set case for play game
                  // function: playGame
                  case TWO:
                  case LITTLE_P:
                  case BIG_P:
                     continueflag = playGame( fin, fout, name, splashInput, difficulty, highLevel, lowLevel,
                                               midLevel, score );
                     break;

               // set case for displying past scores
                  // function: showTopScores
                  case THREE:
                  case LITTLE_S:
                  case BIG_S:
                     showTopScore( namesAndScores, score, name );
                     break;

               // set case for quiting game
                  case FOUR:
                  case LITTLE_Q:
                  case BIG_Q:
                     continueFlag = false;
                     break;
              }

           // display menu
              // function: displayMenu
              displayMenu();

          }
       // check loop condition
       while( continueFlag );
 
    // shut down the program

       // shut down curses
          // function: endCurses
          endCurses();

       // return success 
       return 0;
   }

// Supporting Function Implementation

char displaySplashScreen()
   {
    // initialize function/variables

    // set screen color
       // function: setColor
       setColor( COLOR_MAGENTA, COLOR_BLACK, SET_BRIGHT );

    // print letters in correct places
       // function: printStringAt
       printStringAt( 17, 3, "RRRRRR    OOOOOO   GGGGGGG   UU    UU  EEEEEEEE", "LEFT" );
       printStringAt( 17, 4, "RR   RR  OOO  OOO GGG    GG  UU    UU  EE     E", "LEFT" );
       printStringAt( 17, 5, "RR   RR  OO    OO GG         UU    UU  EEEE", "LEFT" );
       printStringAt( 17, 6, "RRRRRR   OO    OO GG   GGGG  UU    UU  EEEE", "LEFT" );
       printStringAt( 17, 7, "RR RR    OOO  OOO GGG    GG  UUU  UUU  EE     E", "LEFT" );
       printStringAt( 17, 8, "RR  RR    OOOOOO   GGGGGGG    UUUUUU   EEEEEEEE", "LEFT" );
       printStringAt( 25, 11, "LL       IIII  KK  KK   EEEEEEEE", "LEFT" );
       printStringAt( 25, 12, "LL        II   KK KK    EE     E", "LEFT" );
       printStringAt( 25, 13, "LL        II   KK K     EEEE", "LEFT" );
       printStringAt( 25, 14, "LL        II   KKKKK    EEEE", "LEFT" );
       printStringAt( 25, 15, "LL        II   KK  KK   EE     E", "LEFT" );
       printStringAt( 25, 16, "LLLLLLL  IIII  KK   KK  EEEEEEEE", "LEFT" );

    // reset color for sub title
       // function: setColor
       setColor( COLOR_CYAN, COLOR_BLACK, SET_BRIGHT );

    // print subtitle
       // function: printStringAt
       printStringAt( 20, 20, "Implemented By Reese Barton and Zeeshan Sajid", "LEFT" );

    // print continuation prompt
       // function printStringAt
       printStringAt( 28, 22, "Press Any Key To Continue", "LEFT" );

    // hold screen and return input
    return waitForInput( FIXED_WAIT );
   }

void displayInstructionScreen( char splashInput )
   {
    // Intialize Variables
    int xPos = 0, yPos = 0;

    // Reset screen
    setColor( COLOR_WHITE, COLOR_BLACK, SET_BRIGHT );
    clearScreen( SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y );

    // test if 'e' was entered
    if( splashInput == 'e' )
       {
        // display secondary screen
           // function: secondaryInstructionScreen()
           secondaryInstructionScreen();
       }

    // otherwise display instruction screen
    else
       {
       // Set the color for the new screen
          // Function: setColor
          setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT ); 

       // Clear the screen
          // Function: clearScreen
          clearScreen( 14, 3, 68 ,18 );  

       // Set the title of the instruction
          // Function: printStringAt        
          xPos = 39, yPos = 4;
          printStringAt( xPos, yPos, "Rogue-Like Instructions" , "CENTER" );

       // Set the x and Y coordinate for the underline of the title
           // function: printStringAt
           yPos ++;
           printStringAt( xPos, yPos, "=======================" , "CENTER" );
    
       // Set the x and Y coordinate for the first letter of the first instruction
          // function: prinStringAt
          xPos = 16, yPos = 7; 
          printStringAt( xPos, yPos,  "Green" , "LEFT" );  

       // Set the x and y coordinate for the special character value of cloak, and then set the color
          // function: setcolor, printSpecialCharAt
          xPos = 22;
          setColor( COLOR_GREEN, COLOR_WHITE, SET_BRIGHT );
          printSpecialCharAt( xPos, yPos, CLOAK );
    
   
       // Set the x and y coordinate for the next set and then change the color for the set of instructions
          // function: setColor, printStringAt
          xPos = 24;
          setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
          printStringAt( xPos, yPos,  "are magic cloaks that can cover holes" , "LEFT" );   

       // Set the x and y coordinate for the next ascii value, and change the color
          // setColor, printSpecialCharAt
          xPos = 62;
          setColor( COLOR_RED, COLOR_WHITE, SET_BRIGHT );
          printSpecialCharAt( xPos, yPos, HOLE );
          setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );

       // Set the x and y coordinate fo the next set of instructions, and print the special character
         // setColor, printStringAt, printSpecialCharacter
         xPos = 28, yPos=9;
         printStringAt( xPos, yPos,  "Yellow" , "CENTER" );  
         setColor( COLOR_YELLOW, COLOR_WHITE, SET_BRIGHT );

       // Change xPos, and then printcharacter
       xPos = 33;
       printSpecialCharAt( xPos, yPos, TREASURE );
       setColor( COLOR_YELLOW, COLOR_WHITE, SET_BRIGHT );
       setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
   
       // Print the next set of instructions
       xPos = 44;
       printStringAt( xPos, yPos, "are golden treasure", "CENTER" );

       // Print the special characters, and then print the rest of the instructions with appropriate colors
          // function: printStringAt, printSpecialCharacter, setColor
          xPos = 22, yPos = 11;
          setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );   
          printSpecialCharAt( xPos, yPos, BIG_U );
          setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );  
          xPos = 25;
          printStringAt( xPos, yPos, "and", "CENTER" );
          xPos = 28;
          setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );   
          printSpecialCharAt( xPos, yPos, BIG_D );
          xPos = 44;
          setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );  
          printStringAt( xPos, yPos, "lead to Upper and Lower floors", "CENTER" );
       
        // Set the x and y Coordinate for the next set of instructions   
           // function: printStringAt
           xPos = 26, yPos = 13;   
           printStringAt( xPos, yPos,  "Hitting a hole ends the game" , "LEFT" );

       // Set the x and y coordinate for the next set of instrucitons, and then write
          // function: printStringAt
          xPos = 19, yPos = 15; 
          printStringAt( xPos, yPos,  "Try to keep moving for as long as possible" , "LEFT" );

       // Set the x and y coordinate and then write the instruction
          // function: printStringAt
          xPos = 18, yPos = 17; 
          printStringAt( xPos, yPos,  "More treasure and cloaks get a better score" , "LEFT" );

       }
   }

void secondaryInstructionScreen()
   {
    // Intialize Variables
    int xPos = 0, yPos = 0;
    
    // Clear the Screen
    clearScreen( SCRN_MIN_X, SCRN_MIN_Y, SCRN_MIN_X ,SCRN_MIN_Y );

    // Set the color for the new screen
       // Function: setColor
       setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT ); 

    // Clear the screen
       // Function: clearScreen
       clearScreen( EXTRA_INSTRUCTION_MIN_X, EXTRA_INSTRUCTION_MIN_Y, EXTRA_INSTRUCTION_MAX_X, EXTRA_INSTRUCTION_MAX_Y );  

    // Set the title of the instruction
       // Function: printStringAt        
       xPos = 39, yPos = 4;
       printStringAt( xPos, yPos, "Rogue-Like Instructions" , "CENTER" );

    // Set the x and Y coordinate for the underline of the title
       // function: printStringAt
       yPos ++;
       printStringAt( xPos, yPos, "=======================" , "CENTER" );
    
    // Set the x and Y coordinate for the first letter of the first instruction
       // function: prinStringAt
       xPos = 16, yPos = 7; 
       printStringAt( xPos, yPos,  "Green" , "LEFT" );  

    // Set the x and y coordinate for the special character value of cloak, and then set the color
       // function: setcolor, printSpecialCharAt
       xPos = 22;
       setColor( COLOR_GREEN, COLOR_WHITE, SET_BRIGHT );
       printSpecialCharAt(xPos, yPos, CLOAK );
    
   
    // Set the x and y coordinate for the next set and then change the color for the set of instructions
      // function: setColor, printStringAt
       xPos = 24;
       setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
       printStringAt( xPos, yPos,  "are magic cloaks that can cover holes" , "LEFT" ); 
    
    // Print out the special character
       // function: setColor, printSpecialCharAt
       xPos = 62;
       setColor( COLOR_RED, COLOR_WHITE, SET_BRIGHT );
       printSpecialCharAt( xPos, yPos, HOLE );  
       setColor(COLOR_BLUE, COLOR_WHITE, SET_BRIGHT);

    // Set the x and y Position for the instructions, and then print the special character
    xPos = 22, yPos = 9;
    printStringAt( xPos, yPos, "Green", "CENTER" );
    
    // print the special character
       // function: PrintSpecialCharAt
       xPos = 26;
       setColor( COLOR_GREEN, COLOR_WHITE, SET_BRIGHT );
       printSpecialCharAt( xPos, yPos, SWORD );

    // Set the color back to normal, and then prepare the x and y, and then print
       // function: setColor, printStringAt
       setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
       xPos = 42;
       printStringAt( xPos, yPos, "are swords that kill monsters", "CENTER" );

    // Set the color to red, and print the character
       // function: printSpecialCharAt, setColor
       xPos = 58;
       setColor( COLOR_RED, COLOR_WHITE, SET_BRIGHT );
       printSpecialCharAt( xPos, yPos, MONSTER );

    // Set the color to normal, and the print the rest
       // set Color, printStringat
       xPos =21, yPos =11;
       setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
       printStringAt( xPos, yPos, "Green", "CENTER" );

    // Set the color to green and print out the character
    xPos = 25;
    setColor( COLOR_GREEN, COLOR_WHITE, SET_BRIGHT );
    printSpecialCharAt( xPos, yPos, SPELL );

    // Set the color to normal, and then print out the rest of the instructions, and then the wall
    xPos =41, yPos =11;
    setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
    printStringAt( xPos, yPos, "are spells that go through walls", "CENTER" );

    // Change the x location, and then print the char again, and don't change the color
       // function: printSpecialCharAt, set Color
       xPos = 59;
       printSpecialCharAt( xPos, yPos, WALL );

    // Set the x and y coordinate fo the next set of instructions, and print the special character
      // setColor, printStringAt, printSpecialCharacter
      xPos = 28, yPos=13;
      printStringAt( xPos, yPos,  "Yellow" , "CENTER" );  
      setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );

    // Change xPos, and then printcharacter
    xPos = 33;
    setColor( COLOR_YELLOW, COLOR_WHITE, SET_BRIGHT );
    printSpecialCharAt( xPos, yPos, TREASURE );
    setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
   
    // Print the next set of instructions
    xPos = 44;
    printStringAt( xPos, yPos, "are golden treasure", "CENTER" );

    // Print the special characters, and then print the rest of the instructions with appropriate colors
       // function: printStringAt, printSpecialCharacter, setColor
       xPos = 22, yPos = 15;
       setColor( COLOR_WHITE, COLOR_BLACK, SET_BRIGHT );   
       printSpecialCharAt( xPos, yPos, BIG_U );
       setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );  
      xPos = 25;
      printStringAt( xPos, yPos, "and", "CENTER" );
      xPos = 28;
      setColor( COLOR_WHITE, COLOR_BLACK, SET_BRIGHT );   
      printSpecialCharAt( xPos, yPos, BIG_D );
      xPos = 44;
      setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );  
      printStringAt( xPos, yPos, "lead to Upper and Lower floors", "CENTER" );
       
    // Set the x and y Coordinate for the next set of instructions   
       // function: printStringAt
       xPos = 26, yPos = 17;   
       printStringAt( xPos, yPos,  "Hitting a hole ends the game" , "LEFT" );

    // Set the x and y coordinate for the next set of instrucitons, and then write
       // function: printStringAt
       xPos = 19, yPos = 19; 
       printStringAt( xPos, yPos,  "Try to keep moving for as long as possible" , "LEFT" );

    // Set the x and y coordinate and then write the instruction
       // function: printStringAt
       xPos = 18, yPos = 21; 
       printStringAt( xPos, yPos,  "More treasure and cloaks get a better score" , "LEFT" );

   }   

void displayMenu()
   {
    // initialize function/variables

    // reset the screen
       // function: setColor, clearScreen
       setColor( COLOR_WHITE, COLOR_BLACK, SET_BRIGHT );
       clearScreen( SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y );

    // set the color and clear the screen
       // function: setColor, clearScreen
      setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
      clearScreen( 20, 5, 60, 20 );

    // print menu title and underline
       // function: printStringAt
       printStringAt( 30, 8, "MENU SELECTIONS", "LEFT" );
       printStringAt( 30, 9, "---------------", "LEFT" );

    // print menu options
       // function: printStringAt
       printStringAt( 30, 11, "1. Set <D>ifficulty", "LEFT" );
       printStringAt( 30, 12, "2. <P>lay Game", "LEFT" );
       printStringAt( 30, 13, "3. <S>how Top Scores", "LEFT" );
       printStringAt( 30, 14, "4. <Q>uit Program", "LEFT" );

    // print selection prompt
       // function: printStringAt
       printStringAt( 30, 16, "Enter Selection: ", "LEFT" );

   }

int setDifficulty()
   {
    // initialize function/variables
    int setting = 0;
    char input;
    bool flag = true;
    
    // reset the screen
       // function: setColor, clearScreen
       setColor( COLOR_WHITE, COLOR_BLACK, SET_BRIGHT );
       clearScreen( SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y );

    // set the color and clear the screen
       // function: setColor, clearScreen
       setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
       clearScreen( DIFFICULTY_MIN_X, DIFFICULTY_MIN_Y, DIFFICULTY_MAX_X, DIFFICULTY_MAX_Y );

    // print title
       // function: printStringAt
       printStringAt( 30, 11, "Game Data Entry Module", "LEFT" );

    // print selection prompt
       // function: printStringAt
       printStringAt( 20, 13, "Enter Game Difficulty (1-3): ", "LEFT" );

    // start loop
    do
       {
        // get user input
        input = waitForInput( FIXED_WAIT );

        // check for cases
        switch( input )
           {
            // set case for one
            case ONE:
               setting = 5;
               flag = false;
               break;

            // set case for two
            case TWO:
               setting = 3;
               flag = false;
               break;

           // set case for three
            case THREE:
               setting = 1;
               flag = false;
               break;
           }
    // check continuation condition
       }
    while( flag );

    // return setting
    return setting;
   }

bool showTopScore( char namesAndScores[][ NAME_SCORE_COLUMN_SIZE ], int &score, char arr[] )
   {
    // Intialize Variables
    int xPos = 0, yPos = 0, index=0, totalNamesAndScores;
    ifstream fileIn;
    ofstream fileOut;
    int playerScores[10];
    char playersArr[10][25];

    // Clear the screen
      // function; clearScreen
      clearScreen( 0, 0, 79 ,79 );
   
    // Set the new screen to blue
    setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );   
    
    // Set the xPos and yPos for the title of screen
    xPos = 39, yPos = 2;

    // Print the title of the string
       // function: printStringAt
       printStringAt( xPos, yPos, "TOP SCORING PLAYERS", "CENTER" );

    // Underline the title
       // functioN: printStringAt
       yPos =3;
       printStringAt( xPos, yPos, "===================", "CENTER" );
    
    // Set x and y for the names and underline the title
    xPos = 26, yPos = 5;
    printStringAt( xPos, yPos, "NAMES", "CENTER" );
    xPos = 26, yPos ++;
    printStringAt( xPos, yPos, "=====", "CENTER" );
    
    // Set the x and y Coordinate for Scores
    xPos = 51, yPos = 5;
    printStringAt( xPos, yPos, "SCORES", "CENTER" );
    xPos = 51, yPos = 6;
    printStringAt( xPos, yPos, "======", "CENTER" );

    // clear the score array
       // function: 
       clearIntArray( playerScores, 11 );

    // load the score and names into the correct arrays and find the total names and scores
       // function: findScore
       totalNamesAndScores = findScore( fileIn, playersArr, playerScores, score, arr );

    // sort the names and scores
       // function: bubbleSort
       bubbleSort( playerScores, totalNamesAndScores, playersArr );

    // output the names and scores to a file
       // function: openTheScoreAndNames
       openTheScoreAndNames( fileOut, playersArr, playerScores, totalNamesAndScores );

    // check if the file exists or if there are any scores in it
    if( totalNamesAndScores ==0 )
       {
        // set colors and clear screen
           // function: setColor, clearScreen
           setColor( COLOR_WHITE, COLOR_BLACK, SET_BRIGHT );
           clearScreen( SCRN_MIN_X, SCRN_MIN_Y, SCRN_MAX_X, SCRN_MAX_Y );
           setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
           clearScreen( 19, 9, 63 ,15 );

        // display error message
           // function: printStringAt, setColor, waitForInput
           printStringAt( 30, 11, "ERROR: No Scores Found", "LEFT" );
           setColor( COLOR_YELLOW, COLOR_BLUE, SET_BRIGHT );
           printStringAt( 25, 14, "Press any Key to Continue . . .", "LEFT" );
           waitForInput( FIXED_WAIT );

        // return false
        return false;
       }   


    else
       {
        for( yPos =7; index < totalNamesAndScores && index <=10; yPos++)
           {
            xPos = 26;
            printStringAt(xPos, yPos, playersArr[index], "CENTER");
            xPos = 51;
            printIntAt( xPos, yPos, playerScores[index], "CENTER" ); 
            index++;
           }
       }

    // Pause the system
    setColor( COLOR_YELLOW, COLOR_BLUE, SET_BRIGHT );
    xPos = 39;
    yPos += 2;
    printStringAt( xPos, yPos, "Press any Key to Continue . . .", "CENTER" );
    waitForInput( FIXED_WAIT );

    // return true
    return true;
   }

void swap( char one[], char other[] )
   {
     // initialize function/variables
     char tempArray[ MAX_NAME_SIZE ];

     // copy one to temp
     strcpy( tempArray, one );

     // copy other to one
     strcpy( one, other );

     // copy temp to other
     strcpy( other, tempArray );

    }

bool playGame( ifstream &fin, ofstream &fout, char name[], char splashInput, int difficulty,
                char highLevel[], char lowLevel[], char midLevel[], int &score )
   {
    // initialize function/variables
    int percentValue;
    int userInput, xLoc = 43; int yLoc = 2; int xVector = 0; int yVector = 0;
    int spell = 0; int cloak = 0; int treasure = 0; int sword = 0;
    short mapArray[ MAP_ARRAY_ROW_SIZE ][ MAP_ARRAY_COLUMN_SIZE ];
    bool continueGame = true;
    char currentLevel;
    int index;

         // reset score
         score = 0;

         // reset the name index
         for( index = 0; index < 11; index++ )
            {
             name[index] = NULL_CHAR;
            }

    // prompt for the name
       // function: enterNamePrompt
       enterNamePrompt( name );

    // check if maps are available
       // function: checkForMaps
       if( checkForMaps( fin, highLevel, lowLevel, midLevel ) )
          {
           // if not, display error message
              // function: displayErrorMessage
              displayErrorMessage();

           // return false
           return false;
          }

    // display box
       // function: displaySquare
       displaySquare( WIDTH, HEIGHT );

    // display mid level map
       // function: changeMap
       currentLevel = changeMap( fin, midLevel, mapArray, highLevel, midLevel );

    // start loop
    do
       {
        // obtain new percent value for occurances
           // function: percentageGenerator
           percentValue = percentageGenerator();

        // display occurances
           // function: displayOccurances
           displayOccurances( percentValue, splashInput, mapArray, xLoc, yLoc );

        // set color of screen
           // function: setColor
           setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );

        // get user input
           // function: waitForInput
           userInput = waitForInput( difficulty );

        // check conditions of user input
        switch( userInput )
           {
            // set a case for moving right
            case KB_RIGHT_ARROW:
               xVector = 1;
               yVector = 0;
               break;

            // set a case for moving left
            case KB_LEFT_ARROW:
               xVector = -1;
               yVector = 0;
               break;

            // set a case for moving up
            case KB_UP_ARROW:
               xVector = 0;
               yVector = -1;
               break;

            // set a case for moving down
            case KB_DOWN_ARROW:
               xVector = 0;
               yVector = 1;
               break;

            // set a case for pausing the game
            case BIG_P:
               waitForInput( FIXED_WAIT );
               break;

            // set a case for quiting the game
            case KB_ESCAPE:
               setColor( COLOR_YELLOW, COLOR_RED, SET_BRIGHT );
               clearScreen( GAME_ENDS_BOX_MIN_X, GAME_ENDS_BOX_MIN_Y, GAME_ENDS_BOX_MAX_X, GAME_ENDS_BOX_MAX_Y );
               printStringAt( GAME_ENDS_TOP_X, GAME_ENDS_TOP_Y, "GAME", "LEFT" );
               printStringAt( GAME_ENDS_BOTTOM_X, GAME_ENDS_BOTTOM_Y, "ENDS", "LEFT" );
               waitForInput( FIXED_WAIT );
               return false;
               break;

           }

        // check if movement is available
        if( mapArray[ yLoc + yVector ][ xLoc + xVector ] != WALL )
           {
            // if so, do movement
               // function: move
               move( xLoc, yLoc, xVector, yVector );
           }
        // check if a spell is available
        if( spell != 0 && mapArray[ yLoc + yVector ][ xLoc + xVector ] == WALL )
           {
            // if so, do movement
               // function: move
               move( xLoc, yLoc, xVector, yVector );

            // decrement spell and score by 1
            spell -= 1;
            score -= 1;

           // cover up spot
            mapArray[ yLoc ][ xLoc ] = 0;

           }

        // keep score up to date
           // function: sideCounter
           continueGame = sideCounter( splashInput, xLoc, yLoc, mapArray, score, cloak, treasure, spell, sword );

        // check if level was moved down

            // check if current level is midlevel
            if( currentLevel == 'm' && mapArray[ yLoc ][ xLoc ] == BIG_D)
               {
                 // if so, change map
                    // function: changeMap
                    currentLevel = changeMap( fin, lowLevel, mapArray, highLevel, midLevel );
                }

            // otherwise assume current level is highlevel
            else if( currentLevel == 'h' && mapArray[ yLoc ][ xLoc ] == BIG_D)
                {
                 // if so, change map
                    // function: changeMap
                    currentLevel = changeMap( fin, midLevel, mapArray, highLevel, midLevel );
                }

           

        // check if level was moved up

             // check if current level is midlevel
             if( currentLevel == 'm' && mapArray[ yLoc ][ xLoc ] == BIG_U)
                {
                 // if so, change map
                    // function: changeMap
                    currentLevel = changeMap( fin, highLevel, mapArray, highLevel, midLevel );
                }

            // otherwise assume current level is lowlevel
            else if( currentLevel == 'l' && mapArray[ yLoc ][ xLoc ] == BIG_U)
                {
                 // if so, change map
                    // function: changeMap
                    currentLevel = changeMap( fin, midLevel, mapArray, highLevel, midLevel );
                }

        // loop while user input does not equal DEFAULT
        while( userInput != DEFAULT )
           {
            // obtain new input
               // function waitForInput
               userInput = waitForInput( difficulty );
           }

    // check loop continuation condition
       }
    while( continueGame );

    // return true
    return true;
   }

void enterNamePrompt( char name[] )
  {
    // Intialize Varaibles
    int xPos = 0, yPos=0;

    // Clear the screen and turn it into a black
       // function: setColor, clearScreen
       setColor(  COLOR_YELLOW, COLOR_BLACK, SET_BRIGHT ); 
       clearScreen( 0, 0, 79, 79);  
    
    // Clear the screen and turn it into blue instead
      // function: setColor, clearScreen
       setColor(  COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );  
       clearScreen( 19, 9, 63 ,15);  

    // Ask for the user input after setting x and y coordinates
       // function: promptForStringAt 
       xPos = 25, yPos = 12;
       promptForStringAt( xPos, yPos, "Enter Your Name: ", name );

    // check if no name was entered
    if( name[0] == NULL_CHAR )
       {
        // insert a space for the name
        name[0] = SPACE;
       }
   }

bool move( int &xPos, int &yPos, int xVect, int yVect )
   {
    // initialize function/variables
    bool moved = false;
    int oldX = xPos, oldY = yPos;

          setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
    // if x vector is live, test for acceptable movement limits
    if( ( xVect != 0 ) && ( xPos + xVect > 17 ) && ( xPos + xVect < 79 )  )
       {
        // cover up the old marker
        printCharAt( oldX, oldY, SPACE );

        // reset the x position
        xPos = xPos + xVect;

        // set moved flag to indicate success
        moved = true;
       }

    // if y vector is live, test for acceptable movement limits
    else if( ( yVect != 0 ) && ( yPos + yVect > 0 ) && ( yPos + yVect < 24 ) )
       {
        // cover up the old marker
        printCharAt( oldX, oldY, SPACE );

        // reset the y position
        yPos = yPos + yVect;

        // set the moved flag to indicate success
        moved = true;
       }

    // set color for character
       // function: setColor
       setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );

    // print the marker at the specified location
    printCharAt( xPos, yPos, MARKER_CHAR );

    // return successful move
    return moved;
   }

void displaySquare( int width, int height )
   {
    // initialize function/variables
    int counter;
    int leftUpperX = SCRN_MAX_X -width;
    int leftUpperY = 0;
    int rightLowerX = SCRN_MAX_X;
    int rightLowerY = SCRN_MAX_Y;

    // clear screen in shape of box
       // function: clearScreen, setColor
       setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
       clearScreen( leftUpperX, leftUpperY, rightLowerX, rightLowerY );

    // iterate from left to right across box
    for( counter = leftUpperX; counter <= leftUpperX + width; counter++ )
       {
        // print top frame character
        printSpecialCharAt( counter, leftUpperY, WALL );

        // print bottom frame character
        printSpecialCharAt( counter, rightLowerY, WALL );
       }
    
    for( counter = leftUpperY; counter <= leftUpperY + height; counter++ )
       {
        // print left frame character
        printSpecialCharAt( leftUpperX, counter, WALL );

        // print right frame character
        printSpecialCharAt( rightLowerX, counter, WALL );
       }
   }

bool checkForMaps( ifstream &fin, char highLevel[], char lowLevel[], char midLevel[] )
   {
    // Intialize Varaibles

    // clear the file
    fin.clear();

    // open the first file
    fin.open( highLevel );

    // check if is good
    if( fin.good() )
       {
        // close the previous file
        fin.close();

        // clear the file
        fin.clear();

        // open the second file
        fin.open( lowLevel );

        // check if is good
        if( fin.good() )
           {
            // close the previous file
            fin.close();

            // clear the file
            fin.clear();

            // open the third file
            fin.open( midLevel );

            // check if is good
            if( fin.good() )
               {
                // close file
                fin.close();

                // return false
                return false;

               }
           }
       }

    // close file
    fin.close();

    // return true
    return true;
   }

void displayErrorMessage()
   {
    // Intialize Varaibles
    int xPos = 0, yPos=0;

    // Clear the screen and turn it into a black
       // function: setColor
       setColor(  COLOR_YELLOW, COLOR_BLACK, SET_BRIGHT ); 
       clearScreen( 0, 0, 79, 79);  
    
    // Clear the screen and turn it into blue instead
      // function: setColor 
      setColor(  COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );  
      clearScreen( 19, 9, 63 ,15);  

    // Print the error message at the appropriate x and y position
      // function: printStringAt
      xPos = 39, yPos = 10;
      printStringAt(xPos, yPos, "ERROR MESSAGE WINDOW", "CENTER");

    // Print what the problem really is, and set the x and y coordinates
       // function: printStringAt
       xPos = 40, yPos = 12;
       printStringAt(xPos, yPos, "Maps not found, game play aborted", "CENTER");

    // Hold the message for the user 
       // function: waitForInput
       xPos = 48, yPos = 14;
       setColor(  COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );  
       printStringAt(xPos, yPos, "Press any key to continue", "CENTER");
       waitForInput( FIXED_WAIT );

   }

char changeMap( ifstream &fin, char mapName[], short mapArr[][ MAP_ARRAY_COLUMN_SIZE ], char high[], char mid[] )
   {
    // initialize function/variables
    int rowCounter, colCounter;
    int xIndex, yIndex;
    int column, row;
    int randomXValue, randomYValue;
    char currentLevel;

    // set color and clear screen
    setColor( COLOR_BLUE, COLOR_WHITE, SET_BRIGHT );
    clearScreen(18, 1, 78, 23 );

    // reset map array to 0
    for( rowCounter = 0; rowCounter < 50; rowCounter++ )
       {
        for( colCounter = 0; colCounter < 80; colCounter++ )
           {
            mapArr[ rowCounter ] [ colCounter ] = 0;
           }
       }

    // clear for input
    fin.clear();

    // open input file
    fin.open( mapName );

    // loop while file is good
    while( fin.good() )
      {
       // input x index
       fin >> xIndex;

       // input y index
       fin >> yIndex;

       // assign wall symbol to corresponding point
       mapArr[ yIndex + 1 ][ xIndex + 17 ] = WALL;
      }

    // loop while row index is less than 30
    for( row = 0; row <= 30; row++ )
       {
        // loop while column index is less than 79
        for( column = 0; column <= 79; column++ )
           {
            // check if wall symbol is contained in spot
            if( mapArr[ row ][ column ] == WALL )
               {
                // if so, print it on the screen
                printSpecialCharAt( column, row, WALL );
               }

       // end loop
           }

    // end loop
       }

    // set color for u and d characters
    setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );

    // if map is the high level, generate a random down staircase
    if( strcmp( mapName, high ) == 0 )
       {
        // generate random x and y values
        randomXValue = rand() % 60 + 18;
        randomYValue = rand() % 22 + 1;

        // generate new values until they don't overlap walls
        while( mapArr[ randomYValue ][ randomXValue ] == WALL )
           {
            randomXValue = rand() % 60 + 18;
            randomYValue = rand() % 22 + 1;
           }

        // display and record values
        printSpecialCharAt( randomXValue, randomYValue, BIG_D );
        mapArr[ randomYValue ][ randomXValue ] = BIG_D;

        // assign currentLevel h
        currentLevel = 'h';
       }

    // otherwise if it is the mid level, generate up and down staircases
    else if( strcmp( mapName, mid ) == 0 )
       {
        // generate random x and y values for down
        randomXValue = rand() % 60 + 18;
        randomYValue = rand() % 22 + 1;

        // generate new values until they don't overlap walls
        while( mapArr[ randomYValue ][ randomXValue ] == WALL )
           {
            randomXValue = rand() % 60 + 18;
            randomYValue = rand() % 22 + 1;
           }

        // display and record values
        printSpecialCharAt( randomXValue, randomYValue, BIG_D );
        mapArr[ randomYValue ][ randomXValue ] = BIG_D;
           
        // generate random x and y values for up
        randomXValue = rand() % 60 + 18;
        randomYValue = rand() % 22 + 1;

        // generate new values until they don't overlap walls
        while( mapArr[ randomYValue ][ randomXValue ] == WALL )
           {
            randomXValue = rand() % 60 + 18;
            randomYValue = rand() % 22 + 1;
           }

        // display and record values
        printSpecialCharAt( randomXValue, randomYValue, BIG_U );
        mapArr[ randomYValue ][ randomXValue ] = BIG_U;
           
        // assign current level m
        currentLevel = 'm';
       }
    // otherwise generate a random up staircase
    else
       {
        // generate random x and y values
        randomXValue = rand() % 60 + 18;
        randomYValue = rand() % 22 + 1;

        // generate new values until they don't overlap walls
        while( mapArr[ randomYValue ][ randomXValue ] == WALL )
           {
            randomXValue = rand() % 60 + 18;
            randomYValue = rand() % 22 + 1;
           }

        // display and record values
        printSpecialCharAt( randomXValue, randomYValue, BIG_U );
        mapArr[ randomYValue ][ randomXValue ] = BIG_U;

        // assign current level l
        currentLevel = 'l';
       }

    // close file
    fin.close();

    // return current level
    return currentLevel;
   }

int percentageGenerator()
   {
    // initialize function/variables
    int randomNumber;

    // generate random number between 1-100
    randomNumber = rand() % 99 + 1;

    // return number
    return randomNumber;
   }

void displayOccurances( int percent, char splashValue, short mapArr[][ MAP_ARRAY_COLUMN_SIZE ], int xLoc, int yLoc )
   {
    // initialize function/variables
    int randomXValue, randomYValue;

    // possibly display hole
    if( percent <= 35 )
       {
        // change the color
        setColor( COLOR_RED, COLOR_WHITE, SET_BRIGHT );

        // generate random values for x and y
        randomXValue = rand() % 60 + 18;
        randomYValue = rand() % 22 + 1;

        // check if values don't overlap walls, spells, treasure, swords, cloaks, or monsters
        if( mapArr[ randomYValue ][ randomXValue ] != WALL && mapArr[ randomYValue ][ randomXValue ] != SPELL
               && mapArr[ randomYValue ][ randomXValue ] != TREASURE && mapArr[ randomYValue ][ randomXValue ] !=  SWORD
                  && mapArr[ randomYValue ][ randomXValue ] != CLOAK && mapArr[ randomYValue ][ randomXValue ] != MONSTER )
           {
            printSpecialCharAt( randomXValue, randomYValue, HOLE );
            mapArr[ randomYValue ][ randomXValue ] = HOLE;
           }

       }

    // possibly display treasure
    if( percent <= 5 )
       {
        // change the color
        setColor( COLOR_YELLOW, COLOR_WHITE, SET_BRIGHT );

        // generate random values for x and y
        randomXValue = rand() % 60 + 18;
        randomYValue = rand() % 22 + 1;

        // check if values don't overlap walls, spells, holes, swords, cloaks, or monsters
        if( mapArr[ randomYValue ][ randomXValue ] != WALL && mapArr[ randomYValue ][ randomXValue ] != SPELL
               && mapArr[ randomYValue ][ randomXValue ] != HOLE && mapArr[ randomYValue ][ randomXValue ] !=  SWORD
                  && mapArr[ randomYValue ][ randomXValue ] != CLOAK && mapArr[ randomYValue ][ randomXValue ] != MONSTER )
           {
            printSpecialCharAt( randomXValue, randomYValue, TREASURE );
            mapArr[ randomYValue ][ randomXValue ] = TREASURE;
           }

       }

    // possibly display cloak
    if( percent <= 10 )
       {
        // change the color
        setColor( COLOR_GREEN, COLOR_WHITE, SET_BRIGHT );

        // generate random values for x and y
        randomXValue = rand() % 60 + 18;
        randomYValue = rand() % 22 + 1;

        // check if values don't overlap walls, spells, holes, swords, holes, or monsters
        if( mapArr[ randomYValue ][ randomXValue ] != WALL && mapArr[ randomYValue ][ randomXValue ] != SPELL
               && mapArr[ randomYValue ][ randomXValue ] != TREASURE && mapArr[ randomYValue ][ randomXValue ] !=  SWORD
                  && mapArr[ randomYValue ][ randomXValue ] != HOLE && mapArr[ randomYValue ][ randomXValue ] != MONSTER )
           {
            printSpecialCharAt( randomXValue, randomYValue, CLOAK );
            mapArr[ randomYValue ][ randomXValue ] = CLOAK;
           }

       }

    // check if exra credit was chosen
    if( splashValue == 'e' )
       {
        // possibly display sword 
        if( percent <= 10 )
           {
            // change the color
            setColor( COLOR_GREEN, COLOR_WHITE, SET_BRIGHT );

            // generate random values for x and y
            randomXValue = rand() % 60 + 18;
            randomYValue = rand() % 22 + 1;

        // check if values don't overlap walls, spells, treasure, holes, cloaks, or monsters
        if( mapArr[ randomYValue ][ randomXValue ] != WALL && mapArr[ randomYValue ][ randomXValue ] != SPELL
               && mapArr[ randomYValue ][ randomXValue ] != TREASURE && mapArr[ randomYValue ][ randomXValue ] !=  HOLE
                  && mapArr[ randomYValue ][ randomXValue ] != CLOAK && mapArr[ randomYValue ][ randomXValue ] != MONSTER )
               {
                printSpecialCharAt( randomXValue, randomYValue, SWORD );
                mapArr[ randomYValue ][ randomXValue ] = SWORD;
               }

           }

        // possibly display monster
        if( percent <= 25 )
           {
            // change the color
            setColor( COLOR_RED, COLOR_WHITE, SET_BRIGHT );

            // generate random values for x and y
            randomXValue = rand() % 60 + 18;
            randomYValue = rand() % 22 + 1;

        // check if values don't overlap walls, spells, treasure, swords, cloaks, or holes
        if( mapArr[ randomYValue ][ randomXValue ] != WALL && mapArr[ randomYValue ][ randomXValue ] != SPELL
               && mapArr[ randomYValue ][ randomXValue ] != TREASURE && mapArr[ randomYValue ][ randomXValue ] !=  SWORD
                  && mapArr[ randomYValue ][ randomXValue ] != CLOAK && mapArr[ randomYValue ][ randomXValue ] != HOLE )
               {
                printSpecialCharAt( randomXValue, randomYValue, MONSTER );
                mapArr[ randomYValue ][ randomXValue ] = MONSTER;
               }

           }

        // possibly display spell
        if( percent <= 10 )
           {
            // change the color
            setColor( COLOR_GREEN, COLOR_WHITE, SET_BRIGHT );

            // generate random values for x and y
            randomXValue = rand() % 60 + 18;
            randomYValue = rand() % 22 + 1;

        // check if values don't overlap walls, holes, treasure, swords, cloaks, or monsters
        if( mapArr[ randomYValue ][ randomXValue ] != WALL && mapArr[ randomYValue ][ randomXValue ] != HOLE
               && mapArr[ randomYValue ][ randomXValue ] != TREASURE && mapArr[ randomYValue ][ randomXValue ] !=  SWORD
                  && mapArr[ randomYValue ][ randomXValue ] != CLOAK && mapArr[ randomYValue ][ randomXValue ] != MONSTER )
               {
                printSpecialCharAt( randomXValue, randomYValue, SPELL );
                mapArr[ randomYValue ][ randomXValue ] = SPELL;
               }

           }

       }
   }

bool sideCounter( char splashInput, int xValue, int yValue, short mapArr[][ MAP_ARRAY_COLUMN_SIZE ], int &score,
                  int &cloak, int &treasure, int &spell, int &sword )
   {
    // Initialize Variables
    int xPos = 0, yPos = 0;

    // check if player ran over treasure
    if( mapArr[ yValue ][ xValue ] == TREASURE )
       {
        // if so, increment score by 5 and treasure count by 1
        score += 5;
        treasure += 1;

        // cover upt spot
        mapArr[ yValue ][ xValue ] = 0;
       }

    // check if player ran over a cloak
    if( mapArr[ yValue ][ xValue ] == CLOAK )
       {
        // if so, increment score and cloak count by 1
        cloak += 1;
        score += 1;

        // cover upt spot
        mapArr[ yValue ][ xValue ] = 0;
       }

    // check if player ran over a hole
    if( mapArr[ yValue ][ xValue ] == HOLE )
       {
        // check if player has a cloak
        if( cloak > 0 )
           {
            // if so, decrement score and cloak count by one
            cloak -= 1;
            score -= 1;

            // cover upt spot
            mapArr[ yValue ][ xValue ] = 0;
           }

        // otherwise
        else
           {
            // display the game over message
            setColor( COLOR_YELLOW, COLOR_RED, SET_BRIGHT );
            clearScreen( GAME_ENDS_BOX_MIN_X, GAME_ENDS_BOX_MIN_Y, GAME_ENDS_BOX_MAX_X, GAME_ENDS_BOX_MAX_Y );
            printStringAt( GAME_ENDS_TOP_X, GAME_ENDS_TOP_Y, "GAME", "LEFT" );
            printStringAt( GAME_ENDS_BOTTOM_X, GAME_ENDS_BOTTOM_Y, "ENDS", "LEFT" );
            waitForInput( FIXED_WAIT );

            // return false
            return false;
           }
       }

    // check if player ran over a spell
    if( mapArr[ yValue ][ xValue ] == SPELL )
       {
        // if so, increase score and count by 1
        spell += 1;
        score += 1;

        // cover up spot
        mapArr[ yValue ][ xValue ] = 0;
       }

    // check if player ran over a sword
    if( mapArr[ yValue ][ xValue ] == SWORD )
       {
        // if so, increase score and count by 1
        sword += 1;
        score += 1;

        // cover up spot
        mapArr[ yValue ][ xValue ] = 0;
       }

    // check if player ran over a monster
    if( mapArr[ yValue ][ xValue ] == MONSTER )
       {
        // check if player has a sword
        if( sword > 0 )
           {
            // if so, decrement score and sword count by one
            sword -= 1;
            score -= 1;

            // cover up spot
            mapArr[ yValue ][ xValue ] = 0;
           }

        // otherwise
        else
           {
            // display the game over message
               // function: setColor, clearScreen, printStringAt, waitForInput
               setColor( COLOR_YELLOW, COLOR_RED, SET_BRIGHT );
               clearScreen( GAME_ENDS_BOX_MIN_X, GAME_ENDS_BOX_MIN_Y, GAME_ENDS_BOX_MAX_X, GAME_ENDS_BOX_MAX_Y );
               printStringAt( GAME_ENDS_TOP_X, GAME_ENDS_TOP_Y, "GAME", "LEFT" );
               printStringAt( GAME_ENDS_BOTTOM_X, GAME_ENDS_BOTTOM_Y, "ENDS", "LEFT" );
               waitForInput( FIXED_WAIT );

            // return false
            return false;
           }
       }

    // Set the color to the side box
    setColor( COLOR_WHITE, COLOR_BLUE, SET_BRIGHT );
    
    // Clear the screen and then set up a box
    clearScreen( SIDEBAR_MIN_X, SIDEBAR_MIN_Y, SIDEBAR_MAX_X, SIDEBAR_MAX_Y );

    // Set the x Pos and Y Pos to the start of the title
    xPos = 7, yPos = 1;
    
    // Print the title of the side counter
    printStringAt( xPos, yPos, "ROGUE-LIKE", "CENTER" );

    // Reset X and y to print out cloak and its value
       // prinStringAt
       xPos = 2, yPos = 4;
       printStringAt( xPos, yPos, "Cloak: ", "LEFT" );
       printIntAt( xPos + 7, yPos, cloak, "CENTER" );

    // check if extra credit version was entered
    if( splashInput == 'e' )
       // if so, display extra credit version
       {
        // reset X and y to print out sword and its value
           // PrintStringAt
           xPos = 2, yPos = 5;
           printStringAt( xPos, yPos, "Sword: ", "LEFT" );
           printIntAt( xPos + 7, yPos, sword, "CENTER" );

        // reset X and y to print out spell and its value
           // PrintStringAt
           xPos = 2, yPos = 6;
           printStringAt( xPos, yPos, "Spell: ", "LEFT" );
           printIntAt( xPos + 7, yPos, spell, "CENTER" );

        // reset X and y to print out Treasure and its value
           // PrintStringAt
           xPos = 2, yPos = 8;
           printStringAt( xPos, yPos, "Treasure: ", "LEFT" );
           printIntAt( xPos + 10, yPos, treasure, "CENTER" );

       // Reset X and y to print out Score and its value
          // PrintStringAt
          xPos = 2, yPos = 10;
          printStringAt( xPos, yPos, "Score: ", "LEFT" );
          printIntAt( xPos + 7, yPos, score, "CENTER" );

       // Print the rest of the instructions, after setting x and y
          // printStringAt
          xPos = 7, yPos =12;
          printStringAt( xPos, yPos, "Arrows set", "CENTER" );
          yPos ++;
          printStringAt( xPos, yPos, "direction", "CENTER" ); 
    
       // Print out the other set of instructions after setting x and y
          // function: printStringAt
          xPos = 7, yPos = 15;
          printStringAt( xPos, yPos, "Follow U/D", "CENTER" );
          yPos ++;
          printStringAt( xPos, yPos, "to change", "CENTER" );
          xPos = 7, yPos ++;
          printStringAt( xPos, yPos, "level", "CENTER" );
 
       // Print out the other set of instructions after setting x and y
          // function: printString At
          xPos = 7, yPos = 19;
          printStringAt( xPos, yPos, "Falling into", "CENTER" );
          xPos = 7, yPos = 20;
          printStringAt( xPos, yPos, "a hole or", "CENTER" );
          xPos = 7, yPos = 21;
          printStringAt( xPos, yPos, "pressing ESC", "CENTER" );
          xPos = 7, yPos =22; 
          printStringAt( xPos, yPos, "ends game", "CENTER" );
       }

    // otherwise display the regular version
    else
       {
        // reset X and y to print out Treasure and its value
           // PrintStringAt
           xPos = 2, yPos = 6;
           printStringAt( xPos, yPos, "Treasure: ", "LEFT" );
           printIntAt( xPos + 10, yPos, treasure, "CENTER" );

       // Reset X and y to print out Score and its value
          // PrintStringAt
          xPos = 2, yPos = 8;
          printStringAt( xPos, yPos, "Score: ", "LEFT" );
          printIntAt( xPos + 7, yPos, score, "CENTER" );

       // Print the rest of the instructions, after setting x and y
          // printStringAt
          xPos = 7, yPos =12;
          printStringAt( xPos, yPos, "Arrows set", "CENTER" );
          yPos ++;
          printStringAt( xPos, yPos, "direction", "CENTER" ); 
    
       // Print out the other set of instructions after setting x and y
          // function: printStringAt
          xPos = 7, yPos = 15;
          printStringAt( xPos, yPos, "Follow U/D", "CENTER" );
          yPos ++;
          printStringAt( xPos, yPos, "to change", "CENTER" );
          xPos = 7, yPos ++;
          printStringAt( xPos, yPos, "level", "CENTER" );
 
       // Print out the other set of instructions after setting x and y
          // function: printString At
          xPos = 7, yPos = 19;
          printStringAt( xPos, yPos, "Falling into", "CENTER" );
          xPos = 7, yPos = 20;
          printStringAt( xPos, yPos, "a hole or", "CENTER" );
          xPos = 7, yPos = 21;
          printStringAt( xPos, yPos, "pressing ESC", "CENTER" );
          xPos = 7, yPos =22; 
          printStringAt( xPos, yPos, "ends game", "CENTER" );
      }

    // return true
    return true;
   }

int findScore(ifstream &fileIn, char playersArr[][ MAX_NAME_SIZE ], int arr[], int playerScore, char playerName[])
   {
    // initialize function/variables
    char player[100], dummy, fileName[11] = "scores.txt";
    int  index=0, count =0, score =0;

fileIn.clear();
fileIn.open( fileName );

     // input the score
      fileIn >> score;  

     // loop while file is good
       while(fileIn.good())
       {
         // assign arr at index to score
        arr[index] = score; 
   

        // take in the dummy
        fileIn >> dummy;

        // clear the player character array and take int the name
        clearCharArray(player, 100); 

           // loop until reach null char
        fileIn >> player;

        // place player into the list of players
        strcpy(playersArr[index], player);

        // increment the index and count
        index++;
        count ++;
        // input the next score
        fileIn >>score;
        }

    // close the file
    fileIn.close();

    // check if there is a player name entered
    if( playerName[0] != NULL_CHAR )
       {
        // check if the idex is less than 10
        if( index < 10 )
           {
            // assign the player score to arr at index
            arr[ index ] = playerScore;

            // copy the player name to playersArr
            strcpy( playersArr[ index ], playerName );

            // increment the counter
            count++;
           }

        // check if index is or is greater than 10 and that the score is greater than the last score
        else if( index >= 10 && playerScore > arr[ index - 1 ] )
           {
            // replace the last score with the new score
            arr[ index - 1 ] = playerScore;
            strcpy( playersArr[ index - 1 ], playerName );
           }
       }
    // return the count
    return count++;
   }

void clearCharArray( char testArr[], int amount)
{
    //variables
    int index=0;

    // iterate through whole digit array
    while(index<amount)
      {
      // set each element to NULL_CHARACTER
      testArr[index]= NULL_CHAR;
      
      //update
      index++;
      }
}

void openTheScoreAndNames(ofstream &output, char playersArr[][ MAX_NAME_SIZE ], int arr[], int size)
   {
    // Initialize function/variables
    int index=0, score;
    char fileName[12]= "scores.txt";
    char comma = ',';
    
    // clear and open the file
    output.open(fileName);

    // loop while index is less than size
    while(index< size)
       {
        // assign score arr at index
        score = arr[ index ];

        // output the score, a comma, the player name, and an end line
        output << score;
        output << comma;
        output << playersArr[index];
        output << endl;

        // increment the index
        index++;              
       }

    // close file
    output.close();
   }

void bubbleSort( int arr[], int size, char src[][ MAX_NAME_SIZE ] )
   {
    // initialize function/variables
    int row, column;

    // loop while row is less than max size
    for( row = 0; row < 10; row++)
       {
        // loop while column is less than row
        for(column=0;column<row;column++)
           {
            // check if the array at row > the array at column
            if(arr[row]>arr[column])
               {   
                //swap scores
                int temp=arr[row]; 
                arr[row]=arr[column];
                arr[column]=temp;

                // swap names
                swap( src[row], src[column]); 
               }

           }

       }

   }

void clearIntArray(int arr[], int size)
   {
    // initialize function/variables
    int index=0;

    // iterate through whole digit array as long as index is less than amount
    while( index < size )
       {
       // set each element to the null character
       arr[ index ]= NULL_CHAR;
      
       //update the index
       index++;
      }

   }


