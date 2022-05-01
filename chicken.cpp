#include "chicken.h"

using namespace std;

Chicken::Chicken()
{
    x_val_ = 0;
    y_val_ = 0;

    rectOb.x = SCREEN_WIDTH;
    rectOb.y = 0;
}

Chicken::~Chicken()
{

}

void Chicken::HandleMove(const int& x_border, const int& y_border)
{
    if(rectOb.x <= 0 || rectOb.x >= x_border)
    {
        if(status == true) set_status(false);
        else set_status(true);

        int rand_y = rand()%400;

        if(rand_y > y_border - 200)
        {
            rand_y = y_border - 100;
        }

        rectOb.y = rand_y;
        //cout << rand_y << " " << rectOb.y << endl;

        cout << y_border<< endl;

    }
    if(status == true)
    {
        rectOb.x -= x_val_;
    }
    else if(status == false)
    {
        rectOb.x += x_val_;
    }
    SDL_Delay(10);
}

void Chicken::HandleInputAction(SDL_Event &events)
{

}
