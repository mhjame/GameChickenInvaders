#include "Common_Function.h"
#include "Base.h"
#include "Spaceship.h"
#include "Weapon.h"

//loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//the wwindow renderer
SDL_Renderer* gRenderer = NULL;

bool init();
bool loadMedia();
void close();

void xuly()
{
    SDL_Event e;
    while(e.type != SDL_QUIT)
    {
        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
        {
            weaponOb *pBullet = new weaponOb();
            pBullet->loadTextureBullet(gRenderer, 1);
            pBullet->Render(gRenderer);
            cout << pBullet->getIsMove() << endl;
        }

        SDL_Delay(200);
    }

    spaceship Spacecraft(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    weaponOb *pBullet = new weaponOb();
    for(int i = 0; i < Spacecraft.getWeaponList().size(); ++i)
        {
            Spacecraft.handleEvent(e, gRenderer);
            std::vector <weaponOb*> weaponList = Spacecraft.getWeaponList();
            weaponOb *pBullet = weaponList[i];
            pBullet->Render(gRenderer);

            if(pBullet != nullptr)
            {
                if(pBullet->getIsMove())
                {
                    SDL_Rect pBulletRect = pBullet->getRect();
                    pBullet->Render(gRenderer, &pBulletRect);
                    pBullet->handleMoveSpacecraftBullet(SCREEN_WIDTH, SCREEN_HEIGHT);
                }
            }
        }
}

void anotherpartofmainProgress()
{
    SDL_Event e;
    spaceship Spacecraft(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    while(Spacecraft.inside(0,0, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        Spacecraft.move();
        SDL_SetRenderDrawColor(gRenderer, GRAY_COLOR.r, GRAY_COLOR.g, GRAY_COLOR.b, 0);

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

        }
        /*

        if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
        {

            pBullet->loadTextureBullet(gRenderer, 1);
            pBullet->Render(gRenderer);
            cout << pBullet->getIsMove() << endl;


        }*/
    }
}

void mainProgress()
{
    // main loop flag
    bool quit = false;

    //Event handler
    //SDL_Event e;
    spaceship Spacecraft(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

    Spacecraft.loadTexture("Image//spacecraft.png", gRenderer);

    Spacecraft.Render(gRenderer);

    SDL_RenderPresent(gRenderer);

    SDL_Rect BackgroundRect;
    BackgroundRect.x = 0;
    BackgroundRect.y = 0;
    BackgroundRect.w = BACKGROUND_WIDTH;
    BackgroundRect.h = BACKGROUND_HEIGHT;
    gBackground = SDLCommonFunc::loadTexture("Image//background.png", gRenderer);
    SDL_RenderCopy(gRenderer, gBackground, NULL, &BackgroundRect);

    while(Spacecraft.inside(0,0, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        Spacecraft.move();
        SDL_SetRenderDrawColor(gRenderer, GRAY_COLOR.r, GRAY_COLOR.g, GRAY_COLOR.b, 0);
        SDL_RenderCopy(gRenderer, gBackground, NULL, &BackgroundRect);
        Spacecraft.Render(gRenderer);
        SDL_RenderPresent(gRenderer);

        SDL_Delay(100);

        if(SDL_PollEvent(&gEvent) == 0)
        {
            continue;
        }

        if(gEvent.type == SDL_QUIT)
        {
            break;
        }

        Spacecraft.handleEvent(gEvent, gRenderer);

        // SDL_WaitEvent - nó đợi vô thời hạn
        // lên đọc so sánh PollEvent và WaitEven để xem khác biệt

        //if(e.type == SDL_QUIT) break;

    }

    /*
    while(!quit)
    {
        while(SDL_PollEvent(&gEvent))
        {
            Spacecraft.move();
            if(gEvent.type == SDL_QUIT)
            {
                Spacecraft.handleEvent(gEvent, gRenderer);

            Spacecraft.Render(gRenderer);

            SDL_RenderPresent(gRenderer);

            SDL_Delay(200);
                quit = true;
                break;
            }
        }
    }*/
}

int main(int argc, char* argv[])
{
    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        mainProgress();
        /*
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
        }*/
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

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    //load PNG texture
    gBackground = SDLCommonFunc::loadTexture("Image//background.png", gRenderer);
    if(gBackground == NULL)
    {
        printf("Failed to load background image! \n");
        success = false;
    }

    gSpacecraft = SDLCommonFunc::loadTexture("Image//spacecraft.png", gRenderer);
    if(gSpacecraft == NULL)
    {
        printf("Failed to load spacecraft image");
    }
    return success;
}

void close()
{
    ///Free loaded image
    SDL_DestroyTexture(gBackground);
    gBackground = NULL;

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
