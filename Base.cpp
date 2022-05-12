#include "Base.h"

baseOb::baseOb()
{
    object = NULL;
    rectOb.x = 0;
    rectOb.y = 0;
    rectOb.w = 0;
    rectOb.h = 0;

    rectSrc.x = 0;
    rectSrc.y = 0;
    rectSrc.w = 0;
    rectSrc.h = 0;
}

baseOb::~baseOb()
{
    clean();
}

bool baseOb::loadTexture(std::string path, SDL_Renderer* renderer)
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
            if(newTexture!= NULL)
            {
                rectOb.w = loadedSurface->w;
                rectOb.h = loadedSurface->h;
            }
             ///Get rid of loaded surface
            SDL_FreeSurface(loadedSurface);
        }
    }
    object = newTexture;
    //if(object != NULL) cout << "load successful" << endl;

    return object != NULL;
}

void baseOb::clean()
{
    if(object != NULL)
    {
        SDL_DestroyTexture(object);
        object = NULL;
        rectOb.w = 0;
        rectOb.h = 0;
    }
}

void baseOb::Render(SDL_Renderer* renderer, const SDL_Rect* rectPos)
{
    //if(object!= NULL) cout << "load successfully!" << endl;
    SDL_Rect Rect_ = {rectOb.x, rectOb.y, rectOb.w, rectOb.h};
    SDL_RenderCopy(renderer, object, rectPos, &Rect_);
}
