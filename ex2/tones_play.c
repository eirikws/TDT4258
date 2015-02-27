
#include "dac.h"
#include "timer.h"
#include "tones_play.h"
#include "gpio.h"

static int32_t time_left_tone;
static int32_t current_tone;
static int32_t current_volume;


void tone_set(tone mytone){
    //gpio_set_leds(mytone.freq);
    //if (mytone.freq == 0){  //if silence
    //    timer_setup(-1);
    //}
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
    else{
        return -1;
    }
}
