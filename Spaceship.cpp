#include "Spaceship.h"
#include "Weapon.h"

spaceship::spaceship(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
    rectOb.x = posX;
    rectOb.y = posY;
}

spaceship::spaceship() {
    posX = 0;
    posY = 0;
};

spaceship::~spaceship() {};

void spaceship::move()
{
    posX += stepX;
    posY += stepY;

    rectOb.x = posX;
    rectOb.y = posY;
    //cout << stepX << "," << stepY << endl;
}

void spaceship::turnLeft()
{
    stepX =-5;
    stepY = 0;
}

void spaceship::turnRight()
{
    stepX = 5;
    stepY = 0;
}

void spaceship::turnUp()
{
    stepY = -5;
    stepX = 0;
}

void spaceship::turnDown()
{
    stepY = 5;
    stepX = 0;
}

bool spaceship::inside(int minX, int minY, int maxX, int maxY)
{
    if(posX >= minX && posY >= minY && (posX + sizW) <= maxX && (posY + sizH) <= maxY)
        return true;
    return false;
}

void spaceship::handleEvent(SDL_Event events, SDL_Renderer* renderer)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
            {
                case SDLK_ESCAPE: break;
                case SDLK_LEFT:
                    {
                        this->turnLeft();
                        break;
                    }
                case SDLK_RIGHT:
                    {
                        this->turnRight();
                        break;
                    }
                case SDLK_DOWN:
                    {
                        this->turnDown();
                        break;
                    }
                case SDLK_UP:
                    {
                        this->turnUp();
                        break;
                    }
                default: break;
            }
    }
    else if(events.type == SDL_KEYUP);
    {

    }

    if(events.type == SDL_MOUSEBUTTONDOWN)
    {

    }
    else if(events.type == SDL_MOUSEBUTTONUP)
    {

    }

    weaponOb* pBullet = new weaponOb();
    if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        if(events.button.button == SDL_BUTTON_LEFT)
        {
            pBullet->setType(weaponOb::BLASTER);
            pBullet->loadTextureBullet(renderer, 1);
        }
        else if(events.button.button == SDL_BUTTON_RIGHT)
        {
            pBullet->setType(weaponOb::BORON);
            pBullet->loadTextureBullet(renderer, 1);
        }

        SDL_Rect planeRect = this->getRect();
        int x_val = planeRect.x + planeRect.w/2;
        int y_val = planeRect.y + 22;
        pBullet->setRect(x_val, y_val);

        pBullet->setIsMove(true);

        pWeaponList.push_back(pBullet);
    }

    else if(events.type == SDL_MOUSEBUTTONUP)
    {

    }
}
