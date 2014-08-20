#ifndef __c2_gyro_calibration_algorithm_atomic_sub_chart_library_h__
#define __c2_gyro_calibration_algorithm_atomic_sub_chart_library_h__

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

#ifndef typedef_c2_OperationModeStatusEnum
#define typedef_c2_OperationModeStatusEnum

typedef enum OperationModeStatusEnum c2_OperationModeStatusEnum;

#endif                                 /*typedef_c2_OperationModeStatusEnum*/

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

#ifndef typedef_c2_Sensors_Bus
#define typedef_c2_Sensors_Bus

typedef struct Sensors_Bus_tag c2_Sensors_Bus;

#endif                                 /*typedef_c2_Sensors_Bus*/

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

#ifndef typedef_c2_Init_Bus
#define typedef_c2_Init_Bus

typedef struct Init_Bus_tag c2_Init_Bus;

#endif                                 /*typedef_c2_Init_Bus*/

#ifndef struct_PWM_bus_tag
#define struct_PWM_bus_tag

struct PWM_bus_tag
{
  real32_T left;
  real32_T right;
  real32_T tail;
};

#endif                                 /*struct_PWM_bus_tag*/

#ifndef typedef_c2_PWM_bus
#define typedef_c2_PWM_bus

typedef struct PWM_bus_tag c2_PWM_bus;

#endif                                 /*typedef_c2_PWM_bus*/

#ifndef typedef_SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
#define typedef_SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  uint8_T c2_tp_gyro_calibration_mode;
  uint8_T c2_tp_GyroCalibration;
  uint8_T c2_tp_Waiting;
  uint8_T c2_tp_MoveTailDown;
  uint8_T c2_tp_StartCalibration;
  uint8_T c2_tp_Wait;
  uint8_T c2_tp_MakeNoise;
  uint8_T c2_tp_StartCalibration1;
  uint8_T c2_tp_CalibComplete;
  uint8_T c2_b_tp_StartCalibration;
  boolean_T c2_isStable;
  uint8_T c2_is_active_c2_gyro_calibration_algorithm_atomic_sub_chart_libr;
  uint8_T c2_is_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  uint8_T c2_is_gyro_calibration_mode;
  uint8_T c2_is_GyroCalibration;
  real32_T c2_desired_tail;
  uint16_T c2_temporalCounter_i1;
  boolean_T c2_dataWrittenToVector[3];
  uint8_T c2_doSetSimStateSideEffects;
  const mxArray *c2_setSimStateSideEffectsInfo;
  c2_OperationModeStatusEnum *c2_current_task_operation_status_address;
  int32_T c2_current_task_operation_status_index;
  c2_Sensors_Bus *c2_sensors;
  c2_Init_Bus *c2_initFlags;
  c2_PWM_bus *c2_PWM;
} SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct;

#endif                                 /*typedef_SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray
  *sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_eml_resolved_functions_info
  (void);
extern void
  sf_exported_auto_userFcnGatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *c2_S, int32_T c2_ssidNumber, void *c2_ioVarPtrs);
extern void
  sf_exported_auto_autoFcnGatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *c2_S, int32_T c2_fcnNumber, void *c2_ioVarPtrs);

/* Function Definitions */
extern void
  sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_check_sum
  (mxArray *plhs[]);
extern void
  c2_gyro_calibration_algorithm_atomic_sub_chart_library_method_dispatcher
  (SimStruct *S, int_T method, void *data);

#endif
