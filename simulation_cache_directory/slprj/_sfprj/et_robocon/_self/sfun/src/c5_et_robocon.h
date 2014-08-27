#ifndef __c5_et_robocon_h__
#define __c5_et_robocon_h__

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

#ifndef typedef_c5_OperationModeStatusEnum
#define typedef_c5_OperationModeStatusEnum

typedef enum OperationModeStatusEnum c5_OperationModeStatusEnum;

#endif                                 /*typedef_c5_OperationModeStatusEnum*/

#ifndef enum_OperationModeEnum
#define enum_OperationModeEnum

enum OperationModeEnum
{
  OperationModeEnum_SKIP,
  OperationModeEnum_GYRO_CALIBRATION,
  OperationModeEnum_LIGHT_CALIBRATION_ON_TAIL,
  OperationModeEnum_LIGHT_CALIBRATION_UP,
  OperationModeEnum_LINE_TRACKING,
  OperationModeEnum_SEE_SAW,
  OperationModeEnum_LIMBO,
  OperationModeEnum_SEE_SAW_MARIO,
  OperationModeEnum_SEE_SAW_PRINCESS,
  OperationModeEnum_YOSHI,
  OperationModeEnum_PARKING,
  OperationModeEnum_LIGHT_CALIBRATION_LIMBO,
  OperationModeEnum_LINE_TRACKING_LIMBO,
  OperationModeEnum_LINE_TRACKING_ON_MAP,
  OperationModeEnum_LIGHT_CALIBRATION_UP_FLASHING,
  OperationModeEnum_LIGHT_CALIBRATION_UP_FLASHING_ON_MAP
};

#endif                                 /*enum_OperationModeEnum*/

#ifndef typedef_c5_OperationModeEnum
#define typedef_c5_OperationModeEnum

typedef enum OperationModeEnum c5_OperationModeEnum;

#endif                                 /*typedef_c5_OperationModeEnum*/

#ifndef struct_PWM_bus_tag
#define struct_PWM_bus_tag

struct PWM_bus_tag
{
  real32_T left;
  real32_T right;
  real32_T tail;
};

#endif                                 /*struct_PWM_bus_tag*/

#ifndef typedef_c5_PWM_bus
#define typedef_c5_PWM_bus

typedef struct PWM_bus_tag c5_PWM_bus;

#endif                                 /*typedef_c5_PWM_bus*/

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

#ifndef typedef_c5_Balancer_States_Bus
#define typedef_c5_Balancer_States_Bus

typedef struct Balancer_States_Bus_tag c5_Balancer_States_Bus;

#endif                                 /*typedef_c5_Balancer_States_Bus*/

#ifndef struct_States_Bus_tag
#define struct_States_Bus_tag

struct States_Bus_tag
{
  c5_Balancer_States_Bus balancerStates;
  real32_T phi;
  real32_T phi_dot;
  real32_T theta_dot_dot;
};

#endif                                 /*struct_States_Bus_tag*/

#ifndef typedef_c5_States_Bus
#define typedef_c5_States_Bus

typedef struct States_Bus_tag c5_States_Bus;

#endif                                 /*typedef_c5_States_Bus*/

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

#ifndef typedef_c5_Sensors_Bus
#define typedef_c5_Sensors_Bus

typedef struct Sensors_Bus_tag c5_Sensors_Bus;

#endif                                 /*typedef_c5_Sensors_Bus*/

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

#ifndef typedef_c5_Light_Bus
#define typedef_c5_Light_Bus

typedef struct Light_Bus_tag c5_Light_Bus;

#endif                                 /*typedef_c5_Light_Bus*/

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

#ifndef typedef_c5_Init_Bus
#define typedef_c5_Init_Bus

typedef struct Init_Bus_tag c5_Init_Bus;

#endif                                 /*typedef_c5_Init_Bus*/

#ifndef typedef_SFc5_et_roboconInstanceStruct
#define typedef_SFc5_et_roboconInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c5_sfEvent;
  uint8_T c5_tp_emergency_stop;
  uint8_T c5_tp_normal_operation_modes;
  uint8_T c5_tp_gyro_calibration_mode;
  uint8_T c5_tp_light_calibration_up;
  uint8_T c5_tp_line_following;
  uint8_T c5_tp_WeShouldNotBeHere;
  boolean_T c5_isStable;
  uint8_T c5_is_active_c5_et_robocon;
  uint8_T c5_is_c5_et_robocon;
  uint8_T c5_is_normal_operation_modes;
  c5_OperationModeEnum c5_TRACK_MODE_LIST[3];
  uint8_T c5_current_mode_index;
  c5_Init_Bus c5_Init_Bus0;
  c5_Balancer_States_Bus c5_balancerStates_Bus0;
  SimStruct *c5_subchartSimstruct;
  SimStruct *c5_b_subchartSimstruct;
  SimStruct *c5_c_subchartSimstruct;
  boolean_T c5_dataWrittenToVector[1];
  uint8_T c5_doSetSimStateSideEffects;
  const mxArray *c5_setSimStateSideEffectsInfo;
  c5_OperationModeEnum *c5_current_mode_address;
  int32_T c5_b_current_mode_index;
  c5_OperationModeStatusEnum *c5_current_mode_status_address;
  int32_T c5_current_mode_status_index;
  c5_Light_Bus *c5_lightCalib_address;
  int32_T c5_lightCalib_index;
  real32_T *c5_phi_des_address;
  int32_T c5_phi_des_index;
  c5_PWM_bus *c5_PWM;
  c5_States_Bus *c5_states;
  c5_Sensors_Bus *c5_sensors;
  real32_T *c5_BT_status_out;
  c5_Init_Bus *c5_initFlags;
} SFc5_et_roboconInstanceStruct;

#endif                                 /*typedef_SFc5_et_roboconInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_et_robocon_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c5_et_robocon_get_check_sum(mxArray *plhs[]);
extern void c5_et_robocon_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
