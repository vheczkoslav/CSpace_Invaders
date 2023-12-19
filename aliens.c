#include <SDL2/SDL.h>
#include "aliens.h"

void a_start_pos(Alien* aliens, int count){
    for(int i = 0; i < count; i++) {
        int this_row = (int) i / 11;
        switch (this_row) {
            case 0:
                int this_y = 70;
                aliens[i].a_type = TOP_KLINGON;
                aliens[i].texture_width = 12;
                aliens[i].texture_height = 14;
                aliens[i].score = 25;
                aliens[i].alive = true;
                aliens[i].id = i;
                aliens[i].y = y;
            break;
            case 1:
                int this_y = 81;
                aliens[i].a_type = MID_VULCAN;
                aliens[i].texture_width = 20;
                aliens[i].texture_height = 14;
                aliens[i].score = 20;
                aliens[i].alive = true;
                aliens[i].id = i;
                aliens[i].y = y;
                break;
            case 2:
                int this_y = 91;
                aliens[i].a_type = MID_VULCAN;
                aliens[i].texture_width = 20;
                aliens[i].texture_height = 14;
                aliens[i].score = 15;
                aliens[i].alive = true;
                aliens[i].id = i;
                aliens[i].y = y;
            case 3:
                int this_y = 101;
                aliens[i].a_type = BOT_REPTILIAN;
                aliens[i].texture_width = 20;
                aliens[i].texture_height = 14;
                aliens[i].score = 10;
                aliens[i].alive = true;
                aliens[i].id = i;
                aliens[i].y = y;
                break;
            case 4:
                int this_y = 111;
                aliens[i].a_type = BOT_REPTILIAN;
                aliens[i].texture_width = 20;
                aliens[i].texture_height = 14;
                aliens[i].score = 5;
                aliens[i].alive = true;
                aliens[i].id = i;
                aliens[i].y = y;
                break;
            default:
                perror("This... This should NOT happen :O\n");
                exit(0);
                }
            }
        return;
        }

void add_a_textures(Alien* aliens, SDL_Renderer* renderer, int count){
    for(int i = 0; i < count; i++) {
        int this_row = (int) i / 11;
        switch (this_row){
            case 0:
                aliens[i].texture = (SDL_Texture**) malloc(sizeof(SDL_Texture*) * 2);
                aliens[i].texture[0] = IMG_LoadTexture(renderer, "sprites/top1.png");
                aliens[i].texture[1] = IMG_LoadTexture(renderer, "sprites/top2.png");
                break;
            case 1:
                aliens[i].texture = (SDL_Texture**) malloc(sizeof(SDL_Texture*) * 2);
                aliens[i].texture[0] = IMG_LoadTexture(renderer, "sprites/mid1.png");
                aliens[i].texture[1] = IMG_LoadTexture(renderer, "sprites/mid2.png");
                break;
            case 2:
                aliens[i].texture = (SDL_Texture**) malloc(sizeof(SDL_Texture*) * 2);
                aliens[i].texture[0] = IMG_LoadTexture(renderer, "sprites/mid1.png");
                aliens[i].texture[1] = IMG_LoadTexture(renderer, "sprites/mid2.png");
                break;
            case 3:
                aliens[i].texture = (SDL_Texture**) malloc(sizeof(SDL_Texture*) * 2);
                aliens[i].texture[0] = IMG_LoadTexture(renderer, "sprites/top1.png");
                aliens[i].texture[1] = IMG_LoadTexture(renderer, "sprites/top2.png");
                break;
            case 4:
                aliens[i].texture = (SDL_Texture**) malloc(sizeof(SDL_Texture*) * 2);
                aliens[i].texture[0] = IMG_LoadTexture(renderer, "sprites/bot1.png");
                aliens[i].texture[1] = IMG_LoadTexture(renderer, "sprites/bot2.png");
                break;
            default:
                perror("This... This should NOT happen :O\n");
                exit(0);
        }
    }
    return;
}

void kill_alien(Alien* aliens, int index){
    return;
}

void render_aliens(Alien* aliens, int tick){
    // Render is from top to bottom, from index 0 to index 54

    return;
}

void free_aliens(Alien* aliens, int count){
    // Will free aliens in entirety = with all their member vars
    for(int i = 0; i < count; i++){
        SDL_DestroyTexture(aliens[i].texture[0]); aliens[i].texture = NULL;
        SDL_DestroyTexture(aliens[i].texture[1]); aliens[i].texture = NULL;
    }
    free(aliens);
    return;
}