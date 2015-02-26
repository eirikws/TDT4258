#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "gpio.h"
//#include "dac.h"
#include "sounds.h"
#include "tones_play.h"
//#include "tones.h"


typedef enum{
    startup,
    play_some_loop_music,
}Music_State;

void __attribute ((interrupt)) LETIMER0_IRQHandler(void){
    static Music_State music_state = startup;
    *LETIMER0_IFC = 0x01;
    gpio_set_leds(0x1234);
    while (1){} 
    
    
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
    //DAC_write(i);
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */  
}



/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler(void){
    *GPIO_IFC = 0x01;
    gpio_set_leds(gpio_read_buttons());
    return;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler(void){
    *GPIO_IFC = 0x01;
    gpio_set_leds(gpio_read_buttons());
    return;
}


