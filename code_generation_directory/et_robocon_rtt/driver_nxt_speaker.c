/* Copyright 2011 The MathWorks, Inc. */

/**************************************
 *     LEGO NXT Speaker Driver        *
 **************************************/

#include "driver_nxt.h"

/* freq in */
void playSoundFreqOnly(uint32_T in1, uint32_T vol, uint32_T dura)
{
    ecrobot_sound_tone(in1, dura, vol);
}

/* vol in */
void playSoundVolumeOnly(uint32_T in1, uint32_T freq, uint32_T dura)
{
    ecrobot_sound_tone(freq, dura, in1);
}

/* freq and vol */
void playSoundBoth(uint32_T in1, uint32_T in2, uint32_T dura)
{
    ecrobot_sound_tone(in1, dura, in2);
}
