// standard header files
#include <stdbool.h>
#include <time.h>
// SDL headers (third party)
#include <SDL2/SDL.h>
// custom headers
#include "./headers/environment.h"
#include "./headers/paths.h"
#include "./headers/pipe.h"

// random index generator for choosing elements in an array
int generateIndex(int n) {
    time_t t = time(NULL);
    srand((unsigned) t);

    return rand() % n;
}

// initializes the renderer
void initializeSprite(SDL_Renderer* renderer) {
    face.width = 50;
    face.height = 50;
    face.xPos = (WINDOW_WIDTH / 2) - 20;
    face.yPos = (WINDOW_HEIGHT / 2) - 40;
    face.yVel = 0;

    // choosing a random sprite
    face.texture = IMG_LoadTexture(renderer, spritesPaths[generateIndex(numFaces)]);
}

// renders main sprite
void renderSprite(SDL_Renderer* renderer) {
    // initializeSprite();
    face.Rect.x = face.xPos;
    face.Rect.y = face.yPos;
    face.Rect.w = face.width;
    face.Rect.h = face.height;
    // render the bird's texture
    SDL_RenderCopy(renderer, face.texture, NULL, &face.Rect);
}

// keeps track of score
int keepScore(int* score) {
    (*score) ++;

    return *score;
}

// detects collision of main sprite with pipes, ground, sky
bool detectCollision(Pipe pipe, Sprite face) {
    if (face.xPos < (pipe.upperPipe.x + pipe.upperPipe.w) && (face.xPos + face.width) > pipe.upperPipe.x &&
        face.yPos < (pipe.upperPipe.y + pipe.upperPipe.h) && (face.yPos + face.height) > pipe.upperPipe.y) {
        return true;
    }
    else if (face.xPos < (pipe.lowerPipe.x + pipe.lowerPipe.w) && (face.xPos + face.width) > pipe.lowerPipe.x &&
             face.yPos < (pipe.lowerPipe.y + pipe.lowerPipe.h) && (face.yPos + face.height) > pipe.lowerPipe.y) {
        return true;
    }
    else {
        return false;
    }
}