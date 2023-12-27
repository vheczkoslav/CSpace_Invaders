#ifndef ALIENS_H
#define ALIENS_H

#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "dynamic_array.h"

typedef enum
{
    TOP_KLINGON,
    MID_VULCAN,
    BOT_REPTILIAN,
    UFO_SPECIAL
} alien_type;
// TOP = 6x7, MID & BOT = 10x7, SPECIAL = 14x6
typedef struct
{
    SDL_Rect rect;
    bool alive;
    alien_type a_type;
    int score; // depending on type
    int id;    // so that program knows which one to free after being shot down
}Alien;

void a_start_pos(Alien *aliens, int count);
void kill_alien(Alien *aliens, int index, int* SCORE);
void free_aliens(Alien *aliens);
void setAlienStats(Alien *aliens, int x, int y, int width, int height, int id, alien_type type, int score);
void aliens_move(Alien *aliens, int count, int tick);
void alien_shoot(Alien *aliens, dynarray* projectilez);

typedef struct{
    SDL_Rect rect; // x*y - 4*12
    int shooter; // 0 for P, 1 for A
}Shot;

#endif // ALIENS_H