/*
===============================================================================
= Project     = E4BIS Design 1
= Author      = Kim Petersen
= Date        = 17/2 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Lavet på LPC4088
=             = 
=             = 1. OK - diode off, alt ok
=             = 2. Busy - diode blinker hurtigt
=             = 3. Warning - diode blinker langsomt
=             = 4. Error - diode konstant on
===============================================================================
*/
#include "mbed.h"
#include "Led.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
InterruptIn state_btn(p14); // interrupt pin to change between states
LED stateLED(p25);

int state = 0;

void interrupt(void);
void control(int);

int main(void)
{
    led1 = 0;   // on to indicate board on
    led2 = 1;
    state_btn.rise(&interrupt); // watch for interrupt
    while(1) {}
}

void interrupt(void)
{
    state++;
    
    if(state > 4)
    {
        state = 1;
    }
    control(state);
}

void control(int state)
{
    switch(state)
    {
        case 1:     // Busy state, LED blinking fast
            led3 = 0;
            led4 = 1;
            stateLED.blink(0.1f, 0.05f);
            break;
        
        case 2:     // Warning state, LED blinbking slow
            led3 = 1;
            led4 = 0;
            stateLED.blink(1.0f, 0.5f);
            break;
            
        case 3:     // Error state, LED constantly on
            led3 = 1;
            led4 = 1;
            stateLED.blink(1.0f, 1.0f);
            break;
            
        default:     // OK state, LED off
            led3 = 0;
            led4 = 0;
            stateLED.blink(1.0f, 0.0f);
    }
}
