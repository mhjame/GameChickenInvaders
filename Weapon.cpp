#include "Weapon.h"

using namespace std;

weaponOb::weaponOb()
{
    rectOb.x = 0;
    rectOb.y = 0;
    posX = 0;
    posY = 0;
    isMove = false;
    weaponType = BLASTER;
}

weaponOb::~weaponOb()
{
}

void weaponOb::HandleInputAction(SDL_Event events)
{
}

void weaponOb::handleMoveSpaceshipBullet(const int& x_border, const int& y_border)
{
    rectOb.y -= 80;
    if(rectOb.y < 0)
    {
        setIsMove(false);
    }
}


void weaponOb::handleMoveChickenBullet(const int& x_border, const int& y_border)
{
    //cerr << rectOb.y << endl;
    rectOb.y += 20;
    if(rectOb.y >= y_border)
    {
        this->setIsMove(false);
    }
}

void weaponOb::loadTextureBullet(SDL_Renderer* renderer, int weaponLevel)
{
    if(weaponType == BLASTER)
    {
        std::string blasterStr = "Image//blaster" + std::to_string(weaponLevel) + ".png";
        loadTexture(blasterStr, renderer);
    }
    else if(weaponType == NEUTRON)
    {
        std::string neutronStr = "Image//neutron" + std::to_string(weaponLevel) + ".png";
        loadTexture(neutronStr, renderer);
    }
    else if(weaponType == BORON)
    {
        std::string boronStr = "Image//boron" + std::to_string(weaponLevel) + ".png";
        loadTexture(boronStr, renderer);
    }
}
