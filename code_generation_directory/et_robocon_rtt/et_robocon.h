/*
 * File: et_robocon.h
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

#ifndef RTW_HEADER_et_robocon_h_
#define RTW_HEADER_et_robocon_h_
#include <math.h>
#include <string.h>
#ifndef et_robocon_COMMON_INCLUDES_
# define et_robocon_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "driver_nxt.h"
#endif                                 /* et_robocon_COMMON_INCLUDES_ */

#include "et_robocon_types.h"

/* Child system includes */
#include "Speak_private.h"
#include "Speak.h"
#include "StatusLCD_private.h"
#include "StatusLCD.h"
#include "phiController_private.h"
#include "phiController.h"
#include "tail_controller_private.h"
#include "tail_controller.h"
#include "rt_zcfcn.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S11>/see_saw_mode.lineTracker' */
typedef struct {
  real32_T switchsideofline;           /* '<S18>/switch side of line' */
} B_see_saw_modelineTracker_et__T;

/* Block states (auto storage) for system '<S11>/see_saw_mode.lineTracker' */
typedef struct {
  real32_T DiscreteFilter_states;      /* '<S20>/Discrete Filter' */
  real32_T UnitDelay_DSTATE;           /* '<S20>/Unit Delay' */
} DW_see_saw_modelineTracker_et_T;

/* Block signals for system '<S106>/Store Offset' */
typedef struct {
  real32_T x;                          /* '<S110>/x' */
} B_StoreOffset_et_robocon_T;

/* Block signals for system '<S100>/Compute psi' */
typedef struct {
  real32_T OutportBufferForpsi;        /* '<S112>/Discrete-Time Integrator1' */
} B_Computepsi_et_robocon_T;

/* Block states (auto storage) for system '<S100>/Compute psi' */
typedef struct {
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S112>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator1_PREV_U;/* '<S112>/Discrete-Time Integrator1' */
  uint32_T Computepsi_ELAPS_T;         /* '<S100>/Compute psi' */
  uint32_T Computepsi_PREV_T;          /* '<S100>/Compute psi' */
  uint8_T DiscreteTimeIntegrator1_SYSTEM_;/* '<S112>/Discrete-Time Integrator1' */
  boolean_T Computepsi_RESET_ELAPS_T;  /* '<S100>/Compute psi' */
} DW_Computepsi_et_robocon_T;

/* Block signals for system '<S101>/Process theta1' */
typedef struct {
  real32_T psi;                        /* '<S117>/psi' */
  real32_T Gain7;                      /* '<S117>/Gain7' */
  real32_T Sum3;                       /* '<S120>/Sum3' */
  real32_T theta;                      /* '<S117>/Sum2' */
  real32_T Sum3_j;                     /* '<S122>/Sum3' */
  real32_T Sum3_c;                     /* '<S121>/Sum3' */
  real32_T int_theta_f;                /* '<S117>/Discrete-Time Integrator2' */
  real32_T x[2];                       /* '<S123>/x' */
  B_StoreOffset_et_robocon_T EnabledSubsystem;/* '<S117>/Enabled Subsystem' */
} B_Processtheta1_et_robocon_T;

/* Block states (auto storage) for system '<S101>/Process theta1' */
typedef struct {
  real32_T DiscreteTimeIntegrator2_DSTATE;/* '<S117>/Discrete-Time Integrator2' */
  real32_T LowPassFilter1_states;      /* '<S120>/Low Pass Filter1' */
  real32_T UnitDelay_DSTATE;           /* '<S120>/Unit Delay' */
  real32_T LowPassFilter1_states_m;    /* '<S122>/Low Pass Filter1' */
  real32_T UnitDelay_DSTATE_e;         /* '<S122>/Unit Delay' */
  real32_T LowPassFilter1_states_d;    /* '<S121>/Low Pass Filter1' */
  real32_T UnitDelay_DSTATE_h;         /* '<S121>/Unit Delay' */
  real32_T DiscreteTimeIntegrator2_PREV_U;/* '<S117>/Discrete-Time Integrator2' */
  uint32_T Processtheta1_ELAPS_T;      /* '<S101>/Process theta1' */
  uint32_T Processtheta1_PREV_T;       /* '<S101>/Process theta1' */
  uint8_T DiscreteTimeIntegrator2_SYSTEM_;/* '<S117>/Discrete-Time Integrator2' */
  boolean_T Processtheta1_RESET_ELAPS_T;/* '<S101>/Process theta1' */
  boolean_T Enableoninit_PreviousInput;/* '<S117>/Enable on init' */
  boolean_T Enableoninit1_PreviousInput;/* '<S117>/Enable on init1' */
} DW_Processtheta1_et_robocon_T;

