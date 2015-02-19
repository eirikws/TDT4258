#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "efm32gg.h"
#include "gpio.h"

#define CLOCK_FREQUENCY 14000000

void timer_setup(uint32_t frequency){
    *CMU_HFPERCLKEN0    |= (1 << 6);
    *TIMER1_TOP         = CLOCK_FREQUENCY/frequency;
    *TIMER1_IEN         = 1;
    *TIMER1_CMD         = 1;
    return;
}

void timer_set_frequency(uint32_t frequency){
    *TIMER1_TOP = CLOCK_FREQUENCY/frequency;
}
