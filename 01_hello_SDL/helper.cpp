#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <fstream>
#include <string>
#include <random>

#include "globals.h"
#include "helper.h"
#include "texture.h"
#include "tile.h"
#include "entity.h"

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

// Scene textures
LTexture gTileTexture;
const int TOTAL_TILE_SPRITES = 12;
SDL_FRect gTileClips[TOTAL_TILE_SPRITES];

// math helper
int getRandomInt(int min, int max) {
    // static ensures the engine is only initialized once for the whole program
    static std::random_device rd; 
    static std::mt19937 gen(rd()); 

    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// get grid valid points.


bool init() {
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window and renderer
        if (!SDL_CreateWindowAndRenderer("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gWindow, &gRenderer)) {
            printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Enable vsync
            SDL_SetRenderVSync(gRenderer, 1);

            // Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        }
        // initialize sound
    }

    return success;
}

bool loadMedia(Tile *tiles[], valid_tiles *spawn_tiles, Things_Manager* things) {
    bool success = true;

    // Load tile texture
    if (!gTileTexture.loadFromFile("../Assets/forest_tiles_small.png")) {
        printf("Failed to load tile set texture!\n");
        success = false;
    }

    // Load tile map
    if (!setTiles(tiles, spawn_tiles)) {
        printf("Failed to load tile set!\n");
        success = false;
    }

    for (int I = 1; I < MAX_NUMBER_THINGS; I++) {
        if(things->Used[I] == 1) {
            if(!things->Things[I].texture.loadFromFile(things->Things[I].path)) {
                printf("Failed to load tile set texture!\n");
                success = false;
            }
        }
    }

    return success;
}

// passing pointers so I can erase the data
void close(Tile *tiles[], Things_Manager* things) {
    // Deallocate tiles
    for (int i = 0; i < TOTAL_TILES; ++i) {
        if (tiles[i] != NULL) {
            delete tiles[i];
            tiles[i] = NULL;
        }
    }

    // Free loaded images
    for (auto thing : things->Things) {
        thing.texture.free();
    }
    gTileTexture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    SDL_Quit();
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // If any of the sides from A are outside of B
    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    // If none of the sides from A are outside B
    return true;
}

bool setTiles(Tile *tiles[], valid_tiles *spawn_tiles) {
    // Success flag
    bool tilesLoaded = true;

    // The tile offsets
    int x = 0, y = 0;

    // Open the map
    std::ifstream map("../Assets/lazy.map");

    // If the map couldn't be loaded
    if (map.fail()) {
        printf("Unable to load map file!\n");
        tilesLoaded = false;
    } else {
        // Initialize the tiles
        for (int i = 0; i < TOTAL_TILES; ++i) {
            // Determines what kind of tile will be made
            int tileType = -1;

            // Read tile from map file
            map >> tileType;

            // If the was a problem in reading the map
            if (map.fail()) {
                // Stop loading map
                printf("Error loading map: Unexpected end of file!\n");
                tilesLoaded = false;
                break;
            }

            // If the number is a valid tile number
            if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES)) {
                tiles[i] = new Tile(x, y, tileType);
                if (tileType == 0 || tileType == 1 || tileType == 2){
                    spawn_tiles->isvalid[spawn_tiles->valid_count+1] = 1;
                    spawn_tiles->x[spawn_tiles->valid_count+1] = x + TILE_WIDTH/2; // this points to the center of the tile
                    spawn_tiles->y[spawn_tiles->valid_count+1] = y + TILE_HEIGHT/2;
                    spawn_tiles->valid_count++;
                }
                // } else {
                //     spawn_tiles->isvalid[i] = 0;
                //     spawn_tiles->x[i] = 0;
                //     spawn_tiles->y[i] = 0;
                // }
            }
            // If we don't recognize the tile type
            else {
                // Stop loading map
                printf("Error loading map: Invalid tile type at %d!\n", i);
                tilesLoaded = false;
                break;
            }

            // Move to next tile spot
            x += TILE_WIDTH;

            // If we've gone too far
            if (x >= LEVEL_WIDTH) {
                // Move back
                x = 0;

                // Move to the next row
                y += TILE_HEIGHT;
            }
        }

        // Clip the sprite sheet
        if (tilesLoaded) {
            gTileClips[TILE_RED].x = 0;
            gTileClips[TILE_RED].y = 0;
            gTileClips[TILE_RED].w = TILE_WIDTH;
            gTileClips[TILE_RED].h = TILE_HEIGHT;

            gTileClips[TILE_GREEN].x = 0;
            gTileClips[TILE_GREEN].y = 80;
            gTileClips[TILE_GREEN].w = TILE_WIDTH;
            gTileClips[TILE_GREEN].h = TILE_HEIGHT;

            gTileClips[TILE_BLUE].x = 0;
            gTileClips[TILE_BLUE].y = 160;
            gTileClips[TILE_BLUE].w = TILE_WIDTH;
            gTileClips[TILE_BLUE].h = TILE_HEIGHT;

            gTileClips[TILE_TOPLEFT].x = 80;
            gTileClips[TILE_TOPLEFT].y = 0;
            gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
            gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

            gTileClips[TILE_LEFT].x = 80;
            gTileClips[TILE_LEFT].y = 80;
            gTileClips[TILE_LEFT].w = TILE_WIDTH;
            gTileClips[TILE_LEFT].h = TILE_HEIGHT;

            gTileClips[TILE_BOTTOMLEFT].x = 80;
            gTileClips[TILE_BOTTOMLEFT].y = 160;
            gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
            gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

            gTileClips[TILE_TOP].x = 160;
            gTileClips[TILE_TOP].y = 0;
            gTileClips[TILE_TOP].w = TILE_WIDTH;
            gTileClips[TILE_TOP].h = TILE_HEIGHT;

            gTileClips[TILE_CENTER].x = 160;
            gTileClips[TILE_CENTER].y = 80;
            gTileClips[TILE_CENTER].w = TILE_WIDTH;
            gTileClips[TILE_CENTER].h = TILE_HEIGHT;

            gTileClips[TILE_BOTTOM].x = 160;
            gTileClips[TILE_BOTTOM].y = 160;
            gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
            gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

            gTileClips[TILE_TOPRIGHT].x = 240;
            gTileClips[TILE_TOPRIGHT].y = 0;
            gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
            gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

            gTileClips[TILE_RIGHT].x = 240;
            gTileClips[TILE_RIGHT].y = 80;
            gTileClips[TILE_RIGHT].w = TILE_WIDTH;
            gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

            gTileClips[TILE_BOTTOMRIGHT].x = 240;
            gTileClips[TILE_BOTTOMRIGHT].y = 160;
            gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
            gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;
        }
    }

    // Close the file
    map.close();

    // If the map was loaded fine
    return tilesLoaded;
}

