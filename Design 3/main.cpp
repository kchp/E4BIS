/*
===============================================================================
= Project     = E4BIS Design 3
= Author      = Kim Petersen
= Date        = 25/04 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Hvordan kan Design 1 og Design 2  forbedres ved at bruge en
=             = RGB Led?
=             = Brug en RGB led på dit Design 2, ved at lave forskellige farver
=             = og farveintensitet, ved anvendelse af PWM.
=             = 
=             = 1. OK - Led grøn (blinker), ingen lyd
=             = 2. Busy - Led blå (blinker hurtigt), ingen lyd
=             = 3. Warning - Led gul (blinker), bip fra buzzer
=             = 4. Error - Led rød (konstant), konstant tone fra buzzer
===============================================================================
*/

#include "mbed.h"
#include "RGBPWM.h"
#include "PWM.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
PWM buzz(p25);              // Buzzer connected on pin 25
RGBled sled(p26,p27,p28);   // Object to control the 3 led pins
InterruptIn pb(p14);        // interrupt pin to change between states
Timer debounce;             // Debounce init

int count = 0;

void interrupt(void);

int main(void)
{
    led1 = 0;   // on to indicate board on
    led2 = 1;
    bool blink = 0;
    
    debounce.start();
    pb.rise(&interrupt);
     
    while(1)
    {
        switch(count)
        {
            case 1:     // Busy (Led blue fast blink, Buzz off)
                //led3 = 1;
                //led4 = 0;
                buzz.set(0.001f, 0.0f);
                blink = !blink;
                if(blink)
                {
                    sled.set(0.0f, 0.0f, 0.5);
                }
                else
                {
                    sled.set(0.0f, 0.0f, 0.0f);
                }
                wait(.05);
                break;
            case 2:     // Warning (Led yellow blink, Buzz beeping)
                //led3 = 0;
                //led4 = 1;
                blink = !blink;
                if(blink)
                {
                    sled.set(0.8f, 0.2f, 0.0f);
                    buzz.set(0.001f, 0.2f);                  
                }
                else
                {
                    sled.set(0.0f, 0.0f, 0.0f);
                    buzz.set(0.001f, 0.0f);
                }
                wait(.2);
                break;
            case 3:     // Error (Led red, Buzz on)
                //led3 = 1;
                //led4 = 1;
                sled.set(0.5f, 0.0f, 0.0f);
                blink = !blink;
                if(blink)
                {
                    buzz.set(0.001f, 0.3f);
                }
                else
                {
                    buzz.set(0.001f, 0.8f);
                }
                wait(.5);
                break;
            default:     // OK (Led green blink, Buzz off)
                //led3 = 0;
                //led4 = 0;
                buzz.set(0.001f, 0.0f);
                blink = !blink;
                if(blink)
                {
                    sled.set(0.0f, 0.5f, 0.0f);
                }
                else
                {
                    sled.set(0.0f, 0.0f, 0.0f);
                }
                wait(.5);
                break;
        }   
    }
}

void interrupt(void)
{
    if(debounce.read_ms() > 1000)
    {
        count++;
        if(count > 3)
        {
            count = 0;
        }
        debounce.reset();
    }
}
