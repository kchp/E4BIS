#include "mbed.h"
#include "Led.h"

LED::LED(PinName pin)
        :pin(pin)
{
}

void LED::blink(double period, double onTime)
{
    pin.period(period); // sets the period of pwm in seconds
    pin.write(onTime);  // sets pwm on time
}