bool touchesWall(SDL_Rect box, Tile *tiles[]) {
    // Go through the tiles
    for (int i = 0; i < TOTAL_TILES; ++i) {
        // If the tile is a wall type tile
        if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT)) {
            // If the collision box touches the wall tile
            if (checkCollision(box, tiles[i]->getBox())) {
                return true;
            }
        }
    }

    // If no wall tiles were touched
    return false;
}

void render(Things_Manager* things, SDL_Rect &camera) {
    for (int I = 1; I < MAX_NUMBER_THINGS; I++) {
        if(things->Used[I] == 1) {
            things->Things[I].texture.render(things->Things[I].Box.x - camera.x, things->Things[I].Box.y - camera.y, &things->Things[I].CurrentClip);
        }
    }
}

void handleEvent(SDL_Event &e, Things_Manager *things) {
    for (int I = 1; I < MAX_NUMBER_THINGS; I++){
        if (things->Used[I] == 1 && things->Things[I].kind == Kind::Player){
            // If a key was pressed
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.repeat == 0) {
                // Adjust the velocity
                switch (e.key.key) {
                    case SDLK_UP:
                        things->Things[I].VelY -= 5*STD_VEL;
                        break;
                    case SDLK_DOWN:
                        things->Things[I].VelY += 5*STD_VEL;
                        break;
                    case SDLK_LEFT:
                        things->Things[I].VelX -= 5*STD_VEL;
                        break;
                    case SDLK_RIGHT:
                        things->Things[I].VelX += 5*STD_VEL;
                        break;
                }
            }
            // If a key was released
            else if (e.type == SDL_EVENT_KEY_UP && e.key.repeat == 0) {
                // Adjust the velocity
                switch (e.key.key) {
                    case SDLK_UP:
                        things->Things[I].VelY += 5*STD_VEL;
                        break;
                    case SDLK_DOWN:
                        things->Things[I].VelY -= 5*STD_VEL;
                        break;
                    case SDLK_LEFT:
                        things->Things[I].VelX += 5*STD_VEL;
                        break;
                    case SDLK_RIGHT:
                        things->Things[I].VelX -= 5*STD_VEL;
                        break;
                }
            }
        }
    }
}
void move(Tile *tiles[], Things_Manager *things) {
    for (int I = 1; I < MAX_NUMBER_THINGS; I++) {
        if (things->Used[I]==1 && things->Things[I].kind == Kind::Player){
            // Move the dot left or right
            things->Things[I].Box.x += things->Things[I].VelX;

            // If the dot went too far to the left or right or touched a wall
            if ((things->Things[I].Box.x < 0) || (things->Things[I].Box.x + things->Things[I].Box.w > LEVEL_WIDTH) || touchesWall(things->Things[I].Box, tiles)) {
                // move back
                things->Things[I].Box.x -= things->Things[I].VelX;
            }

            // Move the dot up or down
            things->Things[I].Box.y += things->Things[I].VelY;

            // If the dot went too far up or down or touched a wall
            if ((things->Things[I].Box.y < 0) || (things->Things[I].Box.y + things->Things[I].Box.w > LEVEL_HEIGHT) || touchesWall(things->Things[I].Box, tiles)) {
                // move back
                things->Things[I].Box.y -= things->Things[I].VelY;
            }
        } else if (things->Used[I]==1 && things->Things[I].kind == Kind::Monster){
            things->Things[I].Box.x += things->Things[I].VelX;

            // If the dot went too far to the left or right or touched a wall
            if ((things->Things[I].Box.x < 0) || (things->Things[I].Box.x + things->Things[I].Box.w > LEVEL_WIDTH) || touchesWall(things->Things[I].Box, tiles)) {
            // move back
                things->Things[I].VelX = -1*things->Things[I].VelX;
            }

            // Move the dot up or down
            things->Things[I].Box.y += things->Things[I].VelY;

            // If the dot went too far up or down or touched a wall
            if ((things->Things[I].Box.y < 0) || (things->Things[I].Box.y + things->Things[I].Box.h > LEVEL_HEIGHT) || touchesWall(things->Things[I].Box, tiles)) {
                // move back
                things->Things[I].VelY = -1*things->Things[I].VelY;
            }
        }
    }
}

