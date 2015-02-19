#include "stdint.h"


/*
    Setup a timer so that it generates a interrupt every period
*/
void timer_setup(uint32_t frequency);

/*
    Set a new timer frequency
*/
void timer_set_frequency(uint32_t frequency);
