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

int SHOOT_DELAY = 180; // player can shoot one sec after last shot
bool MOVING = false;
enum direction {LEFT, RIGHT};

const int A_ROWS = 5;
const int A_IN_ROW = 11;

typedef struct{
    SDL_Rect rect;
    bool alive;
    // (9x6) * 4
}Player;

typedef struct{
    SDL_Rect rect;
    // (18x16) * 4
}Shield;

Shield* shields;

typedef struct{
    int x;
    int y;
    // Shots do not need SDL_Rect
}Shot;

void render(SDL_Renderer *renderer, int* cas, SDL_Texture** textures, Alien* alienz, TTF_Font* font, Player* p, Shield* shieldz);
void player_move(Player* player, enum direction d);
void info_text(SDL_Renderer *renderer, TTF_Font *font, char* text, int DATA, int r);