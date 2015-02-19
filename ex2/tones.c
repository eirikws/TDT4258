
#include "dac.h"
#include "timer.h"

static int32_t time_left_tone;
static int32_t current_tone;
static int32_t curent_volume;
static int32_t top_or_bottom=0;

void tone_set(int32_t length, int32_t tone, int32_t volume){
    time_left_tone  = length;
    current_tone    = tone;
    current volume  = volume;
    timer_set_frequency(tone);
}

int tone_play();
    if !(tone==-1){
        time_left_tone -= current_tone;
        if (top_or_bottom==1){
            dac_write(current_volume);
            top_or_bottom=0;
        }
        else{
            dac_write(0);
            top_or_bottom=1;
        }
        
        if (time_left_tone > 0){
            return 1;   
        }
        else{
            return -1;
        }
        
    }
    else{
        return 0;
    }
}
