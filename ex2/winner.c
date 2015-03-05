#include "songs.h"


static song winner = {
        .length = 12,
        .tones = (tone[]){
        
        {C4   , 0.3      , 0x20},
        {10   , 0.2      , 0x00},
        {D4   , 0.3      , 0x20},
        {10   , 0.2      , 0x00},
        {E4   , 0.3      , 0x20},
        {10   , 0.2      , 0x00},
        {G4   , 0.3      , 0x20},
        {10   , 0.7      , 0x00},
        {E4   , 0.3      , 0x20},
        {10   , 0.1      , 0x00},
        {G4   , 0.8      , 0x20},
        {10   , 2        , 0x00},

    }
};


song* get_winner(void){
    return &winner;
}
