#include "PlayerPower.h"

playerPower::playerPower()
{

}

playerPower::~playerPower()
{

}

void playerPower::AddPos(const int& xpos)
{
    pos_list_.push_back(xpos);
}

void playerPower::show(SDL_Renderer* renderer)
{
    if(number_ == pos_list_.size())
    {
        for(int i = 0; i < pos_list_.size(); ++i)
        {
            rectOb.x = pos_list_[i];
            Render(renderer);
        }
    }
}

void playerPower::init(SDL_Renderer *renderer)
{
    loadTexture("Image//heart.png", renderer);
    number_ = 3;
    if(pos_list_.size() > 0)
    {
        pos_list_.clear();
    }

    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void playerPower::decrease()
{
    number_ = number_ - 1;
    pos_list_.pop_back();
}
