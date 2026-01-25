#include <SDL.h>
#include <stdio.h>

// const for the screen dimension
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {

  // the window we will render too
  SDL_Window *window = NULL;

  // the surface conataining the window
  SDL_Surface *screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL ERROR: %s\n", SDL_GetError());
  } else {
    // create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window not created: %s", SDL_GetError());
    } else {
      // get window surface
      screenSurface = SDL_GetWindowSurface(window);

      // fill the surface
      SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

      SDL_UpdateWindowSurface(window);

      SDL_Event e; bool quit = false; while (quit==false){while (SDL_PollEvent(&e)) {if (e.type ==SDL_QUIT) quit=true;}}
    }
  }

  //destroy the window
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
