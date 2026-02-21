// eed ome guards here
#ifndef MONSTER_H_
#define MONSTER_H_
// #include "globals.h"
#include "tile.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
// #include <fstream>
// #include <string>
// this is the player class, it contains necessary data
// to make the charater move, render and interact with the world

class Monster {
  public:
    // The dimensions of the dot
    static const int MONSTER_WIDTH = 32;
    static const int MONSTER_HEIGHT = 32;

    // Initializes the variables
    Monster();

    // Takes key presses and adjusts the dot's velocity
    /* void handleEvent( SDL_Event& e ); */

    // Moves the dot and check collision against tiles
    void move(Tile *tiles[], SDL_Rect character_pos);

    // Centers the camera over the dot
    /* void setCamera( SDL_Rect& camera ); */

    // Shows the dot on the screen
    void render(SDL_Rect &camera, SDL_FRect *clip);

    // animate churro
    void animate(int &frame, SDL_FRect &currentClip);

    // check collision with churro
    void collision_character(SDL_Rect churros_box);

  private:
    // Collision box of the dot
    SDL_Rect mBox;

    double m_health = 100;

    // The velocity of the dot
    int mVelX, mVelY;

    const float mkSpriteWidth{32};
    const float mkSpriteHeight{32};
    const float mpadding{0};
    const int mkWakingAnimationFrames{6};
    const int mkWakingAnimationFramesPerSprite{6};
};

#endif // exit class
