#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "efm32gg.h"
#include "gpio.h"


void setup_timer(uint16_t period){
    *CMU_HFPERCLKEN0    |= (1 << 6);
    *TIMER1_TOP         = period;
    *TIMER1_IEN         = 1;
    *TIMER1_CMD         = 1; 
    return;
}

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
    int16_t i=8;
    *TIMER1_IFC = 0xff;
    gpio_set_leds(i << 8);
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */  
}
