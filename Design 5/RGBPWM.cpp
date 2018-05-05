/*
===============================================================================
= Project     = E4BIS Design 3
= Filename    = RGBPWM.cpp
= Author      = Kim Petersen
= Date        = 25/04 - 2018
= Version     = 1.0
= Copyright   = Open source
===============================================================================
= Description = Implementation of the RGBled class
=             = 
===============================================================================
*/

#include "mbed.h"
#include "RGBPWM.h"

RGBled::RGBled(PinName pin_R, PinName pin_G, PinName pin_B)
       :pinR(pin_R), pinG(pin_G), pinB(pin_B)   // constructor
{
}

void RGBled::set(float red, float green, float blue)
{
    pinR = red;     // The level needed of each to get the desired colour
    pinG = green;   // are found at www.w3schools.com/colors/colors_picker.asp
    pinB = blue;    // 
/*
We will be using these colours:
Green   (0.0f, 0.5f, 0.0f)
Blue    (0.0f, 0.0f, 0.5f)
Yellow  (0.8f, 0.2f, 0.0f)
Red     (0.5f, 0.0f, 0.0f)
*/
}
