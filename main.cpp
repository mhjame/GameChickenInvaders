#include "Common_Function.h"
#include "Base.h"
#include "Spaceship.h"
#include "Weapon.h"
#include "Chicken.h"
#include "Explosion.h"
#include "PlayerPower.h"
#include "Text.h"
TTF_Font *g_font_text = NULL;
TTF_Font *g_menu_text = NULL;
//loads individual image as texture
SDL_Texture* loadTexture(std::string path);
//the wwindow renderer
SDL_Renderer* gRenderer = NULL;
bool init();
bool loadMedia();
void close();
Explosion exp_main;
void explose();
void mainProgress();

void chickenFly(int &x_pos, int&y_pos, int& time_delay, Chicken *pChicken)
{
    for(int chic = 0; chic < 18; ++chic)
    {
        pChicken->set_frame(chic);
        pChicken->setRect(x_pos, y_pos);
        pChicken->show(gRenderer);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(time_delay);
    }
}

void thu()
{
    SDL_Rect BackgroundRect;
    BackgroundRect.x = 0;
    BackgroundRect.y = 0;
    BackgroundRect.w = BACKGROUND_WIDTH;
    BackgroundRect.h = BACKGROUND_HEIGHT;
    gBackground = SDLCommonFunc::loadTexture("Image//background.png", gRenderer);
    SDL_RenderCopy(gRenderer, gBackground, NULL, &BackgroundRect);

    Chicken *pChicken = new Chicken;
    bool ret = pChicken->loadTexture("Image//chicken_red.png", gRenderer);
    pChicken->set_clip();
    if(!ret){cout << "load chicken fail" << endl; return;}

    SDL_Rect rect = pChicken->getRect();
    cout << rect.w << " " << rect.w/18 << " " << rect.h << endl;

    int xp = 0;
    int yp = 0;
    int time_delay = 100;
    int loop = 20;
   // while(loop--)(chickenFly(xp, yp, time_delay, pChicken));
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
void explose(int &x_pos, int &y_pos, int& time_delay)
{
    for(int ex = 0; ex < 8; ++ex)
    {
        exp_main.set_frame(ex);
        exp_main.setRect(x_pos, y_pos);
        exp_main.show(gRenderer);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(time_delay);
    }
}

void mainProgress()
{
    int ret_menu = SDLCommonFunc::showMenu(gRenderer, g_menu_text);
    // main loop flag
    bool quit = false;
    if(ret_menu == 1){quit = true;}
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
    // make cnt heart
    playerPower player_power;
    player_power.init(gRenderer);
    player_power.show(gRenderer);
    // handling mark
    textOb mark_game;
    mark_game.setTextColor(textOb::WHITE_TEXT);
    unsigned int mark_val = 0;
    std::string str_mark_val = std::to_string(mark_val);
    std::string strMark = "MARK: " + str_mark_val;
    mark_game.setText(strMark);
    mark_game.createGameText(g_font_text, gRenderer);
    //mark_game.Render(gRenderer);
    textOb time_game;
    time_game.setTextColor(textOb::WHITE_TEXT);
    // init exp main
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
    //int countHeart = 30;
    //Spacecraft.setHeart(countHeart);
    //Spacecraft.inside(0,0, SCREEN_WIDTH, SCREEN_HEIGHT)
    while(quit == false)
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
        player_power.show(gRenderer);
        Spacecraft.Render(gRenderer);
        //SDL_RenderPresent(gRenderer);
        if(gEvent.type == SDL_QUIT)
        {
            quit = true;
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
                    int x_pos = (Spacecraft.getRect().x + Spacecraft.getRect().w/2) - WIDTH_FRAME_EXP/2;
                    int y_pos = (Spacecraft.getRect().y + Spacecraft.getRect().h/2) - HEIGHT_FRAME_EXP/2;
                    int time_delay = 100;
                    explose(x_pos, y_pos, time_delay);
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
                            mark_val += 10;
                            Spacecraft.RemoveWeapon(id);
                            pChicken->set_isLive(false);
                            // xuly vu no khi chicken was shooted
                            Mix_PlayChannel(-1, g_sound_exp[0], 0);
                            int x_pos = (pChicken->getRect().x + pChicken->getRect().w/2) - WIDTH_FRAME_EXP/2;
                            int y_pos = (pChicken->getRect().y + pChicken->getRect().h/2) - HEIGHT_FRAME_EXP/2;
                            int time_delay = 0;
                            explose(x_pos, y_pos, time_delay);
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
                            player_power.decrease();
                            int cntHeart = player_power.getNumber();
                            if(cntHeart > 0)
                            {
                                // Egg return to chicken when crash spacecraft
                                int pWX = pChicken->getRect().x + pChicken->getRect().w/2;
                                int pWY = pChicken->getRect().y + pChicken->getRect().h + 5;
                                pEgg->setRect(pWX, pWY);
                                int x_pos = (Spacecraft.getRect().x + Spacecraft.getRect().w/2) - WIDTH_FRAME_EXP/2;
                                int y_pos = (Spacecraft.getRect().y + Spacecraft.getRect().h/2) - HEIGHT_FRAME_EXP/2;
                                int time_delay = 0;
                                explose(x_pos, y_pos, time_delay);
                                SDL_Delay(1000);
                                Spacecraft.setHeart(cntHeart);
                            }
                            else
                            {
                                Mix_PlayChannel(-1, g_sound_exp[0], 0);
                                int x_pos = (Spacecraft.getRect().x + Spacecraft.getRect().w/2) - WIDTH_FRAME_EXP/2;
                                int y_pos = (Spacecraft.getRect().y + Spacecraft.getRect().h/2) - HEIGHT_FRAME_EXP/2;
                                int time_delay = 100;
                                explose(x_pos, y_pos, time_delay);
                                cout << "your spacecraft was crash" << endl;
                                SDL_Delay(1000);
                                return;
                            }
                        }
                    }
                }
            }
        }
        // show time for game
        std::string str_time = "TIME : ";
        Uint32 time_val = SDL_GetTicks()/1000;
        str_time += std::to_string(time_val);
        time_game.setText(str_time);
        int gX_pos = 25;
        int gY_pos = 100;
        time_game.setRect(gX_pos, gY_pos);
        time_game.createGameText(g_font_text, gRenderer);
        // SDL_WaitEvent - nó đợi vô thời hạn
        // lên đọc so sánh PollEvent và WaitEven để xem khác biệt
        //if(e.type == SDL_QUIT) break;
        // show mark_val to screen
        std::string str_mark_val = std::to_string(mark_val);
        std::string strMark = "MARK : " + str_mark_val;
        mark_game.setText(strMark);
        mark_game.createGameText(g_font_text, gRenderer);
        mark_game.Render(gRenderer);
        SDL_RenderPresent(gRenderer);
        if(SDL_PollEvent(&gEvent) == 0)
        {
            continue;
        }
    }

    delete [] pChickens;
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
    if(TTF_Init() == -1) success = false;
    g_font_text = TTF_OpenFont("Font//font1.ttf", 20);
    if(g_font_text == NULL) success = false;
    g_menu_text = TTF_OpenFont("Font//font1.ttf", 40);
    if(g_menu_text == NULL) success = false;
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
