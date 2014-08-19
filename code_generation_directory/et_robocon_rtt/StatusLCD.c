/*
 * File: StatusLCD.c
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

#include "StatusLCD.h"

/* Include model header file for global data */
#include "et_robocon.h"
#include "et_robocon_private.h"

/* Output and update for Simulink Function: '<Root>/LCD_Status' */
void StatusLCD(uint16_T rtu_state)
{
  /* S-Function (nxt_lcd): '<S8>/LCD' incorporates:
   *  DataTypeConversion: '<S8>/Data Type Conversion'
   *  SignalConversion: '<S1>/TmpSignal ConversionAtstateOutport1'
   */
  lcdDisplay(rtu_state, rtCP_LCD_p1_f, 1U, 1U);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
