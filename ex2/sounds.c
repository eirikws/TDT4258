
#include "timer.h"
#include "tones_play.h"
#include "sounds.h"
#include "dac.h"
#include "gpio.h"

void __attribute__ ((constructor)) begin_sounds(void){
    dac_setup();
    timerLE_setup(); // generate a timer interrupt!
}

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
/*
song static loop_music = {
        .length = 8,
        .tones = (tone[]){
        {A3,    1.0     , 0xff},
        {A3,    0.3     , 0xff},
        {G3,    0.3     , 0xff},
        {A3,    0.3     , 0xff},
        {G3,    1.0     , 0xff},
        {E3,    0.3     , 0xff},
        {E3,    0.3     , 0xff},
        {A4,    1.0     , 0xff},
    }
};
*/


/*
    Pachelbel's Canon in D, arr Lee Galloway
*/
song static pachelbel = {
        .length = 120,
        .tones = (tone[]){
        {Fs5    , 2     , 0xff},
        {E5     , 2     , 0xff},
        {D5     , 2     , 0xff},
        {Cs5    , 2     , 0xff},
        {H4     , 2     , 0xff},
        {A4     , 2     , 0xff},
        {H4     , 2     , 0xff},
        {Cs5    , 2     , 0xff},
        
        {A5     , 1     , 0xff},
        {Fs5    , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {A5     , 1     , 0xff},
        {Fs5    , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        
        {Fs5    , 1     , 0xff},
        {D5     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {Fs5    , 1     , 0xff},
        {Fs4    , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        
        {G4     , 1     , 0xff},
        {H4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {G4     , 1     , 0xff},
        {Fs4    , 0.5   , 0xff},
        {E4     , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {E4     , 0.5   , 0xff},
        {D4     , 0.5   , 0xff},
        {E4     , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        
        {G4     , 1     , 0xff},
        {H4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 1     , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},

        {A5     , 1     , 0xff},          
        {Fs5    , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {A5     , 1     , 0xff},
        {Fs5    , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        
        {Fs5    , 1     , 0xff},
        {D5     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {Fs5    , 1     , 0xff},
        {Fs4    , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},

        {H4     , 1     , 0xff},
        {D5     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {H4     , 1     , 0xff},
        {A4     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},

        {H4     , 1     , 0xff},
        {D5     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 1     , 0xff},
        {Cs5    , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff}
        
    }
};

song* get_pachelbel(void){
    return &pachelbel;
}

song static loop_music = {
		.length = 24,
		.tones = (tone[]) {
		{A5,    2.0     , 0xff},
		{200,    0.15     , 0xff},
        {A5,    0.6     , 0xff},
        {G5,    0.6     , 0xff},
        {A5,    0.6     , 0xff},
        {G5,    2.0     , 0xff},
        {C5,    0.3     , 0xff},
		{200,    0.15     , 0xff},
        {C5,    0.3     , 0xff},
        {A4,    2.0     , 0xff},
		{200,    5.0     , 0xff},
		{A5,    2.0     , 0xff},
		{200,    0.15     , 0xff},
        {A5,    0.6     , 0xff},
        {G5,    0.6     , 0xff},
        {A5,    0.6     , 0xff},
        {G5,    2.0     , 0xff},
        {C5,    0.3     , 0xff},
		{200,    0.15     , 0xff},
        {C5,    0.3     , 0xff},
        {A4,    2.0     , 0xff},
		{200,    5.0     , 0xff},
		{A5,    2.0     , 0xff},
		{200,    0.15     , 0xff},
        {A5,    0.6     , 0xff},
        {G5,    0.6     , 0xff},
        {A5,    0.6     , 0xff},
        {G5,    2.0     , 0xff},
        {C5,    0.3     , 0xff},
		{200,    0.15     , 0xff},
        {C5,    0.3     , 0xff},
        {A4,    2.0     , 0xff},
		{200,    5.0     , 0xff},
        /*{200,    0.15    , 0xff},
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
        {G4,    0.575   , 0xff},*/
    }

};

song* get_loop_music(void){
    return &loop_music;
}

