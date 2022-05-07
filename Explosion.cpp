#include "Explosion.h"

Explosion::Explosion()
{
    frame = 16;
}

Explosion::~Explosion()
{

}

void Explosion::set_clip()
{
    for(int i = 0; i < 8; ++i)
    {
        clip_[i].x = i*WIDTH_FRAME_EXP;  /// fame thứ i
        clip_[i].y = 0;
        clip_[i].w = WIDTH_FRAME_EXP;
        clip_[i].h = HEIGHT_FRAME_EXP;
    }
}

void Explosion::show(SDL_Renderer* renderer)
{
    if(frame >= 8)
    {
        frame = 0;
    }
    SDL_Rect desRect = {rectOb.x, rectOb.y, WIDTH_FRAME_EXP, HEIGHT_FRAME_EXP};
    SDL_RenderCopy(renderer, object, &clip_[frame], &desRect);
}
