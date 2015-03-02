
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
        .length = 335,
        .tones = (tone[]){
        //1
        {Fs5    , 4     , 0xff},
        {E5     , 4     , 0xff},
        //2
        {D5     , 4     , 0xff},
        {Cs5    , 4     , 0xff},
        //3
        {H4     , 4     , 0xff},
        {A4     , 4     , 0xff},
        //4
        {H4     , 4     , 0xff},
        {Cs5    , 4     , 0xff},
        //5
        {Fs5    , 1     , 0xff},
        {Cs5    , 1     , 0xff},
        {D5     , 1     , 0xff},
        {Fs4    , 1     , 0xff},
        {E5     , 1     , 0xff},
        {A4     , 1     , 0xff},
        {G4     , 1     , 0xff},
        {A4     , 1     , 0xff},
        //6
        {D5     , 0.8   , 0xff},
        {20     , 0.2   , 0xff}, // silence
        {D5     , 1     , 0xff},
        {Cs5    , 1     , 0xff},
        {H4     , 1     , 0xff},
        {Cs5    , 1     , 0xff},
        {Fs5    , 1     , 0xff},
        {A5     , 1     , 0xff},
        {H5     , 1     , 0xff},
        //7
        {G5     , 1     , 0xff},
        {Fs5    , 1     , 0xff},
        {E5     , 1     , 0xff},
        {G5     , 1     , 0xff},
        {Fs5    , 1     , 0xff},
        {E5     , 1     , 0xff},
        {D5     , 1     , 0xff},
        {Cs5    , 1     , 0xff},
        //8
        {H4     , 1     , 0xff},
        {A4     , 1     , 0xff},
        {H4     , 1     , 0xff},
        {D5     , 1     , 0xff},
        {20     , 0.2   , 0xff},
        {D5     , 2.2   , 0xff},
        {Cs5    , 2.4   , 0xff},
        //9
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
        //10
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
        //11
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
        //12
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
        //13
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
        //14
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
        {D5     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        //15
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
        //16
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
        {Cs5    , 0.5   , 0xff},
        //17
        {A5     , 2     , 0xff},
        {Fs5    , 1     , 0xff},
        {A5     , 0.8   , 0xff},
        {10     , 0.2   , 0xff},
        {A5     , 1     , 0xff},
        {H5     , 1     , 0xff},
        {A5     , 1     , 0xff},
        {G5     , 1     , 0xff},
        //18
        {Fs5    , 2     , 0xff},
        {D5     , 1     , 0xff},
        {Fs5    , 0.8   , 0xff},
        {10     , 0.2   , 0xff},
        {Fs5    , 1     , 0xff},
        {G5     , 1     , 0xff},
        {Fs5    , 1     , 0xff},
        {E5     , 1     , 0xff},
        //19
        {D5     , 2     , 0xff},
        {H4     , 1     , 0xff},
        {D5     , 0.8   , 0xff},
        {10     , 0.2   , 0xff},
        {D5     , 2     , 0xff},
        {Fs4    , 1     , 0xff},
        {D5     , 0.8   , 0xff},
        {10     , 0.2   , 0xff},
        //20
        {D5     , 1     , 0xff},
        {C5     , 1     , 0xff},
        {H4     , 1     , 0xff},
        {C5     , 1     , 0xff},
        {Cs5    , 2     , 0xff},
        {D5     , 1     , 0xff},
        {E5     , 1     , 0xff},
        //21
        {Fs5    , 2     , 0xff},
        {D6     , 1     , 0xff},
        {Fs5    , 0.8   , 0xff},
        {10     , 0.2   , 0xff},
        {Fs5    , 1     , 0xff},
        {G5     , 1     , 0xff},
        {A5     , 1     , 0xff},
        {E5     , 1     , 0xff},
        //22
        {D5     , 2     , 0xff},
        {H5     , 1     , 0xff},
        {D5     , 0.8   , 0xff},
        {10     , 0.2   , 0xff},
        {D5     , 1     , 0xff},
        {E5     , 1     , 0xff},
        {A5     , 1     , 0xff},
        {Cs5    , 1     , 0xff},
        //23
        {H4     , 2     , 0xff},
        {G5     , 2     , 0xff},
        {D6     , 2     , 0xff},
        {A5     , 2     , 0xff},
        //24
        {H5     , 2     , 0xff},
        {G5     , 2     , 0xff},
        {A5     , 2     , 0xff},
        {Fs5    , 1     , 0xff},
        {G5     , 1     , 0xff},
        //25
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H5     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        //26
        {Fs5    , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {E4     , 0.5   , 0xff},
        //27
        {D5     , 0.5   , 0xff},
        {D4     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {D4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {D4     , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        //28
        {G5     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {H5     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {H5     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Cs6    , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        //29
        {D6     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {D6     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {D6     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {Cs6    , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        //30
        {Cs6    , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {H5     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {H5     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        //31
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        {Fs5    , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {D5     , 0.5   , 0xff},
        //32
        {Fs5    , 0.5   , 0xff},
        {Fs4    , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {H4     , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {E4     , 0.5   , 0xff},
        {G5     , 0.5   , 0xff},
        {G4     , 0.5   , 0xff},
        {A5     , 0.5   , 0xff},
        {A4     , 0.5   , 0xff},
        {Cs5    , 0.5   , 0xff},
        {E5     , 0.5   , 0xff},
        {H5     , 0.5   , 0xff},
        {H5     , 1     , 0xff},
        {Cs5    , 1     , 0xff},
        //33
        {D6     , 2     , 0xff},
        {D5     , 2     , 0xff},
        {Cs5    , 2     , 0xff},
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

