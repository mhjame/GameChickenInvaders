#include "Common_Function.h"

SDL_Texture* SDLCommonFunc::loadTexture(std::string path, SDL_Renderer* renderer)
{
    ///The final texture
    SDL_Texture* newTexture = NULL;

    ///Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
             ///Get rid of loaded surface
            SDL_FreeSurface(loadedSurface);
        }
    }
    return newTexture;
}
