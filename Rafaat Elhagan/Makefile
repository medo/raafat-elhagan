CPP_FILES := $(shell find . -name "*.cpp" )
COMPILE_FLAGS := -lglut -lGL -lGLU -lGLEW -lm -lpthread -std=c++11
MAC_COMPILE_FLAGS := -framework GLUT -framework OpenGL -framework Cocoa -lm -lpthread -std=c++11
EXECUTABLE_NAME := main.bin

all:
	g++ $(CPP_FILES) -o $(EXECUTABLE_NAME) $(COMPILE_FLAGS)

mac:
	g++ $(CPP_FILES) -o $(EXECUTABLE_NAME) $(MAC_COMPILE_FLAGS)
