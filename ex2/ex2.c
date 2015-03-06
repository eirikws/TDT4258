#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"
#include "gpio.h"


void __attribute__ ((constructor)) sleep_mode_init(void){
    *SCR            |=  (1 << 1)    // sleepdeep
                    |   (1 << 2)    // enable sleep mode
                    |   (1 << 4);   // sevondpend, enable send event on interrupt
    *EMU_MEMCTRL    = 7;            // disable ram blocks 1-3
    *MSC_READCTRL   |= (1<<3);      // disable instruction cache
}

int main(void){
    /*gpio_setup_interrupts();
    int i = 0;
    gpio_set_leds(6);
    __asm("SEV");
    __asm("WFE");*/
    __asm("wfi");
    /*
    while(1){
        __asm("WFE");
        gpio_set_leds(i++);
        //__asm("SEV");
    }
    */
    return 0;
}
