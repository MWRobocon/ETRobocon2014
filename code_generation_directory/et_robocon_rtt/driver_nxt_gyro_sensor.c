/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT Gyro Sensor Driver    *
 **************************************/

#include "driver_nxt.h"

int16_T getGyroSensorValue(uint8_T portNumber, uint8_T outputMode, int32_T offset)
{
    int16_T result = 0;
    result = ecrobot_get_gyro_sensor(portNumber-1);
    if (outputMode == 1) // rotation value
    {
        result = result - offset;
        if (result > 360)
        {
            result = 360;
        }
        else if (result < -360) {
            result = -360;
        }
    }
    return result;
}
