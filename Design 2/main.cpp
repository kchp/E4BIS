/*
===============================================================================
= Project     = E4BIS Design 2
= Author      = Kim Petersen
= Date        = 25/04 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Hvordan kan lyd supporterer Design 1?
=             = Brug en buzzer eller lign. for at forbedre Design 1
=             = (LED skal stadig gøre som i Design 1)
=             = 
=             = 1. OK - diode off, ingen lyd
=             = 2. Busy - diode blinker hurtigt, ingen lyd
=             = 3. Warning - diode blinker langsomt, bip fra buzzer
=             = 4. Error - diode konstant on, konstant tone fra buzzer
===============================================================================
*/
#include "mbed.h"
#include "Led.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
InterruptIn state_btn(p14); // interrupt pin to change between states
LED sled(p25);              // LED connected on pin 25
LED buzz(p27);              // Buzzer connected on pin 27
Timer debounce;             // Debounce init

int state = 0;

void interrupt(void);
void LEDctrl(int);
void Buzzctrl(int);

int main(void)
{
    led1 = 0;   // on to indicate board on
    led2 = 1;
    
    debounce.start();
    state_btn.rise(&interrupt); // watch for interrupt
    while(1) {}
}

void interrupt(void)
{
    if(debounce.read_ms() > 1000)
    {
        state++;
        
        // Acknowledgement bip
//        sound.blink(0.005f, 0.5f);
//        wait_ms(100);
//        sound.blink(1.0f, 0.0f);
        
        if(state > 4)
        {
            state = 1;
        }
        LEDctrl(state);
        Buzzctrl(state);
        debounce.reset();
    }            
}

void LEDctrl(int state)
{
    switch(state)
    {
        case 1:     // Busy, LED blinking fast
            //led3 = 0;
            //led4 = 1;
            sled.blink(0.1f, 0.5f);
            break;
        
        case 2:     // Warning, LED blinking slow
            //led3 = 1;
            //led4 = 0;
            sled.blink(1.0f, 0.5f);
            break;
            
        case 3:     // Error, LED on
            //led3 = 1;
            //led4 = 1;
            sled.blink(1.0f, 1.0f);
            break;
            
        default:     // OK, LED off
            //led3 = 0;
            //led4 = 0;
            sled.blink(1.0f, 0.0f);
    }
}

void Buzzctrl(int state)
{
    switch(state)
    {
        case 1:     // Busy state, silent
            buzz.blink(1.0f, 0.0f);
            break;
        case 2:     // Warning state, Beeping tone
            buzz.blink(1.0f, 0.5f);
            break;
        case 3:     // Error state, Constant tone
            buzz.blink(0.001f, 0.5f);
            break;
        default:   // OK state, silent     
            buzz.blink(1.0f, 0.0f);
    }   
}