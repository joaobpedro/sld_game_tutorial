#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "globals.h"
#include "helper.h"
#include "tile.h"
#include "entity.h"
#include "vector.h"

Things_Manager things;


int main() {
    if (!init()) {
        return 1;
    } else {
        // The level tiles
        Tile *tileSet[TOTAL_TILES];
        valid_tiles spawn_tiles;

        // create Churro
        things.Things[1].kind = Kind::Player;
        things.Things[1].Box = {0,0}; // the player alway starts at this position
        things.Things[1].Box.w = 32;
        things.Things[1].Box.h = 42;
        things.Things[1].path = "../Assets/flying_churro1-sheet32.png";
        things.Used[1] = 1;
        
        for (int J = 2; J < MAX_NUMBER_OF_MONSTERS; J++){
            things.Things[J].kind = Kind::Monster;
            things.Things[J].Box.w = 32;
            things.Things[J].Box.h = 32;
            things.Things[J].health = 100;
            things.Things[J].VelX = 1;
            things.Things[J].VelY = 1;
            things.Things[J].path = "../Assets/monster.png";
            things.Used[J] = 1;
            things.MonsterCount++;
        }

        // Load media
        if (!loadMedia(tileSet, &spawn_tiles, &things)) {
            printf("Failed to load media!\n");
        } 

        SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        bool quit = false;
        SDL_Event e;

        int frame{-1};

        // now I can place the monsters because now I have the tiles setted
        for (int I = 2; I<MAX_NUMBER_OF_MONSTERS; I++){
            int random_entry = getRandomInt(1, spawn_tiles.valid_count);
            things.Things[I].Box = {spawn_tiles.x[random_entry], spawn_tiles.y[random_entry]};
        }

        while (!quit) {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                // User requests quit
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
                handleEvent(e, &things);
            }
            move(tileSet, &things);
            setCamera(camera, &things);
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            for (int i = 0; i < TOTAL_TILES; ++i) {
                tileSet[i]->render(camera);
            }
            kill_monster(&things);
            for (int I = 1; I<MAX_NUMBER_THINGS; I++){
                if(things.Used[I] == 1){
                    animate(frame, things.Things[I].CurrentClip);
                }
            }
            render(&things, camera);
            SDL_RenderPresent(gRenderer);
            frame++;
            // spawn monsters here if the monster count is less than a number
            spawn_monster(&things, &spawn_tiles);
        }
        close(tileSet, &things);
    }
    return 0;
}
