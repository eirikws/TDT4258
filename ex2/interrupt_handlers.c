#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "gpio.h"
#include "sounds.h"

void __attribute ((interrupt)) LETIMER0_IRQHandler(void){
    *LETIMER0_IFC = 0x01;
    sounds(-1);
    return;
}

/*
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
*/


/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler(void){
    *GPIO_IFC = *GPIO_IF;
    int32_t gpio_input = gpio_read_buttons();
    gpio_set_leds(gpio_input);
    sound_select(gpio_input);
    return;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler(void){
    *GPIO_IFC = *GPIO_IF;
    int32_t gpio_input = gpio_read_buttons();
    gpio_set_leds(gpio_input);
    sound_select(gpio_input);
    return;
}


