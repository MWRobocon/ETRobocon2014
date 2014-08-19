/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT Touch Sensor Driver   *
 **************************************/

#include "driver_nxt.h"

uint16_T getTouchSensorValue(uint8_T portNumber)
{
    return ecrobot_get_touch_sensor(portNumber-1);
}

