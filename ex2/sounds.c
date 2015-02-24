#include "test_music.h"
#include "timer.h"
#include "tones_play.h"
#include "sounds.h"

int play_song(tone *song){
    static int i;
    if (tone_play() == -1 ){
        tone_set(song[i++]);
        return 1;
    }
    return 0;
}
