#pragma once
#include "tones.h"

typedef struct{
    int length;
    tone* tones;
}song;

song get_pachelbel(void);
