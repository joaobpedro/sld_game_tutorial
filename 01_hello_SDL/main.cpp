#include <SDL.h>
#include <stdio.h>
#include <string>

// const for the screen dimension
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gXOut = NULL;
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* gCurrentSurface = NULL;


// function prototypes
bool init();

bool loadMedia();

void close();


SDL_Surface* loadSurface(std::string path);


bool init(){
    bool success = true;

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        printf("Error %s", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL){
            printf("Error %s", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
   return success;
};

bool loadMedia(){
    bool success = true;

    gXOut = SDL_LoadBMP("./x.bmp");
    if (gXOut == NULL) {
        printf("Error %s", SDL_GetError());
        success = false;
    }

    return success;
};

void close() {
    SDL_FreeSurface(gXOut);
    gXOut = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
};

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("%s", SDL_GetError());        
    }

    return loadedSurface;
}

int main(int argc, char *args[]) {
    // start up SDL
    if (!init()){
        printf("Failed to initialize\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media\n");
        } else {
            // event handling

            bool quit = false;
            SDL_Event e;

            while (!quit) {
                while (SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT) {
                        quit = true;
                    }
                    SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
                    SDL_UpdateWindowSurface(gWindow);
                }
            }
        }
    }

    close();
    return 0;


}
