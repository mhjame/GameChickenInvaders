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

    void set_x_val_(const int& val){x_val_ = val;}
    void set_y_val_(const int& val){y_val_ = val;}

    int get_x_val() const{return x_val_;}
    int get_y_val() const{return y_val_;}
private:
    int x_val_ = 0;
    int y_val_ = 0;
    bool isMove;
    int weaponType;
};

#endif // WEAPON_H_INCLUDED
