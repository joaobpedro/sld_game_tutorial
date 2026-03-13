#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "texture.h"

// this will be an array of structs
#define MAX_NUMBER_THINGS 1000
#define MAX_NUMBER_OF_MONSTERS 30

// FIXME right now I am not using this for anything
struct thing_ref {
    int thingIdx;
    int thingGen;
};

// all kinds of things in my game
enum class Kind {
    Nil,
    Player,
    Monster,
    // Tile,
};

struct Thing {
    // things kind
    Kind kind;

    // collision data
    SDL_Rect Box;

    // game data
    // dont need width and height these are part of the box
    int VelX;
    int VelY;
    float health;

    // asset data
    const char* path;

    // animation data
    // NOTE I made these globals, which means that all things
    // will need the same sprite structure
    // if I want thing specific sprite this is the way
    // float kSpriteWidth; 
    // float kSpriteHeight; 
    // float padding; 
    // int kWakingAnimationFrames; 
    // int kWakingAnimationFramesPerSprite; 

    // rendering
    SDL_FRect CurrentClip;
    LTexture texture;

    // just to manage my fixed array of things
    // FIXME i am not using these at all right now
    thing_ref Parent;
    thing_ref FirstChild;
    thing_ref NextSibling;
    thing_ref PrevSibling;

};

struct Things_Manager {

    Thing Things[MAX_NUMBER_THINGS];
    int Used[MAX_NUMBER_THINGS];
    int NextFree;
    int LastFree;
    int ThingsCount;
    int MonsterCount;

    void update_array(int Things[], int size);
};

#endif
