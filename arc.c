// standard header files
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
// SDL headers (third party)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
// custom header files
#include "./headers/background.h"
#include "./headers/environment.h"
#include "./headers/paths.h"
#include "./headers/pipe.h"
#include "./headers/sprite.h"
// helper functions
#include "./helpers.c"


int main(int argc, char* argv[]) {
    // seeding the random number generator
    time_t seconds = time(NULL);
    srand((unsigned) seconds);

    // attempt to initialize graphics system
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    // handling errors during window creation
    if (!window) {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();

        return -1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);
    // handling errors during renderer creation
    if (!renderer) {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();

        return -1;
    }
    
    // SDL_ttf font setup
    TTF_Init();
    int scoreFontSize = 20;
    TTF_Font* scoreFont = TTF_OpenFont(fontPath, scoreFontSize);
    SDL_Color scoreColor = {0, 0, 0}; // rgb(0, 0, 0)

    // initializing renderer
    initializeSprite(renderer);

    SDL_Rect gameInstructionsContainer = {45, 35, 550, 370};
    SDL_Texture* gameInstructionsTexture = IMG_LoadTexture(renderer, gameIntructionsPath);
    // handling errors during texture creation
    if (!gameInstructionsTexture) {
        printf("Error creating texture\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return -1;
    }

    Background bgs[500] = {};
    Pipe pipes[1000] = {};
    size_t pipeSize = 0; // `size_t` represents size of an object in bytes

    for (int i = 0; i < 500; ++ i) {
        Background* bg = &bgs[i];

        bg->xPos = i * WINDOW_WIDTH;
        bg->yPos = 0;
        bg->xVel = 2;
        bg->width = WINDOW_WIDTH;
        bg->height = WINDOW_HEIGHT;
        bg->textureSource = backgroundPath[generateIndex(numBackgrounds)];
        bg->texture = IMG_LoadTexture(renderer, bg->textureSource);
        bg->rect.x = bg->xPos;
        bg->rect.y = bg->yPos;
        bg->rect.w = bg->width;
        bg->rect.h = bg->height;
        bg->opacity = 220;

        SDL_SetTextureBlendMode(bg->texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(bg->texture, bg->opacity);
    }

    int iterations = 0;
    int score = 0;
    char scoreText[20];
    bool scoreStatuses[1000] = {};

    bool isGameRunning = true;
    bool isSpriteFalling = false;
    bool isGameOver = false;

    SDL_Event event;

    while (isGameRunning) {
        iterations ++;

        sprintf(scoreText, "SCORE: %i", score);

        SDL_Surface* scoreSurface = TTF_RenderText_Solid(scoreFont, scoreText, scoreColor);
        // error handling during surface creation
        if (!scoreSurface) {
            printf("Error creating surface\n");
            SDL_DestroyTexture(gameInstructionsTexture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();

            return -1;
        }

        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_FreeSurface(scoreSurface);
        // error handling during texture creation
        if (!scoreTexture) {
            printf("Error creating texture\n");
            SDL_DestroyTexture(gameInstructionsTexture);
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();

            return -1;
        }

        SDL_Rect scoreContainer = {WINDOW_WIDTH / 2 - 75, 10, 140, 30};

        if (!isGameOver && isSpriteFalling && iterations % 50 == 0) {
            pipeSize ++;
            Pipe *pipe = &pipes[pipeSize - 1];

            int upperPipeHeight = rand() % (int) ((WINDOW_HEIGHT / 2) * 1.2 - WINDOW_HEIGHT / 10 + 1) + WINDOW_HEIGHT / 10;

            // asset handling for the pipes
            pipe->upperPipeSurface = IMG_Load(lowerPipesPath);
            pipe->lowerPipeSurface = IMG_Load(upperPipesPath);
            pipe->upperPipeTexture = SDL_CreateTextureFromSurface(renderer, pipe->upperPipeSurface);
            pipe->lowerPipeTexture = SDL_CreateTextureFromSurface(renderer, pipe->lowerPipeSurface);

            SDL_FreeSurface(pipe->upperPipeSurface);
            SDL_FreeSurface(pipe->lowerPipeSurface);

            pipe->gap = 180;
            pipe->width = 60;
            pipe->xVel = 3;

            pipe->upperPipe.x = pipeSize * 100 + 500;
            pipe->upperPipe.y = 0;
            pipe->upperPipe.w = pipe->width;
            pipe->upperPipe.h = upperPipeHeight;

            pipe->lowerPipe.x = pipeSize * 100 + 500;
            pipe->lowerPipe.y = upperPipeHeight + pipe->gap;
            pipe->lowerPipe.w = pipe->width;
            pipe->lowerPipe.h = WINDOW_HEIGHT - (pipe->lowerPipe.y);
        }

        if (face.yPos + 30 > WINDOW_HEIGHT) {
            isGameOver = true;
        }
        else if (face.yPos < 0) {
            isGameOver = true;
        }
        else if (isSpriteFalling) {
            face.yVel += FALL_RATE;
        }

        // collision detection
        for (int i = 0; i < pipeSize; ++ i) {
            if (detectCollision(pipes[i], face)) {
                for (int j = 0; j < 500; j ++) {
                    pipes[j].xVel = 0;
                }

                face.yVel = 0;
                face.yPos = WINDOW_HEIGHT - face.height;

                for (int j = 0; j < 500; j ++) {
                    bgs[j].xVel = 0;
                }

                isGameOver = true;
            }

            if (!scoreStatuses[i] == true && face.xPos > pipes[i].lowerPipe.x) {
                scoreStatuses[i] = true;
                keepScore(&score);
            }
        }

        // background movement
        for (int i = 0; i < 500; ++ i) {
            bgs[i].rect.x = bgs[i].xPos;
            bgs[i].xPos -= bgs[i].xVel;
        }

        // pipe movement
        if (isSpriteFalling && !isGameOver) {
            for (int i = 0; i < pipeSize; ++i) {
                pipes[i].upperPipe.x -= pipes[i].xVel;
                pipes[i].lowerPipe.x -= pipes[i].xVel;
            }
        }

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    isGameRunning = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                        case SDLK_UP:
                        case SDLK_w:
                            face.yVel = -5;
                            isSpriteFalling = true;
                    }
            }
        }

        face.yPos += (int) face.yVel;

        SDL_RenderClear(renderer);

        for (int i = 0; i < 500; ++ i) {
            SDL_RenderFillRect(renderer, &bgs[i].rect);
            SDL_RenderCopy(renderer, bgs[i].texture, NULL, &bgs[i].rect);
        }

        if (!isGameOver) {
            renderSprite(renderer);
            SDL_RenderCopy(renderer, face.texture, NULL, &face.Rect);
        }

        if (isSpriteFalling && !isGameOver) {
            for (int i = 0; i < pipeSize; ++ i) {
                SDL_Rect upperPipeContainer = pipes[i].upperPipe;
                SDL_Rect lowerPipeContainer = pipes[i].lowerPipe;

                SDL_RenderCopy(renderer, pipes[i].upperPipeTexture, NULL, &upperPipeContainer);
                SDL_RenderCopy(renderer, pipes[i].lowerPipeTexture, NULL, &lowerPipeContainer);
            }
        }

        if (isSpriteFalling) {
            SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreContainer);
        }

        if (!isSpriteFalling && !isGameOver) {
            SDL_RenderCopy(renderer, gameInstructionsTexture, NULL, &gameInstructionsContainer);
        }

        if (isGameOver) {
            SDL_Rect gameOverContainer = {60, 60, WINDOW_WIDTH - 120, WINDOW_HEIGHT - 120};
            SDL_Texture* gameOverTexture = IMG_LoadTexture(renderer, gameOverPath);
            SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverContainer);
        }

        SDL_RenderPresent(renderer);
    }

    // when game is not running
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
