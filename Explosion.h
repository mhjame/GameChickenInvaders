#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "Base.h"
#include "Common_Function.h"

const int WIDTH_FRAME_EXP = 150;
const int HEIGHT_FRAME_EXP = 165;
const int NUMBER_OF_FRAME = 8;

class Explosion: public baseOb
{
private:
    int frame;
    SDL_Rect clip_[NUM_CHICKENS];
public:
    Explosion();
    ~Explosion();

    void set_clip();
    void show(SDL_Renderer *renderer);

    void set_frame(const int &frame_){this->frame = frame_;}
    int get_frame() const{return this->frame;}
};

#endif // EXPLOSION_H_INCLUDED
