#ifndef PLAYERPOWER_H_INCLUDED
#define PLAYERPOWER_H_INCLUDED
#include "Base.h"
#include <vector>

class playerPower:public baseOb
{
public:
    playerPower();
    ~playerPower();
    void setNumber(const int& num){number_ = num;}
    int getNumber(){return number_;}
    void AddPos(const int& xpos);
    void show(SDL_Renderer* renderer);
    void init(SDL_Renderer* renderer);
    void decrease();
    void increase();

private:
    int number_;
    std::vector <int> pos_list_;
};

#endif // PLAYERPOWER_H_INCLUDED
