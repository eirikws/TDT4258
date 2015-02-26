#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "efm32gg.h"
#include "gpio.h"

/*
    TODO:
    implement with low frequency clock! For energy savings!
*/

#define CLOCK_FREQUENCY 14000000
#define LFACLK_CLOCK_FREQUENCY 32768
#define LE_FREQUENCY 4092


void timerLE_setup(uint32_t frequency){
    
    *CMU_LFCLKSEL   |= (1 << 1);            // select LFX= as LFACLK source: 32768 frequency
    *CMU_LFAPRESC0  |= (1 << 9)|(1 << 8);   // prescale LFACLK to 32768 / 8 = 4096
    *CMU_LFACLKEN0  |= (1 << 2);            // enable LFACLK to drive LETIMER0
    
    *LETIMER0_CTRL  |= (1 << 9);            // set comp0 to be top value

             
    *LETIMER0_COMP0 = 0xffff;
    *LETIMER0_IEN   = 1;
    
    *LETIMER0_CMD  = 1; //start!
    
    return;
}

void timer_setup(uint32_t frequency){
    if(frequency == -1){
        /*
            TODO:
            Implement silency. Run the clock as slow as possible.
            *TIMER1_TOP = 0xffff;?
        */
    }
    *CMU_HFPERCLKEN0    |= (1 << 6); // enable clock for TIMER1
    *TIMER1_TOP         = CLOCK_FREQUENCY/frequency;
    *TIMER1_IEN         = 1;
    *TIMER1_CMD         = 1;
    return;
}

void timer_set_frequency(uint32_t frequency){
    *TIMER1_TOP = CLOCK_FREQUENCY/frequency;
}

void timer_turn_off(void){
    *CMU_HFPERCLKEN0    &= !(1 << 6);
    *TIMER1_IEN         = 0;
    *TIMER1_CMD         = 0;
}
