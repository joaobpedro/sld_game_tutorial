// Using SDL, SDL_image, strings, and file streams
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
// #include <string>
// #include <fstream>

#include "character.h"
#include "globals.h"
#include "helper.h"
#include "tile.h"

int main(int argc, char *args[]) {
    // Start up SDL and create window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        // The level tiles
        Tile *tileSet[TOTAL_TILES];

        // Load media
        if (!loadMedia(tileSet)) {
            printf("Failed to load media!\n");
        } else {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // The dot that will be moving around on the screen
            character churro;

            // Level camera
            SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

            int frame{-1};

            // While application is running
            while (!quit) {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_EVENT_QUIT) {
                        quit = true;
                    }

                    // Handle input for the dot
                    churro.handleEvent(e);
                }

                frame++;
                // printf("Frame number: %d \n", frame);

                // Move the dot
                churro.move(tileSet);
                churro.setCamera(camera);
                // maybe dot.animate

                // Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // Render level
                for (int i = 0; i < TOTAL_TILES; ++i) {
                    tileSet[i]->render(camera);
                }

                // Render dot
                SDL_FRect currentClip;
                churro.animate(frame, currentClip);

                churro.render(camera, &currentClip);

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }

        // Free resources and close SDL
        close(tileSet);
    }

    return 0;
}
