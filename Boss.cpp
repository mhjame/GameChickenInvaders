#include "Boss.h"

Boss::Boss()
{
    rectOb.x = SCREEN_WIDTH - 10;
    rectOb.y = 10;

    x_val_ = 0;
    y_val_ = 0;

    status = true;

    frame = 0;
    heart = 100;
}

Boss::~Boss()
{
    if(pWeaponList.size() > 0)
    {
        for(int i = 0; i < pWeaponList.size(); ++i)
        {
            weaponOb* pWeapon = pWeaponList.at(i);
            if(pWeapon)
            {
                delete pWeapon;
                pWeapon = NULL;
            }
        }
    }
    pWeaponList.clear();
}

SDL_Rect Boss::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rectOb.x;
    rect.y = rectOb.y;
    rect.w = WIDTH_BOSS;
    rect.h = HEIGHT_BOSS;

    return rect;
}

void Boss::set_clips()
{
    for(int i = 0; i < 10; ++i)
    {
        clip_[i].x = i*WIDTH_BOSS;
        clip_[i].y = 0;
        clip_[i].w = WIDTH_BOSS;
        clip_[i].h = HEIGHT_BOSS;
    }
}

void Boss::Show(SDL_Renderer *renderer)
{
    if(frame >= 10)
    {
        frame = 0;
    }

   SDL_Rect desRect = {rectOb.x, rectOb.y, WIDTH_BOSS, HEIGHT_BOSS};
   SDL_RenderCopy(renderer, object, &clip_[frame], &desRect);
}

void Boss::initWeapon(weaponOb* pWeapon, SDL_Renderer* renderer)
{
    if(pWeapon != NULL)
    {
        bool ret = pWeapon->loadTexture("Image//egg_boss.png", renderer);
        if(ret)
        {
            pWeapon->setIsMove(true);
            int pWX = this->getRect().x + this->getRect().w/2;
            int pWY = this->getRect().y + this->getRect().h + 5;
            pWeapon->setRect(pWX, pWY);
            pWeapon->set_y_val_(20);
            pWeaponList.push_back(pWeapon);
            //cout << this->getRect().x << " "<< this->getRect().y << " " << this->getRect().w << " " << this->getRect().h << endl;
        }
    }
}
void Boss::useWeapon(SDL_Renderer* renderer, const int& x_limit, const int& y_limit)
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
            pWeapon->Render(renderer);
            //SDL_RenderPresent(renderer);
            //SDL_Delay(10);
        }
    }
}

void Boss::HandleMove(const int& x_border, const int& y_border, int delay_time)
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
    //SDL_Delay(10);
    SDL_Delay(delay_time);
}

void Boss::showHeartBoss(SDL_Renderer *renderer, int x, int y, int w, int h)
{
    SDL_Rect fillRect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fillRect);
}
