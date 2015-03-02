#include "efm32gg.h"
/*
void dma_enable(void){
    *CMU_HFPERCLKEN0    |= (1 << 15);        // enable HF_CLK for PRS
    *CMU_HFCORECLKEN0   |= (1 << 0);         // enable HF_CLOK for DMA
    *PRS_CH0_CTRL       |=  (0b110100 << 16) // select LETIMER0 input for PRS
                        |   (
    *DMA_CONFIG         |= (1 << 0)          // enable DMA controller
   // *DMA_IFS            |= (1 << 0)          // set interrupts on channel 0
    *DMA_IEN            |= (1 << 0)          // enable interrupts on channel 0
    
}

*/
