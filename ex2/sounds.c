
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
    mario_theme = 6,
}Music_State;

/*
void __attribute__ ((constructor)) begin_sounds(void){
    dac_setup();
    //timerLE_setup(); // generate a timer interrupt!
}
*/

void sounds(int new_state){
    static Music_State state;
    static int i;
    static int init;
    gpio_set_leds(1);
    if (new_state > 0){
        gpio_set_leds(4);
        //gpio_set_leds(++i);
        state = new_state;
        timerLE_setup();
        dac_setup();
        //dac_off();
    }
    //gpio_set_leds(++i);
    switch(state){
        case pachelbel:
            if (play_song(get_pachelbel(), init ) == -1){
                //  we can implement some logic for what happens where a song finishes
                //  right now we just turn off the timer and play silence
                timerLE_off();
                dac_off();
                gpio_set_leds(2);
            }
            init =  0;
            break;
        case c_scale:
            if (play_song(get_c_scale(), init ) == -1){
                timerLE_off();
                dac_off();
                gpio_set_leds(2);
            }
            init =  0;
            break;
        case winner:
            if (play_song(get_winner(), init ) == -1){
                timerLE_off();
                dac_off();
                gpio_set_leds(2);

            }
            init =  0;
            break;
        case loser:
            if (play_song(get_loser(), init ) == -1){
                timerLE_off();
                dac_off();
                gpio_set_leds(2);
            }
            init =  0;
            break;
        case hit_wall:
            if (play_song(get_hit_wall(), init ) == -1){
                timerLE_off();
                dac_off();
                gpio_set_leds(2);
            }
            init =  0;
            break;
        case mario_theme:
            if (play_song(get_mario_theme(), init ) == -1){
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
            sounds(mario_theme);
            break;
        case (1 << 6):
            sounds(c_scale);
            break;
        case (1 << 7):
            sounds(c_scale);
            break;
            
    }
}