/* Block signals (auto storage) */
typedef struct {
  Sensors_Bus BusConversion_InsertedFor_MainC;
  States_Bus BusConversion_InsertedFor_Mai_g;
  Init_Bus initFlags;                  /* '<Root>/Main Controller' */
  PWM_bus PWM;                         /* '<Root>/Main Controller' */
  real32_T LowPassFilter;              /* '<S113>/Low Pass Filter' */
  real32_T tail;                       /* '<S111>/tail' */
  real32_T VectorConcatenate_h[2];     /* '<S18>/Vector Concatenate' */
  int32_T sonar;                       /* '<S22>/Rate Transition' */
  int32_T sonar_h;                     /* '<S22>/Ultrasonic Sensor' */
  uint16_T RateTransition1;            /* '<S22>/Rate Transition1' */
  uint16_T battery_n;                  /* '<S22>/Battery' */
  int8_T RateTransition2;              /* '<S22>/Rate Transition2' */
  int8_T Button;                       /* '<S22>/Button' */
  B_Processtheta1_et_robocon_T Processtheta1;/* '<S101>/Process theta1' */
  B_Computepsi_et_robocon_T Computepsi;/* '<S100>/Compute psi' */
  B_StoreOffset_et_robocon_T StoreOffset;/* '<S106>/Store Offset' */
  B_see_saw_modelineTracker_et__T see_saw_modelineTracker;/* '<S11>/see_saw_mode.lineTracker' */
} B_et_robocon_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  Init_Bus Delay_DSTATE;               /* '<Root>/Delay' */
  real32_T LowPassFilter_states;       /* '<S106>/Low Pass Filter' */
  real32_T LowPassFilter_states_h;     /* '<S113>/Low Pass Filter' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S17>/Discrete-Time Integrator' */
  real32_T LPF_states;                 /* '<S17>/LPF' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S17>/Discrete-Time Integrator1' */
  real32_T LowPassFilter_tmp;          /* '<S106>/Low Pass Filter' */
  real32_T LowPassFilter_tmp_d;        /* '<S113>/Low Pass Filter' */
  real32_T desired_tail;               /* '<S2>/normal_operation_modes.line_following' */
  real32_T turningPWM;                 /* '<S2>/normal_operation_modes.line_following' */
  real32_T des_vel;                    /* '<S2>/normal_operation_modes.line_following' */
  real32_T desired_phi;                /* '<S2>/normal_operation_modes.line_following' */
  real32_T DiscreteTimeIntegrator_PREV_U;/* '<S17>/Discrete-Time Integrator' */
  real32_T DiscreteTimeIntegrator1_PREV_U;/* '<S17>/Discrete-Time Integrator1' */
  real32_T desired_tail_c;             /* '<S2>/normal_operation_modes.gyro_calibration_mode' */
  int32_T RateTransition_Buffer0;      /* '<S22>/Rate Transition' */
  uint32_T see_saw_modebalance_ctrl_ELAPS_;/* '<S11>/see_saw_mode.balance_ctrl' */
  uint32_T see_saw_modebalance_ctrl_PREV_T;/* '<S11>/see_saw_mode.balance_ctrl' */
  uint16_T RateTransition1_Buffer0;    /* '<S22>/Rate Transition1' */
  uint16_T temporalCounter_i1;         /* '<S2>/normal_operation_modes.line_following' */
  uint16_T temporalCounter_i1_n;       /* '<S2>/normal_operation_modes.light_calibration_up' */
  uint16_T temporalCounter_i1_c;       /* '<S2>/normal_operation_modes.gyro_calibration_mode' */
  int8_T RateTransition2_Buffer0;      /* '<S22>/Rate Transition2' */
  uint8_T is_active_c3_et_robocon;     /* '<S101>/Reset Subsystem' */
  uint8_T is_c3_et_robocon;            /* '<S101>/Reset Subsystem' */
  uint8_T is_active_c1_et_robocon;     /* '<S100>/Reset Subsystem' */
  uint8_T is_c1_et_robocon;            /* '<S100>/Reset Subsystem' */
  uint8_T is_active_c5_et_robocon;     /* '<Root>/Main Controller' */
  uint8_T is_c5_et_robocon;            /* '<Root>/Main Controller' */
  uint8_T is_normal_operation_modes;   /* '<Root>/Main Controller' */
  uint8_T current_mode_index;          /* '<Root>/Main Controller' */
  uint8_T is_c6_et_robocon;            /* '<S2>/normal_operation_modes.line_following' */
  uint8_T is_see_saw_mode;             /* '<S2>/normal_operation_modes.line_following' */
  uint8_T is_SeesawLogic;              /* '<S2>/normal_operation_modes.line_following' */
  uint8_T is_active_SeesawLogic;       /* '<S2>/normal_operation_modes.line_following' */
  uint8_T is_active_After;             /* '<S2>/normal_operation_modes.line_following' */
  uint8_T DiscreteTimeIntegrator_SYSTEM_E;/* '<S17>/Discrete-Time Integrator' */
  uint8_T DiscreteTimeIntegrator1_SYSTEM_;/* '<S17>/Discrete-Time Integrator1' */
  uint8_T is_c4_light_sensor_calibration_;/* '<S2>/normal_operation_modes.light_calibration_up' */
  uint8_T is_light_sensor_calibration_up;/* '<S2>/normal_operation_modes.light_calibration_up' */
  uint8_T is_c2_gyro_calibration_algorith;/* '<S2>/normal_operation_modes.gyro_calibration_mode' */
  uint8_T is_gyro_calibration_mode;    /* '<S2>/normal_operation_modes.gyro_calibration_mode' */
  uint8_T is_GyroCalibration;          /* '<S2>/normal_operation_modes.gyro_calibration_mode' */
  boolean_T Memory_PreviousInput;      /* '<S106>/Memory' */
  boolean_T isStable;                  /* '<S2>/normal_operation_modes.line_following' */
  boolean_T see_saw_modebalance_ctrl_RESET_;/* '<S11>/see_saw_mode.balance_ctrl' */
  boolean_T isStable_m;                /* '<S2>/normal_operation_modes.light_calibration_up' */
  boolean_T isStable_k;                /* '<S2>/normal_operation_modes.gyro_calibration_mode' */
  boolean_T Gyroinitialization_MODE;   /* '<S100>/Gyro initialization' */
  DW_Processtheta1_et_robocon_T Processtheta1;/* '<S101>/Process theta1' */
  DW_Computepsi_et_robocon_T Computepsi;/* '<S100>/Compute psi' */
  DW_see_saw_modelineTracker_et_T see_saw_modelineTracker;/* '<S11>/see_saw_mode.lineTracker' */
} DW_et_robocon_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState tailinitialization_Trig_ZCE;/* '<S109>/tail initialization' */
} PrevZCX_et_robocon_T;

