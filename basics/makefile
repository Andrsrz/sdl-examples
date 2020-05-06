##
# SDL 2 Basics
#
# @file
CC = g++
STD = -std=c++17
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2
OBJS1 = initializing-sdl.cpp
OBJ_NAME1 = initializing-sdl

.BASICS: all initializing-sdl
all: initializing-sdl
initializing-sdl: $(OBJ_NAME1)

$(OBJ_NAME1): $(OBJS1)
	$(CC) $(COMPILER_FLAGS) $(OBJS1) $(LINKER_FLAGS) -o $(OBJ_NAME1)
# end
