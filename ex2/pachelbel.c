#include "songs.h"

/*
    Pachelbel's Canon in D, arr Lee Galloway
*/
static const song pachelbel = {
        .length = 364,
        .tones = (tone[]){
        //1
        {Fs5    , 4     , 0x20},
        {E5     , 4     , 0x20},
        //2
        {D5     , 4     , 0x20},
        {Cs5    , 4     , 0x20},
        //3
        {H4     , 4     , 0x20},
        {A4     , 4     , 0x20},
        //4
        {H4     , 4     , 0x20},
        {Cs5    , 4     , 0x20},
        //5
        {Fs5    , 1     , 0x20},
        {Cs5    , 1     , 0x20},
        {D5     , 1     , 0x20},
        {Fs4    , 1     , 0x20},
        {E5     , 1     , 0x20},
        {A4     , 1     , 0x20},
        {G4     , 1     , 0x20},
        {A4     , 1     , 0x20},
        //6
        {D5     , 0.8   , 0x20},
        {10     , 0.2   , 0x20}, // silence
        {D5     , 1     , 0x20},
        {Cs5    , 1     , 0x20},
        {H4     , 1     , 0x20},
        {Cs5    , 1     , 0x20},
        {Fs5    , 1     , 0x20},
        {A5     , 1     , 0x20},
        {H5     , 1     , 0x20},
        //7
        {G5     , 1     , 0x20},
        {Fs5    , 1     , 0x20},
        {E5     , 1     , 0x20},
        {G5     , 1     , 0x20},
        {Fs5    , 1     , 0x20},
        {E5     , 1     , 0x20},
        {D5     , 1     , 0x20},
        {Cs5    , 1     , 0x20},
        //8
        {H4     , 1     , 0x20},
        {A4     , 1     , 0x20},
        {H4     , 1     , 0x20},
        {D5     , 1     , 0x20},
        {10     , 0.2   , 0x20},
        {D5     , 2.2   , 0x20},
        {Cs5    , 2.4   , 0x20},
        //9
        {A5     , 1     , 0x20},
        {Fs5    , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {A5     , 1     , 0x20},
        {Fs5    , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        //10
        {Fs5    , 1     , 0x20},
        {D5     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {Fs5    , 1     , 0x20},
        {Fs4    , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        //11
        {G4     , 1     , 0x20},
        {H4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {G4     , 1     , 0x20},
        {Fs4    , 0.5   , 0x20},
        {E4     , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {E4     , 0.5   , 0x20},
        {D4     , 0.5   , 0x20},
        {E4     , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        //12
        {G4     , 1     , 0x20},
        {H4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 1     , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        //13
        {A5     , 1     , 0x20},          
        {Fs5    , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {A5     , 1     , 0x20},
        {Fs5    , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        //14
        {Fs5    , 1     , 0x20},
        {D5     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {Fs5    , 1     , 0x20},
        {Fs4    , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        //15
        {H4     , 1     , 0x20},
        {D5     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {H4     , 1     , 0x20},
        {A4     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        //16
        {H4     , 1     , 0x20},
        {D5     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 1     , 0x20},
        {Cs5    , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        //17
        {A5     , 2     , 0x20},
        {Fs5    , 1     , 0x20},
        {A5     , 0.8   , 0x20},
        {10     , 0.2   , 0x20},
        {A5     , 1     , 0x20},
        {H5     , 1     , 0x20},
        {A5     , 1     , 0x20},
        {G5     , 1     , 0x20},
        //18
        {Fs5    , 2     , 0x20},
        {D5     , 1     , 0x20},
        {Fs5    , 0.8   , 0x20},
        {10     , 0.2   , 0x20},
        {Fs5    , 1     , 0x20},
        {G5     , 1     , 0x20},
        {Fs5    , 1     , 0x20},
        {E5     , 1     , 0x20},
        //19
        {D5     , 2     , 0x20},
        {H4     , 1     , 0x20},
        {D5     , 0.8   , 0x20},
        {10     , 0.2   , 0x20},
        {D5     , 2     , 0x20},
        {Fs4    , 1     , 0x20},
        {D5     , 0.8   , 0x20},
        {10     , 0.2   , 0x20},
        //20
        {D5     , 1     , 0x20},
        {C5     , 1     , 0x20},
        {H4     , 1     , 0x20},
        {C5     , 1     , 0x20},
        {Cs5    , 2     , 0x20},
        {D5     , 1     , 0x20},
        {E5     , 1     , 0x20},
        //21
        {Fs5    , 2     , 0x20},
        {D6     , 1     , 0x20},
        {Fs5    , 0.8   , 0x20},
        {10     , 0.2   , 0x20},
        {Fs5    , 1     , 0x20},
        {G5     , 1     , 0x20},
        {A5     , 1     , 0x20},
        {E5     , 1     , 0x20},
        //22
        {D5     , 2     , 0x20},
        {H5     , 1     , 0x20},
        {D5     , 0.8   , 0x20},
        {10     , 0.2   , 0x20},
        {D5     , 1     , 0x20},
        {E5     , 1     , 0x20},
        {A5     , 1     , 0x20},
        {Cs5    , 1     , 0x20},
        //23
        {H4     , 2     , 0x20},
        {G5     , 2     , 0x20},
        {D6     , 2     , 0x20},
        {A5     , 2     , 0x20},
        //24
        {H5     , 2     , 0x20},
        {G5     , 2     , 0x20},
        {A5     , 2     , 0x20},
        {Fs5    , 1     , 0x20},
        {G5     , 1     , 0x20},
        //25
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H5     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        //26
        {Fs5    , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {E4     , 0.5   , 0x20},
        //27
        {D5     , 0.5   , 0x20},
        {D4     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {D4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {D4     , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        //28
        {G5     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {H5     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {H5     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Cs6    , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        //29
        {D6     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {D6     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {D6     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {Cs6    , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        //30
        {Cs6    , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {H5     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {H5     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        //31
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {D5     , 0.5   , 0x20},
        //32
        {Fs5    , 0.5   , 0x20},
        {Fs4    , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {H4     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {E4     , 0.5   , 0x20},
        {G5     , 0.5   , 0x20},
        {G4     , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {H5     , 1     , 0x20},
        {Cs6    , 1     , 0x20},
        //33
        {D6     , 2     , 0x20},
        {D5     , 2     , 0x20},
        {Cs5    , 1.5   , 0x20},
        {Cs6    , 0.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {E5     , 0.5   , 0x20},
        //34
        {H5     , 2     , 0x20},
        {H4     , 2     , 0x20},
        {A4     , 1.5   , 0x20},
        {A5     , 0.5   , 0x20},
        {Fs5    , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        {A4     , 0.5   , 0x20},
        {Cs5    , 0.5   , 0x20},
        //35
        {G5     , 2     , 0x20},
        {G4     , 2     , 0x20},
        {Fs4    , 2     , 0x20},
        {Fs5    , 2     , 0x20},
        //36
        {G4     , 2     , 0x20},
        {H5     , 2     , 0x20},
        {Cs5    , 1     , 0x20},
        {E5     , 1     , 0x20},
        {A5     , 1     , 0x20},
        {Cs6    , 1     , 0x20},
        {D6     , 4     , 0x20},
        {D5     , 4     , 0x20},
        {2      , 10    , 0},
    }
};

song get_pachelbel(void){
    return pachelbel;
}












