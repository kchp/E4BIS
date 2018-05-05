/*
===============================================================================
= Project     = E4BIS Design 2
= Filename    = PWM.h
= Author      = Kim Petersen
= Date        = 25/04 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Header for class to create PWM signal
=             = 
===============================================================================
*/

#ifndef LED_H
#define LED_H

#include "mbed.h"

class PWM
{
    public:
        PWM(PinName pin);
        void set(float period, float onTime);
        
    private:
        PwmOut pin;
};

#endif