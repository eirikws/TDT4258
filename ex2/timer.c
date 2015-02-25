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

void timer_setup(uint32_t frequency){
    if(frequency == -1){
        /*
            TODO:
            Implement silency. Run the clock as slow as possible.
            *TIMER1_TOP = 0xffff;?
        */
    }
    *CMU_HFPERCLKEN0    |= (1 << 6);
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
