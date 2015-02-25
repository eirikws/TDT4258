#include "timer.h"
#include "tones_play.h"
#include "sounds.h"
#include <strings.h>



int play_song(song *mysong, int start_again){
    static int i;
    if (start_again == 1){i=0;}
    if (tone_play() == -1 ){
        if (i == mysong->length){
            return -1;
        }
        tone_set(mysong->tones[i++]);
        return 1;
    }
    return 0;
}

void sounds_setup(){
    timer_setup(100);
}

/*
    TODO:
    make some nice startup music.
*/
song static startup_music = {
        .length = 15,
        .tones = (tone[]){
        {C4, 0.4, 0xff},
        {D4, 0.6, 0xff},
        {E4, 1.2, 0xff},
        {F4, 0.4, 0xff},
        {G4, 0.5, 0xff},
        {A4, 0.4, 0xff},
        {H4, 0.4, 0xff},
        {C5, 0.4, 0xff},
        {H4, 0.4, 0xff},
        {A4, 0.4, 0xff},
        {G4, 0.4, 0xff},
        {F4, 0.4, 0xff},
        {E4, 0.4, 0xff},
        {D4, 0.4, 0xff},
        {C4, 0.4, 0xff}
    }
};

song* get_test_music(void){
    return &startup_music;
}

/*
    TODO:
    make some nice looping music.
*/

/*
    Mario theme...ish
*/
song static loop_music = {
        .length = 15,
        .tones = (tone[]){
        {E5,    0.1     , 0xff},
        {200,    0.15    , 0xff}, //supposed to be silence but 0 is too low frequency
        {E5,    0.1     , 0xff},
        {200,    0.3     , 0xff},
        {E5,    0.1     , 0xff},
        {200,    0.3     , 0xff},
        {C5,    0.1     , 0xff},
        {200,    0.1     , 0xff},
        {E5,    0.1     , 0xff},
        {200,    0.3     , 0xff},
        {G5,    0.1     , 0xff},
        {200,    0.550   , 0xff},
        {G4,    0.575   , 0xff},
    }
};

song* get_loop_music(void){
    return &loop_music;
}

