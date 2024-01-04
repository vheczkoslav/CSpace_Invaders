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

void create_shield(Shield* shield, int x, int y) {
    for (int j = 0; j < 16; j++) {
        int pix_y = y + j * 4;
        for (int i = 0; i < 18; i++) {
            int pix_x = x + i * 4;
            if (shield_template[j][i] == '.') {
                shield->rect[j][i].destroyed = true;
            }
            else {
                shield->rect[j][i].destroyed = false;
            }
            shield->rect[j][i].rect.x = pix_x;
            shield->rect[j][i].rect.y = pix_y;
            shield->rect[j][i].rect.w = 4;
            shield->rect[j][i].rect.h = 4;
        }
    }
}

void load_textures(SDL_Texture *teksture[12], SDL_Renderer *rend){
    SDL_Surface *tmp = IMG_Load("sprites/top1.png");
    teksture[0] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/top2.png");
    teksture[1] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/mid1.png");
    teksture[2] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/mid2.png");
    teksture[3] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/bot1.png");
    teksture[4] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/bot2.png");
    teksture[5] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/ufo.png");
    teksture[6] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/player.png");
    teksture[7] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/shield.png");
    teksture[8] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/shot_pl.png");
    teksture[9] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/shot_al.png");
    teksture[10] = SDL_CreateTextureFromSurface(rend, tmp);
    tmp = IMG_Load("sprites/menu.png");
    teksture[11] = SDL_CreateTextureFromSurface(rend, tmp);
    free(tmp);
}

