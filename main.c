// HEC 0083 - SDL(2) project:
///////////////////////////////////////////////////////////////////////////////////////
// ##### ##### ##### ##### #####   ##### #    # #   # ##### ####  ##### ##### #####  //
// #     #   # #   # #     #         #   ##   # #   # #   # #   # #     #   # #      //
// ##### ##### ##### #     #####     #   #  # #  # #  ##### #   # ##### ##### #####  //
//     # #     #   # #     #         #   #   ##  # #  #   # #   # #     ###       #  //
// ##### #     #   # ##### #####   ##### #    #   #   #   # ####  ##### #   # #####  //
///////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "aliens.h"
#include <SDL2/SDL.h>

// gcc main.c aliens.c -lSDL2 -lSDL2_image -g -fsanitize=address -o main && ./main
// cmake . && make && ./main

void player_move(Player* player, enum direction d){
    if(d == LEFT && player->rect.x > 12){
        player->rect.x -= 2;
    }
    if(d == RIGHT && player->rect.x < WIN_WID-player->rect.w-12){
        player->rect.x += 2;
    }
    if( d == NONE){  }
}

void player_shoot(Player* player, dynarray* projectilez){
    Shot* s; s = (Shot*)malloc(sizeof(Shot));
    s->rect.x = player->rect.x + 16;
    s->rect.y = player->rect.y - 12;
    s->rect.w = 4;
    s->rect.h = 12;
    s->shooter = 0;
    dynarray_push(projectilez, s);
}

void shoot_move(dynarray* projectilez, Player* p, int* lives){
    // This function is also handling collision check in addition to movement
    for(int i = 0; i < projectilez->size; i++){
        Shot* currentShot = (Shot*) projectilez->items[i];
        if(currentShot->shooter == 0){
            for(int j = 0; j < A_ROWS * A_IN_ROW; j++){
                if(currentShot->rect.x >= aliens[j].rect.x && currentShot->rect.x <= aliens[j].rect.x + aliens[j].rect.w
                && currentShot->rect.y >= aliens[j].rect.y && currentShot->rect.y <= aliens[j].rect.y && aliens[j].alive == true){
                    kill_alien(aliens, j, &SCORE);
                    dynarray_remove(projectilez, currentShot);
                    break;
                }
            }
            for(int j = 0; j < 4; j++){
                if(currentShot->rect.x >= shields[j].rect.x && currentShot->rect.x <= shields[j].rect.x + shields[j].rect.w
                && currentShot->rect.y >= shields[j].rect.y && currentShot->rect.y <= shields[j].rect.y){
                    dynarray_remove(projectilez, currentShot);
                }
            }
            if(currentShot->rect.y == 12){ dynarray_remove(projectilez, currentShot); }
            else{ currentShot->rect.y -= 2; } // no collision
        }
        else{
            for(int j = 0; j < 4; j++){
                if(currentShot->rect.x >= shields[j].rect.x && currentShot->rect.x <= shields[j].rect.x + shields[j].rect.w
                   && currentShot->rect.y >= shields[j].rect.y && currentShot->rect.y <= shields[j].rect.y){
                    dynarray_remove(projectilez, currentShot);
                }
            }
            if(currentShot->rect.y == WIN_HEI - 24){ dynarray_remove(projectilez, currentShot); }
            if(currentShot->rect.x >= p->rect.x &&
               currentShot->rect.x <= p->rect.x + p->rect.w &&
               currentShot->rect.y >= p->rect.y &&
               currentShot->rect.y <= p->rect.y + p->rect.h){
                dynarray_remove(projectilez, currentShot);
                a_start_pos(aliens, A_ROWS * A_IN_ROW);
                (*lives)--;
                for(int k = 0; k < projectilez->size; k++){
                    Shot* current_projectile = (Shot*) projectilez->items[k];
                    dynarray_remove(projectilez, current_projectile);
                }
                if((*lives) == 0){
                    GAME = false;
                }
            }
            else{ currentShot->rect.y += 2; }
        }
    }
}

void info_text(SDL_Renderer *renderer, TTF_Font *font, char* text, int DATA, int r){
    char buffer_text[40];
    snprintf(buffer_text, 40, "%s: %d", text, DATA);
    SDL_Color buffer_color = {255, 255, 255, 255};
    SDL_Surface* buffer_surface = TTF_RenderText_Solid(font, buffer_text, buffer_color);
    SDL_Texture* buffer_texture = SDL_CreateTextureFromSurface(renderer, buffer_surface);
    SDL_Rect buffer_rect = {.x = r, .y = 0};
    buffer_rect.h = 30;
    buffer_rect.w = 150; // 20 * strlen(score_text);
    SDL_RenderCopyEx(renderer, buffer_texture, NULL, &buffer_rect, 0, NULL, SDL_FLIP_NONE);

    SDL_DestroyTexture(buffer_texture); SDL_FreeSurface(buffer_surface);
}

