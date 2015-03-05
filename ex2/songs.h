#pragma once
#include "tones.h"

typedef struct{
    int length;
    tone* tones;
}song;

song get_pachelbel(void);

song get_loser(void);

song get_hit_wall(void);

song get_winner(void);
