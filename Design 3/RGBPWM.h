/*
===============================================================================
= Project     = E4BIS Design 3
= Filename    = RGBPWM.h
= Author      = Kim Petersen
= Date        = 25/04 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Header for class to create various colours for the RGB led
=             = 
===============================================================================
*/

#ifndef RGBPWM_H
#define RGBPWM_H
#include "mbed.h"

class RGBled
{
    public:
        RGBled(PinName pin_R, PinName pin_G, PinName pin_B);
        void set(float red, float green, float blue);
        
    private:
        PwmOut pinR;
        PwmOut pinG;
        PwmOut pinB;
};

#endif