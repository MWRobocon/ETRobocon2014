/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT LCD Driver            *
 **************************************/

#include "driver_nxt.h"

void lcdDisplay(int32_T inData, char* s, uint8_T line, uint8_T mode)
{
    display_goto_xy(0, line-1);
    display_string(s);
    display_goto_xy(6, line-1);
    if (mode == 1) //decimal
        display_int(inData, 10);
    else // hex
        display_hex(inData, 10);
    
    display_update();
    
    return;
}

