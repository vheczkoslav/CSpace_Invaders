#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

const int WIN_WID = 800;
const int WIN_HEI = 700;

int SCORE = 0;
int LVL = 1;

int TICK = 90;
int TICK_COUNT = 0;
const int TICK_LIMIT = 30; // TICK is never going to be slower than this

int SHOOT_DELAY = 60; // player can shoot one sec after last shot

void render(SDL_Renderer* renderer, int* cas);

typedef struct{
    int x;
    const int y;
    bool alive;
    SDL_Texture* texture;
    // (9x6) * 2
    int texture_width;
    int texture_height;
}Player;

int A_ROWS = 5;
int A_IN_ROW = 11;
typedef struct{
    int x;
    int y;
    bool alive;
    SDL_Texture* texture;
    int texture_width;
    int texture_height;
    enum type {TOP_CLINGON, MID_VULCAN, BOT_REPTILIAN, UFO_SPECIAL};
    int score; //depending on type
}Alien;

typedef struct{
    int x;
    int y;
    SDL_Texture* texture;
    // 18x16
    int texture_width;
    int texture_height;
}Shield;