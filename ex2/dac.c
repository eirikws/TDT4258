#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"
#include "dac.h"

void dac_setup(void){
    *CMU_HFPERCLKEN0 |= (1 << 17 );
    *DAC0_CTRL       = 0x50010;
    *DAC0_CH0CTRL    = 1;
    *DAC0_CH1CTRL    = 1;
    return;
    
  /*ygyg
    TODO enable and set up the Digital-Analog Converter
    g
    1. Enable the DAC clock by setting bit 17 in CMU_HFPERCLKEN0
    2. Prescale DAC clock by writing 0x50010 to DAC0_CTRL
    3. Enable left and right audio channels by writing 1 to DAC0_CH0CTRL and DAC0_CH1CTRL
    4. Write a continuous stream of samples to the DAC data registers, DAC0_CH0DATA and DAC0_CH1DATA, for example from a timer interrupt
  */
}

void dac_off(void){
    *CMU_HFPERCLKEN0 &= !(1 << 17 );
    *DAC0_CTRL       &= !0x50010;
    *DAC0_CH0CTRL    = 0;
    *DAC0_CH1CTRL    = 0;
}

void dac_sine(void){
    *DAC0_CTRL |= (1 << 1);
    //DAC0_CHO0CTRL |= (
    /*
    TODO:
        DACn_CTRL sinemode bit
        DACn_CHO0CTRL PRS bit
        
    */
}

void dac_write(int16_t data){
    *DAC0_CH0DATA = data; 
    *DAC0_CH1DATA = data;
    return;
}
