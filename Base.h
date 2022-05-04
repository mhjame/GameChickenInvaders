#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include "Common_Function.h"

class baseOb
{
/// nếu để private các lớp con kế thừa nó muốn đọc sẽ không đọc được
protected:
    SDL_Rect rectOb;
    SDL_Rect rectSrc;
    SDL_Texture* object;

public:
    baseOb();
    ~baseOb();

    void setRect( int& posX, int& posY)
    {
        rectOb.x = posX;
        rectOb.y = posY;
    }

    SDL_Rect getRect()
    {
        return rectOb;
    }

    void setSrcRect(int &posX, int& posY, int &wid, int &hei){rectSrc.x = posX, rectSrc.y = posY, rectSrc.w = wid, rectSrc.h = hei;}
    SDL_Rect getSrcRect(){return rectSrc;}

    void setObject(SDL_Texture* object)
    {
        this->object = object;
    }

    SDL_Texture* getObject() const
    {
        return object;
    }

    void Render(SDL_Renderer* renderer, const SDL_Rect* rectPos = NULL);
    void clean();
    bool loadTexture(std::string path, SDL_Renderer* renderer);
};

#endif // BASE_H_INCLUDED