void restart_lvl(dynarray* projectilez){
    a_start_pos(aliens, 55);
    for(int k = 0; k < projectilez->size; k++){
        Shot* current_projectile = (Shot*) projectilez->items[k];
        dynarray_remove(projectilez, current_projectile);
    }
}

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
            if(UFO){
                if (currentShot->rect.x >= UFO->rect.x &&
                    currentShot->rect.x <= UFO->rect.x + UFO->rect.w
                    && currentShot->rect.y >= UFO->rect.y && currentShot->rect.y <= UFO->rect.y &&
                    UFO->alive == true) {
                    UFO->alive = false;
                    SCORE += UFO->score;
                    dynarray_remove(projectilez, currentShot);
                    break;
                }
            }
            if(currentShot->rect.x >= 100 && currentShot->rect.x <= 172){
                for(int y = 0; y < 16; y++){
                    for (int x = 0; x < 18; x++) {
                        if(currentShot->rect.x >= shields[0].rect[y][x].rect.x && currentShot->rect.x <= shields[0].rect[y][x].rect.x + shields[0].rect[y][x].rect.w
                           && currentShot->rect.y >= shields[0].rect[y][x].rect.y && currentShot->rect.y <= shields[0].rect[y][x].rect.y + shields[0].rect[y][x].rect.h
                           && !shields[0].rect[y][x].destroyed){
                            shields[0].rect[y][x].destroyed = true;
                            dynarray_remove(projectilez, currentShot);
                        }
                    }
                }
            }
            else if(currentShot->rect.x >= 275 && currentShot->rect.x <= 347){
                for(int y = 0; y < 16; y++){
                    for (int x = 0; x < 18; x++) {
                        if(currentShot->rect.x >= shields[1].rect[y][x].rect.x && currentShot->rect.x <= shields[1].rect[y][x].rect.x + shields[1].rect[y][x].rect.w
                           && currentShot->rect.y >= shields[1].rect[y][x].rect.y && currentShot->rect.y <= shields[1].rect[y][x].rect.y + shields[1].rect[y][x].rect.h
                           && !shields[1].rect[y][x].destroyed){
                            shields[1].rect[y][x].destroyed = true;
                            dynarray_remove(projectilez, currentShot);
                        }
                    }
                }
            }
            else if(currentShot->rect.x >= 450 && currentShot->rect.x <= 522){
                for(int y = 0; y < 16; y++){
                    for (int x = 0; x < 18; x++) {
                        if(currentShot->rect.x >= shields[2].rect[y][x].rect.x && currentShot->rect.x <= shields[2].rect[y][x].rect.x + shields[2].rect[y][x].rect.w
                           && currentShot->rect.y >= shields[2].rect[y][x].rect.y && currentShot->rect.y <= shields[2].rect[y][x].rect.y + shields[2].rect[y][x].rect.h
                           && !shields[2].rect[y][x].destroyed){
                            shields[2].rect[y][x].destroyed = true;
                            dynarray_remove(projectilez, currentShot);
                        }
                    }
                }
            }
            else if(currentShot->rect.x >= 625 && currentShot->rect.x <= 697){
                for(int y = 0; y < 16; y++){
                    for (int x = 0; x < 18; x++) {
                        if(currentShot->rect.x >= shields[3].rect[y][x].rect.x && currentShot->rect.x <= shields[3].rect[y][x].rect.x + shields[3].rect[y][x].rect.w
                           && currentShot->rect.y >= shields[3].rect[y][x].rect.y && currentShot->rect.y <= shields[3].rect[y][x].rect.y + shields[3].rect[y][x].rect.h
                           && !shields[3].rect[y][x].destroyed){
                            shields[1].rect[y][x].destroyed = true;
                            dynarray_remove(projectilez, currentShot);
                        }
                    }
                }
            }
            for(int j = 0; j < A_ROWS * A_IN_ROW; j++){
                if(currentShot->rect.x >= aliens[j].rect.x && currentShot->rect.x <= aliens[j].rect.x + aliens[j].rect.w
                && currentShot->rect.y >= aliens[j].rect.y && currentShot->rect.y <= aliens[j].rect.y && aliens[j].alive == true){
                    kill_alien(aliens, j, &SCORE);
                    dynarray_remove(projectilez, currentShot);
                    DEAD_ALIENS++;
                    break;
                }
            }
            for(int j = 0; j < projectilez->size; j++){
                Shot* currentProjectile = (Shot*) projectilez->items[j];
                if(currentProjectile->shooter == 1 && currentShot->rect.x >= currentProjectile->rect.x - 2 && currentShot->rect.x <= currentProjectile->rect.x + currentProjectile->rect.w + 2
                && currentShot->rect.y >= currentProjectile->rect.y && currentShot->rect.y <= currentProjectile->rect.y + currentProjectile->rect.h){
                    dynarray_remove(projectilez, currentShot);
                    dynarray_remove(projectilez, currentProjectile);
                }
            }
            if(currentShot->rect.y == 12){ dynarray_remove(projectilez, currentShot); }
            else{ currentShot->rect.y -= 2; } // no collision
        }
        else{
            if(currentShot->rect.x >= 100 && currentShot->rect.x <= 172){
                for(int y = 0; y < 16; y++){
                    for (int x = 0; x < 18; x++) {
                        if(currentShot->rect.x >= shields[0].rect[y][x].rect.x && currentShot->rect.x <= shields[0].rect[y][x].rect.x + shields[0].rect[y][x].rect.w
                           && currentShot->rect.y >= shields[0].rect[y][x].rect.y && currentShot->rect.y <= shields[0].rect[y][x].rect.y + shields[0].rect[y][x].rect.h
                           && !shields[0].rect[y][x].destroyed){
                            shields[0].rect[y][x].destroyed = true;
                            dynarray_remove(projectilez, currentShot);
                        }
                    }
                }
            }
            else if(currentShot->rect.x >= 275 && currentShot->rect.x <= 347){
                for(int y = 0; y < 16; y++){
                    for (int x = 0; x < 18; x++) {
                        if(currentShot->rect.x >= shields[1].rect[y][x].rect.x && currentShot->rect.x <= shields[1].rect[y][x].rect.x + shields[1].rect[y][x].rect.w
                           && currentShot->rect.y >= shields[1].rect[y][x].rect.y && currentShot->rect.y <= shields[1].rect[y][x].rect.y + shields[1].rect[y][x].rect.h
                           && !shields[1].rect[y][x].destroyed){
                            shields[1].rect[y][x].destroyed = true;
                            dynarray_remove(projectilez, currentShot);
                        }
                    }
                }
            }
            else if(currentShot->rect.x >= 450 && currentShot->rect.x <= 522){
                for(int y = 0; y < 16; y++){
                    for (int x = 0; x < 18; x++) {
                        if(currentShot->rect.x >= shields[2].rect[y][x].rect.x && currentShot->rect.x <= shields[2].rect[y][x].rect.x + shields[2].rect[y][x].rect.w
                           && currentShot->rect.y >= shields[2].rect[y][x].rect.y && currentShot->rect.y <= shields[2].rect[y][x].rect.y + shields[2].rect[y][x].rect.h
                           && !shields[2].rect[y][x].destroyed){
                            shields[2].rect[y][x].destroyed = true;
                            dynarray_remove(projectilez, currentShot);
                        }
                    }
                }
            }
            else if(currentShot->rect.x >= 625 && currentShot->rect.x <= 697){
                for(int y = 0; y < 16; y++){
                    for (int x = 0; x < 18; x++) {
                        if(currentShot->rect.x >= shields[3].rect[y][x].rect.x && currentShot->rect.x <= shields[3].rect[y][x].rect.x + shields[3].rect[y][x].rect.w
                           && currentShot->rect.y >= shields[3].rect[y][x].rect.y && currentShot->rect.y <= shields[3].rect[y][x].rect.y + shields[3].rect[y][x].rect.h
                           && !shields[3].rect[y][x].destroyed){
                            shields[1].rect[y][x].destroyed = true;
                            dynarray_remove(projectilez, currentShot);
                        }
                    }
                }
            }
            if(currentShot->rect.y == WIN_HEI - 24){ dynarray_remove(projectilez, currentShot); }
            if(currentShot->rect.x >= p->rect.x &&
               currentShot->rect.x <= p->rect.x + p->rect.w &&
               currentShot->rect.y >= p->rect.y &&
               currentShot->rect.y <= p->rect.y + p->rect.h){
                dynarray_remove(projectilez, currentShot);
                (*lives)--;
                restart_lvl(projectilez);
                if((*lives) == 0){
                    GAME = false;
                }
            }
            else{ currentShot->rect.y += 3; }
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

void render(SDL_Renderer *renderer, int* cas, SDL_Texture** textures, Alien* alienz, TTF_Font* font, Player* p, Shield* shieldz, dynarray* projectilez, Alien* oopho)
{
    SDL_RenderClear(renderer);

    info_text(renderer, font, "SCORE", SCORE, 0);
    info_text(renderer, font, "LVL", LVL, 325);
    info_text(renderer, font, "LIVES", LIVES, 650);

    for(int i = 0; i < SHIELD_COUNT; i++){
        for(int y = 0; y < 16; y++){
            for(int x = 0; x < 18; x++){
                if(shieldz[i].rect[y][x].destroyed == true){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                    SDL_RenderFillRect(renderer, &shieldz[i].rect[y][x].rect);
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    SDL_RenderFillRect(renderer, &shieldz[i].rect[y][x].rect);
                }
                SDL_SetRenderDrawColor(renderer, 0,0,0,0);
            }
        }
    }

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
            if( alienz[i].rect.x >= p->rect.x &&
                alienz[i].rect.x <= p->rect.x + p->rect.w &&
                alienz[i].rect.y >= p->rect.y &&
                alienz[i].rect.y <= p->rect.y + p->rect.h ){
                restart_lvl(projectilez);
                LIVES--;
            }
            SDL_RenderCopy(renderer, textures[index + (TICK_COUNT % 2)], NULL, &alienz[i].rect);
        }
    }

    if (UFO_SPAWNED)
    {
            if (UFO->alive == true) {
                SDL_RenderCopy(renderer, textures[6], NULL, &UFO->rect);
                UFO->rect.x += 1;
            }
        if (UFO->rect.x + 2 == 800)
        {
            UFO->alive = false;
            UFO_SPAWNED = false;
            free(UFO);
        }
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
    load_textures(textures, rend);

    int running = 1;
    int cas = 0;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 deltaTime = 0;
    const Uint32 targetFrameTime = 1000 / 60; // 60 frames per second

    // Alien* aliens defined in main.h for scope reasons
    aliens = (Alien *)malloc(sizeof(Alien) * A_ROWS * A_IN_ROW);
    a_start_pos(aliens, A_ROWS * A_IN_ROW);

    Player p = {.rect.x = WIN_WID / 2 - 9, .rect.y = WIN_HEI - 36, .alive = true, .rect.w = 36, .rect.h = 24};

    shields = (Shield*)malloc(sizeof(Shield) * SHIELD_COUNT);
    create_shield(&shields[0], 100, WIN_HEI - 144);
    create_shield(&shields[1], 275, WIN_HEI - 144);
    create_shield(&shields[2], 450, WIN_HEI - 144);
    create_shield(&shields[3], 625, WIN_HEI - 144);

    dynarray projectiles;
    dynarray_init(&projectiles, 1);

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("fonts/space_invaders.ttf", 18);
    if(font == NULL){
        perror("Font not loaded correctly!\n");
        return 1;
    }

    SDL_Rect menu_rect = {0,0,800,700};
    int mx = 0, my = 0;

        enum direction dir = NONE;
        while (running == 1)
        {
            if(!GAME){
                SDL_RenderClear(rend);
                while(SDL_PollEvent(&event)){
                    if (event.type == SDL_QUIT)
                    {
                        running = 0;
                    }
                    if( event.type == SDL_KEYDOWN ){
                        if( event.key.keysym.sym == SDLK_SPACE){
                            GAME = true;
                        }
                    }
                    else if ( event.type == SDL_MOUSEBUTTONDOWN ){
                        if( event.button.button == SDL_BUTTON_LEFT ){
                            SDL_GetMouseState(&mx, &my);
                            printf("x: %d\ny: %d\n", mx, my);
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
                            if(SHOOT_DELAY == 30){
                                player_shoot(&p, &projectiles);
                                SHOOT_DELAY = 0;
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

                render(rend, &cas, textures, aliens, font, &p, shields,&projectiles, UFO);

                if(TICK_COUNT % 24 == 0){
                    cas = 0;
                    if(TICK - 5 > TICK_LIMIT){
                        TICK -=5;
                    }
                    else{
                        TICK = TICK_LIMIT;
                    }
                }

                if(cas % 240 == 0){
                    alien_shoot(aliens, &projectiles);
                }
                if (cas % TICK == 0)
                {
                    aliens_move(aliens, A_ROWS * A_IN_ROW, TICK_COUNT);
                    printf("cas: %d\ntick count: %d\ntick: %d\n", cas, TICK_COUNT, TICK);
                    TICK_COUNT++;
                }
                if(SHOOT_DELAY != 30){
                    SHOOT_DELAY++;
                }
                cas++;
                if(DEAD_ALIENS == 55){
                    LVL++;
                    if(TICK - 5 > TICK_LIMIT){
                        TICK -=5;
                    }
                    else{
                        TICK = TICK_LIMIT;
                    }
                    restart_lvl(&projectiles);
                    DEAD_ALIENS = 0;
                }
                if (TICK_COUNT % 48 == 0 && !UFO_SPAWNED)
                {
                    UFO = (Alien*)malloc(sizeof(Alien));
                    UFO->rect.x = 0;
                    UFO->rect.y = 40;
                    UFO->rect.h = 6 * 4;
                    UFO->rect.w = 14 * 4;
                    UFO->alive = true;
                    UFO->score = 100;
                    UFO->a_type = UFO_SPECIAL;
                    UFO_SPAWNED = true;
                }

                lastTime = currentTime;
            }
        }

    for (int i = 0; i < 11; i++)
        SDL_DestroyTexture(textures[i]);

    free_aliens(aliens);
    free(shields);
    dynarray_free(&projectiles);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    return 0;
}