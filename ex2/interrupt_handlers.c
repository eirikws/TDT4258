#include <stdint.h>

#include "efm32gg.h"
#include "gpio.h"
#include "sounds.h"

void __attribute ((interrupt)) LETIMER0_IRQHandler(void){
    *LETIMER0_IFC = 0x01;
    sounds(-1);
    return;
}


void __attribute__ ((interrupt)) TIMER1_IRQHandler(void){
    *TIMER1_IFC = 0x01;
    sounds(-1);
    return;
}


void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler(void){
    *GPIO_IFC = *GPIO_IF;
    int32_t gpio_input = gpio_read_buttons();
    gpio_set_leds(gpio_input);
    sound_select(gpio_input);
    return;
}


void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler(void){
    *GPIO_IFC = *GPIO_IF;
    int32_t gpio_input = gpio_read_buttons();
    gpio_set_leds(gpio_input);
    sound_select(gpio_input);
    return;
}


