#pragma once
#include "tones.h"

typedef struct{
    int length;
    tone* tones;
}song;


/*
    return 1 if it sets a new tone
    return 0 if does nothing
    return -1 if song is finished
    write 1 to start song again
*/
int play_song(song *mysong, int start_again);


/*
    getter to test_music
*/
song* get_test_music(void);

/*
    getter to loop_music
*/
song* get_loop_music(void);

song* get_pachelbel(void);

void sounds_setup(void);
