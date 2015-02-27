#include "stdint.h"


/*
    setup low freuency timer
*/

void timerLE_setup(void);

/*
    set low energy timer to generate interrupt with a frequency
*/
void timerLE_set(int32_t frequency);



/*
    Setup a timer so that it generates a interrupt every period
*/
void timer_setup(uint32_t frequency);

/*
    Set a new timer frequency
*/
void timer_set_frequency(uint32_t frequency);

void timer_turn_off(void);