/* Parameters for system: '<S11>/see_saw_mode.lineTracker' */
struct P_see_saw_modelineTracker_et__T_ {
  real_T Gain_Gain;                    /* Expression: 100
                                        * Referenced by: '<S18>/Gain'
                                        */
  real32_T cmd_Y0;                     /* Computed Parameter: cmd_Y0
                                        * Referenced by: '<S18>/cmd'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S18>/Constant'
                                        */
  real32_T DiscreteFilter_NumCoef;     /* Computed Parameter: DiscreteFilter_NumCoef
                                        * Referenced by: '<S20>/Discrete Filter'
                                        */
  real32_T DiscreteFilter_DenCoef[2];  /* Computed Parameter: DiscreteFilter_DenCoef
                                        * Referenced by: '<S20>/Discrete Filter'
                                        */
  real32_T DiscreteFilter_InitialStates;/* Computed Parameter: DiscreteFilter_InitialStates
                                         * Referenced by: '<S20>/Discrete Filter'
                                         */
  real32_T Gain_Gain_j;                /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S20>/Gain'
                                        */
  real32_T UnitDelay_InitialCondition; /* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S20>/Unit Delay'
                                        */
  real32_T DeadZone_Start;             /* Computed Parameter: DeadZone_Start
                                        * Referenced by: '<S18>/Dead Zone'
                                        */
  real32_T DeadZone_End;               /* Computed Parameter: DeadZone_End
                                        * Referenced by: '<S18>/Dead Zone'
                                        */
  real32_T PD_Gain[2];                 /* Computed Parameter: PD_Gain
                                        * Referenced by: '<S18>/PD'
                                        */
  real32_T Saturation_UpperSat;        /* Computed Parameter: Saturation_UpperSat
                                        * Referenced by: '<S18>/Saturation'
                                        */
  real32_T Saturation_LowerSat;        /* Computed Parameter: Saturation_LowerSat
                                        * Referenced by: '<S18>/Saturation'
                                        */
  real32_T Saturation1_UpperSat;       /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S18>/Saturation1'
                                        */
  real32_T Saturation1_LowerSat;       /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S18>/Saturation1'
                                        */
  real32_T switchsideofline_Gain;      /* Computed Parameter: switchsideofline_Gain
                                        * Referenced by: '<S18>/switch side of line'
                                        */
};

/* Parameters for system: '<S106>/Store Offset' */
struct P_StoreOffset_et_robocon_T_ {
  real32_T x0_Y0;                      /* Computed Parameter: x0_Y0
                                        * Referenced by: '<S110>/x0'
                                        */
};

/* Parameters for system: '<S100>/Compute psi' */
struct P_Computepsi_et_robocon_T_ {
  real32_T psi_Y0;                     /* Computed Parameter: psi_Y0
                                        * Referenced by: '<S112>/psi'
                                        */
  real32_T Filtered_Y0;                /* Computed Parameter: Filtered_Y0
                                        * Referenced by: '<S112>/Filtered'
                                        */
  real32_T DiscreteTimeIntegrator1_gainval;/* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                            * Referenced by: '<S112>/Discrete-Time Integrator1'
                                            */
  real32_T DiscreteTimeIntegrator1_IC; /* Computed Parameter: DiscreteTimeIntegrator1_IC
                                        * Referenced by: '<S112>/Discrete-Time Integrator1'
                                        */
};

