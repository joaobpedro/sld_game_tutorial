#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <fstream>

#include "globals.h"
#include "texture.h"
#include "tile.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );

//Checks collision box against set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Scene textures
extern LTexture gCharacterTexture[];
extern LTexture gTileTexture;

extern SDL_FRect gTileClips[];
