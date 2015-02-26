#include "stdint.h"


/*
    setup low freuency timer
*/

void timerLE_setup(uint32_t frequency);

/*
    Setup a timer so that it generates a interrupt every period
*/
void timer_setup(uint32_t frequency);

/*
    Set a new timer frequency
*/
void timer_set_frequency(uint32_t frequency);

void timer_turn_off(void);
