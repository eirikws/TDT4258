
#include "timer.h"
#include "tones_play.h"
#include "sounds.h"
#include "dac.h"
#include "gpio.h"

typedef enum{
    pachelbel   = 1,
    c_scale     = 2,
    winner      = 3,
    loser       = 4,
    hit_wall    = 5,
}Music_State;

/*
void __attribute__ ((constructor)) begin_sounds(void){
    dac_setup();
    //timerLE_setup(); // generate a timer interrupt!
}
*/

void sounds(int new_state){
    static Music_State state;
    static int init;
    if (new_state > 0){
        state = new_state;
        timerLE_setup();
        dac_setup();
    }
    
    switch(state){
        case pachelbel:
            
            if (play_song(get_pachelbel(), init ) == -1){
                //  we can implement some logic for what happens where a song finishes
                //  right now we just turn off the timer and play silence
                
                timerLE_off();
            }
            init =  0;
            break;
        case c_scale:
            if (play_song(get_c_scale(), init ) == -1){
                timerLE_off();
            }
            init =  0;
            break;
        case winner:
            if (play_song(get_winner(), init ) == -1){
                timerLE_off();
            }
            init =  0;
            break;
        case loser:
            if (play_song(get_loser(), init ) == -1){
                timerLE_off();
            }
            init =  0;
            break;
        case hit_wall:
            if (play_song(get_hit_wall(), init ) == -1){
                timerLE_off();
            }
            init =  0;
            break;
    }
}



int play_song(song* mysong, int start_again){
    /*
        i is the index of the current tone
        if start_again = 1 we set the index to 0
    */
    if (start_again == 1){
        mysong->index=0;
    }
    
    if (tone_play() == -1 ){
        if (mysong->index == mysong->length){
            mysong->index=0;
            return -1;
        }
        tone_set(mysong->tones[mysong->index++]);
        return 1;
    }
    return 0;
}


void sound_select(int input){
    static int last_input;
            //  find newly pressed buttons:   
    //  first find the button that has changed
    //  then find if it was pressed (if it was just released we don't care)
    int pressed = last_input ^ input;
    pressed = (pressed & input);
    last_input = input;
    switch(pressed){
        case (1 << 0):
            sounds(pachelbel);
            break;
        case (1 << 1):
            sounds(c_scale);
            break;
        case (1 << 2):
            sounds(winner);
            break;
        case (1 << 3):
            sounds(loser);
            break;
        case (1 << 4):
            sounds(hit_wall);
            break;
        case (1 << 5):
            sounds(c_scale);
            break;
        case (1 << 6):
            sounds(c_scale);
            break;
        case (1 << 7):
            sounds(c_scale);
            break;
            
    }
}


/*
    TODO:
    make some nice startup music.
*/

static song startup_music = {
        .index  = 0,
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
        .index  = 0,
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



static song loop_music = {
        .index  = 0,
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

