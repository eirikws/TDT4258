#pragma once
#include "tones.h"
#include "songs.h"

/*
    return 1 if it sets a new tone
    return 0 if does nothing
    return -1 if song is finished
    write 1 to start song again
*/
int play_song(song* mysong, int start_again);


/*
    getter to test_music
*/
song get_test_music(void);


/*
    getter to loop_music
*/
song get_loop_music(void);


/*
    give a number to set a new state.
    -1 to not change the state but play some sound
*/
void sounds(int state);


/*
    void select_song();
*/
void sound_select(int input);
