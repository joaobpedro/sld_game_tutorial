#include "monster.h"
#include "globals.h"
#include "helper.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
// #include <fstream>

Monster::Monster() {
    // Initialize the collision box
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = MONSTER_WIDTH;
    mBox.h = MONSTER_HEIGHT;

    // Initialize the velocity
    mVelX = 3;
    mVelY = 1;
}

// void monster::handleEvent(SDL_Event &e) {
//     // If a key was pressed
//     if (e.type == SDL_EVENT_KEY_DOWN && e.key.repeat == 0) {
//         // Adjust the velocity
//         switch (e.key.key) {
//         case SDLK_UP:
//             mVelY -= DOT_VEL;
//             break;
//         case SDLK_DOWN:
//             mVelY += DOT_VEL;
//             break;
//         case SDLK_LEFT:
//             mVelX -= DOT_VEL;
//             break;
//         case SDLK_RIGHT:
//             mVelX += DOT_VEL;
//             break;
//         }
//     }
//     // If a key was released
//     else if (e.type == SDL_EVENT_KEY_UP && e.key.repeat == 0) {
//         // Adjust the velocity
//         switch (e.key.key) {
//         case SDLK_UP:
//             mVelY += DOT_VEL;
//             break;
//         case SDLK_DOWN:
//             mVelY -= DOT_VEL;
//             break;
//         case SDLK_LEFT:
//             mVelX += DOT_VEL;
//             break;
//         case SDLK_RIGHT:
//             mVelX -= DOT_VEL;
//             break;
//         }
//     }
// }

void Monster::animate(int &frame, SDL_FRect &currentClip) {
    // this is just the selection of the sprite clip to show given a frame
    if (frame / mkWakingAnimationFramesPerSprite >= mkWakingAnimationFrames) {
        frame = 0;
    }

    // this should be mkWakingAnimationFrames but clangd is complaining that this is variable
    // so I am hardcoding this to 6
    SDL_FRect spriteClips[6] = {
        {mkSpriteWidth * 0, 0.f, mkSpriteWidth, mkSpriteHeight},
        {mkSpriteWidth * 1 + mpadding, 0.f, mkSpriteWidth, mkSpriteHeight},
        {mkSpriteWidth * 2 + 2 * mpadding, 0.f, mkSpriteWidth, mkSpriteHeight},
        {mkSpriteWidth * 3 + 3 * mpadding, 0.f, mkSpriteWidth, mkSpriteHeight},
        {mkSpriteWidth * 4 + 4 * mpadding, 0.f, mkSpriteWidth, mkSpriteHeight},
        {mkSpriteWidth * 5 + 5 * mpadding, 0.f, mkSpriteWidth, mkSpriteHeight},
    };
    // Set sprite clips
    currentClip = spriteClips[frame / mkWakingAnimationFramesPerSprite];
};

void Monster::move(Tile *tiles[]) {
    mBox.x += mVelX;

    // If the dot went too far to the left or right or touched a wall
    if ((mBox.x < 0) || (mBox.x + MONSTER_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles)) {
        // move back
        mVelX = mVelX * (-1);
    }

    // Move the dot up or down
    mBox.y += mVelY;

    // If the dot went too far up or down or touched a wall
    if ((mBox.y < 0) || (mBox.y + MONSTER_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, tiles)) {
        // move back
        mVelY = mVelY * (-1);
    }
}

// void monster::setCamera(SDL_Rect &camera) {
//     // Center the camera over the dot
//     camera.x = (mBox.x + DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
//     camera.y = (mBox.y + DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

//     // Keep the camera in bounds
//     if (camera.x < 0) {
//         camera.x = 0;
//     }
//     if (camera.y < 0) {
//         camera.y = 0;
//     }
//     if (camera.x > LEVEL_WIDTH - camera.w) {
//         camera.x = LEVEL_WIDTH - camera.w;
//     }
//     if (camera.y > LEVEL_HEIGHT - camera.h) {
//         camera.y = LEVEL_HEIGHT - camera.h;
//     }
// }

void Monster::render(SDL_Rect &camera, SDL_FRect *clip) {
    // Show the dot
    // here I can define the redering
    gMonsterTexture.render(mBox.x-camera.x, mBox.y-camera.y, clip);
}
