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
            -1 if nothing is playing. You should change to the next tone.
*/
int tone_play(void);
