#include "songs.h"


static song hit_wall = {
        .length = 3,
        .tones = (tone[]){
        
        {10   , 0.1      , 0x00},
        {D3   , 0.2      , 0x20},
        {10   , 0.1      , 0x00},

    }
};


song* get_hit_wall(void){
    return &hit_wall;
}
