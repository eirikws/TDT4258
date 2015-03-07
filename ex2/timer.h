#include "stdint.h"


/*
    setup low freuency timer
*/

void timerLE_setup(void);

/*
    set low energy timer to generate interrupt with a frequency
*/
void timerLE_set(int32_t frequency);


void timerLE_off(void);

/*
    set timer to generate interrupt with a frequency
*/
void timer1_setup(void);

/*
    Set a new timer frequency
*/
void timer1_set(int32_t frequency);

void timer1_off(void);
