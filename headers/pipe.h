#ifndef PIPE_HEADER
#define PIPE_HEADER
#include <SDL2/SDL.h>

typedef struct
{
    SDL_Rect upperPipe;
    SDL_Rect lowerPipe;
    SDL_Texture* upperPipeTexture;
    SDL_Texture* lowerPipeTexture;
    SDL_Surface* upperPipeSurface;
    SDL_Surface* lowerPipeSurface;

    int gap;
    int width;
    double xVel;
} Pipe;

#endif