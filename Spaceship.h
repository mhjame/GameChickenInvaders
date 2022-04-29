#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "Common_Function.h"
#include "Base.h"

// class spaceship: public baseOb kế thừa những
// cái public của baseOb và những cái protected của baseOb

class spaceship: public baseOb{

public:
    int posX;
    int posY;
    int sizW = SPACECRAFT_WIDTH;
    int sizH = SPACECRAFT_HEIGHT;
    int stepX = 5;
    int stepY = 5;

    void render(SDL_Renderer* renderer)
    {
         SDL_Rect SpacecraftRect;
         SpacecraftRect.x = posX;
         SpacecraftRect.y = posY;

         SpacecraftRect.w = sizW;
         SpacecraftRect.h = sizH;

         //Clear screen
        SDL_SetRenderDrawColor(renderer, GRAY_COLOR.r, GRAY_COLOR.g, GRAY_COLOR.b, 0);
        SDL_RenderClear(renderer);
        //Render texture to screen
        //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        SDL_Rect BackgroundRect;
        BackgroundRect.x = 0;
        BackgroundRect.y = 0;
        BackgroundRect.w = BACKGROUND_WIDTH;
        BackgroundRect.h = BACKGROUND_HEIGHT;
        SDL_RenderCopy(renderer, gBackground, NULL, &BackgroundRect);
        SDL_RenderCopy(renderer, gSpacecraft, NULL, &SpacecraftRect);
        //Update screen
        SDL_RenderPresent(renderer);
    }

    spaceship(int posX, int posY);
    spaceship();

    ~spaceship();

    void move();

    void turnLeft();

    void turnRight();

    void turnUp();

    void turnDown();

    bool inside(int minX, int minY , int maxX, int maxY);
};

#endif // SPACESHIP_H_INCLUDED
