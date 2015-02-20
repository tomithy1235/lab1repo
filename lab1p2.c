// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "LEDs.h"
#include "initSwitches.h"
#include <stdio.h>

#define RELEASED 1
#define PRESSED 0



_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )


// ******************************************************************************************* //

typedef enum stateTypeEnum{
    stop,
   //waitstop,
    //waitrun,
    run,
    clear,
    //updateTime
}stateType;

volatile stateType curState;
volatile int SW2wasPressed = 0;
volatile int SW1wasPressed = 0;
volatile long int i = 0;

int main(void)
{
    curState = run;
    initTimer2();
    initTimer1();
    initExtLEDs();
    initSW1();
    initSW2();
    
    initLCD();
    updateLCDtime(0,0);
    checkstring;
    while(1)
    {
        //testLCD();
        
        switch (curState){
            
            
            case stop:
                turnOn(1);
                break;
            case run:
                turnOn(2);
                break;
            case clear:
                turnOn(3);
                curState = stop;
                break;
                /*
            case updateTime:
                i++;//increases 1s count
                curState = run;
                break;
                 * */
            
        }
        delayUs(10000);//delay 10ms
        updateLCDtime(i,TMR1);
            
            
//            case waitstop:
//                turnOn(2);
//                break;
//
//            case waitrun:
//                turnOn(3);
//                break;
                
        
        
    }
    
    return 0;
}

void _ISR _CNInterrupt(void)
{//This puts flag down, debounces switch, and then handles/checks which button was pressed
    
    IFS1bits.CNIF = 0;
    
    delayUs(5000);//waits 5ms to debounce switch

    //NOTE: I changed this to just one if statement for simplicity,
    //getting rid of 2 states. It should function the same though.
    
    if(PORTBbits.RB2 == RELEASED)
    {

        if(SW2wasPressed == 1){
            SW2wasPressed = 0;//reset this
            
            if(curState == run){
                curState = stop;
            }

            else if (curState == stop){
                curState = run;
            }
        }
    }
    else if(PORTBbits.RB2 == PRESSED)

        SW2wasPressed = 1;//so we know when it's released which button changed



    if(curState != run){
        if(PORTBbits.RB5 == RELEASED){

            if(SW1wasPressed == 1){
            i = 0;//dump out current time count
            SW1wasPressed = 0;
            curState = clear;
            }
        }
        else if(PORTBbits.RB5 == PRESSED)
            SW1wasPressed = 1;
    }
    
}

void _ISR _T1Interrupt(void)
{//This has been now set for 1s
    IFS0bits.T1IF = 0;
    i++;
    //curState = updateTime;
}