void setCamera(SDL_Rect &camera, Things_Manager *things) {
    // Center the camera over the dot
    // HARDCODED the payer index is hard coded
    camera.x = (things->Things[1].Box.x + things->Things[1].Box.w / 2) - SCREEN_WIDTH / 2;
    camera.y = (things->Things[1].Box.y + things->Things[1].Box.h / 2) - SCREEN_HEIGHT / 2;

    // Keep the camera in bounds
    if (camera.x < 0) {
        camera.x = 0;
    }
    if (camera.y < 0) {
        camera.y = 0;
    }
    if (camera.x > LEVEL_WIDTH - camera.w) {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h) {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void kill_monster(Things_Manager *things) {
    for (int I = 2; I < MAX_NUMBER_THINGS; I++) {
        if (things->Used[I] == 1){
            if (checkCollision(things->Things[1].Box, things->Things[I].Box)) {
                things->Things[I].health -= 5;
                if (things->Things[I].health <= 0){
                    things->Used[I] == 0;
                    things->Things[I] = Thing();
                    things->MonsterCount--;
                }
            }
        }
    }

}

void spawn_monster(Things_Manager *things, valid_tiles *spawn_tiles){
    for (int I = 2; I < MAX_NUMBER_THINGS; I++) {
        if (things->Used[I] == 0 && things->MonsterCount < MAX_NUMBER_OF_MONSTERS){
            things->Things[I].kind = Kind::Monster;
            int random_entry = getRandomInt(1, spawn_tiles->valid_count);
            things->Things[I].Box = {spawn_tiles->x[random_entry],spawn_tiles->y[random_entry]};
            things->Things[I].Box.w = 32;
            things->Things[I].Box.h = 32;
            things->Things[I].health = 100;
            things->Things[I].VelX = 1;
            things->Things[I].VelY = 1;
            things->Things[I].path = "../Assets/monster.png";
            things->Used[I] = 1;
            things->MonsterCount++;
        }
    }
};

// animate any thing
void animate(int &frame, SDL_FRect &currentClip) {
    // this is just the selection of the sprite clip to show given a frame
    if (frame / WalkingAnimationsFramesperSprite >= WalkingAnimationFrames) {
        frame = 0;
    }

    // HARDCODED this frames per animation needs to come from somewhere,
    // but right now is hard coded, its my cabin anyway
    SDL_FRect spriteClips[6] = {
        {SpriteWidth * 0, 0.f, SpriteWidth, SpriteHeight},
        {SpriteWidth * 1 + padding, 0.f, SpriteWidth, SpriteHeight},
        {SpriteWidth * 2 + 2 * padding, 0.f, SpriteWidth, SpriteHeight},
        {SpriteWidth * 3 + 3 * padding, 0.f, SpriteWidth, SpriteHeight},
        {SpriteWidth * 4 + 4 * padding, 0.f, SpriteWidth, SpriteHeight},
        {SpriteWidth * 5 + 5 * padding, 0.f, SpriteWidth, SpriteHeight},
    };
    // Set sprite clips
    currentClip = spriteClips[frame / WalkingAnimationsFramesperSprite];
};
