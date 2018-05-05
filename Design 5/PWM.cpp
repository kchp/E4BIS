/*
===============================================================================
= Project     = E4BIS Design 2
= Filename    = PWM.cpp
= Author      = Kim Petersen
= Date        = 25/04 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = implementation for class to create PWM signal
=             = 
===============================================================================
*/

#include "mbed.h"
#include "PWM.h"

PWM::PWM(PinName pin)
    :pin(pin)
{
}

void PWM::set(float period, float onTime)
{
    pin.period(period); // sets the period of pwm in seconds
    pin.write(onTime);  // sets pwm on time
}