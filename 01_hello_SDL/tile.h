#ifndef TILE_H_
#define TILE_H_

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
/* #include <string> */
/* #include <fstream> */
#include "globals.h"

class Tile
{
    public:
        //Initializes position and type
        Tile( int x, int y, int tileType );

        //Shows the tile
        void render( SDL_Rect& camera );

        //Get the tile type
        int getType();

        //Get the collision box
        SDL_Rect getBox();

    private:
        //The attributes of the tile
        SDL_Rect mBox;

        //The tile type
        int mType;
};

#endif
