/*
 * File: tail_controller.c
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

#include "tail_controller.h"

/* Include model header file for global data */
#include "et_robocon.h"
#include "et_robocon_private.h"

/* Output and update for Simulink Function: '<Root>/Tail_Controller' */
void tail_controller(real32_T rtu_current, real32_T rtu_desired, real32_T
                     *rty_cmd)
{
  /* Gain: '<S7>/Gain' incorporates:
   *  SignalConversion: '<S7>/TmpSignal ConversionAtcurrentOutport1'
   *  SignalConversion: '<S7>/TmpSignal ConversionAtdesiredOutport1'
   *  Sum: '<S7>/Sum'
   */
  *rty_cmd = (rtu_desired - rtu_current) * et_robocon_P.Gain_Gain_m;

  /* Saturate: '<S7>/Saturation' */
  if (*rty_cmd > et_robocon_P.Saturation_UpperSat_o) {
    /* SignalConversion: '<S7>/TmpSignal ConversionAtcmdInport1' */
    *rty_cmd = et_robocon_P.Saturation_UpperSat_o;
  } else {
    if (*rty_cmd < et_robocon_P.Saturation_LowerSat_j) {
      /* SignalConversion: '<S7>/TmpSignal ConversionAtcmdInport1' */
      *rty_cmd = et_robocon_P.Saturation_LowerSat_j;
    }
  }

  /* End of Saturate: '<S7>/Saturation' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
