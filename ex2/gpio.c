#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"
#include "gpio.h"

void setup_GPIO_input(void);
void setup_GPIO_output(void);
void setup_GPIO_interrupts(void);

//constructor is run before main();
void __attribute__ ((constructor)) GPIOconstructor(void){
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;  /* enable GPIO clock*/
    setup_GPIO_input();
    setup_GPIO_output();
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    *GPIO_IFC = 0xff;
    gpio_set_leds(gpio_read_buttons());
    return;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
    *GPIO_IFC = 0xff;
    gpio_set_leds(gpio_read_buttons());
    return;
}

void setup_GPIO_input(void){            //set input buttons:
    *GPIO_PC_MODEL  =   0x33333333;
    *GPIO_PC_DOUT   =   0xff;           //internal pull-ups
    return;
}

void setup_GPIO_output(void){
    *GPIO_PA_CTRL       =   2;          /* set high drive strength */
    *GPIO_PA_MODEH      =   0x55555555; /* set pins A8-15 as output */
    return;
}

void setup_GPIO_interrupts(void){
    *GPIO_EXTIPSELL = 0x22222222;
    *GPIO_EXTIRISE  = 0xff;
    *GPIO_EXTIFALL  = 0xff;
    *GPIO_IEN       = 0xff;
    *ISER0          = 0x802;
    return;
}

void gpio_set_leds(int num){
    *GPIO_PA_DOUT = (num << 8);
    return;
}

int gpio_read_buttons(void){
    return *GPIO_PC_DIN;
}
