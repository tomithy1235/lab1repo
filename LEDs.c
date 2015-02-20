#include "LEDs.h"
#include "p24fj64ga002.h"

void initExtLEDs(){
    TRISAbits.TRISA0 = 0;//set as output
    TRISAbits.TRISA1 = 0;
    ODCAbits.ODA0 = 1;//set ODC
    ODCAbits.ODA1 = 1;

    LATAbits.LATA0 = OFF;
    LATAbits.LATA1 = OFF;
}