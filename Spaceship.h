#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "Common_Function.h"
#include "Base.h"
#include "Weapon.h"
#include <vector>

// class spaceship: public baseOb kế thừa những
// cái public của baseOb và những cái protected của baseOb

class spaceship: public baseOb{

public:
    /*
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
    }*/

    spaceship(int posX, int posY);
    spaceship();

    ~spaceship();

    void move();

    void turnLeft();

    void turnRight();

    void turnUp();

    void turnDown();

    bool inside(int minX, int minY , int maxX, int maxY);

    void setWeaponList(std::vector <weaponOb*> pWeaponList_)
    {
        this->pWeaponList = pWeaponList_;
    }

    std::vector<weaponOb*> getWeaponList() const{return this->pWeaponList;}

    void handleEvent(SDL_Event events, SDL_Renderer* renderer);

    void makeWeaponList(SDL_Renderer* renderer);
private:
    int posX;
    int posY;
    int sizW = SPACECRAFT_WIDTH;
    int sizH = SPACECRAFT_HEIGHT;
    int stepX = 15;
    int stepY = 15;
    std::vector <weaponOb*> pWeaponList; // 1 vector con trỏ
};

#endif // SPACESHIP_H_INCLUDED
