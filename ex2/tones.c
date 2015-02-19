
#include "dac.h"
#include "timer.h"
#include "tones.h"
#include "gpio.h"

static int32_t time_left_tone;
static int32_t current_tone;
static int32_t current_volume;


void tone_set(float length, int32_t tone, int32_t volume){
    time_left_tone  = tone*length;
    current_tone    = tone;
    current_volume  = volume;
    timer_setup(2*tone);
    return;
}


int tone_play(){
    gpio_set_leds(time_left_tone >> 8);
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
            timer_turn_off();
            current_tone=-1;
            return -1;
        }
        
    }
    else{
        return 0;
    }
}
