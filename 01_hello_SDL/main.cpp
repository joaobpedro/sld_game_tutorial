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

        // create Churro
        things.Things[1].kind = Kind::Player;
        things.Things[1].Box = {0,0};
        things.Things[1].Box.w = 32;
        things.Things[1].Box.h = 32;
        things.Things[1].path = "../Assets/churro_standing.png";
        things.Used[1] = 1;
        
        for (int J = 2; J < 20; J++){
            things.Things[J].kind = Kind::Monster;
            things.Things[J].Box = {getRandomInt(1,200),getRandomInt(1,200)};
            things.Things[J].Box.w = 32;
            things.Things[J].Box.h = 32;
            things.Things[J].health = 100;
            things.Things[J].VelX = 1;
            things.Things[J].VelY = 1;
            things.Things[J].path = "../Assets/monster.png";
            things.Used[J] = 1;
        }

        // Load media
        if (!loadMedia(tileSet, &things)) {
            printf("Failed to load media!\n");
        } 

        SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        bool quit = false;
        SDL_Event e;

        int frame{-1};

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
        }
        close(tileSet, &things);
    }
    return 0;
}
