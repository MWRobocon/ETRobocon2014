#ifndef __c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_h__
#define __c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_h__

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

#ifndef typedef_c4_OperationModeStatusEnum
#define typedef_c4_OperationModeStatusEnum

typedef enum OperationModeStatusEnum c4_OperationModeStatusEnum;

#endif                                 /*typedef_c4_OperationModeStatusEnum*/

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

#ifndef typedef_c4_Sensors_Bus
#define typedef_c4_Sensors_Bus

typedef struct Sensors_Bus_tag c4_Sensors_Bus;

#endif                                 /*typedef_c4_Sensors_Bus*/

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

#ifndef typedef_c4_Light_Bus
#define typedef_c4_Light_Bus

typedef struct Light_Bus_tag c4_Light_Bus;

#endif                                 /*typedef_c4_Light_Bus*/

#ifndef struct_PWM_bus_tag
#define struct_PWM_bus_tag

struct PWM_bus_tag
{
  real32_T left;
  real32_T right;
  real32_T tail;
};

#endif                                 /*struct_PWM_bus_tag*/

#ifndef typedef_c4_PWM_bus
#define typedef_c4_PWM_bus

typedef struct PWM_bus_tag c4_PWM_bus;

#endif                                 /*typedef_c4_PWM_bus*/

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

#ifndef typedef_c4_Init_Bus
#define typedef_c4_Init_Bus

typedef struct Init_Bus_tag c4_Init_Bus;

#endif                                 /*typedef_c4_Init_Bus*/

#ifndef typedef_SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
#define typedef_SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c4_sfEvent;
  uint8_T c4_tp_wait;
  uint8_T c4_tp_MoveUp;
  uint8_T c4_tp_Reset;
  uint8_T c4_tp_light_sensor_calibration_up;
  uint8_T c4_tp_WaitForBlack;
  uint8_T c4_tp_StoreBlack;
  uint8_T c4_tp_WaitForWhite;
  uint8_T c4_tp_StoreWhite;
  uint8_T c4_tp_CalibComplete;
  boolean_T c4_isStable;
  uint8_T c4_is_active_c4_light_sensor_calibration_algorithm_atomic_sub_ch;
  uint8_T c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib;
  uint8_T c4_is_light_sensor_calibration_up;
  real32_T c4_desired_tail;
  uint16_T c4_temporalCounter_i1;
  boolean_T c4_dataWrittenToVector[3];
  uint8_T c4_doSetSimStateSideEffects;
  const mxArray *c4_setSimStateSideEffectsInfo;
  c4_OperationModeStatusEnum *c4_current_task_operation_status_address;
  int32_T c4_current_task_operation_status_index;
  c4_Light_Bus *c4_lightCalib_address;
  int32_T c4_lightCalib_index;
  c4_Sensors_Bus *c4_sensors;
  c4_PWM_bus *c4_PWM;
  c4_Init_Bus *c4_initFlags;
} SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct;

#endif                                 /*typedef_SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_eml_resolved_functions_info
  (void);
extern void
  sf_exported_auto_userFcnGatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *c4_S, int32_T c4_ssidNumber, void *c4_ioVarPtrs);
extern void
  sf_exported_auto_autoFcnGatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *c4_S, int32_T c4_fcnNumber, void *c4_ioVarPtrs);

/* Function Definitions */
extern void
  sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_check_sum
  (mxArray *plhs[]);
extern void
  c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_method_dispatcher
  (SimStruct *S, int_T method, void *data);

#endif
