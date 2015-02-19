


/*
    sets a new tone, volume and length
*/
void tone_set(int32_t length, int32_t tone, int32_t volume);

/*
    Play the current tone!
    returns:
            1 if nothing is detected
            -1 if the tone is finished. You should change to the next one.
            0 if there are no current tone
*/
void play_tone(void);
