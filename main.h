#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "aliens.h"

Alien* aliens;

const int WIN_WID = 800;
const int WIN_HEI = 700;

int SCORE = 0;
int LVL = 1;
int LIVES = 3;

int TICK = 90;
int TICK_COUNT = 1;
const int TICK_LIMIT = 30; // TICK is never going to be slower than this

int SHOOT_DELAY = 60; // player can shoot one sec after last shot
bool MOVING = false;


const int A_ROWS = 5;
const int A_IN_ROW = 11;

typedef struct{
    SDL_Rect rect;
    bool alive;
    // (9x6) * 2
}Player;

typedef struct{
    SDL_Rect rect;
    // (18x16) * 2
}Shield;

typedef struct{

}Shot;

void render(SDL_Renderer *renderer, int* cas, SDL_Texture** textures, Alien* alienz, TTF_Font* font, Player* p);