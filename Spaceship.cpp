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
    stepX =-15;
    stepY = 0;
}

void spaceship::turnRight()
{
    stepX = 15;
    stepY = 0;
}

void spaceship::turnUp()
{
    stepY = -15;
    stepX = 0;
}

void spaceship::turnDown()
{
    stepY = 15;
    stepX = 0;
}

bool spaceship::inside(int minX, int minY, int maxX, int maxY)
{
    if(posX >= minX && posY >= minY && (posX + sizW) <= maxX && (posY + sizH) <= maxY)
        return true;
    return false;
}

void spaceship::makeWeaponList(SDL_Renderer* renderer)
{
    for(int i = 0; i < pWeaponList.size(); ++i)
    {
        weaponOb *pBullet = pWeaponList.at(i);

        pBullet->Render(renderer);

        if(pBullet != nullptr)
        {
            if(pBullet->getIsMove())
            {
                SDL_Rect pBulletRect = pBullet->getRect();
                pBullet->Render(renderer, &pBulletRect);
                pBullet->handleMoveSpaceshipBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
                //SDL_Delay(10);
            }
            else
            {
                pWeaponList.erase(pWeaponList.begin() + i);

                delete pBullet;
                pBullet = NULL;
            }
        }
    }
}

void spaceship::handleEvent(SDL_Event events, SDL_Renderer* renderer)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
            {
                case SDLK_ESCAPE: break;
                case SDLK_a:
                case SDLK_LEFT:
                    {
                        this->turnLeft();
                        this->move();
                        break;
                    }

                case SDLK_d:
                case SDLK_RIGHT:
                    {
                        this->turnRight();
                        this->move();
                        break;
                    }

                case SDLK_s:
                case SDLK_DOWN:
                    {
                        this->turnDown();
                        this->move();
                        break;
                    }

                case SDLK_w:
                case SDLK_UP:
                    {
                        this->turnUp();
                        this->move();
                        break;
                    }


                case SDLK_v:
                    {
                        weaponOb* pBullet = new weaponOb();

                        pBullet->setType(weaponOb::BLASTER);
                        pBullet->loadTextureBullet(renderer, 1);

                        SDL_Rect planeRect = this->getRect();
                        int x_val = planeRect.x + planeRect.w/2 - 10;
                        int y_val = planeRect.y - planeRect.h - 5;
                        pBullet->setRect(x_val, y_val);
                        pBullet->setIsMove(true);
                        pBullet->set_y_val_(80);

                        pWeaponList.push_back(pBullet);

                        break;
                    }

                case SDLK_SPACE:
                    {
                         weaponOb* pBullet = new weaponOb();

                         pBullet->setType(weaponOb::BORON);
                         pBullet->loadTextureBullet(renderer, 1);

                        SDL_Rect planeRect = this->getRect();
                        int x_pos = planeRect.x + planeRect.w/2 - 10;
                        int y_pos = planeRect.y - planeRect.h - 5;
                        pBullet->setRect(x_pos, y_pos);
                        pBullet->set_y_val_(80);
                        pBullet->setIsMove(true);

                        pWeaponList.push_back(pBullet);

                        break;
                    }
                default: break;
            }
    }
    else if(events.type == SDL_KEYUP);
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_UP:
            {
                rectOb.x -= stepX;
                rectOb.y -= stepY;
                break;
            }
        }
    }
    /*
    if (events.type == SDL_MOUSEBUTTONDOWN)
    {
        weaponOb* pBullet = new weaponOb();

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
        int x_val = planeRect.x + planeRect.w/2 - 10;
        int y_val = planeRect.y - planeRect.h - 5;
        pBullet->setRect(x_val, y_val);

        pBullet->setIsMove(true);

        pWeaponList.push_back(pBullet);
    }
    else if(events.type == SDL_MOUSEBUTTONUP)
    {

    }*/
}

void spaceship::RemoveWeapon(const int& idx)
{
    int siz = pWeaponList.size();
    if(siz > 0 && idx < siz)
    {
        for(int i = 0; i < pWeaponList.size(); ++i)
        {
            weaponOb *pWeapon = pWeaponList.at(idx);
            pWeaponList.erase(pWeaponList.begin() + idx);

            if(pWeapon != NULL)
            {
                delete pWeapon;
                pWeapon = NULL;
            }
        }
    }

}


