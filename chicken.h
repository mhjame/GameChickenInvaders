#ifndef CHICKEN_H_INCLUDED
#define CHICKEN_H_INCLUDED
#include "Common_Function.h"
#include "Base.h"
#include "Weapon.h"
#include <vector>

const int WIDTH_FRAME_CHICKEN = 75;
const int HEIGHT_FRAME_CHICKEN = 68;
const int NUMBER_OF_CFRAME = 18;

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
    void set_isLive(bool val){isLive = val;}
    bool get_isLive(){return isLive;}
    void setWeaponList(std::vector <weaponOb*> pWeaponList_)
    {
        this->pWeaponList = pWeaponList_;
    }
    std::vector<weaponOb*> getWeaponList() const{return this->pWeaponList;}
    void initWeapon(weaponOb* pWeapon, SDL_Renderer* renderer);
    void useWeapon(SDL_Renderer* renderer, const int& x_limit, const int& y_limit);

    void set_clips();
    void Show(SDL_Renderer *renderer);
    SDL_Rect GetRectFrame();

private:
    int x_val_;
    int y_val_;
    bool status;
    bool isLive;
    std::vector <weaponOb*> pWeaponList; // 1 vector con trỏ

    int frame;
    SDL_Rect clip_[18];
};

#endif // CHICKEN_H_INCLUDED