void render(SDL_Renderer *renderer, int* cas, SDL_Texture** textures, Alien* alienz, TTF_Font* font, Player* p, Shield* shieldz, dynarray* projectilez)
{
    SDL_RenderClear(renderer);

    info_text(renderer, font, "SCORE", SCORE, 0);
    info_text(renderer, font, "LVL", LVL, 325);
    info_text(renderer, font, "LIVES", LIVES, 650);

    for(int p = 0; p < projectilez->size; p++){
        Shot* currentShot = (Shot*) projectilez->items[p];
        if(currentShot->shooter == 0){
            SDL_RenderCopy(renderer, textures[9], NULL, &currentShot->rect);
        }
        if(currentShot->shooter == 1){
            SDL_RenderCopy(renderer, textures[10], NULL, &currentShot->rect);
        }
    }

    if(p->alive == true){
        SDL_RenderCopy(renderer, textures[7], NULL, &p->rect);
    }

    for(int i = 0; i < A_ROWS * A_IN_ROW; i++){
        if(alienz[i].alive == true){
            // [0] - [5] -> top1/2, mid1/2, bot1/2
            int index = 0;
            if(alienz[i].id >= 0 && alienz[i].id < 11){ index = 0; } // 0 - 10 (11)
            if(alienz[i].id >= 11 && alienz[i].id < 33){ index = 2; } // 11 - 32 (22)
            if(alienz[i].id >= 33 && alienz[i].id < 55){ index = 4; } // 33 - 54 (22)
            SDL_RenderCopy(renderer, textures[index + (TICK_COUNT % 2)], NULL, &alienz[i].rect);
        }
    }

    for(int i = 0; i < 4; i++){
        SDL_RenderCopy(renderer, textures[8], NULL, &shieldz[i].rect);
    }

    SDL_RenderPresent(renderer);
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

    SDL_Texture *textures[12];
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
    tmp = IMG_Load("sprites/shot_pl.png");
    textures[9] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/shot_al.png");
    textures[10] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/menu.png");
    textures[11] = SDL_CreateTextureFromSurface(rend, tmp);

    int running = 1;
    int cas = 0;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 deltaTime = 0;
    const Uint32 targetFrameTime = 1000 / 60; // 60 frames per second

    // Alien* aliens defined in main.h for scope reasons
    aliens = (Alien *)malloc(sizeof(Alien) * A_ROWS * A_IN_ROW);
    a_start_pos(aliens, A_ROWS * A_IN_ROW);

    Player p = {.rect.x = WIN_WID / 2 - 9, .rect.y = WIN_HEI - 36, .alive = true, .rect.w = 36, .rect.h = 24};

    shields = (Shield *)malloc(sizeof(Shield) * 4);
    for(int s = 0; s < 4; ++s){
        shields[s].rect.w = 18 * 4;
        shields[s].rect.h = 16 * 4;
        shields[s].rect.y = WIN_HEI - 144;
    }
    shields[0].rect.x = 100; shields[1].rect.x = 275; shields[2].rect.x = 450; shields[3].rect.x = 625;

    dynarray projectiles;
    dynarray_init(&projectiles, 1);

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("fonts/space_invaders.ttf", 18);
    if(font == NULL){
        perror("Font not loaded correctly!\n");
        return 1;
    }

    SDL_Rect menu_rect = {0,0,800,700};

        enum direction dir = NONE;
        while (running == 1)
        {
            if(!GAME){
                SDL_RenderClear(rend);
                while(SDL_PollEvent(&event)){
                    if( event.type == SDL_KEYDOWN ){
                        if( event.key.keysym.sym == SDLK_SPACE){
                            GAME = true;
                        }
                    }
                }

                Uint32 currentTime = SDL_GetTicks();
                deltaTime = currentTime - lastTime;

                if (deltaTime < targetFrameTime)
                {
                    SDL_Delay(targetFrameTime - deltaTime);
                }

                SDL_RenderCopy(rend, textures[11], NULL, &menu_rect);
                SDL_RenderPresent(rend);

                lastTime = currentTime;
            }
            else{
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
                        if( event.key.keysym.sym == SDLK_LEFT ){
                            MOVING = true; dir = LEFT;
                        }
                        if( event.key.keysym.sym == SDLK_RIGHT ){
                            MOVING = true; dir = RIGHT;
                        }
                    }
                    else if( event.type == SDL_KEYUP ){
                        if( event.key.keysym.sym == SDLK_SPACE ){
                            if(SHOOT_DELAY == 180){
                                player_shoot(&p, &projectiles);
                                SHOOT_DELAY = 0;
                                //printf("Shoot!\n");
                            }
                        }
                        if( event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT){
                            MOVING = false; dir = NONE;
                        }
                    }
                }
                player_move(&p, dir);
                shoot_move(&projectiles, &p, &LIVES);

                Uint32 currentTime = SDL_GetTicks();
                deltaTime = currentTime - lastTime;

                if (deltaTime < targetFrameTime)
                {
                    SDL_Delay(targetFrameTime - deltaTime);
                }

                render(rend, &cas, textures, aliens, font, &p, shields, &projectiles);

                if(cas % 240 == 0){
                    alien_shoot(aliens, &projectiles);
                }

                if (cas % TICK == 0)
                {
                    aliens_move(aliens, A_ROWS * A_IN_ROW, TICK_COUNT);
                    //printf("cas: %d\ntick count: %d\n", cas, TICK_COUNT);
                    TICK_COUNT++;
                }
                cas++;
                if(SHOOT_DELAY != 180){
                    SHOOT_DELAY++;
                }

                lastTime = currentTime;
            }
        }

    for (int i = 0; i < 11; i++)
        SDL_DestroyTexture(textures[i]);

    free_aliens(aliens);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    return 0;
}