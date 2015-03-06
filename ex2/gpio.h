#pragma once
#include "stdint.h"

/*
    read input from buttons. get number from 0 to 256;
*/
int32_t gpio_read_buttons(void);

/*
    set light to leds. input from 0 to 256
*/
void gpio_set_leds(int32_t num);

/*
    We need to setup gpio interrupts in the main file for some reason...
*/
void gpio_setup_interrupts(void);
