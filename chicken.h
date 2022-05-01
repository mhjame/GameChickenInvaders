#ifndef CHICKEN_H_INCLUDED
#define CHICKEN_H_INCLUDED

#include "Common_Function.h"
#include "Base.h"

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
private:
    int x_val_;
    int y_val_;
    bool status;
};

#endif // CHICKEN_H_INCLUDED
