/*
===============================================================================
= Project     = E4BIS Design 6
= Author      = Kim Petersen
= Date        = 08/05 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Design 6
=             = Flyt dine objekter ved at bruge en bending sensor. Forsøg at
=             = gøre bevægelse så nøjagtig som muligt.
=             = Tilføj lys og lyd for at forbedre UX. Tænk på en
=             = brugssituation, og overvej hvorfor brugeren skal bruge dit
=             = produkt.
=             = 
=             = Servo motor styres ved at bruge bending sensoren.
=             = 
=             = Tilstanden:
=             = Sensoren bøjes lidt,  Servoen bevæges mod venstre,
=             =                       hurtigt blå blink,
=             =                       konstant rød ved 90 graders drejning.
=             = Sensoren bøjes meget, Servoen bevæges mod højre,
=             =                       hurtigt blå blink,
=             =                       konstant rød ved 90 graders drejning.
=             = Ingen bøjning,        Servoen centreres,
=             =                       Grønt blink
===============================================================================
*/
#include "mbed.h"
#include "RGBPWM.h"

DigitalOut led1(LED1);      // Onboard leds
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
Serial pc(USBTX, USBRX);    // USB interface to console
PwmOut servo(p30);          // Servo connected on p30
AnalogIn bend(p15);         // Bending sensor connected on p15
RGBled sled(p26,p27,p28);   // RGB led connect on pins 26, 27, 28

#define MID 1370
#define MAX 2220
#define MIN 520

void init(void);
void readOut(int value);
void moveLeft(void);
void moveRight(void);
void center(void);

int pos;
bool limit = 0;

int main()
{
    bool blink = 0;
    init();

    while(1)
    {
        if((bend.read() > 0.82) && (bend.read() < 0.88))
        {
            moveLeft();
            blink = !blink;
            if(blink && limit != 1)
            {
                sled.set(0.0f, 0.0f, 0.5f);
                wait(0.05);
            }
            else if(!blink && limit != 1)
            {
                sled.set(0.0f, 0.0f, 0.0f);
                wait(0.05);
            }
            else
            {
                sled.set(0.5f, 0.0f, 0.0f);
            }
            //readOut(pos);
        }
        else if((bend.read() > 0.91) && (bend.read() < 1.0))
        {
            moveRight();
            blink = !blink;
            if(blink && limit != 1)
            {
                sled.set(0.0f, 0.0f, 0.5f);
                wait(0.05);
            }
            else if(!blink && limit != 1)
            {
                sled.set(0.0f, 0.0f, 0.0f);
                wait(0.05);
            }
            else
            {
                sled.set(0.5f, 0.0f, 0.0f);
            }
            //readOut(pos);
        }
        else if((bend.read() < 0.81))
        {
            center();
            blink = !blink;
            if(blink)
            {
                sled.set(0.0f, 0.4f, 0.0f);
                wait(0.3);
            }
            else
            {
                sled.set(0.0f, 0.0f, 0.0f);
                wait(0.3);
            }
            //readOut(pos);
        }
    }
/* test loop */    
/*    while(1)
    {
        led1 = !led1;
        readOut();
        wait(.3);
    }
*/
}

void init(void)
{
    led1 = 0;
    led2 = 1;
    led3 = 0;
    led4 = 0;
    pos = MID;
    servo.period_ms(20);      // servo needs to run on 20ms period (50Hz)
    servo.pulsewidth_us(pos); // center servo 
    sled.set(0.0f, 0.4f, 0.0f);
}

/* print sensor value to console */
void readOut(int value)
{
    pc.printf("%d\n", value);
}

void moveLeft(void)
{
    if(pos <= MIN)
    {
        servo.pulsewidth_us(MIN);
        limit = 1;
    }
    else
    {
        limit = 0;
        pos -= 50;
        servo.pulsewidth_us(pos);
    }    
}

void moveRight(void)
{
    if(pos >= MAX)
    {
        servo.pulsewidth_us(MAX);
        limit = 1;
    }
    else
    {
        limit = 0;
        pos += 50;
        servo.pulsewidth_us(pos);
    } 
}

void center(void)
{
    pos = MID;
    servo.pulsewidth_us(pos); // center servo
}
