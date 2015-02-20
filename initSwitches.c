#include "p24fj64ga002.h"
#include "initSwitches.h"

void initSW1()
{//Using the switch on the board connected to RB5
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    CNEN2bits.CN27IE = 1;
}

void initSW2()
{//for the external switch
    TRISBbits.TRISB2 = 1;
    CNPU1bits.CN6PUE = 1;//set pull up resistor
    AD1PCFGbits.PCFG4 = 1;//Set as digital input
    IEC1bits.CNIE = 1;
    CNEN1bits.CN6IE = 1;//enable interrupts
    IFS1bits.CNIF = 0;
}