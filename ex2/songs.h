#pragma once
#include "tones.h"

typedef struct{
    int index;
    int length;
    tone* tones;
}song;

song* get_pachelbel(void);

song* get_c_scale(void);

song* get_pachelbel(void);

song* get_loser(void);

song* get_hit_wall(void);

song* get_winner(void);

song* get_mario_theme(void);

song* get_dr_wily(void);
