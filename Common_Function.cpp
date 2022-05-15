#include "Common_Function.h"
#include "Text.h"

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

bool SDLCommonFunc::checkFocusWithRect(int x, int y, SDL_Rect &rect)
{
    if(x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) return true;
    return false;
}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
      int bottom_a = object1.y + object1.h;

      int left_b = object2.x;
      int right_b = object2.x + object2.w;
      int top_b = object2.y;
      int bottom_b = object2.y + object2.h;

      // Case 1: size object 1 < size object 2
      if (left_a > left_b && left_a < right_b)
      {
        if (top_a > top_b && top_a < bottom_b)
        {
          return true;
        }
      }

      if (left_a > left_b && left_a < right_b)
      {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
          return true;
        }
      }

      if (right_a > left_b && right_a < right_b)
      {
        if (top_a > top_b && top_a < bottom_b)
        {
          return true;
        }
      }

      if (right_a > left_b && right_a < right_b)
      {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
          return true;
        }
      }

      // Case 2: size object 1 < size object 2
      if (left_b > left_a && left_b < right_a)
      {
        if (top_b > top_a && top_b < bottom_a)
        {
          return true;
        }
      }

      if (left_b > left_a && left_b < right_a)
      {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
          return true;
        }
      }

      if (right_b > left_a && right_b < right_a)
      {
        if (top_b > top_a && top_b < bottom_a)
        {
          return true;
        }
      }

      if (right_b > left_a && right_b < right_a)
      {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
          return true;
        }
      }

       // Case 3: size object 1 = size object 2
      if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
      {
        return true;
      }

      return false;
}



int SDLCommonFunc::showMenu(SDL_Renderer *renderer, TTF_Font* font)
{
    //g_sound_start = Mix_LoadMUS("Sound//sound_start.mp3");

    //if(g_sound_start == NULL) return false;
    //Mix_PlayMusic(g_sound_start, -1);

    g_click = Mix_LoadMUS("Sound//sound_buttonClick.mp3");

    if(g_click == NULL) return false;

    g_img_menu = SDLCommonFunc::loadTexture("Image//menu.png", renderer);
    if(g_img_menu == NULL)
    {
        return 1;
    }

    const int cntMenuItem = 2;
    SDL_Rect pos_arr[cntMenuItem];
    pos_arr[0].x = SCREEN_WIDTH/2 - 100;
    pos_arr[0].y = SCREEN_HEIGHT*2/3;

    pos_arr[1].x = SCREEN_WIDTH/2 -100 ;
    pos_arr[1].y = SCREEN_HEIGHT*2/3 + 50;

    textOb text_menu[cntMenuItem];
    text_menu[0].setText("PLAY GAME");
    text_menu[0].setTextColor(textOb::BLACK_TEXT);
    text_menu[0].setRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].setText("EXIT");
    text_menu[1].setTextColor(textOb::BLACK_TEXT);
    text_menu[1].setRect(pos_arr[1].x, pos_arr[1].y);

    bool selected[cntMenuItem] = {0, 0};
    int xm = 0;
    int ym = 0;

    SDL_Event m_event;
    while(true)
    {
        SDL_RenderCopy(renderer, g_img_menu, NULL, NULL);
        for(int i = 0; i < cntMenuItem; ++i)
        {
            text_menu[i].createGameText(font, renderer);
        }

        while(SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT:
                return 1;
            case SDL_MOUSEMOTION:
                {
                    xm = m_event.motion.x;
                    ym = m_event.motion.y;

                    for(int i = 0; i < cntMenuItem; ++i)
                    {
                        SDL_Rect rect = text_menu[i].getRect();
                        if(checkFocusWithRect(xm, ym, rect))
                        {
                            if(selected[i] == false){selected[i] = true;}
                            text_menu[i].setTextColor(textOb::WHITE_TEXT);
                            text_menu[i].createGameText(font, renderer);
                            //SDL_RenderPresent(renderer);
                        }
                        else
                        {
                            if(selected[i] == true)
                            {
                                selected[i] == false;
                                text_menu[i].setTextColor(textOb::BLACK_TEXT);
                                text_menu[i].createGameText(font, renderer);
                            }
                        }
                    }
                }
            case SDL_MOUSEBUTTONDOWN:
                if(m_event.button.button == SDL_BUTTON_LEFT)
                {
                    Mix_PlayMusic(g_click, 0);
                    xm = m_event.button.x;
                    ym = m_event.button.y;

                    for(int i = 0; i < cntMenuItem; ++i)
                    {
                        SDL_Rect rect = text_menu[i].getRect();
                        if(checkFocusWithRect(xm, ym, rect))
                        {
                            return i;
                        }
                    }
                }
                break;


            case SDL_KEYDOWN:
                if(m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1; //exit
                    break;
                }
            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    return 1;
}

