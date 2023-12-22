// HEC 0083 - SDL(2) project:
///////////////////////////////////////////////////////////////////////////////////////
// ##### ##### ##### ##### #####   ##### #    # #   # ##### ####  ##### ##### #####  //
// #     #   # #   # #     #         #   ##   # #   # #   # #   # #     #   # #      //
// ##### ##### ##### #     #####     #   #  # #  # #  ##### #   # ##### ##### #####  //
//     # #     #   # #     #         #   #   ##  # #  #   # #   # #     ###       #  //
// ##### #     #   # ##### #####   ##### #    #   #   #   # ####  ##### #   # #####  //
///////////////////////////////////////////////////////////////////////////////////////

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"
#include "aliens.h"

// gcc main.c aliens.c -lSDL2 -lSDL2_image -g -fsanitize=address -o main && ./main
// cmake . && make && ./main

void render(SDL_Renderer *renderer, int *cas, SDL_Texture** textures, Alien* aliens, TTF_Font* font)
{
    SDL_RenderClear(renderer);

    char text[50];
    snprintf(text, 50, "SCORE: %d", SCORE);
    SDL_Color text_color = {255,255,255,255};
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, text_color);
    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect = {.x = 0, .y = 0};
    text_rect.h = 60;
    text_rect.w = 300; // 20 * strlen(text);
    SDL_RenderCopyEx(renderer, text_texture, NULL, &text_rect, 0, NULL, SDL_FLIP_NONE);

    for(int i = 0; i < A_ROWS * A_IN_ROW; i++){
        if(aliens[i].alive == true){
            // [0] - [5] -> top1/2, mid1/2, bot1/2
            int id = 0;
            if(aliens[i].id >= 0 && aliens[i].id < 11){ id = 0; }
            if(aliens[i].id >= 11 && aliens[i].id < 32){ id = 2; }
            if(aliens[i].id >= 32 && aliens[i].id < 54){ id = 4; }
            SDL_RenderCopy(renderer, textures[id + (TICK_COUNT % 2)], NULL, &aliens[i].rect);
        }
    }

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(text_texture); SDL_FreeSurface(text_surface);
    return;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode SDL_DM;
    SDL_GetCurrentDisplayMode(0, &SDL_DM);
    int monitor_width = SDL_DM.w;
    int monitor_height = SDL_DM.h;
    int window_x = (monitor_width - WIN_WID) / 2;
    int window_y = (monitor_height - WIN_HEI) / 2;
    SDL_Window *window = SDL_CreateWindow("Space Invaders - HEC0083", window_x, window_y, WIN_WID, WIN_HEI, SDL_WINDOW_SHOWN);
    SDL_Renderer *rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    SDL_Texture *textures[9];
    SDL_Surface *tmp = IMG_Load("sprites/top1.png");
    textures[0] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/top2.png");
    textures[1] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/mid1.png");
    textures[2] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/mid2.png");
    textures[3] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/bot1.png");
    textures[4] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/bot2.png");
    textures[5] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/ufo.png");
    textures[6] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/player.png");
    textures[7] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/shield.png");
    textures[8] = SDL_CreateTextureFromSurface(rend, tmp);

    int running = 1;
    int cas = 0;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 deltaTime = 0;
    const Uint32 targetFrameTime = 1000 / 60; // 60 frames per second

    // Alien* aliens defined in main.h for scope reasons
    aliens = (Alien *)malloc(sizeof(Alien) * A_ROWS * A_IN_ROW);
    a_start_pos(aliens, A_ROWS * A_IN_ROW);

    TTF_Font* font = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 24);

    while (running == 1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if ( event.type == SDL_KEYDOWN ) { // key pressed down
                if ( event.key.keysym.sym == SDLK_r ) {
                    running = 0;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) { // mouse button released
                // x: e.button.button.x
                // y: e.button.button.y
            }
        }
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;

        if (deltaTime < targetFrameTime)
        {
            SDL_Delay(targetFrameTime - deltaTime);
        }

        render(rend, &cas, textures, aliens, font);
        aliens_move(aliens, A_ROWS * A_IN_ROW, cas, TICK);

        if (cas % TICK == 0)
        {
            printf("cas: %d\ntick count: %d\n", cas, TICK_COUNT);
            TICK_COUNT++;
        }
        cas++;

        lastTime = currentTime;
    }

    for (int i = 0; i < 9; i++)
        SDL_DestroyTexture(textures[i]);

    free_aliens(aliens, A_ROWS * A_IN_ROW);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    return 0;
}