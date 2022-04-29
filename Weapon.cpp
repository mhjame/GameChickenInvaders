#include "Weapon.h"

using namespace std;

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
