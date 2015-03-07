#pragma once
#include "stdint.h"

void dac_setup(void);

void dac_off(void);

void dac_write(int16_t data);
