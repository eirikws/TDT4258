#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"
#include "gpio.h"

void gpio_setup_input(void);
void gpio_setup_output(void);
void gpio_setup_interrupts(void);

//constructor is run before main();
void __attribute__ ((constructor)) gpio_constructor(void){
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;  /* enable GPIO clock*/
    gpio_setup_input();
    gpio_setup_output();
    //setup_GPIO_interrupts();
}

void gpio_setup_input(void){            //set input buttons:
    *GPIO_PC_MODEL  =   0x33333333;
    *GPIO_PC_DOUT   =   0xff;           //internal pull-ups
    return;
}

void gpio_setup_output(void){
    *GPIO_PA_CTRL       =   2;          /* set high drive strength */
    *GPIO_PA_MODEH      =   0x55555555; /* set pins A8-15 as output */
    return;
}
void gpio_setup_interrupts(void){
    *GPIO_EXTIPSELL = 0x22222222;
    *GPIO_EXTIRISE  = 0xff;
    *GPIO_EXTIFALL  = 0xff;
    *GPIO_IEN       = 0xff;
    return;
}

void gpio_set_leds(int16_t num){
    *GPIO_PA_DOUT = (num << 8);
    return;
}

int16_t gpio_read_buttons(void){
    return *GPIO_PC_DIN;
}
