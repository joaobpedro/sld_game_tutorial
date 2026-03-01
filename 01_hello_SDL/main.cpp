#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_rect.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
// #include <string>
// #include <fstream>

// #include "character.h"
#include "globals.h"
#include "helper.h"
#include "tile.h"
#include "entity.h"
// #include "texture.h"

// need to remake the init
// the load media
// render

Things_Manager things;

// init one character

int main() {
    if (!init()) {
        return 1;
    } else {
        // The level tiles
        Tile *tileSet[TOTAL_TILES];

        // create Churro
        Thing Churro;
        Churro.kind = Kind::Player;
        Churro.Box = {0,0};
        Churro.width = 32;
        Churro.height = 32;
        Churro.path = "../Assets/churro_standing.png";
        things.Things[0] = Churro;
        things.Used[0] = 1;

        // Load media
        if (!loadMedia(tileSet, &things)) {
            printf("Failed to load media!\n");
        } 

        SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        bool quit = false;
        SDL_Event e;



        while (!quit) {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0) {
                // User requests quit
                if (e.type == SDL_EVENT_QUIT) {
                    quit = true;
                }
                handleEvent(e, &things);
                // printf("churro vel %d:", Churro.VelX);
            }
            move(tileSet, &things);
            setCamera(camera, &things);
            // printf("churro box %d:", Churro.Box.x);
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            for (int i = 0; i < TOTAL_TILES; ++i) {
                tileSet[i]->render(camera);
            }
            render(&things, camera, 0);
            SDL_RenderPresent(gRenderer);
        }
    }
    return 0;
}

// int OLDmain(int argc, char *args[]) {
//     // Start up SDL and create window
//     if (!init()) {
//         printf("Failed to initialize!\n");
//     } else {
//         // The level tiles
//         Tile *tileSet[TOTAL_TILES];
//
//         // Load media
//         if (!loadMedia(tileSet)) {
//             printf("Failed to load media!\n");
//         } else {
//             // Main loop flag
//             bool quit = false;
//
//             // Event handler
//             SDL_Event e;
//
//             // The dot that will be moving around on the screen
//             character churro;
//             Monster monster;
//
//             // Level camera
//             SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
//
//             int frame{-1};
//
//             // While application is running
//             while (!quit) {
//                 // Handle events on queue
//                 while (SDL_PollEvent(&e) != 0) {
//                     // User requests quit
//                     if (e.type == SDL_EVENT_QUIT) {
//                         quit = true;
//                     }
//
//                     // Handle input for the dot
//                     churro.handleEvent(e);
//                 }
//
//                 frame++;
//                 // printf("Frame number: %d \n", frame);
//
//                 // render monster
//
//                 // Move the dot
//                 churro.move(tileSet);
//                 churro.setCamera(camera);
//
//                 // check collision with churro
//                 SDL_Rect churro_position = churro.get_position();
//                 monster.move(tileSet, churro_position);
//
//                 // Clear screen
//                 SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
//                 SDL_RenderClear(gRenderer);
//
//                 // Render level
//                 for (int i = 0; i < TOTAL_TILES; ++i) {
//                     tileSet[i]->render(camera);
//                 }
//
//                 SDL_FRect monsterClip;
//                 monster.animate(frame, monsterClip);
//                 monster.render(camera, &monsterClip);
//
//                 // Render dot
//                 SDL_FRect currentClip;
//                 churro.animate(frame, currentClip);
//                 churro.render(camera, &currentClip);
//
//                 // Update screen
//                 SDL_RenderPresent(gRenderer);
//             }
//         }
//
//         // Free resources and close SDL
//         close(tileSet);
//     }
//
//     return 0;
// }
