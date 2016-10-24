PA9 - Air Hockey
================
-Group
	Zeeshan Sajid, Vance Piscitelli

Note: This is the program that should be graded.

Objective
---------
To win, a player must be the first to score three goals on the other player’s goal. Goals are made by hitting the puck with the player’s paddle such that it moves into the goal. An AI can be enabled to play as the yellow puck.

Extra Credit
------------
For extra credit, we have sound effects, a top 10 scores history, Text2D displayed, Game replay, 
changeable puck shape with correct physics, changeable paddle shape, a simple and toggleable AI, 
and changeable names.

Required Libraries
------------------
In order to compile and run this program, some additional programs/libraries must be downloaded and installed. For more information on these programs/libraries, see the Technical Manual. These programs/libraries are:
Magick++, Assimp, OpenGl, Bullet, Irrklang Audio Library

Compiling the Program
---------------------
To compile the program, from the build folder:	
		make 

Or from the PA7 folder type:
		make -C ./build

Or from the bin folder type:
		make -C ../build

Executing the Program
---------------------
To run the program, from the bin folder, type: 	./Hockey
To change the players' names, type in the first name of each player as a command line argument
e.g. ./Hockey Vance Zeeshan
Where the first argument is the left (yellow) player's name 
and the second argument is the right (red) player's name.

User Controls
-------------

	Right-click: Brings up our menu

	Start - Can start the game from the title menu, or unpause the game while playing
	Stop - Pauses the game while playing, pieces do not move
	Replay - Starts a new game allowing the player to replay the game without exiting. 
	Change paddle/Puck shape - Toggles puck/paddles between circles and squares.
	Show Top Scores - Shows the topScore menu if and only if user is on the title Screen
	Reset Board - Resets the board, but not the scores.
	Quit - Ends the program, writing the top scores to a file before exiting.
	Keyboard:

	'WASD': 
		The 'W' key moves the yellow paddle up.
		The 'A' key moves the yellow paddle left.
		The 'S' key moves the yellow paddle down.
		The 'D' key moves the yellow paddle right.
		The 'F' key stops the yellow paddle
		The 'G' key speeds up the yellow paddle

	'Arrow Keys’: 
		Up key moves the red paddle up.
		Down key moves the red paddle down.
		Right key moves the red paddle right.
		Left key moves the red paddle left.
		The '/' key speeds up the red paddle
		The '.' key stops the red paddle

	'9': Goes to the top Score menu
	'r': Goes back to the title menu at any point and resets the game
	'Space': Goes to game screen
	'p': Changes paddles to squares
	';': Changes puck to a square
	'\': Disables ai or enables
	'1': Top-down view
	'2': Angled view
	'3': Angled view and follows puck

	Mouse controls:
		While holding down the left mouse button, 
		the mouse controls the direction of the right (red) paddle.
	
	Camera controls:
		'U': Increments the X-position of the camera
		'J': Decrements the X-position of the camera
		'I': Decrements the Y-position of the camera
		'K': Increments the Y-position of the camera
		'O': Increments the Z-position of the camera
		'L': Decrements the Z-position of the camera

	Esc Key: Quits the game entirely

Installation Instructions
-------------------------
For help installing any of the libraries, see our technical manual.

