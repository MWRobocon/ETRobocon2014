/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT Button Driver         *
 **************************************/

#include "driver_nxt.h"

int pressButton(int buttonType)
{
    int pressed = 0;
    if (buttonType == 1) 
    {
        pressed = ecrobot_is_ENTER_button_pressed();
    } else {
        pressed = ecrobot_is_RUN_button_pressed();
    }
    return pressed;
}

