#ifndef SPRITE_HEADER
#define SPRITE_HEADER
#include <SDL2/SDL.h>

typedef struct
{
    SDL_Rect Rect;
    SDL_Texture* texture;

    int width;
    int height;
    int xPos;
    int yPos;
    double yVel;
} Sprite;

#endif