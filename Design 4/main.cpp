/*
===============================================================================
= Project     = E4BIS Design 4
= Author      = Kim Petersen
= Date        = 01/5 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Hvordan kan haptic feedback forbedre UX af Design 3?
=             = Tilføj en vibrator etc til at give taktil feedback for design 3
=             = Det er vigtigt for designet at du forkuserer på at give en
=             = tydelig lys, lyd og haptid indikation af de fire forskellige
=             = tilstande.
=             = 
=             = Der gives 2 hurtige vibrationer når der trykkes på knappen
=             = 1. OK: Led blinkende grøn, ingen lyd, ingen vibration
=             = 2. Busy: Led blinker hurtigt blå, ingen lyd,
=             =          hurtig mild vibration
=             = 3. Warning: Led blinker gult, bip, vibration i takt med blink
=             = 4. Error: Led konstant rød, Hi/Lo tone, konstant vibration
===============================================================================
*/

#include "mbed.h"
#include "RGBPWM.h"
#include "PWM.h"

DigitalOut led1(LED1);      // Onboard leds
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
PWM tack(p29);              // Vibrator connected on pin 29
PWM buzz(p25);              // Buzzer connected on pin 25
RGBled sled(p26,p27,p28);   // Object to control the 3 led pins
InterruptIn pb(p14);        // interrupt pin to change between states
Timer debounce;             // Debounce init

int count = 0;

void interrupt(void);
void acknowledge(void);

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
            case 1:     // Busy (Led blue fast blink, Buzz off, )
                //led3 = 1;   // onboard leds used to indicate state
                //led4 = 0;   // only used during development
                buzz.set(0.001f, 0.0f);
                blink = !blink;
                if(blink)
                {
                    sled.set(0.0f, 0.0f, 0.5f);
                    tack.set(0.001f, 0.6f);
                }
                else
                {
                    sled.set(0.0f, 0.0f, 0.0f);
                    tack.set(0.001f, 0.0f);
                }
                wait(.05);
                break;
            case 2:     // Warning (Led yellow blink, Buzz beeping, 
                        //          Tack vibrate with blink)
                //led3 = 0;   // onboard leds used to indicate state
                //led4 = 1;   // only used during development
                blink = !blink;
                if(blink)
                {
                    sled.set(0.8f, 0.2f, 0.0f);
                    buzz.set(0.001f, 0.2f);
                    tack.set(0.001f, 0.5f);                  
                }
                else
                {
                    sled.set(0.0f, 0.0f, 0.0f);
                    buzz.set(0.001f, 0.0f);
                    tack.set(0.001f, 0.0f);
                }
                wait(.2);
                break;
            case 3:     // Error (Led red, Buzz on, Tack on)
                //led3 = 1;   // onboard leds used to indicate state
                //led4 = 1;   // only used during development
                sled.set(0.5f, 0.0f, 0.0f);
                tack.set(0.001f, 0.4f);
                blink = !blink;
                if(blink)
                {
                    buzz.set(0.001f, 0.3f);
                }
                else
                {
                    buzz.set(0.001f, 0.5f);
                }
                wait(.5);
                break;
            default:     // OK (Led green blink, Buzz off, Tack off)
                //led3 = 0;   // onboard leds used to indicate state
                //led4 = 0;   // only used during development
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
        sled.set(0.0f, 0.0f, 0.0f);
        buzz.set(0.001f, 0.0f);
        tack.set(0.001f, 0.0f);
        wait(0.1);
        count++;      // disable while testing
        acknowledge();
        if(count > 3)
        {
            count = 0;
        }
        debounce.reset();
    }
}

void acknowledge(void)
{
    tack.set(0.001f, 0.7f);
    wait(0.15);
    tack.set(0.001f, 0.0f);
    wait(0.15);
    tack.set(0.001f, 0.7f);
    wait(0.15);
    tack.set(0.001f, 0.0f);
    wait(0.15);
}
   
