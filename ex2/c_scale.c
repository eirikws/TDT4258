#include "songs.h"
#include "tones.h"

static song c_scale = {
        .index  = 0,
        .length = 15,
        .tones = (tone[]){
        {C4, 0.4, 0x20},
        {D4, 0.4, 0x20},
        {E4, 0.4, 0x20},
        {F4, 0.4, 0x20},
        {G4, 0.4, 0x20},
        {A4, 0.4, 0x20},
        {H4, 0.4, 0x20},
        {C5, 0.4, 0x20},
        {H4, 0.4, 0x20},
        {A4, 0.4, 0x20},
        {G4, 0.4, 0x20},
        {F4, 0.4, 0x20},
        {E4, 0.4, 0x20},
        {D4, 0.4, 0x20},
        {C4, 0.4, 0x20}
    }
};

song* get_c_scale(void){
    return &c_scale;
}
