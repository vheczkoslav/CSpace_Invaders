#include <stdbool.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

typedef enum {TOP_KLINGON, MID_VULCAN, BOT_REPTILIAN, UFO_SPECIAL}alien_type;
// TOP = 6x7, MID & BOT = 10x7, SPECIAL = 14x6
typedef struct{
    int x;
    int y;
    bool alive;
    SDL_Texture** texture;
    int texture_width;
    int texture_height;
    alien_type a_type;
    int score; //depending on type
    int id; // so that program knows which one to free after being shot down
}Alien;

void a_start_pos(Alien* aliens, int count);
void add_a_textures(Alien* aliens, SDL_Renderer* renderer, int count);
void render_aliens(Alien* aliens, int tick);
void free_aliens(Alien* aliens, int count);