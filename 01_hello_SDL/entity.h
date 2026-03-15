#ifndef ENTITY_H_
#define ENTITY_H_

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "texture.h"

// this will be an array of structs
#define MAX_NUMBER_THINGS 1000
#define MAX_NUMBER_PLAYERS 1
#define MAX_NUMBER_OF_MONSTERS 5
#define MAX_NUMBER_OF_TREES 30
#define MAX_NUMBER_OF_WEAPONS 300

// right now I am not using this for anything
struct ThingRef {
    int Idx;
    int Gen;

    static ThingRef nil() {
        return {0,0};
    }
};

// all kinds of things in my game
enum class Kind {
    Nil,
    Player,
    Monster,
    Weapon,
    Tree,
    // Tile,
};

struct Thing {
    // thing ref

    ThingRef ref;

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
    float kSpriteWidth{32}; 
    float kSpriteHeight{32}; 
    // float padding; 
    // int kWakingAnimationFrames; 
    // int kWakingAnimationFramesPerSprite; 

    // rendering
    SDL_FRect CurrentClip;
    LTexture texture;

    // just to manage my fixed array of things
    // FIXME i am not using these at all right now
    ThingRef Parent;
    ThingRef FirstChild;
    ThingRef NextSibling;
    ThingRef PrevSibling;

};

struct Things_Manager {

    Thing Things[MAX_NUMBER_THINGS];
    int Used[MAX_NUMBER_THINGS];
    int Gen[MAX_NUMBER_THINGS];
    int NextFree;
    int LastFree;
    int ThingsCount;
    int MonsterCount;

    ThingRef add_things(Kind kind){
        int slot = find_empty(kind);
        if(slot) {
            Things[slot] = Thing{};
            Things[slot].kind = kind;
            Used[slot] = 1;
            Gen[slot] += 1;
            if(kind == Kind::Monster) {
                MonsterCount++;
            }
            return {slot, Gen[slot]};
        } else {
            return ThingRef::nil();
        }
    };
    
    void remove(ThingRef ref) {
        int slot = deref(ref);
        Used[slot] = 0;
        if(Things[slot].kind == Kind::Monster){
            MonsterCount--;
        }
    }

    Thing& get(ThingRef ref){
        return Things[deref(ref)];
    };

    private: 

    int find_empty(Kind kind){
        switch(kind) {
            case Kind::Player:
                for (int I = 0 + 1; I<=MAX_NUMBER_PLAYERS; ++I){
                    if (Used[I] == 0) {
                        return I;
                    }        
                }
            case Kind::Monster:
                for (int I = 0 + 1 + MAX_NUMBER_PLAYERS; I<=MAX_NUMBER_OF_MONSTERS + 1; ++I){
                    if (Used[I] == 0) {
                        return I;
                    } 
                }
            case Kind::Tree:
                for (int I = 0 + 1 + MAX_NUMBER_PLAYERS + MAX_NUMBER_OF_MONSTERS; I<=MAX_NUMBER_OF_TREES + 1; ++I){
                    if (Used[I] == 0) {
                        return I;
                    }
                }
            case Kind::Weapon:
                for (int I = 0 + 1 + MAX_NUMBER_PLAYERS + MAX_NUMBER_OF_MONSTERS + MAX_NUMBER_OF_TREES; I<=MAX_NUMBER_OF_WEAPONS + 1; ++I){
                    if (Used[I] == 0) {
                        return I;
                    }
                }
            case Kind::Nil:
                return 0;
        }
        // for (int I = 1; I<MAX_NUMBER_THINGS; ++I){
        //     if (Used[I] == 0) {
        //         return I;
        //     }
        // }
        return 0;
    };

    int deref(ThingRef ref) {
        if(ref.Idx > 0 && ref.Idx < MAX_NUMBER_THINGS && Used[ref.Idx] && ref.Gen == Gen[ref.Idx]){
            return ref.Idx;
        } else {
            return 0;
        }
    }
};

#endif
