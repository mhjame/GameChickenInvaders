#ifndef CHICKEN_H_INCLUDED
#define CHICKEN_H_INCLUDED

#include "Common_Function.h"
#include "Base.h"
#include "Weapon.h"
#include <vector>

class Chicken: public baseOb
{
public:

    Chicken();
    ~Chicken();
    void HandleMove(const int& x_border, const int& y_border);
    void HandleInputAction(SDL_Event & events);

    void set_x_val(const int& val)
    {
        x_val_ = val;
    }

    void set_y_val(const int&val){y_val_ = val;}
    int get_x_val() const{return x_val_;}
    int get_y_val() const{return y_val_;}
    void set_status(bool val){status = val;}
    bool get_status(){return status;}

    void setWeaponList(std::vector <weaponOb*> pWeaponList_)
    {
        this->pWeaponList = pWeaponList_;
    }

    std::vector<weaponOb*> getWeaponList() const{return this->pWeaponList;}
    void initWeapon(weaponOb* pWeapon, SDL_Renderer* renderer);
    void useWeapon(SDL_Renderer* renderer, const int& x_limit, const int& y_limit);

private:
    int x_val_;
    int y_val_;
    bool status;
    std::vector <weaponOb*> pWeaponList; // 1 vector con trỏ
};

#endif // CHICKEN_H_INCLUDED
