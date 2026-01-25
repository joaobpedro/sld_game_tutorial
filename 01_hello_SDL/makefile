#OBJS specify the files to compile
OBJS = main.cpp

# compiler name
cc = g++

# compilers flags
COMPILER_FLAGS = -w

#sdl2 lib requirement
LIBSDL = `sdl2-config --cflags --libs`

#linker flags
LINKER_FLAG = -lSDL2

# OBJ_NAME specifies the target name
OBJ_NAME = game

all : $(OBJS)
	$(cc) $(OBJS) $(COMPILER_FLAGS) $(LIBSDL) $(LINKER_FLAGS) -o $(OBJ_NAME)
