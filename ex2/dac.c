#include <stdint.h>
#include "efm32gg.h"
#include "dac.h"

void dac_setup(void){
    *CMU_HFPERCLKEN0 |= (1 << 17 );
    *DAC0_CTRL       |= (1 << 4)     // dac output
                     |  (1 << 2)     // set to SAMPLE/HOLD mode
                     |  (3 << 16);   // prescaler
    *DAC0_CH0CTRL    = 1;
    *DAC0_CH1CTRL    = 1;
    return;
}

void dac_off(void){
    *DAC0_CTRL       &= ~(1 << 4)
                     &  ~(1 << 2)
                     &  ~(3 << 16);
    *DAC0_CH0CTRL    = 0;
    *DAC0_CH1CTRL    = 0;
    *CMU_HFPERCLKEN0 &= ~(1 << 17);
}

void dac_write(int16_t data){
    *DAC0_CH0DATA = data; 
    *DAC0_CH1DATA = data;
    return;
}
