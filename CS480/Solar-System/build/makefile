# Linux
CC=g++ -w
LIBS= -lglut -lGLEW -lGL -lGLU -lassimp -lMagick++

# For Macs uncomment the next line and comment out the previous one
#CC=clang++
#LIBS=  -framework OpenGL -framework GLUT -framework Cocoa -lGLEW -stdlib=libc++
# Assuming you want to use a recent compiler

# Compiler flags
CXXFLAGS=  -g -std=c++0x
LDFLAGS = `Magick++-config --cppflags --cxxflags --ldflags --libs`

all: ../bin/Solar

../bin/Solar: ../src/shader.cpp ../src/main.cpp
	$(CC) $(CXXFLAGS) ../src/shader.cpp ../src/main.cpp -o ../bin/Solar $(LDFLAGS) $(LIBS)

clean:
	rm -rf *.o ../bin/Solar
