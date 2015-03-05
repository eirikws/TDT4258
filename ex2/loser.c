#include "songs.h"


static song loser = {
        .length = 8,
        .tones = (tone[]){
        
        {E3     , 0.7     , 0x20},
        {10     , 0.5     , 0x20},
        {Eb3    , 0.7     , 0x20},
        {10     , 0.5     , 0x20},
        {D3     , 0.7     , 0x20},
        {10     , 0.5     , 0x20},
        {Db3    , 2.2     , 0x20},
        {10     , 2       , 0x20},
        
        


    }
};


song* get_loser(void){
    return &loser;
}

