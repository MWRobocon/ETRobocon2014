#ifndef __c6_et_robocon_h__
#define __c6_et_robocon_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef enum_OperationModeStatusEnum
#define enum_OperationModeStatusEnum

enum OperationModeStatusEnum
{
  OperationModeStatusEnum_NOT_STARTED,
  OperationModeStatusEnum_IN_PROGRESS,
  OperationModeStatusEnum_SUCCESSFULLY_COMPLETED,
  OperationModeStatusEnum_ABORTED
};

#endif                                 /*enum_OperationModeStatusEnum*/

#ifndef typedef_c6_OperationModeStatusEnum
#define typedef_c6_OperationModeStatusEnum

typedef enum OperationModeStatusEnum c6_OperationModeStatusEnum;

#endif                                 /*typedef_c6_OperationModeStatusEnum*/

#ifndef struct_Sensors_Bus_tag
#define struct_Sensors_Bus_tag

struct Sensors_Bus_tag
{
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
};

#endif                                 /*struct_Sensors_Bus_tag*/

#ifndef typedef_c6_Sensors_Bus
#define typedef_c6_Sensors_Bus

typedef struct Sensors_Bus_tag c6_Sensors_Bus;

#endif                                 /*typedef_c6_Sensors_Bus*/

#ifndef struct_Light_Bus_tag
#define struct_Light_Bus_tag

struct Light_Bus_tag
{
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
};

#endif                                 /*struct_Light_Bus_tag*/

#ifndef typedef_c6_Light_Bus
#define typedef_c6_Light_Bus

typedef struct Light_Bus_tag c6_Light_Bus;

#endif                                 /*typedef_c6_Light_Bus*/

#ifndef struct_PWM_bus_tag
#define struct_PWM_bus_tag

struct PWM_bus_tag
{
  real32_T left;
  real32_T right;
  real32_T tail;
};

#endif                                 /*struct_PWM_bus_tag*/

#ifndef typedef_c6_PWM_bus
#define typedef_c6_PWM_bus

typedef struct PWM_bus_tag c6_PWM_bus;

#endif                                 /*typedef_c6_PWM_bus*/

#ifndef struct_Init_Bus_tag
#define struct_Init_Bus_tag

struct Init_Bus_tag
{
  boolean_T fall;
  real32_T gyroInit;
  real32_T gyroReset;
  real32_T theta;
  real32_T tail;
};

#endif                                 /*struct_Init_Bus_tag*/

#ifndef typedef_c6_Init_Bus
#define typedef_c6_Init_Bus

typedef struct Init_Bus_tag c6_Init_Bus;

#endif                                 /*typedef_c6_Init_Bus*/

#ifndef struct_struct_FjjrIT366yeIj3aqvn0HfE_tag
#define struct_struct_FjjrIT366yeIj3aqvn0HfE_tag

struct struct_FjjrIT366yeIj3aqvn0HfE_tag
{
  real32_T theta;
  real32_T psi;
  real32_T theta_dot;
  real32_T psi_dot;
  real32_T int_theta;
};

#endif                                 /*struct_struct_FjjrIT366yeIj3aqvn0HfE_tag*/

#ifndef typedef_c6_struct_FjjrIT366yeIj3aqvn0HfE
#define typedef_c6_struct_FjjrIT366yeIj3aqvn0HfE

typedef struct struct_FjjrIT366yeIj3aqvn0HfE_tag
  c6_struct_FjjrIT366yeIj3aqvn0HfE;

#endif                                 /*typedef_c6_struct_FjjrIT366yeIj3aqvn0HfE*/

#ifndef struct_Balancer_States_Bus_tag
#define struct_Balancer_States_Bus_tag

struct Balancer_States_Bus_tag
{
  real32_T theta;
  real32_T psi;
  real32_T theta_dot;
  real32_T psi_dot;
  real32_T int_theta;
};

#endif                                 /*struct_Balancer_States_Bus_tag*/

#ifndef typedef_c6_Balancer_States_Bus
#define typedef_c6_Balancer_States_Bus

typedef struct Balancer_States_Bus_tag c6_Balancer_States_Bus;

#endif                                 /*typedef_c6_Balancer_States_Bus*/

#ifndef struct_States_Bus_tag
#define struct_States_Bus_tag

