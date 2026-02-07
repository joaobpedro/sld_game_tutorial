// need some guards here
#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "tile.h"
#include "globals.h"
/* #include <string> */
/* #include <fstream> */

// this is the player class, it contains necessary data
// to make the charater move, render and interact with the world

class Dot
{
    public:
        //The dimensions of the dot
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;

        //Maximum axis velocity of the dot
        static const int DOT_VEL = 10;

        //Initializes the variables
        Dot();

        //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e );

        //Moves the dot and check collision against tiles
        void move( Tile *tiles[] );

        //Centers the camera over the dot
        void setCamera( SDL_Rect& camera );

        //Shows the dot on the screen
        void render( SDL_Rect& camera );

    private:
        //Collision box of the dot
        SDL_Rect mBox;

        //The velocity of the dot
        int mVelX, mVelY;
};

#endif //exit class