/* Parameters for system: '<S101>/Process theta1' */
struct P_Processtheta1_et_robocon_T_ {
  real32_T x0_Y0;                      /* Computed Parameter: x0_Y0
                                        * Referenced by: '<S123>/x0'
                                        */
  real32_T theta_Y0;                   /* Computed Parameter: theta_Y0
                                        * Referenced by: '<S117>/theta'
                                        */
  real32_T psi_out_Y0;                 /* Computed Parameter: psi_out_Y0
                                        * Referenced by: '<S117>/psi_out'
                                        */
  real32_T theta_dot_Y0;               /* Computed Parameter: theta_dot_Y0
                                        * Referenced by: '<S117>/theta_dot'
                                        */
  real32_T int_theta_Y0;               /* Computed Parameter: int_theta_Y0
                                        * Referenced by: '<S117>/int_theta'
                                        */
  real32_T phi_Y0;                     /* Computed Parameter: phi_Y0
                                        * Referenced by: '<S117>/phi'
                                        */
  real32_T phi_dot_Y0;                 /* Computed Parameter: phi_dot_Y0
                                        * Referenced by: '<S117>/phi_dot'
                                        */
  real32_T theta_dot_dot_Y0;           /* Computed Parameter: theta_dot_dot_Y0
                                        * Referenced by: '<S117>/theta_dot_dot'
                                        */
  real32_T DiscreteTimeIntegrator2_gainval;/* Computed Parameter: DiscreteTimeIntegrator2_gainval
                                            * Referenced by: '<S117>/Discrete-Time Integrator2'
                                            */
  real32_T DiscreteTimeIntegrator2_IC; /* Computed Parameter: DiscreteTimeIntegrator2_IC
                                        * Referenced by: '<S117>/Discrete-Time Integrator2'
                                        */
  real32_T UsePhiInTheta_Gain;         /* Computed Parameter: UsePhiInTheta_Gain
                                        * Referenced by: '<S117>/UsePhiInTheta'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S117>/Gain2'
                                        */
  real32_T Gain7_Gain;                 /* Expression: R/W
                                        * Referenced by: '<S117>/Gain7'
                                        */
  real32_T LowPassFilter1_NumCoef;     /* Computed Parameter: LowPassFilter1_NumCoef
                                        * Referenced by: '<S120>/Low Pass Filter1'
                                        */
  real32_T LowPassFilter1_DenCoef[2];  /* Computed Parameter: LowPassFilter1_DenCoef
                                        * Referenced by: '<S120>/Low Pass Filter1'
                                        */
  real32_T LowPassFilter1_InitialStates;/* Computed Parameter: LowPassFilter1_InitialStates
                                         * Referenced by: '<S120>/Low Pass Filter1'
                                         */
  real32_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S120>/Gain'
                                        */
  real32_T UnitDelay_InitialCondition; /* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S120>/Unit Delay'
                                        */
  real32_T LowPassFilter1_NumCoef_f;   /* Computed Parameter: LowPassFilter1_NumCoef_f
                                        * Referenced by: '<S122>/Low Pass Filter1'
                                        */
  real32_T LowPassFilter1_DenCoef_e[2];/* Computed Parameter: LowPassFilter1_DenCoef_e
                                        * Referenced by: '<S122>/Low Pass Filter1'
                                        */
  real32_T LowPassFilter1_InitialStates_h;/* Computed Parameter: LowPassFilter1_InitialStates_h
                                           * Referenced by: '<S122>/Low Pass Filter1'
                                           */
  real32_T Gain_Gain_f;                /* Computed Parameter: Gain_Gain_f
                                        * Referenced by: '<S122>/Gain'
                                        */
  real32_T UnitDelay_InitialCondition_a;/* Computed Parameter: UnitDelay_InitialCondition_a
                                         * Referenced by: '<S122>/Unit Delay'
                                         */
  real32_T LowPassFilter1_NumCoef_n;   /* Computed Parameter: LowPassFilter1_NumCoef_n
                                        * Referenced by: '<S121>/Low Pass Filter1'
                                        */
  real32_T LowPassFilter1_DenCoef_f[2];/* Computed Parameter: LowPassFilter1_DenCoef_f
                                        * Referenced by: '<S121>/Low Pass Filter1'
                                        */
  real32_T LowPassFilter1_InitialStates_k;/* Computed Parameter: LowPassFilter1_InitialStates_k
                                           * Referenced by: '<S121>/Low Pass Filter1'
                                           */
  real32_T Gain_Gain_h;                /* Computed Parameter: Gain_Gain_h
                                        * Referenced by: '<S121>/Gain'
                                        */
  real32_T UnitDelay_InitialCondition_i;/* Computed Parameter: UnitDelay_InitialCondition_i
                                         * Referenced by: '<S121>/Unit Delay'
                                         */
  boolean_T Constant_Value;            /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S117>/Constant'
                                        */
  boolean_T Constant1_Value;           /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S117>/Constant1'
                                        */
  boolean_T Enableoninit_X0;           /* Computed Parameter: Enableoninit_X0
                                        * Referenced by: '<S117>/Enable on init'
                                        */
  boolean_T Enableoninit1_X0;          /* Computed Parameter: Enableoninit1_X0
                                        * Referenced by: '<S117>/Enable on init1'
                                        */
  P_StoreOffset_et_robocon_T EnabledSubsystem;/* '<S117>/Enabled Subsystem' */
};

