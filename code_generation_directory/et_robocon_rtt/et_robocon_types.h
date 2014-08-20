/*
 * File: et_robocon_types.h
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

#ifndef RTW_HEADER_et_robocon_types_h_
#define RTW_HEADER_et_robocon_types_h_
#include "rtwtypes.h"
#include "OperationModeEnum.h"
#include "OperationModeStatusEnum.h"
#ifndef _DEFINED_TYPEDEF_FOR_struct_Jzcr9MVoeBkPBuOOZ1GwHC_
#define _DEFINED_TYPEDEF_FOR_struct_Jzcr9MVoeBkPBuOOZ1GwHC_

typedef struct {
  boolean_T fall;
  real32_T gyroInit;
  real32_T gyroReset;
  real32_T theta;
  real32_T tail;
} struct_Jzcr9MVoeBkPBuOOZ1GwHC;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_struct_FjjrIT366yeIj3aqvn0HfE_
#define _DEFINED_TYPEDEF_FOR_struct_FjjrIT366yeIj3aqvn0HfE_

typedef struct {
  real32_T theta;
  real32_T psi;
  real32_T theta_dot;
  real32_T psi_dot;
  real32_T int_theta;
} struct_FjjrIT366yeIj3aqvn0HfE;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_PWM_bus_
#define _DEFINED_TYPEDEF_FOR_PWM_bus_

typedef struct {
  real32_T left;
  real32_T right;
  real32_T tail;
} PWM_bus;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Balancer_States_Bus_
#define _DEFINED_TYPEDEF_FOR_Balancer_States_Bus_

typedef struct {
  real32_T theta;
  real32_T psi;
  real32_T theta_dot;
  real32_T psi_dot;
  real32_T int_theta;
} Balancer_States_Bus;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_States_Bus_
#define _DEFINED_TYPEDEF_FOR_States_Bus_

typedef struct {
  Balancer_States_Bus balancerStates;
  real32_T phi;
  real32_T phi_dot;
  real32_T theta_dot_dot;
} States_Bus;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Sensors_Bus_
#define _DEFINED_TYPEDEF_FOR_Sensors_Bus_

typedef struct {
  real32_T theta_L;
  real32_T theta_R;
  real32_T theta_T;
  real32_T light;
  real32_T gyro;
  real32_T sonar;
  real32_T battery;
  real32_T touch;
  real32_T time;
  real32_T ok_button;
  real32_T BT_status_in;
} Sensors_Bus;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Init_Bus_
#define _DEFINED_TYPEDEF_FOR_Init_Bus_

typedef struct {
  boolean_T fall;
  real32_T gyroInit;
  real32_T gyroReset;
  real32_T theta;
  real32_T tail;
} Init_Bus;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Light_Bus_
#define _DEFINED_TYPEDEF_FOR_Light_Bus_

typedef struct {
  real32_T whiteOnLimbo;
  real32_T blackOnLimbo;
  real32_T black;
  real32_T white;
  real32_T black_white;
  real32_T gray;
  real32_T blackOnTail;
  real32_T whiteOnTail;
  real32_T flashingBlack;
  real32_T flashingWhite;
  real32_T flashingMapBlack;
  real32_T flashingMapWhite;
} Light_Bus;

#endif

/* Parameters for system: '<S11>/see_saw_mode.lineTracker' */
typedef struct P_see_saw_modelineTracker_et__T_ P_see_saw_modelineTracker_et__T;

/* Parameters for system: '<S106>/Store Offset' */
typedef struct P_StoreOffset_et_robocon_T_ P_StoreOffset_et_robocon_T;

/* Parameters for system: '<S100>/Compute psi' */
typedef struct P_Computepsi_et_robocon_T_ P_Computepsi_et_robocon_T;

/* Parameters for system: '<S101>/Process theta1' */
typedef struct P_Processtheta1_et_robocon_T_ P_Processtheta1_et_robocon_T;

/* Parameters (auto storage) */
typedef struct P_et_robocon_T_ P_et_robocon_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_et_robocon_T RT_MODEL_et_robocon_T;

#endif                                 /* RTW_HEADER_et_robocon_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
