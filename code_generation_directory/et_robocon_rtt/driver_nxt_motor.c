/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT Motor Driver          *
 **************************************/

#include "driver_nxt.h"

void setMotor(int8_T* inData, uint8_T portNumber, uint8_T stopAction)
{
    if (stopAction == 1) // coast
    {
        nxt_motor_set_speed(portNumber-1, *inData, 0);
    } else { // brake
        nxt_motor_set_speed(portNumber-1, *inData, 1);
    }
    
    return;
}

void terminateMotor(uint8_T portNumber, uint8_T stopAction)
{
    if (stopAction == 1) // coast
    {
        nxt_motor_set_speed(portNumber-1, 0, 0);
    } else { // brake
        nxt_motor_set_speed(portNumber-1, 0, 1);
    }
    
    return;
}

int32_T getEncoderValueNoReset(uint8_T portNumber)
{
    return nxt_motor_get_count(portNumber-1);
}

int32_T getEncoderValueSampleReset(uint8_T portNumber)
{
    int32_T result = 0;
    result = nxt_motor_get_count(portNumber-1);
    nxt_motor_set_count(portNumber-1, 0);
    return result;
}

int32_T getEncoderValueExternalReset(uint8_T portNumber, int8_T *in)
{
    int32_T result = 0;
    result = nxt_motor_get_count(portNumber-1);
    
    if (*in != 0)
    {
        nxt_motor_set_count(portNumber-1, 0);
    }
    
    return result;
}
