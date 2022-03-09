#include <xc.h>

void INTERRUPT_Initialize (void)
{
//    RCONbits.IPEN = 1;      //enable Interrupt Priority mode
    INTCONbits.GIE = 1;    //enable high priority interrupt
//    INTCONbits.GIEL = 1;     //disable low priority interrupt
    INTCONbits.INT0IE = 1;
//    INTCONbits.RBIE = 1;
}

