CPP_FILES := $(shell find . -name "*.cpp" )
COMPILE_FLAGS := -lglut -lGL -lGLU -lGLEW -std=c++11
EXECUTABLE_NAME := main.bin

all:
	g++ $(CPP_FILES) -o $(EXECUTABLE_NAME) $(COMPILE_FLAGS)