struct States_Bus_tag
{
  c6_Balancer_States_Bus balancerStates;
  real32_T phi;
  real32_T phi_dot;
  real32_T theta_dot_dot;
};

#endif                                 /*struct_States_Bus_tag*/

#ifndef typedef_c6_States_Bus
#define typedef_c6_States_Bus

typedef struct States_Bus_tag c6_States_Bus;

#endif                                 /*typedef_c6_States_Bus*/

#ifndef typedef_SFc6_et_roboconInstanceStruct
#define typedef_SFc6_et_roboconInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c6_sfEvent;
  uint8_T c6_tp_see_saw_mode;
  uint8_T c6_tp_Waiting;
  uint8_T c6_tp_StandUp;
  uint8_T c6_tp_Balancing;
  uint8_T c6_tp_SeesawLogic;
  uint8_T c6_tp_MoveForwardSlowly;
  uint8_T c6_tp_StationnaryBalance;
  uint8_T c6_tp_Curvature;
  uint8_T c6_tp_Slowdown;
  uint8_T c6_tp_Const;
  uint8_T c6_tp_SpeedUp;
  uint8_T c6_tp_ConstantSpeed;
  uint8_T c6_tp_After;
  uint8_T c6_tp_Ramp;
  uint8_T c6_tp_RampUpOne;
  uint8_T c6_tp_BridgeTest;
  uint8_T c6_tp_RampUpTwo;
  uint8_T c6_tp_RotateInPlace;
  uint8_T c6_tp_SlowtoRotate;
  uint8_T c6_tp_Stop;
  boolean_T c6_isStable;
  uint8_T c6_is_active_c6_et_robocon;
  uint8_T c6_is_c6_et_robocon;
  uint8_T c6_is_see_saw_mode;
  uint8_T c6_is_SeesawLogic;
  uint8_T c6_is_active_SeesawLogic;
  uint8_T c6_is_Curvature;
  uint8_T c6_is_active_After;
  uint8_T c6_is_Ramp;
  real32_T c6_desired_tail;
  c6_struct_FjjrIT366yeIj3aqvn0HfE c6_balancerStates_Bus0;
  real32_T c6_turningPWM;
  real32_T c6_normalizedLight;
  real32_T c6_forwardPWM;
  real32_T c6_des_vel;
  real32_T c6_desired_phi;
  real32_T c6_desiredangle;
  uint16_T c6_temporalCounter_i1;
  boolean_T c6_dataWrittenToVector[13];
  uint8_T c6_doSetSimStateSideEffects;
  const mxArray *c6_setSimStateSideEffectsInfo;
  c6_OperationModeStatusEnum *c6_current_task_operation_status_address;
  int32_T c6_current_task_operation_status_index;
  c6_Light_Bus *c6_lightCalib_address;
  int32_T c6_lightCalib_index;
  c6_Sensors_Bus *c6_sensors;
  c6_PWM_bus *c6_PWM;
  c6_Init_Bus *c6_initFlags;
  c6_States_Bus *c6_states;
  real32_T *c6_BT_status_out;
  real32_T *c6_rawLight;
  c6_Light_Bus *c6_lightCalib;
  real32_T *c6_light;
  c6_Balancer_States_Bus *c6_balancerStates;
  real32_T *c6_desired_velocity;
  real_T *c6_battery;
  real32_T *c6_cmd;
  real32_T *c6_b_cmd;
  real32_T *c6_desiredLight;
  real32_T *c6_b_light;
  real32_T *c6_trackingPower;
  real_T *c6_b_battery;
} SFc6_et_roboconInstanceStruct;

#endif                                 /*typedef_SFc6_et_roboconInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_et_robocon_get_eml_resolved_functions_info(void);
extern void sf_exported_auto_userFcnGatewayc6_et_robocon(SimStruct *c6_S,
  int32_T c6_ssidNumber, void *c6_ioVarPtrs);
extern void sf_exported_auto_autoFcnGatewayc6_et_robocon(SimStruct *c6_S,
  int32_T c6_fcnNumber, void *c6_ioVarPtrs);

/* Function Definitions */
extern void sf_c6_et_robocon_get_check_sum(mxArray *plhs[]);
extern void c6_et_robocon_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
