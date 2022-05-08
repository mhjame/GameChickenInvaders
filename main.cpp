#include "Common_Function.h"
#include "Base.h"
#include "Spaceship.h"
#include "Weapon.h"
#include "Chicken.h"
#include "Explosion.h"

//loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//the wwindow renderer
SDL_Renderer* gRenderer = NULL;

bool init();
bool loadMedia();
void close();

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

    // Apply background
    //int background_y = 0;

    SDL_Rect BackgroundRect;
    BackgroundRect.x = 0;
    BackgroundRect.y = 0;
    BackgroundRect.w = BACKGROUND_WIDTH;
    BackgroundRect.h = BACKGROUND_HEIGHT;
    gBackground = SDLCommonFunc::loadTexture("Image//background.png", gRenderer);

    SDL_RenderCopy(gRenderer, gBackground, NULL, &BackgroundRect);

    // init exp main

    Explosion exp_main;
    bool ret = exp_main.loadTexture("Image//exp.png", gRenderer);
    exp_main.set_clip();
    if(!ret) return;


    // Make chicken
    Chicken* pChickens = new Chicken[NUM_CHICKENS + 5];

    for(int i = 1; i < NUM_CHICKENS; ++i)
    {
        Chicken* pChicken = (pChickens + i);
        if(pChicken == NULL) return;
        bool ret = pChicken->loadTexture("Image//chicken_red1.png", gRenderer);
        if(ret == false) {
            return;
        }
        //pChicken->Render(gRenderer);
        //SDL_RenderPresent(gRenderer);

        int pCX = 0 + i*100;
        int pCY = 0;
        //int pCY = rand()%400;

        pChicken->setRect(pCX , pCY);
        if(ret == false) {return;}

        pChicken->set_x_val(10);
        weaponOb* p_Weapon_chicken = new weaponOb();
        pChicken->initWeapon(p_Weapon_chicken, gRenderer);
        pChicken->set_isLive(true);

        /*
        p_Weapon->Render(gRenderer);
        SDL_RenderPresent(gRenderer);*/
    }


    int countHeart = 30;
    Spacecraft.setHeart(countHeart);

    while(Spacecraft.inside(0,0, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        // apply backgound
        //background_y += 2;

        SDL_SetRenderDrawColor(gRenderer, GRAY_COLOR.r, GRAY_COLOR.g, GRAY_COLOR.b, 0);
        SDL_RenderCopy(gRenderer, gBackground, NULL, &BackgroundRect);

        SDL_Rect BackgroundRect2 = BackgroundRect;
        BackgroundRect2.y -= SCREEN_HEIGHT;
        SDL_RenderCopy(gRenderer, gBackground, NULL, &BackgroundRect2);

        BackgroundRect.y += 2;

        if(BackgroundRect.y >= SCREEN_HEIGHT)
        {
            BackgroundRect.y = 0;
        }

        Spacecraft.Render(gRenderer);
        //SDL_RenderPresent(gRenderer);

        if(gEvent.type == SDL_QUIT)
        {
            break;
        }

        Spacecraft.handleEvent(gEvent, gRenderer, g_sound_bullet);
        // truyền g_sound_bullet thì ok, g_sound_bullet[2] thì ko đc
        Spacecraft.makeWeaponList(gRenderer); // make bullet list of spacecraft

        //cout << Spacecraft.getWeaponList().size() << endl;
        // Run Chicken

        for(int t = 1; t < NUM_CHICKENS; ++t)
        {
            Chicken *pChicken = (pChickens + t);
            if(pChicken)
            {
                if(pChicken->get_isLive() == false){continue;}
                /*SDL_Rect srcRect = pChicken->getSrcRect();
                srcRect.x += CHICKEN_W;
                int lim_x = pChicken->getRect().w;

                if(srcRect.x >= lim_x)
                {
                    srcRect.x = 0;
                    srcRect.y = 0;
                    srcRect.w = CHICKEN_W;
                    srcRect.h = CHICKEN_H;
                }*/

                pChicken->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);

                //cout << pChicken->getRect().x << " " << pChicken->getRect().y << " " << pChicken->getRect().w << " " << pChicken->getRect().h << endl;
                pChicken->useWeapon(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
                //p_Weapon_chicken->Render(gRenderer);
                pChicken->Render(gRenderer);
                //SDL_RenderPresent(gRenderer);

                bool is_col = SDLCommonFunc::CheckCollision(Spacecraft.getRect(), pChicken->getRect());
                if(is_col)
                {
                    Mix_PlayChannel(-1, g_sound_exp[0], 0);
                    // xuly vu no spacecraft and chicken
                    for(int ex = 0; ex < 8; ++ex)
                    {
                        int x_pos = (Spacecraft.getRect().x + Spacecraft.getRect().w/2) - WIDTH_FRAME_EXP/2;
                        int y_pos = (Spacecraft.getRect().y + Spacecraft.getRect().h/2) - HEIGHT_FRAME_EXP/2;

                        exp_main.set_frame(ex);
                        exp_main.setRect(x_pos, y_pos);
                        exp_main.show(gRenderer);
                        SDL_RenderPresent(gRenderer);
                        SDL_Delay(100);
                    }

                    //SDL_Delay(500);
                    //cout << "have collision - game over!" << endl;
                    delete [] pChickens;

                    close();
                    return;
                }

                //xuly đạn bắn



                std::vector<weaponOb*> bulletList = Spacecraft.getWeaponList();
                //cout << Spacecraft.getWeaponList().size() << endl;

                for(int id = 0; id < bulletList.size(); ++id)
                {
                    weaponOb *pBullet = bulletList.at(id);
                    if(pBullet != NULL)
                    {
                       // cout << pBullet->getRect().x << " " << pBullet->getRect().y
                                //<< " " << pBullet->getRect().w << " " << pBullet->getRect().h << endl;

                        bool bulShoot = SDLCommonFunc::CheckCollision(pBullet->getRect(), pChicken->getRect());
                        if(bulShoot)
                        {
                            Spacecraft.RemoveWeapon(id);
                            pChicken->set_isLive(false);

                            Mix_PlayChannel(-1, g_sound_exp[0], 0);

                            // xuly vu no khi chicken was shooted
                            for(int ex = 0; ex < 8; ++ex)
                            {
                                int x_pos = (pChicken->getRect().x + pChicken->getRect().w/2) - WIDTH_FRAME_EXP/2;
                                int y_pos = (pChicken->getRect().y + pChicken->getRect().h/2) - HEIGHT_FRAME_EXP/2;

                                exp_main.set_frame(ex);
                                exp_main.setRect(x_pos, y_pos);
                                exp_main.show(gRenderer);
                                SDL_RenderPresent(gRenderer);
                                //SDL_Delay(10);
                            }
                        }
                    }
                }

                // xuly egg shooting spacecraft

                std::vector<weaponOb*> eggList = pChicken->getWeaponList();

                for(int ide = 0; ide < eggList.size(); ++ide)
                {
                    weaponOb *pEgg = eggList.at(ide);
                    if(pEgg != NULL)
                    {
                        bool eggShoot = SDLCommonFunc::CheckCollision(pEgg->getRect(), Spacecraft.getRect());
                        if(eggShoot)
                        {
                            int cntHeart = Spacecraft.getHeart();
                            cntHeart-= 1;
                            cout << cntHeart << endl;
                            if(cntHeart > 0)
                            {
                                Spacecraft.setHeart(cntHeart);
                            }
                            else
                            {
                                cout << "your spacecraft was crash" << endl;
                                SDL_Delay(1000);
                                return;
                            }
                        }
                    }
                }

            }
        }

        // SDL_WaitEvent - nó đợi vô thời hạn
        // lên đọc so sánh PollEvent và WaitEven để xem khác biệt

        //if(e.type == SDL_QUIT) break;

        SDL_RenderPresent(gRenderer);

        if(SDL_PollEvent(&gEvent) == 0)
        {
            continue;
        }

    }

    delete [] pChickens;
}

int main(int argc, char* argv[])
{
    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        //thu();
        mainProgress();
        close();
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

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;

    // Read file wav audio
    g_sound_bullet[0] = Mix_LoadWAV("Sound//sound_blaster.wav");
    g_sound_bullet[1] = Mix_LoadWAV("Sound//sound_boron.wav");
    g_sound_exp[0] = Mix_LoadWAV("Sound//sound_exp.wav");

    if(g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_exp[0] == NULL) return false;

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
