
#include "dac.h"
#include "timer.h"
#include "tones_play.h"
#include "gpio.h"

static int time_left_tone;
static int current_tone;
static int current_volume;


void tone_set(tone mytone){
    time_left_tone  = mytone.freq*mytone.length;
    current_tone    = mytone.freq;
    current_volume  = mytone.volume;
    timerLE_set(2*mytone.freq);
    return;
}


int tone_play(){
    static int32_t top_or_bottom=0;
    if (current_tone>0){
        if (top_or_bottom==1){
            dac_write(current_volume);
            top_or_bottom=0;
        }
        else{
            dac_write(0);
            top_or_bottom=1;
        }
        time_left_tone -= 1;
        if (time_left_tone > 1){
            return 1;   
        }
        else{
            current_tone=-1;
            return -1;
        }
    }
    return -1;
}
