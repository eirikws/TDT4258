#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "gpio.h"
#include "timer.h"
//#include "dac.h"
#include "tones.h"

int a = 0;

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{
   // static int16_t i = 0;
   *TIMER1_IFC = 0x01;
   // gpio_set_leds(i++);
    
    tone_play();
    return;
    //DAC_write(i);
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */  
}



/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    *GPIO_IFC = 0x01;
    gpio_set_leds(gpio_read_buttons());
    return;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
    *GPIO_IFC = 0x01;
    gpio_set_leds(gpio_read_buttons());
    return;
}


