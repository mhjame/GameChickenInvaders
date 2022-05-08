#ifndef COMMON_FUNCTION_H_INCLUDED
#define COMMON_FUNCTION_H_INCLUDED
#include <SDL_mixer.h>
/// where put every function or figure in general process

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int BACKGROUND_WIDTH = 1200;
const int BACKGROUND_HEIGHT = 3840;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 760;

const int SPACECRAFT_WIDTH =  70;
const int SPACECRAFT_HEIGHT = 57;

const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GRAY_COLOR = {211,211,211};

const int COLOR_KEY_R = 170;
const int COLOR_KEY_G = 170;
const int COLOR_KEY_B = 170;

const int CHICKEN_W = 74;
const int CHICKEN_H = 68;
const int NUM_CHICKENS= 10;

// The window we'll be rendering to
static SDL_Window* gWindow = NULL;

//Current displayed texture
static SDL_Texture* gBackground = NULL;
//
static SDL_Event gEvent;

// the spacescraft we'll be rendering to
static SDL_Texture* gSpacecraft = NULL;

static Mix_Chunk* g_sound_bullet[2];
static Mix_Chunk* g_sound_exp[2];

namespace SDLCommonFunc
{
    SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
    bool CheckCollision(const SDL_Rect &object1, const SDL_Rect &object2);
}

#endif // COMMON_FUNCTION_H_INCLUDED
