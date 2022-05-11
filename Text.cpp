#include "Text.h"

textOb::textOb()
{
    rectOb.x = 25;
    rectOb.y = 50;
    text_color_.r = 255;
    text_color_.g = 0;
    text_color_.b = 0;
}

textOb::~textOb()
{

}

void textOb::setTextColor(const int&type)
{
    if(type == RED_TEXT)
    {
        SDL_Color color = {225, 0, 0};
        this->text_color_ = color;
    }
    else if(type == WHITE_TEXT)
    {
        SDL_Color color = {255, 255, 255};
        this->text_color_ = color;
    }
    else
    {
        SDL_Color color = {0,0,0};
        text_color_ = color;
    }
}

void textOb::createGameText(TTF_Font *font, SDL_Renderer *renderer)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    object = Message;

    if(object != NULL)
    {
        rectOb.w = surfaceMessage->w;
        rectOb.h = surfaceMessage->h;
    }
    this->Render(renderer);
}
