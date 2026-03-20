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

int main(int argc, char* argv[]) {
    if (!init()) {
        return 1;
    } else {
        // The level tiles
        Tile *tileSet[TOTAL_TILES];
        valid_tiles spawn_tiles;
        spawn_tiles.valid_count = 0; // initializ the cout to zero

        // create Churro
        ThingRef PlayerIdx = things.add_things(Kind::Player);
        things.get(PlayerIdx).ref = PlayerIdx;
        things.get(PlayerIdx).Box = {0,0};
        things.get(PlayerIdx).Box.w = 42;
        things.get(PlayerIdx).Box.h = 32;
        things.get(PlayerIdx).kSpriteWidth = 42;
        things.get(PlayerIdx).kSpriteHeight= 32;
        things.get(PlayerIdx).path = "../Assets/flying_churro1-sheet32.png";
        
        for (int I = 2; I < MAX_NUMBER_OF_MONSTERS+2; I++){
            ThingRef MonsterIdx = things.add_things(Kind::Monster);
            things.get(MonsterIdx).ref = MonsterIdx;
            things.get(MonsterIdx).Box.w = 32;
            things.get(MonsterIdx).Box.h = 32;
            things.get(MonsterIdx).VelX = 1;
            things.get(MonsterIdx).VelY = 1;
            things.get(MonsterIdx).health = 100;
            things.get(MonsterIdx).path = "../Assets/monster.png";
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
        for (int I = 2; I<MAX_NUMBER_OF_MONSTERS+2; I++){
            int random_entry = getRandomInt(0, spawn_tiles.valid_count);
            things.Things[I].Box = {spawn_tiles.x[random_entry], spawn_tiles.y[random_entry]};
        }


        // deal with the audio stuff
        MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        if (!mixer) {
            printf("SDL Audio failed: %s\n", SDL_GetError());
            return -1;
        }
        // 4. Load the Background Music
        // The 'false' here is important! It means "Stream this from the hard drive."
        // For long music, you want 'false'. For short sound effects, use 'true' to pre-load them into RAM.
        MIX_Audio* bgmAudio = MIX_LoadAudio(mixer, "../Assets/Churros_dance.mp3", false);
    
        // 5. Create a Track to play the music on
        MIX_Track* bgmTrack = MIX_CreateTrack(mixer);
    
        // 6. Assign the music to the track
        MIX_SetTrackAudio(bgmTrack, bgmAudio);
    
        // 7. Play the music and tell it to loop!
        // SDL3 uses "Properties" to pass in extra settings like looping
        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1); // -1 means infinite loops
        MIX_PlayTrack(bgmTrack, props);
        
        SDL_DestroyProperties(props); // Clean up the properties object
        // load the killing sound
        MIX_Audio* deathSound = MIX_LoadAudio(mixer, "../Assets/powerup.wav", true);
        if (!deathSound) {
            printf("SDL Audio failed: %s\n", SDL_GetError());
            return -1;
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
            kill_monster(&things, mixer, deathSound);
            // spawn monsters here if the monster count is less than a number
            spawn_monster(&things, &spawn_tiles);
            for (int I = 1; I<MAX_NUMBER_THINGS; I++){
                if(things.Used[I] == 1){
                    animate(frame, things.Things[I].CurrentClip, things.Things[I]);
                }
            }
            render(&things, camera);
            SDL_RenderPresent(gRenderer);
            frame++;
        }
        MIX_DestroyAudio(deathSound);
        close(tileSet, &things);
    }
    return 0;
}
