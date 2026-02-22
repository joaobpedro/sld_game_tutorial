#ifndef TEXTURE_H_
#define TEXTURE_H_

#include<SDL3_mixer/SDL_mixer.h>

//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

//The dimensions of the level
extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

//Tile constants
extern const int TILE_WIDTH;
extern const int TILE_HEIGHT;
extern const int TOTAL_TILES;
// extern constexpr int TOTAL_TILE_SPRITES;

//The different tile sprites
extern const int TILE_RED;
extern const int TILE_GREEN;
extern const int TILE_BLUE;
extern const int TILE_CENTER;
extern const int TILE_TOP;
extern const int TILE_TOPRIGHT;
extern const int TILE_RIGHT;
extern const int TILE_BOTTOMRIGHT;
extern const int TILE_BOTTOM;
extern const int TILE_BOTTOMLEFT;
extern const int TILE_LEFT ;
extern const int TILE_TOPLEFT ;

// music variable

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
#endif
