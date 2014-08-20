/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT Light Sensor Driver   *
 **************************************/

#include "driver_nxt.h"

uint16_T getLightSensorValue(uint8_T portNumber, uint8_T outputMode)
{
    uint16_T result = 0;
    result = ecrobot_get_light_sensor(portNumber-1);
    if (outputMode == 1) // light intensity
    {
        result = (1024 - result) / 10;
        result = (result > 100 ? 100 : result);
    }
    return result;
}

void initLightSensor(uint8_T portNumber)
{
    ecrobot_set_light_sensor_active(portNumber-1);
}

void terminateLightSensor(uint8_T portNumber)
{
    ecrobot_set_light_sensor_inactive(portNumber-1);
}
