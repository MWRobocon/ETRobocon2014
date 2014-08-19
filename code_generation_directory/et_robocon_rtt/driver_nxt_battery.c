/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT Battery Driver        *
 **************************************/

#include "driver_nxt.h"

unsigned short getBattery()
{
    return ecrobot_get_battery_voltage();
}

