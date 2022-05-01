#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "Base.h"
#include <string>

using namespace std;

class weaponOb : public baseOb
{
public:
    enum weaponList
    {
        BLASTER, //0
        NEUTRON, //1
        BORON, //2
    };

    weaponOb();
    ~weaponOb();

    void HandleInputAction(SDL_Event events);
    void handleMoveSpaceshipBullet(const int &x_border, const int &y_border);
    void handleMoveChickenBullet(const int &x_border, const int &y_border);

    int getType() const{return weaponType;}
    void setType(const int&type){weaponType = type;}

    bool getIsMove() const{return isMove;}
    void setIsMove(bool isMove_){this->isMove = isMove_;}

    void setWidthHeight(const int& width, const int& height)
    {
        rectOb.w = width;
        rectOb.h = height;
    }

    void loadTextureBullet(SDL_Renderer* renderer, int weaponLevel);

private:
    int posX = 0;
    int posY = 0;
    bool isMove;
    int weaponType;
};

#endif // WEAPON_H_INCLUDED
