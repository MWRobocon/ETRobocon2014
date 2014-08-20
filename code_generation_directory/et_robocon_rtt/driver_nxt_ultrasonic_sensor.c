/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *  LEGO NXT Ultrasonic Sensor Driver *
 **************************************/

#include "driver_nxt.h"

int32_T getUltrasonicSensorValue(uint8_T portNumber)
{
    return ecrobot_get_sonar_sensor(portNumber-1);
}

void initUltrasonicSensor(uint8_T portNumber)
{
    ecrobot_init_sonar_sensor(portNumber-1);
}

void terminateUltrasonicSensor(uint8_T portNumber)
{
    ecrobot_term_sonar_sensor(portNumber-1);
}


