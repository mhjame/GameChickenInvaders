#include "chicken.h"
#include "Common_Function.h"

using namespace std;

Chicken::Chicken()
{
    x_val_ = 0;
    y_val_ = 0;

    rectOb.x = SCREEN_WIDTH;
    rectOb.y = 0;
}

Chicken::~Chicken()
{

}

void Chicken::initWeapon(weaponOb* pWeapon, SDL_Renderer* renderer)
{
    if(pWeapon != NULL)
    {
        bool ret = pWeapon->loadTexture("Image//egg.png", renderer);
        if(ret)
        {
            pWeapon->setIsMove(true);
            int pWX = this->getRect().x + this->getRect().w/2;
            int pWY = this->getRect().y + this->getRect().h + 5;

            pWeapon->setRect(pWX, pWY);
            pWeaponList.push_back(pWeapon);
            //cout << this->getRect().x << " "<< this->getRect().y << " " << this->getRect().w << " " << this->getRect().h << endl;
        }
    }
}

void Chicken::useWeapon(SDL_Renderer* renderer, const int& x_limit, const int& y_limit)
{
    for(int i = 0; i < this->pWeaponList.size(); ++i)
    {
        weaponOb* pWeapon = pWeaponList.at(i);
        if(pWeapon != NULL)
        {
            if(pWeapon->getIsMove())
            {
                SDL_Rect pRect = pWeapon->getRect();

                pWeapon->Render(renderer, &pRect);
                pWeapon->handleMoveChickenBullet(x_limit, y_limit);
                 //cout << this->getRect().x << " "<< this->getRect().y << " " << this->getRect().w << " " << this->getRect().h << endl;
            }
            else
            {
                int pWX = rectOb.x + rectOb.w/2;
                int pWY = rectOb.y + rectOb.h + 5;
                pWeapon->setRect(pWX, pWY);
                pWeapon->setIsMove(true);

            }

            //cout << this->getRect().x << " "<< this->getRect().y << " " << this->getRect().w << " " << this->getRect().h << endl;

            //cout << 1 << " " << pWX << " " << pWY << endl;
            //pWeapon->Render(renderer);
            //SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }
}

void Chicken::HandleMove(const int& x_border, const int& y_border)
{
    if(rectOb.x <= 0 || rectOb.x >= x_border)
    {
        if(status == true) set_status(false);
        else set_status(true);

        int rand_y = rand()%400;

        if(rand_y > y_border - 200)
        {
            rand_y = y_border - 100;
        }

        rectOb.y = rand_y;
        //cout << rand_y << " " << rectOb.y << endl;

        //cout << y_border<< endl;

    }
    if(status == true)
    {
        rectOb.x -= x_val_;
    }
    else if(status == false)
    {
        rectOb.x += x_val_;
    }
    SDL_Delay(10);
}

void Chicken::HandleInputAction(SDL_Event &events)
{

}