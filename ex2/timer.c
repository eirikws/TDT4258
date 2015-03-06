#include <stdint.h>
#include "timer.h"
#include "efm32gg.h"


void __attribute__ ((constructor))turn_off_LFA_LFB(void){
    /*go to sleep mode 3*/
    *CMU_LFCLKSEL   &=  ~(1 << 0)
                    &   ~(1 << 2);
}

#define CLOCK_FREQUENCY 14000000
#define LE_FREQUENCY 32768

void timerLE_setup(void){
    *CMU_OSCENCMD       |= (1 << 8);            // enable LFXO oscilliator
    *CMU_LFCLKSEL       &= ~(1 << 0);
    *CMU_LFCLKSEL       |= (2 << 0);            // select LFXO as LFACLK source: 32768 frequency
    *CMU_LFACLKEN0      |= (1 << 2);            // enable LFACLK to drive LETIMER0
    //*CMU_LFAPRESC0      |= (2 << 8);          // prescale LFACLK to 32768 / 8 = 4096
    *CMU_HFCORECLKEN0   |= (1 << 4);            // enable clock for LE
    *LETIMER0_CTRL      |= (1 << 9);            // set comp0 to be top value
    *LETIMER0_COMP0      = 1;                   // generate a timer interrupt asap
    *LETIMER0_IEN        = 1;
    
    *ISER0              |= (1 << 26);           // enable LETIMER0 interrupts
    return;
}

void timerLE_set(int32_t frequency){
    *LETIMER0_COMP0 = LE_FREQUENCY / frequency; 
    *LETIMER0_CMD   = 1;                        // start the timer
    return;
}

void timerLE_off(void){
    *LETIMER0_COMP0      = 0;
    *LETIMER0_IEN        = 0;
    *LETIMER0_CMD        = 0;
    *LETIMER0_CTRL      &= ~(1 << 9);
    //*ISER0              &= ~(1 << 26);
    *CMU_OSCENCMD       |= (1 << 9);
    *CMU_LFCLKSEL       &= ~(2 << 0);
    *CMU_LFACLKEN0      &= ~(1 << 2);
    //*CMU_LFAPRESC0      ~= (2 << 8);
    
    *CMU_HFCORECLKEN0   &= ~(1 << 4);
     
    return;
}

/*
    not used. use timerLE instead
*/
void timer_setup(int32_t frequency){
    *CMU_HFPERCLKEN0    |= (1 << 6);                // enable clock for TIMER1
    *TIMER1_TOP         = CLOCK_FREQUENCY/frequency;
    *TIMER1_IEN         = 1;
    *TIMER1_CMD         = 1;
    *ISER0              |= (1 << 12);               // enable TIMER1 interrupts
    return;
}

/*
    not used. use timerLE instead
*/
void timer_set_frequency(int32_t frequency){
    *TIMER1_TOP = CLOCK_FREQUENCY/frequency;
}

/*
    not used. use timerLE instead
*/
void timer_turn_off(void){
    *CMU_HFPERCLKEN0    &= ~(1 << 6);
    *TIMER1_IEN         = 0;
    *TIMER1_CMD         = 0;
}