/* Parameters (auto storage) */
struct P_et_robocon_T_ {
  struct_FjjrIT366yeIj3aqvn0HfE balancerStates_Bus0;/* Variable: balancerStates_Bus0
                                                     * Referenced by: '<S2>/normal_operation_modes.line_following'
                                                     */
  real32_T K[5];                       /* Variable: K
                                        * Referenced by: '<S17>/Gain1'
                                        */
  uint32_T Speaker_speakerFreq;        /* Mask Parameter: Speaker_speakerFreq
                                        * Referenced by: '<S97>/Speaker'
                                        */
  Light_Bus lightCalib_InitialValue;   /* Computed Parameter: lightCalib_InitialValue
                                        * Referenced by: synthesized block
                                        */
  Init_Bus Delay_InitialCondition;     /* Computed Parameter: Delay_InitialCondition
                                        * Referenced by: '<Root>/Delay'
                                        */
  real_T Gain_Gain;                    /* Expression: 100
                                        * Referenced by: '<S17>/Gain'
                                        */
  real_T Constant_Value;               /* Expression: 50
                                        * Referenced by: '<S5>/Constant'
                                        */
  real32_T light_Y0;                   /* Computed Parameter: light_Y0
                                        * Referenced by: '<S19>/light'
                                        */
  real32_T Gain_Gain_d;                /* Computed Parameter: Gain_Gain_d
                                        * Referenced by: '<S19>/Gain'
                                        */
  real32_T Gain1_Gain;                 /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S19>/Gain1'
                                        */
  real32_T cmd_Y0;                     /* Computed Parameter: cmd_Y0
                                        * Referenced by: '<S17>/cmd'
                                        */
  real32_T DiscreteTimeIntegrator_gainval;/* Computed Parameter: DiscreteTimeIntegrator_gainval
                                           * Referenced by: '<S17>/Discrete-Time Integrator'
                                           */
  real32_T DiscreteTimeIntegrator_IC;  /* Computed Parameter: DiscreteTimeIntegrator_IC
                                        * Referenced by: '<S17>/Discrete-Time Integrator'
                                        */
  real32_T msrads_Gain;                /* Expression: 1/R
                                        * Referenced by: '<S17>/m//s --> rad//s'
                                        */
  real32_T LPF_NumCoef;                /* Computed Parameter: LPF_NumCoef
                                        * Referenced by: '<S17>/LPF'
                                        */
  real32_T LPF_DenCoef[2];             /* Computed Parameter: LPF_DenCoef
                                        * Referenced by: '<S17>/LPF'
                                        */
  real32_T LPF_InitialStates;          /* Computed Parameter: LPF_InitialStates
                                        * Referenced by: '<S17>/LPF'
                                        */
  real32_T Constant_Value_e;           /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S17>/Constant'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S17>/Constant1'
                                        */
  real32_T DiscreteTimeIntegrator1_gainval;/* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                            * Referenced by: '<S17>/Discrete-Time Integrator1'
                                            */
  real32_T DiscreteTimeIntegrator1_IC; /* Computed Parameter: DiscreteTimeIntegrator1_IC
                                        * Referenced by: '<S17>/Discrete-Time Integrator1'
                                        */
  real32_T Saturation_UpperSat;        /* Computed Parameter: Saturation_UpperSat
                                        * Referenced by: '<S17>/Saturation'
                                        */
  real32_T Saturation_LowerSat;        /* Computed Parameter: Saturation_LowerSat
                                        * Referenced by: '<S17>/Saturation'
                                        */
  real32_T tail_0_Y0;                  /* Computed Parameter: tail_0_Y0
                                        * Referenced by: '<S111>/tail_0'
                                        */
  real32_T psi_dot_0_Y0;               /* Computed Parameter: psi_dot_0_Y0
                                        * Referenced by: '<S113>/psi_dot_0'
                                        */
  real32_T LowPassFilter_NumCoef;      /* Computed Parameter: LowPassFilter_NumCoef
                                        * Referenced by: '<S113>/Low Pass Filter'
                                        */
  real32_T LowPassFilter_DenCoef[2];   /* Computed Parameter: LowPassFilter_DenCoef
                                        * Referenced by: '<S113>/Low Pass Filter'
                                        */
  real32_T LowPassFilter_InitialStates;/* Computed Parameter: LowPassFilter_InitialStates
                                        * Referenced by: '<S113>/Low Pass Filter'
                                        */
  real32_T Gain1_Gain_k;               /* Computed Parameter: Gain1_Gain_k
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real32_T Gain2_Gain;                 /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S4>/Gain2'
                                        */
  real32_T Saturation1_UpperSat;       /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S4>/Saturation1'
                                        */
  real32_T Saturation1_LowerSat;       /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S4>/Saturation1'
                                        */
  real32_T Gain_Gain_m;                /* Computed Parameter: Gain_Gain_m
                                        * Referenced by: '<S7>/Gain'
                                        */
  real32_T Saturation_UpperSat_o;      /* Computed Parameter: Saturation_UpperSat_o
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real32_T Saturation_LowerSat_j;      /* Computed Parameter: Saturation_LowerSat_j
                                        * Referenced by: '<S7>/Saturation'
                                        */
  real32_T Gain1_Gain_n;               /* Computed Parameter: Gain1_Gain_n
                                        * Referenced by: '<S104>/Gain1'
                                        */
  real32_T Gain1_Gain_g;               /* Computed Parameter: Gain1_Gain_g
                                        * Referenced by: '<S102>/Gain1'
                                        */
  real32_T Gain1_Gain_c;               /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S103>/Gain1'
                                        */
  real32_T Gain1_Gain_gi;              /* Computed Parameter: Gain1_Gain_gi
                                        * Referenced by: '<S105>/Gain1'
                                        */
  real32_T LowPassFilter_NumCoef_m;    /* Computed Parameter: LowPassFilter_NumCoef_m
                                        * Referenced by: '<S106>/Low Pass Filter'
                                        */
  real32_T LowPassFilter_DenCoef_e[2]; /* Computed Parameter: LowPassFilter_DenCoef_e
                                        * Referenced by: '<S106>/Low Pass Filter'
                                        */
  real32_T LowPassFilter_InitialStates_f;/* Computed Parameter: LowPassFilter_InitialStates_f
                                          * Referenced by: '<S106>/Low Pass Filter'
                                          */
  real32_T Gain1_Gain_j;               /* Computed Parameter: Gain1_Gain_j
                                        * Referenced by: '<S108>/Gain1'
                                        */
  real32_T Constant_Value_ei;          /* Computed Parameter: Constant_Value_ei
                                        * Referenced by: '<S108>/Constant'
                                        */
  real32_T Constant_Value_b;           /* Expression: single(0)
                                        * Referenced by: '<S31>/Constant'
                                        */
  real32_T phi_des_InitialValue;       /* Computed Parameter: phi_des_InitialValue
                                        * Referenced by: synthesized block
                                        */
  int32_T RateTransition_X0;           /* Computed Parameter: RateTransition_X0
                                        * Referenced by: '<S22>/Rate Transition'
                                        */
  uint32_T Speaker_p3;                 /* Computed Parameter: Speaker_p3
                                        * Referenced by: '<S97>/Speaker'
                                        */
  uint32_T Speaker_p4;                 /* Computed Parameter: Speaker_p4
                                        * Referenced by: '<S97>/Speaker'
                                        */
  uint32_T Delay_DelayLength;          /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<Root>/Delay'
                                        */
  OperationModeEnum current_mode_InitialValue;/* Expression: []
                                               * Referenced by: synthesized block
                                               */
  OperationModeStatusEnum current_mode_status_InitialValu;/* Expression: []
                                                           * Referenced by: synthesized block
                                                           */
  uint16_T RateTransition1_X0;         /* Computed Parameter: RateTransition1_X0
                                        * Referenced by: '<S22>/Rate Transition1'
                                        */
  int8_T RateTransition2_X0;           /* Computed Parameter: RateTransition2_X0
                                        * Referenced by: '<S22>/Rate Transition2'
                                        */
  uint8_T Speaker_p1;                  /* Computed Parameter: Speaker_p1
                                        * Referenced by: '<S97>/Speaker'
                                        */
  boolean_T Memory_X0;                 /* Computed Parameter: Memory_X0
                                        * Referenced by: '<S106>/Memory'
                                        */
  boolean_T Constant_Value_g;          /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S106>/Constant'
                                        */
  P_Processtheta1_et_robocon_T Processtheta1;/* '<S101>/Process theta1' */
  P_Computepsi_et_robocon_T Computepsi;/* '<S100>/Compute psi' */
  P_StoreOffset_et_robocon_T StoreOffset;/* '<S106>/Store Offset' */
  P_see_saw_modelineTracker_et__T see_saw_modelineTracker;/* '<S11>/see_saw_mode.lineTracker' */
};

