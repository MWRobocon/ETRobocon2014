/*
 * File: Speak.c
 *
 * Code generated for Simulink model 'et_robocon'.
 *
 * Model version                  : 1.785
 * Simulink Coder version         : 8.7 (R2014b Prerelease) 21-May-2014
 * TLC version                    : 8.7 (May 23 2014)
 * C/C++ source code generated on : Sun Aug 17 18:53:19 2014
 *
 * Target selection: realtime.tlc
 * Embedded hardware selection: ARM Compatible->ARM 7
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Speak.h"

/* Include model header file for global data */
#include "et_robocon.h"
#include "et_robocon_private.h"

/* Output and update for Simulink Function: '<Root>/Speak' */
void Speak(void)
{
  uint32_T tmp;

  /* DataTypeConversion: '<S97>/Data Type Conversion' incorporates:
   *  Constant: '<S5>/Constant'
   */
  if (et_robocon_P.Constant_Value < 4.294967296E+9) {
    if (et_robocon_P.Constant_Value >= 0.0) {
      tmp = (uint32_T)et_robocon_P.Constant_Value;
    } else {
      tmp = 0U;
    }
  } else {
    tmp = MAX_uint32_T;
  }

  /* End of DataTypeConversion: '<S97>/Data Type Conversion' */

  /* S-Function (nxt_speaker): '<S97>/Speaker' */
  playSoundVolumeOnly(tmp, et_robocon_P.Speaker_speakerFreq,
                      et_robocon_P.Speaker_p4);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
