#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "gpio.h"
//#include "dac.h"
#include "sounds.h"
#include "tones_play.h"
#include "songs.h"
//#include "tones.h"


typedef enum{
    startup,
    play_some_loop_music,
}Music_State;

void __attribute ((interrupt)) LETIMER0_IRQHandler(void){
    static Music_State music_state = startup;
    static int init = 1;
    *LETIMER0_IFC = 0x01;
    switch(music_state){
        case startup:
            if (play_song(get_test_music(), ( init ? 1 : 0) ) == -1){
                music_state=play_some_loop_music;
                init = 1;
                break;
            }
            init = 0;
            break;
        case play_some_loop_music:
            if (play_song(get_pachelbel(), (init ? 1 : 0) ) == -1){
                music_state=play_some_loop_music;
                init = 1;
                break;
            }
            init = 0;
            break;
    }
    return;
}


void __attribute__ ((interrupt)) TIMER1_IRQHandler(void){
    static Music_State music_state = startup;
    *TIMER1_IFC = 0x01;
    switch(music_state){
        case startup:
            if (play_song(get_test_music(),0) == -1){
                music_state=play_some_loop_music;
            }
            break;
        case play_some_loop_music:
            if (play_song(get_loop_music(),0) == -1){
                music_state=play_some_loop_music;
                play_song(get_loop_music(),1);
            }
            break;
    }
    return;
}



/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler(void){
    *GPIO_IFC = *GPIO_IF;
    gpio_set_leds(gpio_read_buttons());
    return;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler(void){
    *GPIO_IFC = *GPIO_IF;
    gpio_set_leds(gpio_read_buttons());
    return;
}


