
#include "timer.h"
#include "tones_play.h"
#include "sounds.h"
#include "dac.h"
#include "gpio.h"

void __attribute__ ((constructor)) begin_sounds(void){
    dac_setup();
    timerLE_setup(); // generate a timer interrupt!
}

int play_song(const song mysong, int start_again){
    static int i;
    if (start_again == 1){i=0;}
    if (tone_play() == -1 ){
        if (i == mysong.length){
            return -1;
        }
        tone_set(mysong.tones[i++]);
        return 1;
    }
    return 0;
}

/*
    TODO:
    make some nice startup music.
*/

static const song startup_music = {
        .length = 15,
        .tones = (tone[]){
        {C4, 0.4, 0x20},
        {D4, 0.6, 0x20},
        {E4, 1.2, 0x20},
        {F4, 0.4, 0x20},
        {G4, 0.5, 0x20},
        {A4, 0.4, 0x20},
        {H4, 0.4, 0x20},
        {C5, 0.4, 0x20},
        {H4, 0.4, 0x20},
        {A4, 0.4, 0x20},
        {G4, 0.4, 0x20},
        {F4, 0.4, 0x20},
        {E4, 0.4, 0x20},
        {D4, 0.4, 0x20},
        {C4, 0.4, 0x20}
    }
};


song get_test_music(void){
    return startup_music;
}

/*
    TODO:
    make some nice looping music.
*/

/*
    Mario theme...ish
*/
/*
song static loop_music = {
        .length = 8,
        .tones = (tone[]){
        {A3,    1.0     , 0x20},
        {A3,    0.3     , 0x20},
        {G3,    0.3     , 0x20},
        {A3,    0.3     , 0x20},
        {G3,    1.0     , 0x20},
        {E3,    0.3     , 0x20},
        {E3,    0.3     , 0x20},
        {A4,    1.0     , 0x20},
    }
};
*/



static const song loop_music = {
		.length = 24,
		.tones = (tone[]) {
		{A5,    2.0     , 0x20},
		{200,    0.15     , 0x20},
        {A5,    0.6     , 0x20},
        {G5,    0.6     , 0x20},
        {A5,    0.6     , 0x20},
        {G5,    2.0     , 0x20},
        {C5,    0.3     , 0x20},
		{200,    0.15   , 0x20},
        {C5,    0.3     , 0x20},
        {A4,    2.0     , 0x20},
		{200,    5.0    , 0x20},
		{A5,    2.0     , 0x20},
		{200,    0.15   , 0x20},
        {A5,    0.6     , 0x20},
        {G5,    0.6     , 0x20},
        {A5,    0.6     , 0x20},
        {G5,    2.0     , 0x20},
        {C5,    0.3     , 0x20},
		{200,    0.15     , 0x20},
        {C5,    0.3     , 0x20},
        {A4,    2.0     , 0x20},
		{200,    5.0     , 0x20},
		{A5,    2.0     , 0x20},
		{200,    0.15     , 0x20},
        {A5,    0.6     , 0x20},
        {G5,    0.6     , 0x20},
        {A5,    0.6     , 0x20},
        {G5,    2.0     , 0x20},
        {C5,    0.3     , 0x20},
		{200,    0.15     , 0x20},
        {C5,    0.3     , 0x20},
        {A4,    2.0     , 0x20},
		{200,    5.0     , 0x20},
        /*{200,    0.15    , 0x20},
        {E5,    0.1     , 0x20},
        {200,    0.3     , 0x20},
        {E5,    0.1     , 0x20},
        {200,    0.3     , 0x20},
        {C5,    0.1     , 0x20},
        {200,    0.1     , 0x20},
        {E5,    0.1     , 0x20},
        {200,    0.3     , 0x20},
        {G5,    0.1     , 0x20},
        {200,    0.550   , 0x20},
        {G4,    0.575   , 0x20},*/
    }

};

song get_loop_music(void){
    return loop_music;
}

