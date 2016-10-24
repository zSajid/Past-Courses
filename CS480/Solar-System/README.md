PA7 - Solar System
============================
-Group
	Zeeshan Sajid, Vance Piscitelli

Note: This is the program that should be graded.

Compile
-------
- cd build; make clean, make

Run 
---
- cd bin; ./bin/Solar
- run from the PA7 and not from bin

Easy Compiling/Running notes
----------------------------
To compile from the main project folder:
	make -C ./build
To run the executable after compiling from the main project folder:
	./bin/Solar 

Controls
--------
- Right clicking opens up the menu
	- Start Rotation: Stars the rotations of the planet if stop rotations was clicked
	- Stop Rotations: Stops the rotation if the rotation is turned on
	- Toggle Scale: Changes the scale, so all planets have relative distance when clicked upon, and vice versa. From the start everything is scaled accurately
	- Quit: Escapes the program

- Keyboard:
		- 0 = Have the camera look at the Sun
		- 1 = Have the camera look at Mercury
		- 2 = Have the camera look at Venus
		- 3 = Have the camera look at Earth
		- 4 = Have the camera look at Mars
		- 5 = Have the camera look at Jupiter
		- 6 = Have the camera look at Saturn
		- 7 = Have the camera look at Uranus
		- 8 = Have the camera look at Neptune
		- 9 = Have the camera look at Pluto
		- * = Have the camera look at next. So if on Sun, it looks at moon. If on Pluto, it looks at the first moon which is Earth's if recalled correctly and so on.
		- + = Changes to global so the individual can look at the whole thing from top down and see everything in action

		-Up arrow: Essentially just zooms in 
		-Down arrow: Zooms out

		-Scroll wheel: Another way to zoom in and out

-Esc key:
		Escapes the game

Magick++ Installation Instructions
----------------------------------

In your .cpp file, include:
#include <Magick++.h>

And initialize in main:
Magick :: InitializeMagick(*argv);

In the makefile, add LDFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`
and then add LDFlAGS to the compilation line like this :
$(CC) $(CXXFLAGS) ../src/shader.cpp ../src/main.cpp -o ../bin/Solar $(LDFLAGS)

Also, don't forget to add -lMagick++ to the LIBS to use. 

Install these libraries with sudo apt-get install:
(These are the libraries installed on the ECC computers)
libgraphicsmagick3
libgraphicsmagick1-dev
libgraphics-magick-perl
libgraphicsmagick++1-dev
libmagickcore5-extra
libmagickwand5
imagemagick
libgraphicsmagick++3
graphicsmagick-libmagick-dev-compat
libmagickcore5
imagemagick-common

Or you can follow the installation instructions from:
http://www.imagemagick.org

Extra Credit
------------
Each planet has its own orbit path being drawn.
By opening up the menu and selecting toggle scale, the user can switch from actual data to a scaled view.
Saturn, Jupiter, Uranus, and Neptune all have their proper rings.

Overall Notes
-------------
-Added all the planets that are textured
-Added couple of the satellites, the ones that are somewhat important I guess you could say
-Extra credit has been done completely. All of the planets that need the rings have rings on them, and the orbit path has been calculated and drawn to the screen

