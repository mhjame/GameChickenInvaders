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

void weaponOb::handleMoveSpacecraftBullet(const int& x_border, const int& y_border)
{
    rectOb.y += 20;
    if(rectOb.y > y_border)
    {
        setIsMove(false);
    }
}

void weaponOb::loadTextureBullet(SDL_Renderer* renderer, int weaponLevel)
{
    if(weaponType == BLASTER)
    {
        std::string blasterStr = "Image//blaster" + std::to_string(weaponLevel) + ".png";
        cout << loadTexture(blasterStr, renderer) << endl;
    }
    else if(weaponType == NEUTRON)
    {
        std::string neutronStr = "Image//neutron" + std::to_string(weaponLevel) + ".png";
        cout << loadTexture(neutronStr, renderer) << endl;
    }
    else if(weaponType == BORON)
    {
        std::string boronStr = "Image//boron" + std::to_string(weaponLevel) + ".png";
        cout << loadTexture(boronStr, renderer) << endl;
    }
}
