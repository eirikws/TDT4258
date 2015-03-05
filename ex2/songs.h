#pragma once
#include "tones.h"

typedef struct{
    int index;
    int length;
    tone* tones;
}song;

song* get_pachelbel(void);

song* get_c_scale(void);
