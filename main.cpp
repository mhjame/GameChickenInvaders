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

//loads individual image as texture
SDL_Texture* loadTexture(std::string path);

// The window we'll be rendering to
SDL_Window* gWindow = NULL;

//the wwindow renderer
SDL_Renderer* gRenderer = NULL;

// the spacescraft we'll be rendering to
SDL_Texture* gSpacecraft = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

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

    void render(SDL_Renderer* renderer)
    {
         SDL_Rect SpacecraftRect;
         SpacecraftRect.x = posX;
         SpacecraftRect.y = posY;

         SpacecraftRect.w = sizW;
         SpacecraftRect.h = sizH;

         //Clear screen
        SDL_SetRenderDrawColor(renderer, GRAY_COLOR.r, GRAY_COLOR.g, GRAY_COLOR.b, 0);
        SDL_RenderClear(renderer);
        //Render texture to screen
        //SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
        SDL_RenderCopy(renderer, gSpacecraft, NULL, &SpacecraftRect);
        //Update screen
        SDL_RenderPresent(renderer);
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
        SDL_SetRenderDrawColor(gRenderer, GRAY_COLOR.r, GRAY_COLOR.g, GRAY_COLOR.b, 0);
        Spacecraft.render(gRenderer);

        SDL_RenderPresent(gRenderer);
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

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("SDL Turorial", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if(gWindow == NULL)
        {
            printf("Window could not be create! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                printf("Renderer could not be create! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else{
                //Initialize renderer color
                Uint8 r = 255;
                Uint8 g = 255;
                Uint8 b = 255;
                Uint8 a = 0;
                SDL_SetRenderDrawColor(gRenderer, r, g, b, a);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)& imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
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

SDL_Texture* loadTexture(std::string path)
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
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

         if (newTexture != NULL)
         {
           Uint32 color_key = SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF);
           SDL_SetColorKey(newTexture, SDL_TRUE, color_key);
         }

         ///Get rid of loaded surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    //load PNG texture
    gTexture = loadTexture("Image//background.png");
    if(gTexture == NULL)
    {
        printf("Failed to load background image! \n");
        success = false;
    }

    gSpacecraft = loadTexture("Image//spacecraft.png");
    if(gSpacecraft == NULL)
    {
        printf("Failed to load spacecraft image");
    }
    return success;
}

void close()
{
    ///Free loaded image
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
