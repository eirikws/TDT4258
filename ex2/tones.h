#pragma once
#include <stdint.h>

typedef struct Tone{
    int16_t freq;
    double length;
    int16_t volume;
} tone;

#define C3      130
#define Cs3     139
#define Db3     139
#define D3      147
#define Ds3     156
#define Eb3     156     
#define E3      165
#define F3      175
#define Fs3     185
#define Gb3     185
#define G3      196
#define Gs3     208
#define Ab3     208
#define A3      220
#define As3     233
#define Hb3     233
#define H3      247
#define C4      262
#define Cs4     277
#define Db4     277
#define D4      294
#define Ds4     311
#define Eb4     311
#define E4      330
#define F4      349
#define Fs4     370
#define Gb4     370
#define G4      392
#define Gs4     415
#define Ab4     415
#define A4      440
#define As4     466
#define Hb4     466
#define H4      494
#define C5      523
#define Cs5     554
#define Db5     554
#define D5      587
#define Ds5     622
#define Eb5     622
#define E5      659
#define F5      699
#define Fs5     740
#define Gb5     740
#define G5      784
#define Gs5     831
#define Ab5     831
#define A5      880

