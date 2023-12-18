//HEC 0083 - SDL(2) project:
///////////////////////////////////////////////////////////////////////////////////////
// ##### ##### ##### ##### #####   ##### #    # #   # ##### ####  ##### ##### #####  //
// #     #   # #   # #     #         #   ##   # #   # #   # #   # #     #   # #      //
// ##### ##### ##### #     #####     #   #  # #  # #  ##### #   # ##### ##### #####  //
//     # #     #   # #     #         #   #   ##  # #  #   # #   # #     ###       #  //
// ##### #     #   # ##### #####   ##### #    #   #   #   # ####  ##### #   # #####  //
///////////////////////////////////////////////////////////////////////////////////////

#include <SDL2/SDL.h>
#include "main.h"
#include "aliens.h"

// gcc main.c aliens.c -lSDL2 -lSDL2_image -g -fsanitize=address -o main && ./main
// cmake . && make && ./main

void render(SDL_Renderer* renderer, int* cas){
    SDL_RenderClear(renderer);


    if(*cas % TICK == 0){
        printf("cas: %d\ntick count: %d\n", *cas, TICK_COUNT);
        TICK_COUNT++;
    }
    (*cas)++;
    return;
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_DisplayMode SDL_DM; SDL_GetCurrentDisplayMode(0, &SDL_DM);
    int monitor_width = SDL_DM.w; int monitor_height = SDL_DM.h;
    int window_x = (monitor_width - WIN_WID) / 2; int window_y = (monitor_height - WIN_HEI) / 2;
    SDL_Window* window = SDL_CreateWindow("Space Invaders - HEC0083", window_x, window_y, WIN_WID, WIN_HEI, SDL_WINDOW_SHOWN);
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    int running = 1;
    int cas = 0;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 deltaTime = 0;
    const Uint32 targetFrameTime = 1000 / 60;  // 60 frames per second

    Alien* aliens;
    aliens = (Alien*)malloc(sizeof(Alien) * A_ROWS * A_IN_ROW);
    a_start_pos(aliens, A_ROWS * A_IN_ROW);
    add_a_textures(aliens, rend, A_ROWS * A_IN_ROW);

    while (running == 1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;

        if (deltaTime < targetFrameTime) {
            SDL_Delay(targetFrameTime - deltaTime);
        }

        render(rend, &cas);

        SDL_RenderPresent(rend);
        lastTime = currentTime;
    }

    free_aliens(aliens, A_ROWS * A_IN_ROW);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    return 0;
}