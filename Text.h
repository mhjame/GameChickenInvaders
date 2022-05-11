#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "Base.h"
#include <string>
#include <SDL_ttf.h>

class textOb: public baseOb
{
public:
    enum TEXTCOLOR
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };
    textOb();
    ~textOb();
    void setText(const std::string &text){str_val_ = text;}
    void setTextColor(const int&type);
    void createGameText(TTF_Font *font, SDL_Renderer *renderer);
private:
    std::string str_val_;
    SDL_Color text_color_;

};

#endif // TEXT_H_INCLUDED
