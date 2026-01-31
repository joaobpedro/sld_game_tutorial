#OBJS specify the files to compile
OBJS = main.cpp

# compiler name
cc = g++

# compilers flags
COMPILER_FLAGS = -g -w

#sdl2 lib requirement
LIBSDL = `pkg-config --cflags --libs sdl3 sdl3-image`

#linker flags
LINKER_FLAGS = -lSDL3 -lSDL3_image

# OBJ_NAME specifies the target name
OBJ_NAME = game

all : $(OBJS)
	$(cc) $(OBJS) $(COMPILER_FLAGS) $(LIBSDL) $(LINKER_FLAGS) -o $(OBJ_NAME)
