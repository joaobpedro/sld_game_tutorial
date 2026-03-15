#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <fstream>
#include <random>

#include "globals.h"
#include "texture.h"
#include "tile.h"
#include "entity.h"

// lets make a global struct to hold the good tile
struct valid_tiles {
    int isvalid[TOTAL_TILES];
    int x[TOTAL_TILES];
    int y[TOTAL_TILES];
    int valid_count;
};

// generates random numbers
int getRandomInt(int min, int max); 

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[], valid_tiles *spawn_tiles, Things_Manager *things);

//Frees media and shuts down SDL
void close( Tile* tiles[] ,Things_Manager *things);

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//Checks collision box against set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile *tiles[], valid_tiles *spawn_tiles);

// render all objects
void render(Things_Manager* things, SDL_Rect &camera);

// handle events for the Player
void handleEvent(SDL_Event &e,Things_Manager *things);

// move the things
void move(Tile *tiles[], Things_Manager *things);

// the camera follows the player
void setCamera(SDL_Rect &camera, Things_Manager *things);

// kill monster by touching
void kill_monster(Things_Manager *things, MIX_Mixer* mixer, MIX_Audio* deathSound);

// spawn new monsters so we can keep playing
void spawn_monster(Things_Manager *things, valid_tiles *spawn_tiles);

// create heapon for churro to traw
void weapon(Things_Manager *things);

// animate sprites
void animate(int &frame, SDL_FRect &currentClip, const Thing& thing);

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Scene textures
extern LTexture gTileTexture;
extern SDL_FRect gTileClips[];


// implementation below
