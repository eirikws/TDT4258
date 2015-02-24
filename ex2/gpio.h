#pragma once
#include "stdint.h"

/*
    read input from buttons. get number from 0 to 256;
*/
int16_t gpio_read_buttons(void);

/*
    set light to leds. input from 0 to 256
*/
void gpio_set_leds(int16_t num);


