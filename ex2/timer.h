#include "stdint.h"


/*
    setup low freuency timer
*/

void timerLE_setup(void);

/*
    set low energy timer to generate interrupt with a frequency
*/

/*
    set frequency to timerLE
*/
void timerLE_set(int32_t frequency);


void timerLE_off(void);

/*
    Setup a timer so that it generates a interrupt every period
*/
void timer_setup(int32_t frequency);

/*
    Set a new timer frequency
*/
void timer_set_frequency(int32_t frequency);

void timer_turn_off(void);
