/*
===============================================================================
= Project     = E4BIS Design 5
= Author      = Kim Petersen
= Date        = 02/05 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Design 5
=             = De videoer vi har set handler om bevægelse på en skærm.
=             = Kan vi bruge disse læringer på en embedded platform?
=             = Flyt nogle objekter (brug f.eks. en servo tilsluttet din mbed).
=             = Hvordan skal denne bevægelse designes for at give en god UX?
=             = 
=             = Retninglinjer:
=             = Husk vi kører realtidssystemer, så brugeren skal altid have
=             = feedback på sine handlinger. Pas på ikke at komme til at hænge
=             = i en tilstand, hvor du ikke kan tage imod et knaptryk.
=             = Hvis du ikke udfører brugerens ønsker her og nu, skal du finde
=             = måde at fortælle brugeren det på, med en god UX. Det er vigtigt
=             = at dine knaptryk er OK, idet det er en del af UX, så brug en
=             = debounce på din knap og evt. en state-machine til at holde styr
=             = på dine tilstande.
===============================================================================
*/
#include "mbed.h"
#include "PWM.h"
#include "RGBPWM.h"

DigitalOut led1(LED1);      // Onboard leds
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
InterruptIn pb(p14);        // interrupt pin to change between states
Timer debounce;             // Debounce init
PwmOut servo(p30);          // Servo connected on pin 30
PWM tack(p29);              // Vibrator connected on pin 29
PWM buzz(p25);              // Buzzer connected on pin 25
RGBled sled(p26,p27,p28);   // LED connected on pins 26, 27, 28

#define MID 1370

int count = 0;

void interrupt(void);
void init(void);

int main(void)
{
    init();
    debounce.start();
    pb.rise(&interrupt);
    
    while(1)
    {
        switch(count)
        {
            case 1:     // Robo L90
                servo.pulsewidth_us(2220);
                break;
            case 2:     // Robo R90
                servo.pulsewidth_us(520);
                break;
            case 3:     // Robo L45
                servo.pulsewidth_us(1795);
                break;
            case 4:     // Robo R45
                servo.pulsewidth_us(945);
                break;
            default:    // Robo center
                servo.pulsewidth_us(MID);
                break;
            
        }
    }
}

void interrupt(void)
{
    if(debounce.read_ms() > 1000)
    {
        count++;
        if(count > 4)
        {
            count = 0;
        }
    }
    debounce.reset();
}

void init(void)
{
    led1 = 0;   // onboard green led to indicate board on
    led2 = 1;
    servo.period_ms(20);        // init servo pwm period to 20ms
    servo.pulsewidth_us(MID);   // init servo to middle position
}
