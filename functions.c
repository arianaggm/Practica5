
#include <xc.h>

#include "functions.h"

void configADC(char CHANNELS){
    char allchannelsoff = 0x0F;
    ADCON1 = (allchannelsoff-CHANNELS);
    ADCON2 = 0x80;
    ADCON0bits.ADON = 1;
}

unsigned int analogRead(char canal){
    ADCON0 = 1+canal*4;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1){
        
    }
    char lowbits = ADRESL;
    char highbits = ADRESH;
    unsigned int adresult = highbits*256+lowbits;
    return adresult;
}
