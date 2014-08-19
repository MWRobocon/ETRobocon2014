/*
 * File: phiController.c
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

#include "phiController.h"

/* Include model header file for global data */
#include "et_robocon.h"
#include "et_robocon_private.h"

/* Output and update for Simulink Function: '<Root>/Phi_Controller' */
void phiController(real32_T rtu_desired, real32_T rtu_current, real32_T
                   rtu_battery, real32_T *rty_cmd)
{
  /* Gain: '<S4>/Gain2' incorporates:
   *  Gain: '<S4>/Gain1'
   *  Product: '<S4>/Divide'
   *  SignalConversion: '<S4>/TmpSignal ConversionAtbatteryOutport1'
   *  SignalConversion: '<S4>/TmpSignal ConversionAtcurrent1Outport1'
   *  SignalConversion: '<S4>/TmpSignal ConversionAtdesired1Outport1'
   *  Sum: '<S4>/Sum1'
   */
  *rty_cmd = (rtu_desired - rtu_current) * et_robocon_P.Gain1_Gain_k /
    rtu_battery * et_robocon_P.Gain2_Gain;

  /* Saturate: '<S4>/Saturation1' */
  if (*rty_cmd > et_robocon_P.Saturation1_UpperSat) {
    /* SignalConversion: '<S4>/TmpSignal ConversionAtcmd1Inport1' */
    *rty_cmd = et_robocon_P.Saturation1_UpperSat;
  } else {
    if (*rty_cmd < et_robocon_P.Saturation1_LowerSat) {
      /* SignalConversion: '<S4>/TmpSignal ConversionAtcmd1Inport1' */
      *rty_cmd = et_robocon_P.Saturation1_LowerSat;
    }
  }

  /* End of Saturate: '<S4>/Saturation1' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
