#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "texture.h"

// this will be an array of structs
#define MAX_NUMBER_THINGS 1024

struct thing_ref {
    int thingIdx;
    int thingGen;
};

// all kinds of things in my game
enum class Kind {
    Nil,
    Player,
    Monster,
    Tile,
};

struct Thing {
    // things kind
    Kind kind;

    // collision data
    SDL_Rect mBox;

    // game data
    int width;
    int height;
    int velX;
    int velY;
    float health;

    // asset data
    char* path;

    // animation data
    float kSpriteWidth; 
    float kSpriteHeight; 
    float padding; 
    int kWakingAnimationFrames; 
    int kWakingAnimationFramesPerSprite; 

    // rendering
    LTexture texture;

    // just to manage my fixed array of things
    thing_ref Parent;
    thing_ref FirstChild;
    thing_ref NextSibling;
    thing_ref PrevSibling;

};

struct Things_Manager {

    int Things[MAX_NUMBER_THINGS];
    int Used[MAX_NUMBER_THINGS];
    int NextFree;
    int LastFree;
    int ThingsCount;

    void update_array(int Things[], int size);
};

#endif
