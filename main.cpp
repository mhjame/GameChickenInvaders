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

/// loads individual image
SDL_Surface* loadSurface(std::string path);

/// The window we'll be rendering to
SDL_Window* gWindow = NULL;

///the surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// the spacescraft we'll be rendering to
SDL_Surface* gSpacecraft = NULL;


//
SDL_Surface* gBackground = NULL;

bool init();
bool loadMedia();
void close();

struct spaceShip{
    int posX;
    int posY;
    int sizW = SPACECRAFT_WIDTH;
    int sizH = SPACECRAFT_HEIGHT;
    int stepX = 5;
    int stepY = 5;

    void render()
    {
         SDL_Rect SpacecraftRect;
         SpacecraftRect.x = posX;
         SpacecraftRect.y = posY;

         SpacecraftRect.w = sizW;
         SpacecraftRect.h = sizH;

         SDL_BlitScaled(gBackground, NULL, gScreenSurface, NULL);
         SDL_BlitScaled(gSpacecraft, NULL, gScreenSurface, &SpacecraftRect);

         //update Surface
         SDL_UpdateWindowSurface(gWindow);
    }

    spaceShip(int posX, int posY)
    {
        this->posX = posX;
        this->posY = posY;
    }

    spaceShip(){};

    ~spaceShip(){};

    void move()
    {
        posX += stepX;
        posY += stepY;

        //cout << stepX << "," << stepY << endl;
    }

    void turnLeft()
    {
        stepX =-5;
        stepY = 0;
    }

    void turnRight()
    {
        stepX = 5;
        stepY = 0;
    }

    void turnUp()
    {
        stepY = -5;
        stepX = 0;
    }

    void turnDown()
    {
        stepY = 5;
        stepX = 0;
    }

    bool inside(int minX, int minY , int maxX, int maxY)
    {
        if(posX >= minX && posY >= minY && (posX + sizW) <= maxX && (posY + sizH) <= maxY)
            return true;
        return false;
    }
};

void mainProgress()
{
    // main loop flag
    //bool quit = false;

    //Event handler
    SDL_Event e;
    spaceShip Spacecraft(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    while(Spacecraft.inside(0,0, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        Spacecraft.move();
        //SDL_SetRenderDrawColor(gRenderer, GRAY_COLOR.r, GRAY_COLOR.g, GRAY_COLOR.b, 0);
        Spacecraft.render();

        //SDL_RenderPresent(gRenderer);
        SDL_Delay(100);

        if(SDL_PollEvent(&e) == 0)
        {
            continue;
        }

        if(e.type == SDL_QUIT)
        {
            break;
        }

        // SDL_WaitEvent - nó đợi vô thời hạn
        // lên đọc so sánh PollEvent và WaitEven để xem khác biệt

        //if(e.type == SDL_QUIT) break;

        // nếu có một phím được nhấn thì xét phím đó là gì để xử lỷ
        if(e.type == SDL_KEYDOWN)
        {
            switch(e.key.keysym.sym)
            {
                case SDLK_ESCAPE: break;
                case SDLK_LEFT:
                    {
                        Spacecraft.turnLeft();
                        break;
                    }
                case SDLK_RIGHT:
                    {
                        Spacecraft.turnRight();
                        break;
                    }
                case SDLK_DOWN:
                    {
                        Spacecraft.turnDown();
                        break;
                    }
                case SDLK_UP:
                    {
                        Spacecraft.turnUp();
                        break;
                    }
                default: break;
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("failed to load Media!\n");
        }
        else
        {
            if(loadMedia())
            {
                mainProgress();
            }
        }
    }
    return 0;
}

bool init()
{
    // Initialization flag
    bool success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // create window
        gWindow = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(gWindow == NULL)
        {
            printf("Window could not be create! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else{
            //get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

/**
After we create our window, we have to create a renderer for our window
so we can render textures on it. Fortunately this is easily done with a
call to SDL_CreateRenderer.

After creating the renderer, we want to initialize the
rendering color using SDL_SetRenderDrawColor. This controls
what color is used for various rendering operations.*/

SDL_Surface* loadSurface(std::string path)
{
    // the final optimized image
    SDL_Surface* optimizedSurface = NULL;

    // load image at specific path

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
        if(optimizedSurface == NULL)
        {
            printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
        if(optimizedSurface!= NULL)
        {
            Uint32 color_key = SDL_MapRGB(optimizedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B);
            SDL_SetColorKey(optimizedSurface, SDL_TRUE, color_key);
        }
    }

    return optimizedSurface;
}


bool loadMedia()
{
    //Loading success flag
    bool success = true;
    //load PNG texture
    gBackground = loadSurface("Image//background.png");
    if(gBackground == NULL)
    {
        printf("Failed to load background image! \n");
        success = false;
    }

    gSpacecraft = loadSurface("Image//spacecraft.png");
    if(gSpacecraft == NULL)
    {
        printf("Failed to load spacecraft image");
    }

    return success;
}

void close()
{
    //Deallocate surface
    SDL_FreeSurface(gBackground);
    SDL_FreeSurface(gSpacecraft);

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystem
    SDL_Quit();
}
