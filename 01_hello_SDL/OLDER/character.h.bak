// need some guards here
#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "tile.h"
// #include "globals.h"
/* #include <string> */
/* #include <fstream> */

// this is the player class, it contains necessary data
// to make the charater move, render and interact with the world

class character
{
    public:
        //The dimensions of the dot
        static const int DOT_WIDTH = 60;
        static const int DOT_HEIGHT = 60;

        //Maximum axis velocity of the dot
        static const int DOT_VEL = 7;

        //Initializes the variables
        character();

        //Takes key presses and adjusts the dot's velocity
        void handleEvent( SDL_Event& e );

        //Moves the dot and check collision against tiles
        void move( Tile *tiles[] );

        //Centers the camera over the dot
        void setCamera( SDL_Rect& camera );

        //Shows the dot on the screen
        void render( SDL_Rect& camera, SDL_FRect* clip );

        // animate churro
        void animate(int& frame, SDL_FRect& currentClip);

        // return churros positions
        SDL_Rect get_position();

    private:
        //Collision box of the dot
        SDL_Rect mBox;

        //The velocity of the dot
        int mVelX, mVelY;

        const float mkSpriteWidth {1};
        const float mkSpriteHeight {60};
        const float mpadding {1};
        const int mkWakingAnimationFrames {6};
        const int mkWakingAnimationFramesPerSprite {6};

        int m_movement{0};
};

#endif //exit class
