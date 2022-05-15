#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED

#include "Common_Function.h"
#include "Base.h"
#include "Weapon.h"
#include "Explosion.h"
#include <vector>

#define WIDTH_BOSS 200
#define HEIGHT_BOSS 117
#define BOSS_SPEED 1
#define BOSS_BULLET_SPEED 13

class Boss: public baseOb{
public:
    Boss();
    ~Boss();

    void HandleMove(const int& x_border, const int& y_border, int delay_time);

    void set_x_val(const int &val){x_val_ = val;}
    void set_y_val(const int &val){y_val_ = val;}

    int get_x_val() const{return x_val_;}
    int get_y_val() const{return y_val_;}

    void Show(SDL_Renderer *renderer);
    void set_clips();
    SDL_Rect GetRectFrame();

    void setWeaponList(std::vector <weaponOb*> pWeaponList_)
    {
        this->pWeaponList = pWeaponList_;
    }
    std::vector<weaponOb*> getWeaponList() const{return this->pWeaponList;}
    void initWeapon(weaponOb* pWeapon, SDL_Renderer* renderer);
    void useWeapon(SDL_Renderer* renderer, const int& x_limit, const int& y_limit);

    void setHeart(const float &heart){this->heart = heart;}
    float getHeart() const{return heart;}

    void decrease(const float &bulletDamage){heart -= bulletDamage;}
    void showHeartBoss(SDL_Renderer* renderer, int x, int y, int w, int h);

    void set_status(bool val){status = val;}
    bool get_status(){return status;}

    void set_isLive(bool val){isLive = val;}
    bool get_isLive(){return isLive;}

private:
    float heart;
    std::vector<weaponOb*> pWeaponList;

    int x_val_;
    int y_val_;
    bool isLive;
    bool status;
    int frame;
    SDL_Rect clip_[10];
};

#endif // BOSS_H_INCLUDED
