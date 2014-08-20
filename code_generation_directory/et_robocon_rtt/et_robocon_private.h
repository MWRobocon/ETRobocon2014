/*
 * File: et_robocon_private.h
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

#ifndef RTW_HEADER_et_robocon_private_h_
#define RTW_HEADER_et_robocon_private_h_
#include "rtwtypes.h"

extern const OperationModeEnum rtCP_pooled_8zK8QN4IYQ2C[3];
extern const uint8_T rtCP_pooled_7Voa1bA5GWKn[7];
extern const uint8_T rtCP_pooled_rl4GAPNFSkcY[7];
extern const uint8_T rtCP_pooled_NO8XQD0cqSxW[6];
extern const uint8_T rtCP_pooled_A11GRD0Jme6l[7];

#define rtCP_MainController_TRACK_     rtCP_pooled_8zK8QN4IYQ2C  /* Expression: TRACK_MODE_LIST
                                                                  * Referenced by: '<Root>/Main Controller'
                                                                  */
#define rtCP_LCD_p1                    rtCP_pooled_7Voa1bA5GWKn  /* Expression: lcdStr1
                                                                  * Referenced by: '<S21>/LCD'
                                                                  */
#define rtCP_LCD_p1_f                  rtCP_pooled_rl4GAPNFSkcY  /* Expression: lcdStr1
                                                                  * Referenced by: '<S8>/LCD'
                                                                  */
#define rtCP_LCD_p1_i                  rtCP_pooled_NO8XQD0cqSxW  /* Expression: lcdStr1
                                                                  * Referenced by: '<S24>/LCD'
                                                                  */
#define rtCP_LCD_p1_c                  rtCP_pooled_A11GRD0Jme6l  /* Expression: lcdStr1
                                                                  * Referenced by: '<S25>/LCD'
                                                                  */

extern void et_see_saw_modelineTracker_Init(DW_see_saw_modelineTracker_et_T
  *localDW, P_see_saw_modelineTracker_et__T *localP);
extern void e_see_saw_modelineTracker_Start(B_see_saw_modelineTracker_et__T
  *localB, P_see_saw_modelineTracker_et__T *localP);
extern void et_robo_see_saw_modelineTracker(real32_T rtu_light, real32_T
  rtu_trackingPower, real_T rtu_battery, real32_T rty_0[2],
  B_see_saw_modelineTracker_et__T *localB, DW_see_saw_modelineTracker_et_T
  *localDW, P_see_saw_modelineTracker_et__T *localP);
extern void et_robocon_StoreOffset_Start(B_StoreOffset_et_robocon_T *localB,
  P_StoreOffset_et_robocon_T *localP);
extern void et_robocon_StoreOffset(boolean_T rtu_Enable, real32_T rtu_x,
  B_StoreOffset_et_robocon_T *localB);
extern void et_robocon_Computepsi_Init(DW_Computepsi_et_robocon_T *localDW,
  P_Computepsi_et_robocon_T *localP);
extern void et_robocon_Computepsi_Enable(DW_Computepsi_et_robocon_T *localDW);
extern void et_robocon_Computepsi_Start(B_Computepsi_et_robocon_T *localB,
  P_Computepsi_et_robocon_T *localP);
extern void et_robocon_Computepsi(RT_MODEL_et_robocon_T * const et_robocon_M,
  real32_T rtu_gyro, B_Computepsi_et_robocon_T *localB,
  DW_Computepsi_et_robocon_T *localDW, P_Computepsi_et_robocon_T *localP);
extern void et_robocon_Processtheta1_Init(DW_Processtheta1_et_robocon_T *localDW,
  P_Processtheta1_et_robocon_T *localP);
extern void et_robocon_Processtheta1_Enable(DW_Processtheta1_et_robocon_T
  *localDW);
extern void et_robocon_Processtheta1_Start(B_Processtheta1_et_robocon_T *localB,
  P_Processtheta1_et_robocon_T *localP);
extern void et_roboco_Processtheta1_Disable(B_Processtheta1_et_robocon_T *localB,
  P_Processtheta1_et_robocon_T *localP);
extern void et_robocon_Processtheta1(RT_MODEL_et_robocon_T * const et_robocon_M,
  real32_T rtu_psi, real32_T rtu_theta_l, real32_T rtu_theta_r,
  B_Processtheta1_et_robocon_T *localB, DW_Processtheta1_et_robocon_T *localDW,
  P_Processtheta1_et_robocon_T *localP);

#endif                                 /* RTW_HEADER_et_robocon_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
