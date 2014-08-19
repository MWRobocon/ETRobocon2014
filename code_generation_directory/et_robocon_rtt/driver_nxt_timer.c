/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT Timer Driver          *
 **************************************/

#include "driver_nxt.h"

uint32_T getTime()
{
    static uint32_T nxt_time = 0;
    static int i=0;
    if (i==0)
    {
        nxt_time = systick_get_ms();
        i++;
    }
    return systick_get_ms() - nxt_time;
}

