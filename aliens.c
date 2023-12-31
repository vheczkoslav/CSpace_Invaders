#include <SDL2/SDL.h>
#include "aliens.h"

void a_start_pos(Alien *aliens, int count)
{
    for (int i = 0; i < count / 11; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            switch (i)
            {
                case 0:
                    setAlienStats(&aliens[i * 11 + j], j * 51 + 40, (i+1) * 40, 24, 28, i * 11 + j, TOP_KLINGON, 25);
                    break;
                case 1:
                    setAlienStats(&aliens[i * 11 + j], j * 50 + 40, (i+1) * 40, 40, 28, i * 11 + j, MID_VULCAN, 20);
                    break;
                case 2:
                    setAlienStats(&aliens[i * 11 + j], j * 50 + 40, (i+1) * 40, 40, 28, i * 11 + j, MID_VULCAN, 15);
                case 3:
                    setAlienStats(&aliens[i * 11 + j], j * 50 + 40, (i+1) * 40, 40, 28, i * 11 + j, BOT_REPTILIAN, 10);
                    break;
                case 4:
                    setAlienStats(&aliens[i * 11 + j], j * 50 + 40, (i+1) * 40, 40, 28, i * 11 + j, BOT_REPTILIAN, 5);
                    break;
                default:
                    perror("This... This should NOT happen :O\n");
                    exit(0);
            }
        }
    }
    return;
}

void kill_alien(Alien *aliens, int index, int* SCORE)
{
    aliens[index].alive = false;
    *SCORE += aliens[index].score;
    return;
}

void free_aliens(Alien *aliens)
{
    free(aliens);
    return;
}

void setAlienStats(Alien *aliens, int x, int y, int width, int height, int id, alien_type type, int score)
{
    aliens->rect.x = x;
    aliens->rect.y = y;
    aliens->rect.w = width;
    aliens->rect.h = height;
    aliens->id = id;
    aliens->a_type = type;
    aliens->score = score;
    aliens->alive = true;
    return;
}

void aliens_move(Alien *aliens, int count, int tick){
    for(int i = 0; i < count; i++){
        if((tick / 24) % 2 == 0 && tick % 24 != 0){
            aliens[i].rect.x += 6;
        }
        if((tick / 24) % 2 == 1 && tick % 24 != 0){
            aliens[i].rect.x -= 6;
        }
        if(tick % 24 == 0){
            aliens[i].rect.y += 20;
        }
    }
}

void alien_shoot(Alien *aliens, dynarray* projectilez){
    int alive_index[55];
    int length = 0;
    for(int i = 0; i < 55; i++){
        if(aliens[i].alive == true){
            length++;
            alive_index[length-1] = i;
        }
    }

    int index = rand() % length;
    int shooter = alive_index[index];

    Shot* s; s = (Shot*)malloc(sizeof(Shot));
    if(shooter > 11){
        s->rect.x = aliens[shooter].rect.x + 12;
    }
    else{
        s->rect.x = aliens[shooter].rect.x + 20;
    }
    s->rect.y = aliens[shooter].rect.y - 14;
    s->rect.w = 4;
    s->rect.h = 12;
    s->shooter = 1;
    dynarray_push(projectilez, s);
}