#include "timer.h"
#include "lcd.h"
#include "p24fj64ga002.h"


int delayUsTest()
{
    //tests the delayUs() function at 1 Us, 100 Us, 10000 Us
    //TODO: compare the time delayed to a different timer's delay (I mean, I gotta do SOMETHING I guess...)
    int tookTooLong1 = 0;
    int tookTooLong3 = 0;
    int tookTooLong2 = 0;
    PR3 = 18;//gives it a touch of leniency
    IFS0bits.T3IF = 0;
    TMR3 = 0;
    T3CONbits.TON = 1;
    delayUs(1);
    T3CONbits.TON = 0;
    if(IFS0bits.T3IF == 1)
        tookTooLong1 = 1;

    TMR3 = 0;
    IFS0bits.T3IF = 0;
    PR3 = 14.7456*101 - 1;//again, slight leniency
    T3CONbits.TON = 1;
    delayUs(100);
    T3CONbits.TON = 0;
    if(IFS0bits.T3IF == 1)
        tookTooLong2 = 1;

    TMR3 = 0;
    IFS0bits.T3IF = 0;
    PR3 = 14.7456*10001 - 1;
    T3CONbits.TON = 1;
    delayUs(10000);
    T3CONbits.TON = 0;
    if(IFS0bits.T3IF == 1)
        tookTooLong3 = 1;

    return tookTooLong3 && tookTooLong2 && tookTooLong1;//overall pass/fail
}

int updateLCDTimeTest()
{
    //Tests the updateLCDTime() function from lcd.h
    //NOTE: This is OUR version of the getTimeString() function
    int stringIsWrong1 = 0;
    int stringIsWrong2 = 0;
    int stringIsWrong3 = 0;
    char* string;
    string = updateLCDtime(100,0);
    if(*string != "01:40:00")
        stringIsWrong1 = 1;

    string = updateLCDtime(1002,0);
    if(*string != "16:42:00")
        stringIsWrong2 = 1;

    string = updateLCDtime(200,0);
    if(*string != "03:20:00")
        stringIsWrong3 = 1;

    return stringIsWrong3 && stringIsWrong2 && stringIsWrong1;
}