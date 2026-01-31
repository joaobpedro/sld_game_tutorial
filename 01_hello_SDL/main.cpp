#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Texture wrapper class
class LTexture {
public:
  // Initializes variables
  LTexture();

  // Deallocates memory
  ~LTexture();

  // Loads image at specified path
  bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
  // Creates image from font string
  bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

  // Deallocates texture
  void free();

  // Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  // Set blending
  void setBlendMode(SDL_BlendMode blending);

  // Set alpha modulation
  void setAlpha(Uint8 alpha);

  // Renders texture at given point
  void render(int x, int y, SDL_FRect *clip = NULL, double angle = 0.0,
              SDL_FPoint *center = NULL, SDL_FlipMode flip = SDL_FLIP_NONE);

  // Gets image dimensions
  int getWidth();
  int getHeight();

private:
  // The actual hardware texture
  SDL_Texture *mTexture;

  // Image dimensions
  int mWidth;
  int mHeight;
};

// The application time based timer
class LTimer {
public:
  // Initializes variables
  LTimer();

  // The various clock actions
  void start();
  void stop();
  void pause();
  void unpause();

  // Gets the timer's time
  Uint64 getTicks();

  // Checks the status of the timer
  bool isStarted();
  bool isPaused();

private:
  // The clock time when the timer started
  Uint64 mStartTicks;

  // The ticks stored when the timer was paused
  Uint64 mPausedTicks;

  // The timer status
  bool mPaused;
  bool mStarted;
};

// The dot that will move around on the screen
class Dot {
public:
  // The dimensions of the dot
  static const int DOT_WIDTH = 20;
  static const int DOT_HEIGHT = 20;

  // Maximum axis velocity of the dot
  static const int DOT_VEL = 10;

  // Initializes the variables
  Dot();

  // Takes key presses and adjusts the dot's velocity
  void handleEvent(SDL_Event &e);

  // Moves the dot
  void move();

  // Shows the dot on the screen
  void render();

private:
  // The X and Y offsets of the dot
  int mPosX, mPosY;

  // The velocity of the dot
  int mVelX, mVelY;
};

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

// Scene textures
LTexture gDotTexture;

LTexture::LTexture() {
  // Initialize
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

LTexture::~LTexture() {
  // Deallocate
  free();
}

bool LTexture::loadFromFile(std::string path) {
  // Get rid of preexisting texture
  free();

  // The final texture
  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL) {
    SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
            SDL_GetError());
  } else {
    // Color key image
    SDL_SetSurfaceColorKey(loadedSurface, true,
                           SDL_MapSurfaceRGB(loadedSurface, 0, 0xFF, 0xFF));

    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
      SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
              SDL_GetError());
    } else {
      // Get image dimensions
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }

    // Get rid of old loaded surface
    SDL_DestroySurface(loadedSurface);
  }

  // Return success
  mTexture = newTexture;
  return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool LTexture::loadFromRenderedText(std::string textureText,
                                    SDL_Color textColor) {
  // Get rid of preexisting texture
  free();

  // Render text surface
  SDL_Surface *textSurface =
      TTF_RenderText_Blended(gFont, textureText.c_str(), 0, textColor);
  if (textSurface != NULL) {
    // Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (mTexture == NULL) {
      SDL_Log("Unable to create texture from rendered text! SDL Error: %s\n",
              SDL_GetError());
    } else {
      // Get image dimensions
      mWidth = textSurface->w;
      mHeight = textSurface->h;
    }

    // Get rid of old surface
    SDL_DestroySurface(textSurface);
  } else {
    SDL_Log("Unable to render text surface! SDL_ttf Error: %s\n",
            SDL_GetError());
  }

  // Return success
  return mTexture != NULL;
}
#endif

void LTexture::free() {
  // Free texture if it exists
  if (mTexture != NULL) {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
  // Modulate texture rgb
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending) {
  // Set blending function
  SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha) {
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_FRect *clip, double angle,
                      SDL_FPoint *center, SDL_FlipMode flip) {
  // Set rendering space and render to screen
  SDL_FRect renderQuad = {(float)x, (float)y, (float)mWidth, (float)mHeight};

  // Set clip rendering dimensions
  if (clip != NULL) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  // Render to screen
  SDL_RenderTextureRotated(gRenderer, mTexture, clip, &renderQuad, angle,
                           center, flip);
}

int LTexture::getWidth() { return mWidth; }

int LTexture::getHeight() { return mHeight; }

Dot::Dot() {
  // Initialize the offsets
  mPosX = 0;
  mPosY = 0;

  // Initialize the velocity
  mVelX = 0;
  mVelY = 0;
}

void Dot::handleEvent(SDL_Event &e) {
  // If a key was pressed
  if (e.type == SDL_EVENT_KEY_DOWN && e.key.repeat == 0) {
    // Adjust the velocity
    switch (e.key.key) {
    case SDLK_UP:
      mVelY -= DOT_VEL;
      break;
    case SDLK_DOWN:
      mVelY += DOT_VEL;
      break;
    case SDLK_LEFT:
      mVelX -= DOT_VEL;
      break;
    case SDLK_RIGHT:
      mVelX += DOT_VEL;
      break;
    }
  }
  // If a key was released
  else if (e.type == SDL_EVENT_KEY_UP && e.key.repeat == 0) {
    // Adjust the velocity
    switch (e.key.key) {
    case SDLK_UP:
      mVelY += DOT_VEL;
      break;
    case SDLK_DOWN:
      mVelY -= DOT_VEL;
      break;
    case SDLK_LEFT:
      mVelX += DOT_VEL;
      break;
    case SDLK_RIGHT:
      mVelX -= DOT_VEL;
      break;
    }
  }
}

void Dot::move() {
  // Move the dot left or right
  mPosX += mVelX;

  // If the dot went too far to the left or right
  if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH)) {
    // Move back
    mPosX -= mVelX;
  }

  // Move the dot up or down
  mPosY += mVelY;

  // If the dot went too far up or down
  if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT)) {
    // Move back
    mPosY -= mVelY;
  }
}

void Dot::render() {
  // Show the dot
  gDotTexture.render(mPosX, mPosY);
}

bool init() {
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Create window and renderer
    if (!SDL_CreateWindowAndRenderer("SDL Tutorial", SCREEN_WIDTH,
                                     SCREEN_HEIGHT, 0, &gWindow, &gRenderer)) {
      SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      // Enable vsync
      SDL_SetRenderVSync(gRenderer, 1);

      // Initialize renderer color
      SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
  }

  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;

  // Load dot texture
  if (!gDotTexture.loadFromFile("churro_game_main.bmp")) {
    SDL_Log("Failed to load dot texture!\n");
    success = false;
  }

  return success;
}

void close() {
  // Free loaded images
  gDotTexture.free();

  // Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}

int main(int argc, char *args[]) {
  // Start up SDL and create window
  if (!init()) {
    SDL_Log("Failed to initialize!\n");
  } else {
    // Load media
    if (!loadMedia()) {
      SDL_Log("Failed to load media!\n");
    } else {
      // Main loop flag
      bool quit = false;

      // Event handler
      SDL_Event e;

      // The dot that will be moving around on the screen
      Dot dot;

      // While application is running
      while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
          // User requests quit
          if (e.type == SDL_EVENT_QUIT) {
            quit = true;
          }

          // Handle input for the dot
          dot.handleEvent(e);
        }

        // Move the dot
        dot.move();

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render objects
        dot.render();

        // Update screen
        SDL_RenderPresent(gRenderer);
      }
    }
  }

  // Free resources and close SDL
  close();

  return 0;
}
