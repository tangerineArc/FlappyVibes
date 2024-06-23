#ifndef BACKGROUND_HEADER
#define BACKGROUND_HEADER
#include <SDL2/SDL.h>

typedef struct
{
    SDL_Texture* texture;
    SDL_Rect rect;

    int xPos;
    int yPos;
    double xVel;
    int width;
    int height;
    char* textureSource;
    double opacity;
} Background;

#endif