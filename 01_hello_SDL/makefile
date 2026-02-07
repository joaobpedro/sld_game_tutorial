#OBJS specify the files to compile
# OBJS = main.cpp
OBJS1 = 14-animation.cpp
OBJS2 = 14-animation.cpp

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

all : $(OBJS1)
	$(cc) $(OBJS1) $(COMPILER_FLAGS) $(LIBSDL) $(LINKER_FLAGS) -o $(OBJ_NAME)

# all : $(OBJS2)
# 	$(cc) $(OBJS2) $(COMPILER_FLAGS) $(LIBSDL) $(LINKER_FLAGS) -o $(OBJ_NAME)