/* Real-time Model Data Structure */
struct tag_RTM_et_robocon_T {
  const char_T * volatile errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    struct {
      uint8_T TID[4];
    } TaskCounters;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_et_robocon_T et_robocon_P;

/* Block signals (auto storage) */
extern B_et_robocon_T et_robocon_B;

/* Block states (auto storage) */
extern DW_et_robocon_T et_robocon_DW;

/*
 * Exported States
 *
 * Note: Exported states are block states with an exported global
 * storage class designation.  Code generation will declare the memory for these
 * states and exports their symbols.
 *
 */
extern Light_Bus lightCalib;           /* Simulink.Signal object 'lightCalib' */
extern real32_T phi_des;               /* Simulink.Signal object 'phi_des' */
extern OperationModeEnum current_mode; /* Simulink.Signal object 'current_mode' */
extern OperationModeStatusEnum current_mode_status;/* Simulink.Signal object 'current_mode_status' */

/* External data declarations for dependent source files */
extern const Light_Bus et_robocon_rtZLight_Bus;/* Light_Bus ground */

/* Zero-crossing (trigger) state */
extern PrevZCX_et_robocon_T et_robocon_PrevZCX;

/* Model entry point functions */
extern void et_robocon_initialize(void);
extern void et_robocon_output(void);
extern void et_robocon_update(void);
extern void et_robocon_terminate(void);

/* Real-time Model object */
extern RT_MODEL_et_robocon_T *const et_robocon_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'et_robocon'
 * '<S1>'   : 'et_robocon/LCD_Status'
 * '<S2>'   : 'et_robocon/Main Controller'
 * '<S3>'   : 'et_robocon/NXT'
 * '<S4>'   : 'et_robocon/Phi_Controller'
 * '<S5>'   : 'et_robocon/Speak'
 * '<S6>'   : 'et_robocon/State Estimation'
 * '<S7>'   : 'et_robocon/Tail_Controller'
 * '<S8>'   : 'et_robocon/LCD_Status/LCD'
 * '<S9>'   : 'et_robocon/Main Controller/normal_operation_modes.gyro_calibration_mode'
 * '<S10>'  : 'et_robocon/Main Controller/normal_operation_modes.light_calibration_up'
 * '<S11>'  : 'et_robocon/Main Controller/normal_operation_modes.line_following'
 * '<S12>'  : 'et_robocon/Main Controller/normal_operation_modes.gyro_calibration_mode/gyro_calibration_mode.GyroCalibration.Speak'
 * '<S13>'  : 'et_robocon/Main Controller/normal_operation_modes.gyro_calibration_mode/gyro_calibration_mode.GyroCalibration.Speak/Speaker'
 * '<S14>'  : 'et_robocon/Main Controller/normal_operation_modes.light_calibration_up/Speak'
 * '<S15>'  : 'et_robocon/Main Controller/normal_operation_modes.light_calibration_up/Speak/Speaker'
 * '<S16>'  : 'et_robocon/Main Controller/normal_operation_modes.line_following/see_saw_mode.'
 * '<S17>'  : 'et_robocon/Main Controller/normal_operation_modes.line_following/see_saw_mode.balance_ctrl'
 * '<S18>'  : 'et_robocon/Main Controller/normal_operation_modes.line_following/see_saw_mode.lineTracker'
 * '<S19>'  : 'et_robocon/Main Controller/normal_operation_modes.line_following/see_saw_mode.processLight'
 * '<S20>'  : 'et_robocon/Main Controller/normal_operation_modes.line_following/see_saw_mode.lineTracker/LPF and deriv'
 * '<S21>'  : 'et_robocon/Main Controller/normal_operation_modes.line_following/see_saw_mode.processLight/LCD'
 * '<S22>'  : 'et_robocon/NXT/Hardware'
 * '<S23>'  : 'et_robocon/NXT/Simulation'
 * '<S24>'  : 'et_robocon/NXT/Hardware/LCD'
 * '<S25>'  : 'et_robocon/NXT/Hardware/LCD_LINE1'
 * '<S26>'  : 'et_robocon/NXT/Hardware/Motor Left'
 * '<S27>'  : 'et_robocon/NXT/Hardware/Motor Right'
 * '<S28>'  : 'et_robocon/NXT/Hardware/Motor Tail'
 * '<S29>'  : 'et_robocon/NXT/Hardware/Receive Bluetooth Status'
 * '<S30>'  : 'et_robocon/NXT/Hardware/Send Bluetooth Status'
 * '<S31>'  : 'et_robocon/NXT/Hardware/Receive Bluetooth Status/BluetoothOFF'
 * '<S32>'  : 'et_robocon/NXT/Hardware/Receive Bluetooth Status/BluetoothONMario'
 * '<S33>'  : 'et_robocon/NXT/Hardware/Receive Bluetooth Status/BluetoothONPrincess'
 * '<S34>'  : 'et_robocon/NXT/Hardware/Send Bluetooth Status/BluetoothOFF'
 * '<S35>'  : 'et_robocon/NXT/Hardware/Send Bluetooth Status/BluetoothONMario'
 * '<S36>'  : 'et_robocon/NXT/Hardware/Send Bluetooth Status/BluetoothONPrincess'
 * '<S37>'  : 'et_robocon/NXT/Simulation/Environment'
 * '<S38>'  : 'et_robocon/NXT/Simulation/Robot'
 * '<S39>'  : 'et_robocon/NXT/Simulation/Virtual Sensors'
 * '<S40>'  : 'et_robocon/NXT/Simulation/Robot/Robot'
 * '<S41>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD'
 * '<S42>'  : 'et_robocon/NXT/Simulation/Robot/Robot/Left Motor'
 * '<S43>'  : 'et_robocon/NXT/Simulation/Robot/Robot/Measurements'
 * '<S44>'  : 'et_robocon/NXT/Simulation/Robot/Robot/Right Motor'
 * '<S45>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID'
 * '<S46>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Left Motor'
 * '<S47>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Left Wheel'
 * '<S48>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Measurements'
 * '<S49>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Right Motor'
 * '<S50>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Right Wheel'
 * '<S51>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/CPU_1_RIGID'
 * '<S52>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/CrossTemplate_1_RIGID'
 * '<S53>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Lego_NXT_Touch_sensor_1_RIGID'
 * '<S54>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Light_sensor_1_RIGID'
 * '<S55>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Motor_1_RIGID'
 * '<S56>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Motor_2_RIGID'
 * '<S57>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Motor_3_RIGID'
 * '<S58>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/NXT_Lego_Liftarm_bent_2_RIGID'
 * '<S59>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/NXT_Lego_Liftarm_bent_3_RIGID'
 * '<S60>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Rotor_1_RIGID'
 * '<S61>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Rotor_2_RIGID'
 * '<S62>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Rotor_3_RIGID'
 * '<S63>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID'
 * '<S64>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID'
 * '<S65>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Lego_NXT_Touch_sensor_1_RIGID/Electric_touch_sensor_NXT_nose_1_RIGID'
 * '<S66>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Lego_NXT_Touch_sensor_1_RIGID/Electric_touch_sensor_NXT_plunger_2_RIGID'
 * '<S67>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Lego_NXT_Touch_sensor_1_RIGID/Sensor_NXT_body_2_RIGID'
 * '<S68>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Lego_NXT_Touch_sensor_1_RIGID/Sensor_NXT_body_connector_socket_2_RIGID'
 * '<S69>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/Lego_NXT_Touch_sensor_1_RIGID/Sensor_NXT_cover_1_RIGID'
 * '<S70>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID/All_Straight_2_RIGID'
 * '<S71>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID/BlueConnectorLong_3_RIGID'
 * '<S72>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID/BlueConnectorLong_4_RIGID'
 * '<S73>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID/BlueConnectorLong_5_RIGID'
 * '<S74>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID/BlueConnectorLong_6_RIGID'
 * '<S75>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID/L_Three_Five_90degrees_1_RIGID'
 * '<S76>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID/L_Three_Five_90degrees_3_RIGID'
 * '<S77>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/head_1_RIGID/ProximitySensor_1_RIGID'
 * '<S78>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/All_Straight_1_RIGID'
 * '<S79>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/All_Straight_2_RIGID'
 * '<S80>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/All_Straight_3_RIGID'
 * '<S81>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/BlueConnectorLong_1_RIGID'
 * '<S82>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/BlueConnectorLong_2_RIGID'
 * '<S83>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/Light_Gray_X10_1_RIGID'
 * '<S84>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/Light_Gray_X10_3_RIGID'
 * '<S85>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/Light_Gray_X10_4_RIGID'
 * '<S86>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Body_1_RIGID/lower_horizontal_connector_1_RIGID/Light_sensor_1_RIGID'
 * '<S87>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Left Wheel/CrossComplementEnd_Small_1_RIGID'
 * '<S88>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Left Wheel/CrossTemplate_1_RIGID'
 * '<S89>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Left Wheel/Light_Gray_X8_Template_1_RIGID'
 * '<S90>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Left Wheel/Light_Gray_X8_Template_2_RIGID'
 * '<S91>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Left Wheel/NXTWheel_1_RIGID'
 * '<S92>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Right Wheel/CrossComplementEnd_Small_1_RIGID'
 * '<S93>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Right Wheel/CrossTemplate_1_RIGID'
 * '<S94>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Right Wheel/Light_Gray_X8_Template_1_RIGID'
 * '<S95>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Right Wheel/Light_Gray_X8_Template_2_RIGID'
 * '<S96>'  : 'et_robocon/NXT/Simulation/Robot/Robot_CAD/Right Wheel/NXTWheel_1_RIGID'
 * '<S97>'  : 'et_robocon/Speak/Speaker'
 * '<S98>'  : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization'
 * '<S99>'  : 'et_robocon/State Estimation/Fall Detection'
 * '<S100>' : 'et_robocon/State Estimation/Gyro Processing'
 * '<S101>' : 'et_robocon/State Estimation/StateEstimation'
 * '<S102>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/Degrees to Radians'
 * '<S103>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/Degrees to Radians1'
 * '<S104>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/Degrees to Radians2'
 * '<S105>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/Degrees to Radians4'
 * '<S106>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/Low Pass Filter'
 * '<S107>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/Process Sonar'
 * '<S108>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/Vmax'
 * '<S109>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/tail processing'
 * '<S110>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/Low Pass Filter/Store Offset'
 * '<S111>' : 'et_robocon/State Estimation/Data Type Conversion Unit Conversion Tail Initialization/tail processing/tail initialization'
 * '<S112>' : 'et_robocon/State Estimation/Gyro Processing/Compute psi'
 * '<S113>' : 'et_robocon/State Estimation/Gyro Processing/Gyro initialization'
 * '<S114>' : 'et_robocon/State Estimation/Gyro Processing/Reset Subsystem'
 * '<S115>' : 'et_robocon/State Estimation/Gyro Processing/Compute psi/Very Low Pass Filter'
 * '<S116>' : 'et_robocon/State Estimation/Gyro Processing/Compute psi/Very Low Pass Filter/Unit Delay External IC'
 * '<S117>' : 'et_robocon/State Estimation/StateEstimation/Process theta1'
 * '<S118>' : 'et_robocon/State Estimation/StateEstimation/Reset Subsystem'
 * '<S119>' : 'et_robocon/State Estimation/StateEstimation/Process theta1/Enabled Subsystem'
 * '<S120>' : 'et_robocon/State Estimation/StateEstimation/Process theta1/Filteered_Derivative'
 * '<S121>' : 'et_robocon/State Estimation/StateEstimation/Process theta1/Filteered_Derivative1'
 * '<S122>' : 'et_robocon/State Estimation/StateEstimation/Process theta1/Filteered_Derivative2'
 * '<S123>' : 'et_robocon/State Estimation/StateEstimation/Process theta1/Store x0'
 */
#endif                                 /* RTW_HEADER_et_robocon_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
