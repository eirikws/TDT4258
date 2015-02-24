#pragma once
#include "tones.h"

/*
    sets a new tone, volume and length
    length in s
    tone in Hz
*/
void tone_set(tone mytone);

/*
    Play the current tone!
    returns:
            1 if nothing is detected
            -1 if the tone is finished. You should change to the next one.
            0 if there are no current tone
*/
int tone_play(void);
