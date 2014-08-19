/*
 * File: et_robocon.c
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

#include "et_robocon.h"
#include "et_robocon_private.h"
#include "nxt_util.h"

/* Named constants for Chart: '<S2>/normal_operation_modes.gyro_calibration_mode' */
#define et_rob_IN_gyro_calibration_mode ((uint8_T)1U)
#define et_roboco_IN_StartCalibration_l ((uint8_T)4U)
#define et_robocon_IN_CalibComplete    ((uint8_T)1U)
#define et_robocon_IN_GyroCalibration  ((uint8_T)1U)
#define et_robocon_IN_MakeNoise        ((uint8_T)2U)
#define et_robocon_IN_MoveTailDown     ((uint8_T)3U)
#define et_robocon_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define et_robocon_IN_StartCalibration ((uint8_T)2U)
#define et_robocon_IN_StartCalibration1 ((uint8_T)5U)
#define et_robocon_IN_Wait             ((uint8_T)6U)

/* Named constants for Chart: '<S2>/normal_operation_modes.light_calibration_up' */
#define IN_light_sensor_calibration_up ((uint8_T)3U)
#define et_robocon_IN_MoveUp           ((uint8_T)1U)
#define et_robocon_IN_Reset            ((uint8_T)2U)
#define et_robocon_IN_StoreBlack       ((uint8_T)2U)
#define et_robocon_IN_StoreWhite       ((uint8_T)3U)
#define et_robocon_IN_WaitForBlack     ((uint8_T)4U)
#define et_robocon_IN_WaitForWhite     ((uint8_T)5U)
#define et_robocon_IN_wait             ((uint8_T)4U)

/* Named constants for Chart: '<S2>/normal_operation_modes.line_following' */
#define et_roboco_IN_StationnaryBalance ((uint8_T)5U)
#define et_robocon_IN_ApproachtoRamp_1 ((uint8_T)1U)
#define et_robocon_IN_Balancing        ((uint8_T)1U)
#define et_robocon_IN_ConstantSpeed    ((uint8_T)2U)
#define et_robocon_IN_MoveForwardSlowly ((uint8_T)3U)
#define et_robocon_IN_SpeedUp          ((uint8_T)4U)
#define et_robocon_IN_StandUp          ((uint8_T)2U)
#define et_robocon_IN_Waiting_f        ((uint8_T)3U)
#define et_robocon_IN_see_saw_mode     ((uint8_T)1U)

/* Named constants for Chart: '<Root>/Main Controller' */
#define et_r_IN_gyro_calibration_mode_l ((uint8_T)2U)
#define et_ro_IN_normal_operation_modes ((uint8_T)2U)
#define et_robo_IN_light_calibration_up ((uint8_T)3U)
#define et_robocon_IN_WeShouldNotBeHere ((uint8_T)1U)
#define et_robocon_IN_emergency_stop   ((uint8_T)1U)
#define et_robocon_IN_line_following   ((uint8_T)4U)

/* Named constants for Chart: '<S100>/Reset Subsystem' */
#define et_robocon_IN_CheckForReset    ((uint8_T)1U)

const Light_Bus et_robocon_rtZLight_Bus = {
  0.0F,                                /* whiteOnLimbo */
  0.0F,                                /* blackOnLimbo */
  0.0F,                                /* black */
  0.0F,                                /* white */
  0.0F,                                /* black_white */
  0.0F,                                /* gray */
  0.0F,                                /* blackOnTail */
  0.0F,                                /* whiteOnTail */
  0.0F,                                /* flashingBlack */
  0.0F,                                /* flashingWhite */
  0.0F,                                /* flashingMapBlack */
  0.0F                                 /* flashingMapWhite */
} ;                                    /* Light_Bus ground */

/* Exported block states */
Light_Bus lightCalib;                  /* Simulink.Signal object 'lightCalib' */
real32_T phi_des;                      /* Simulink.Signal object 'phi_des' */
OperationModeEnum current_mode;        /* Simulink.Signal object 'current_mode' */
OperationModeStatusEnum current_mode_status;/* Simulink.Signal object 'current_mode_status' */

/* Block signals (auto storage) */
B_et_robocon_T et_robocon_B;

/* Block states (auto storage) */
DW_et_robocon_T et_robocon_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_et_robocon_T et_robocon_PrevZCX;

/* Real-time model */
RT_MODEL_et_robocon_T et_robocon_M_;
RT_MODEL_et_robocon_T *const et_robocon_M = &et_robocon_M_;

/* Forward declaration for local functions */
static void enter_internal_normal_operation(void);
static void rate_scheduler(void);
static Init_Bus Init_Bus0;

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (et_robocon_M->Timing.TaskCounters.TID[1])++;
  if ((et_robocon_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.02s, 0.0s] */
    et_robocon_M->Timing.TaskCounters.TID[1] = 0;
  }

  (et_robocon_M->Timing.TaskCounters.TID[2])++;
  if ((et_robocon_M->Timing.TaskCounters.TID[2]) > 9) {/* Sample time: [0.04s, 0.0s] */
    et_robocon_M->Timing.TaskCounters.TID[2] = 0;
  }

  (et_robocon_M->Timing.TaskCounters.TID[3])++;
  if ((et_robocon_M->Timing.TaskCounters.TID[3]) > 24) {/* Sample time: [0.1s, 0.0s] */
    et_robocon_M->Timing.TaskCounters.TID[3] = 0;
  }
}

/* Initial conditions for function-call system: '<S11>/see_saw_mode.lineTracker' */
void et_see_saw_modelineTracker_Init(DW_see_saw_modelineTracker_et_T *localDW,
  P_see_saw_modelineTracker_et__T *localP)
{
  /* InitializeConditions for DiscreteFilter: '<S20>/Discrete Filter' */
  localDW->DiscreteFilter_states = localP->DiscreteFilter_InitialStates;

  /* InitializeConditions for UnitDelay: '<S20>/Unit Delay' */
  localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;
}

/* Start for function-call system: '<S11>/see_saw_mode.lineTracker' */
void e_see_saw_modelineTracker_Start(B_see_saw_modelineTracker_et__T *localB,
  P_see_saw_modelineTracker_et__T *localP)
{
  /* VirtualOutportStart for Outport: '<S18>/cmd' */
  localB->switchsideofline = localP->cmd_Y0;
}

/* Output and update for function-call system: '<S11>/see_saw_mode.lineTracker' */
void et_robo_see_saw_modelineTracker(real32_T rtu_light, real32_T
  rtu_trackingPower, real_T rtu_battery, real32_T rty_0[2],
  B_see_saw_modelineTracker_et__T *localB, DW_see_saw_modelineTracker_et_T
  *localDW, P_see_saw_modelineTracker_et__T *localP)
{
  real32_T rtb_Gain_n4;
  real32_T DiscreteFilter_tmp;
  real32_T rtb_DeadZone;
  real32_T rtb_DeadZone_idx_0;
  real_T u0;

  /* Constant: '<S18>/Constant' */
  rty_0[1] = localP->Constant_Value;

  /* DiscreteFilter: '<S20>/Discrete Filter' */
  DiscreteFilter_tmp = (rtu_light - localP->DiscreteFilter_DenCoef[1] *
                        localDW->DiscreteFilter_states) /
    localP->DiscreteFilter_DenCoef[0];

  /* Gain: '<S20>/Gain' incorporates:
   *  DiscreteFilter: '<S20>/Discrete Filter'
   */
  rtb_Gain_n4 = localP->DiscreteFilter_NumCoef * DiscreteFilter_tmp *
    localP->Gain_Gain_j;

  /* Sum: '<S18>/Sum' incorporates:
   *  SignalConversion: '<S18>/ConcatBufferAtVector Concatenate1In1'
   *  Sum: '<S20>/Sum3'
   *  UnitDelay: '<S20>/Unit Delay'
   */
  rtb_DeadZone_idx_0 = rty_0[0] - rtu_light;
  rtb_DeadZone = rty_0[1] - (rtb_Gain_n4 - localDW->UnitDelay_DSTATE);

  /* DeadZone: '<S18>/Dead Zone' */
  if (rtb_DeadZone_idx_0 > localP->DeadZone_End) {
    rtb_DeadZone_idx_0 -= localP->DeadZone_End;
  } else if (rtb_DeadZone_idx_0 >= localP->DeadZone_Start) {
    rtb_DeadZone_idx_0 = 0.0F;
  } else {
    rtb_DeadZone_idx_0 -= localP->DeadZone_Start;
  }

  if (rtb_DeadZone > localP->DeadZone_End) {
    rtb_DeadZone -= localP->DeadZone_End;
  } else if (rtb_DeadZone >= localP->DeadZone_Start) {
    rtb_DeadZone = 0.0F;
  } else {
    rtb_DeadZone -= localP->DeadZone_Start;
  }

  /* End of DeadZone: '<S18>/Dead Zone' */

  /* Gain: '<S18>/PD' */
  rtb_DeadZone_idx_0 = localP->PD_Gain[0] * rtb_DeadZone_idx_0 + localP->
    PD_Gain[1] * rtb_DeadZone;

  /* Saturate: '<S18>/Saturation' incorporates:
   *  Gain: '<S18>/PD'
   */
  if (rtb_DeadZone_idx_0 > localP->Saturation_UpperSat) {
    rtb_DeadZone_idx_0 = localP->Saturation_UpperSat;
  } else {
    if (rtb_DeadZone_idx_0 < localP->Saturation_LowerSat) {
      rtb_DeadZone_idx_0 = localP->Saturation_LowerSat;
    }
  }

  /* Gain: '<S18>/Gain' incorporates:
   *  Product: '<S18>/Divide'
   *  Product: '<S18>/Product'
   *  Saturate: '<S18>/Saturation'
   */
  u0 = rtu_trackingPower * rtb_DeadZone_idx_0 / rtu_battery * localP->Gain_Gain;

  /* Saturate: '<S18>/Saturation1' */
  if (u0 > localP->Saturation1_UpperSat) {
    u0 = localP->Saturation1_UpperSat;
  } else {
    if (u0 < localP->Saturation1_LowerSat) {
      u0 = localP->Saturation1_LowerSat;
    }
  }

  /* Gain: '<S18>/switch side of line' incorporates:
   *  Saturate: '<S18>/Saturation1'
   */
  localB->switchsideofline = localP->switchsideofline_Gain * (real32_T)u0;

  /* Update for DiscreteFilter: '<S20>/Discrete Filter' */
  localDW->DiscreteFilter_states = DiscreteFilter_tmp;

  /* Update for UnitDelay: '<S20>/Unit Delay' */
  localDW->UnitDelay_DSTATE = rtb_Gain_n4;
}

/*
 * Start for enable system:
 *    '<S106>/Store Offset'
 *    '<S117>/Enabled Subsystem'
 */
void et_robocon_StoreOffset_Start(B_StoreOffset_et_robocon_T *localB,
  P_StoreOffset_et_robocon_T *localP)
{
  /* VirtualOutportStart for Outport: '<S110>/x0' */
  localB->x = localP->x0_Y0;
}

/*
 * Output and update for enable system:
 *    '<S106>/Store Offset'
 *    '<S117>/Enabled Subsystem'
 */
void et_robocon_StoreOffset(boolean_T rtu_Enable, real32_T rtu_x,
  B_StoreOffset_et_robocon_T *localB)
{
  /* Outputs for Enabled SubSystem: '<S106>/Store Offset' incorporates:
   *  EnablePort: '<S110>/Enable'
   */
  if (rtu_Enable) {
    /* Inport: '<S110>/x' */
    localB->x = rtu_x;
  }

  /* End of Outputs for SubSystem: '<S106>/Store Offset' */
}

/* Initial conditions for function-call system: '<S100>/Compute psi' */
void et_robocon_Computepsi_Init(DW_Computepsi_et_robocon_T *localDW,
  P_Computepsi_et_robocon_T *localP)
{
  /* InitializeConditions for DiscreteIntegrator: '<S112>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE = localP->DiscreteTimeIntegrator1_IC;
  localDW->DiscreteTimeIntegrator1_PREV_U = 0.0F;
}

/* Enable for function-call system: '<S100>/Compute psi' */
void et_robocon_Computepsi_Enable(DW_Computepsi_et_robocon_T *localDW)
{
  localDW->Computepsi_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S112>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_SYSTEM_ = 1U;
}

/* Start for function-call system: '<S100>/Compute psi' */
void et_robocon_Computepsi_Start(B_Computepsi_et_robocon_T *localB,
  P_Computepsi_et_robocon_T *localP)
{
  /* VirtualOutportStart for Outport: '<S112>/psi' */
  localB->OutportBufferForpsi = localP->psi_Y0;
}

/* Output and update for function-call system: '<S100>/Compute psi' */
void et_robocon_Computepsi(RT_MODEL_et_robocon_T * const et_robocon_M, real32_T
  rtu_gyro, B_Computepsi_et_robocon_T *localB, DW_Computepsi_et_robocon_T
  *localDW, P_Computepsi_et_robocon_T *localP)
{
  real32_T DiscreteTimeIntegrator1;
  if (localDW->Computepsi_RESET_ELAPS_T) {
    localDW->Computepsi_ELAPS_T = 0U;
  } else {
    localDW->Computepsi_ELAPS_T = et_robocon_M->Timing.clockTick0 -
      localDW->Computepsi_PREV_T;
  }

  localDW->Computepsi_PREV_T = et_robocon_M->Timing.clockTick0;
  localDW->Computepsi_RESET_ELAPS_T = false;

  /* DiscreteIntegrator: '<S112>/Discrete-Time Integrator1' */
  if (localDW->DiscreteTimeIntegrator1_SYSTEM_ != 0) {
    DiscreteTimeIntegrator1 = localDW->DiscreteTimeIntegrator1_DSTATE;
  } else {
    DiscreteTimeIntegrator1 = localP->DiscreteTimeIntegrator1_gainval *
      (real32_T)localDW->Computepsi_ELAPS_T
      * localDW->DiscreteTimeIntegrator1_PREV_U +
      localDW->DiscreteTimeIntegrator1_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S112>/Discrete-Time Integrator1' */

  /* SignalConversion: '<S112>/OutportBufferForpsi' */
  localB->OutportBufferForpsi = DiscreteTimeIntegrator1;

  /* Update for DiscreteIntegrator: '<S112>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_SYSTEM_ = 0U;
  localDW->DiscreteTimeIntegrator1_DSTATE = DiscreteTimeIntegrator1;
  localDW->DiscreteTimeIntegrator1_PREV_U = rtu_gyro;
}

/* Initial conditions for function-call system: '<S101>/Process theta1' */
void et_robocon_Processtheta1_Init(DW_Processtheta1_et_robocon_T *localDW,
  P_Processtheta1_et_robocon_T *localP)
{
  /* InitializeConditions for DiscreteIntegrator: '<S117>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_DSTATE = localP->DiscreteTimeIntegrator2_IC;
  localDW->DiscreteTimeIntegrator2_PREV_U = 0.0F;

  /* InitializeConditions for Memory: '<S117>/Enable on init' */
  localDW->Enableoninit_PreviousInput = localP->Enableoninit_X0;

  /* InitializeConditions for Memory: '<S117>/Enable on init1' */
  localDW->Enableoninit1_PreviousInput = localP->Enableoninit1_X0;

  /* InitializeConditions for DiscreteFilter: '<S120>/Low Pass Filter1' */
  localDW->LowPassFilter1_states = localP->LowPassFilter1_InitialStates;

  /* InitializeConditions for UnitDelay: '<S120>/Unit Delay' */
  localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

  /* InitializeConditions for DiscreteFilter: '<S122>/Low Pass Filter1' */
  localDW->LowPassFilter1_states_m = localP->LowPassFilter1_InitialStates_h;

  /* InitializeConditions for UnitDelay: '<S122>/Unit Delay' */
  localDW->UnitDelay_DSTATE_e = localP->UnitDelay_InitialCondition_a;

  /* InitializeConditions for DiscreteFilter: '<S121>/Low Pass Filter1' */
  localDW->LowPassFilter1_states_d = localP->LowPassFilter1_InitialStates_k;

  /* InitializeConditions for UnitDelay: '<S121>/Unit Delay' */
  localDW->UnitDelay_DSTATE_h = localP->UnitDelay_InitialCondition_i;
}

/* Enable for function-call system: '<S101>/Process theta1' */
void et_robocon_Processtheta1_Enable(DW_Processtheta1_et_robocon_T *localDW)
{
  localDW->Processtheta1_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S117>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_SYSTEM_ = 1U;
}

/* Disable for function-call system: '<S101>/Process theta1' */
void et_roboco_Processtheta1_Disable(B_Processtheta1_et_robocon_T *localB,
  P_Processtheta1_et_robocon_T *localP)
{
  /* Disable for Outport: '<S117>/theta_dot' */
  localB->Sum3_j = localP->theta_dot_Y0;

  /* Disable for Outport: '<S117>/phi' */
  localB->Gain7 = localP->phi_Y0;

  /* Disable for Outport: '<S117>/phi_dot' */
  localB->Sum3 = localP->phi_dot_Y0;

  /* Disable for Outport: '<S117>/theta_dot_dot' */
  localB->Sum3_c = localP->theta_dot_dot_Y0;
}

/* Start for function-call system: '<S101>/Process theta1' */
void et_robocon_Processtheta1_Start(B_Processtheta1_et_robocon_T *localB,
  P_Processtheta1_et_robocon_T *localP)
{
  /* Start for Enabled SubSystem: '<S117>/Store x0' */
  /* VirtualOutportStart for Outport: '<S123>/x0' */
  localB->x[0] = localP->x0_Y0;
  localB->x[1] = localP->x0_Y0;

  /* End of Start for SubSystem: '<S117>/Store x0' */

  /* Start for Enabled SubSystem: '<S117>/Enabled Subsystem' */
  et_robocon_StoreOffset_Start(&localB->EnabledSubsystem,
    (P_StoreOffset_et_robocon_T *)&localP->EnabledSubsystem);

  /* End of Start for SubSystem: '<S117>/Enabled Subsystem' */

  /* VirtualOutportStart for Outport: '<S117>/theta' */
  localB->theta = localP->theta_Y0;

  /* VirtualOutportStart for Outport: '<S117>/psi_out' */
  localB->psi = localP->psi_out_Y0;

  /* VirtualOutportStart for Outport: '<S117>/theta_dot' */
  localB->Sum3_j = localP->theta_dot_Y0;

  /* VirtualOutportStart for Outport: '<S117>/int_theta' */
  localB->int_theta_f = localP->int_theta_Y0;

  /* VirtualOutportStart for Outport: '<S117>/phi' */
  localB->Gain7 = localP->phi_Y0;

  /* VirtualOutportStart for Outport: '<S117>/phi_dot' */
  localB->Sum3 = localP->phi_dot_Y0;

  /* VirtualOutportStart for Outport: '<S117>/theta_dot_dot' */
  localB->Sum3_c = localP->theta_dot_dot_Y0;
}

/* Output and update for function-call system: '<S101>/Process theta1' */
void et_robocon_Processtheta1(RT_MODEL_et_robocon_T * const et_robocon_M,
  real32_T rtu_psi, real32_T rtu_theta_l, real32_T rtu_theta_r,
  B_Processtheta1_et_robocon_T *localB, DW_Processtheta1_et_robocon_T *localDW,
  P_Processtheta1_et_robocon_T *localP)
{
  real32_T rtb_Gain_f;
  real32_T rtb_Sum4;
  real32_T int_theta;
  real32_T LowPassFilter1_tmp_p;
  real32_T LowPassFilter1_tmp_c;
  real32_T rtb_theta_idx_0;
  real32_T rtb_theta_idx_1;
  if (localDW->Processtheta1_RESET_ELAPS_T) {
    localDW->Processtheta1_ELAPS_T = 0U;
  } else {
    localDW->Processtheta1_ELAPS_T = et_robocon_M->Timing.clockTick0 -
      localDW->Processtheta1_PREV_T;
  }

  localDW->Processtheta1_PREV_T = et_robocon_M->Timing.clockTick0;
  localDW->Processtheta1_RESET_ELAPS_T = false;

  /* DiscreteIntegrator: '<S117>/Discrete-Time Integrator2' */
  if (localDW->DiscreteTimeIntegrator2_SYSTEM_ != 0) {
    int_theta = localDW->DiscreteTimeIntegrator2_DSTATE;
  } else {
    int_theta = localP->DiscreteTimeIntegrator2_gainval * (real32_T)
      localDW->Processtheta1_ELAPS_T * localDW->DiscreteTimeIntegrator2_PREV_U +
      localDW->DiscreteTimeIntegrator2_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S117>/Discrete-Time Integrator2' */

  /* Inport: '<S117>/psi' */
  localB->psi = rtu_psi;

  /* Outputs for Enabled SubSystem: '<S117>/Store x0' incorporates:
   *  EnablePort: '<S123>/Enable'
   */
  /* Memory: '<S117>/Enable on init' incorporates:
   *  Inport: '<S123>/x'
   */
  if (localDW->Enableoninit_PreviousInput) {
    localB->x[0] = rtu_theta_l;
    localB->x[1] = rtu_theta_r;
  }

  /* End of Memory: '<S117>/Enable on init' */
  /* End of Outputs for SubSystem: '<S117>/Store x0' */

  /* Sum: '<S117>/Sum' */
  rtb_theta_idx_0 = rtu_theta_l - localB->x[0];
  rtb_theta_idx_1 = rtu_theta_r - localB->x[1];

  /* Sum: '<S117>/Sum4' incorporates:
   *  Gain: '<S117>/Gain2'
   *  Gain: '<S117>/UsePhiInTheta'
   *  Sum: '<S117>/Sum1'
   */
  rtb_Sum4 = (rtb_theta_idx_0 + rtb_theta_idx_1) * localP->Gain2_Gain +
    localP->UsePhiInTheta_Gain * localB->psi;

  /* Outputs for Enabled SubSystem: '<S117>/Enabled Subsystem' */

  /* Memory: '<S117>/Enable on init1' */
  et_robocon_StoreOffset(localDW->Enableoninit1_PreviousInput, rtb_Sum4,
    &localB->EnabledSubsystem);

  /* End of Outputs for SubSystem: '<S117>/Enabled Subsystem' */

  /* Gain: '<S117>/Gain7' incorporates:
   *  Sum: '<S117>/Sum5'
   */
  localB->Gain7 = (rtb_theta_idx_1 - rtb_theta_idx_0) * localP->Gain7_Gain;

  /* DiscreteFilter: '<S120>/Low Pass Filter1' */
  rtb_theta_idx_0 = (localB->Gain7 - localP->LowPassFilter1_DenCoef[1] *
                     localDW->LowPassFilter1_states) /
    localP->LowPassFilter1_DenCoef[0];

  /* Gain: '<S120>/Gain' incorporates:
   *  DiscreteFilter: '<S120>/Low Pass Filter1'
   */
  rtb_theta_idx_1 = localP->LowPassFilter1_NumCoef * rtb_theta_idx_0 *
    localP->Gain_Gain;

  /* Sum: '<S120>/Sum3' incorporates:
   *  UnitDelay: '<S120>/Unit Delay'
   */
  localB->Sum3 = rtb_theta_idx_1 - localDW->UnitDelay_DSTATE;

  /* Sum: '<S117>/Sum2' */
  localB->theta = rtb_Sum4 - localB->EnabledSubsystem.x;

  /* DiscreteFilter: '<S122>/Low Pass Filter1' */
  LowPassFilter1_tmp_p = (localB->theta - localP->LowPassFilter1_DenCoef_e[1] *
    localDW->LowPassFilter1_states_m) / localP->LowPassFilter1_DenCoef_e[0];

  /* Gain: '<S122>/Gain' incorporates:
   *  DiscreteFilter: '<S122>/Low Pass Filter1'
   */
  rtb_Gain_f = localP->LowPassFilter1_NumCoef_f * LowPassFilter1_tmp_p *
    localP->Gain_Gain_f;

  /* Sum: '<S122>/Sum3' incorporates:
   *  UnitDelay: '<S122>/Unit Delay'
   */
  localB->Sum3_j = rtb_Gain_f - localDW->UnitDelay_DSTATE_e;

  /* DiscreteFilter: '<S121>/Low Pass Filter1' */
  LowPassFilter1_tmp_c = (localB->Sum3_j - localP->LowPassFilter1_DenCoef_f[1] *
    localDW->LowPassFilter1_states_d) / localP->LowPassFilter1_DenCoef_f[0];

  /* Gain: '<S121>/Gain' incorporates:
   *  DiscreteFilter: '<S121>/Low Pass Filter1'
   */
  rtb_Sum4 = localP->LowPassFilter1_NumCoef_n * LowPassFilter1_tmp_c *
    localP->Gain_Gain_h;

  /* Sum: '<S121>/Sum3' incorporates:
   *  UnitDelay: '<S121>/Unit Delay'
   */
  localB->Sum3_c = rtb_Sum4 - localDW->UnitDelay_DSTATE_h;

  /* SignalConversion: '<S117>/OutportBufferForint_theta' */
  localB->int_theta_f = int_theta;

  /* Update for DiscreteIntegrator: '<S117>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_SYSTEM_ = 0U;
  localDW->DiscreteTimeIntegrator2_DSTATE = int_theta;
  localDW->DiscreteTimeIntegrator2_PREV_U = localB->theta;

  /* Update for Memory: '<S117>/Enable on init' incorporates:
   *  Constant: '<S117>/Constant'
   */
  localDW->Enableoninit_PreviousInput = localP->Constant_Value;

  /* Update for Memory: '<S117>/Enable on init1' incorporates:
   *  Constant: '<S117>/Constant1'
   */
  localDW->Enableoninit1_PreviousInput = localP->Constant1_Value;

  /* Update for DiscreteFilter: '<S120>/Low Pass Filter1' */
  localDW->LowPassFilter1_states = rtb_theta_idx_0;

  /* Update for UnitDelay: '<S120>/Unit Delay' */
  localDW->UnitDelay_DSTATE = rtb_theta_idx_1;

  /* Update for DiscreteFilter: '<S122>/Low Pass Filter1' */
  localDW->LowPassFilter1_states_m = LowPassFilter1_tmp_p;

  /* Update for UnitDelay: '<S122>/Unit Delay' */
  localDW->UnitDelay_DSTATE_e = rtb_Gain_f;

  /* Update for DiscreteFilter: '<S121>/Low Pass Filter1' */
  localDW->LowPassFilter1_states_d = LowPassFilter1_tmp_c;

  /* Update for UnitDelay: '<S121>/Unit Delay' */
  localDW->UnitDelay_DSTATE_h = rtb_Sum4;
}

/* Function for Chart: '<Root>/Main Controller' */
static void enter_internal_normal_operation(void)
{
  /* Entry Internal 'normal_operation_modes': '<S2>:9' */
  /* Transition: '<S2>:20' */
  current_mode_status = IN_PROGRESS;
  if (current_mode == GYRO_CALIBRATION) {
    /* Transition: '<S2>:21' */
    et_robocon_DW.is_normal_operation_modes = et_r_IN_gyro_calibration_mode_l;

    /* Entry: gyro_calibration_mode */
    /* Entry Internal: gyro_calibration_mode */
    et_robocon_DW.is_c2_gyro_calibration_algorith =
      et_rob_IN_gyro_calibration_mode;

    /* Entry Internal 'gyro_calibration_mode': '<S9>:1' */
    /* Transition: '<S9>:47' */
    et_robocon_DW.isStable_k = false;
    et_robocon_DW.is_gyro_calibration_mode = et_robocon_IN_StartCalibration;
  } else {
    /* Transition: '<S2>:22' */
    if (current_mode == LIGHT_CALIBRATION_UP) {
      /* Transition: '<S2>:143' */
      et_robocon_DW.is_normal_operation_modes = et_robo_IN_light_calibration_up;

      /* Entry: light_calibration_up */
      /* Entry Internal: light_calibration_up */
      /* Transition: '<S10>:34' */
      et_robocon_DW.isStable_m = false;
      et_robocon_DW.is_c4_light_sensor_calibration_ = et_robocon_IN_wait;

      /* Entry 'wait': '<S10>:32' */
      StatusLCD(200U);
    } else {
      /* Transition: '<S2>:24' */
      /* Transition: '<S2>:146' */
      if (current_mode == SEE_SAW_MARIO) {
        /* Transition: '<S2>:182' */
        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_line_following;

        /* Entry: Main Controller/normal_operation_modes.line_following */
        /* Entry Internal: Main Controller/normal_operation_modes.line_following */
        et_robocon_DW.isStable = false;
        et_robocon_DW.is_c6_et_robocon = et_robocon_IN_see_saw_mode;

        /* Enable for Function Call SubSystem: '<S11>/see_saw_mode.balance_ctrl' */
        /* Entry 'see_saw_mode': '<S11>:96' */
        et_robocon_DW.see_saw_modebalance_ctrl_RESET_ = true;

        /* Enable for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
        et_robocon_DW.DiscreteTimeIntegrator_SYSTEM_E = 1U;

        /* Enable for DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */
        et_robocon_DW.DiscreteTimeIntegrator1_SYSTEM_ = 1U;

        /* End of Enable for SubSystem: '<S11>/see_saw_mode.balance_ctrl' */
        et_robocon_DW.des_vel = 0.0F;
        et_robocon_DW.desired_tail = 0.0F;
        Speak();

        /* Entry Internal 'see_saw_mode': '<S11>:96' */
        /* Transition: '<S11>:97' */
        et_robocon_DW.isStable = false;
        et_robocon_DW.is_see_saw_mode = et_robocon_IN_Waiting_f;
      } else {
        /* Transition: '<S2>:34' */
        /* Transition: '<S2>:100' */
        /* Transition: '<S2>:101' */
        et_robocon_DW.is_normal_operation_modes =
          et_robocon_IN_WeShouldNotBeHere;
      }
    }
  }
}

/* Model output function */
void et_robocon_output(void)
{
  int16_T rtb_gyro_0;
  uint16_T rtb_touch_h_0;
  uint16_T rtb_touch_h_1;
  uint32_T rtb_time_b_0;
  int32_T k;
  real32_T rtb_Gain1_a;
  ZCEventType zcEvent;
  real32_T Gain1;
  real32_T Gain1_o;
  real32_T Gain1_a;
  real32_T Sum;
  real32_T VectorConcatenate[5];
  real32_T tmp[5];
  int32_T i;
  int8_T rtb_DataTypeConversion12_0;
  real_T u0;

  /* S-Function (nxt_gyro_sensor): '<S22>/Gyro Sensor' */
  rtb_gyro_0 = getGyroSensorValue(1U, 2U, 599);

  /* Gain: '<S104>/Gain1' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion4'
   *  S-Function (nxt_gyro_sensor): '<S22>/Gyro Sensor'
   */
  Gain1 = et_robocon_P.Gain1_Gain_n * (real32_T)rtb_gyro_0;

  /* Outputs for Enabled SubSystem: '<S100>/Gyro initialization' incorporates:
   *  EnablePort: '<S113>/Enable'
   */
  /* Delay: '<Root>/Delay' */
  if (et_robocon_DW.Delay_DSTATE.gyroInit > 0.0F) {
    if (!et_robocon_DW.Gyroinitialization_MODE) {
      /* InitializeConditions for DiscreteFilter: '<S113>/Low Pass Filter' */
      et_robocon_DW.LowPassFilter_states_h =
        et_robocon_P.LowPassFilter_InitialStates;
      et_robocon_DW.Gyroinitialization_MODE = true;
    }

    /* DiscreteFilter: '<S113>/Low Pass Filter' */
    et_robocon_DW.LowPassFilter_tmp_d = (Gain1 -
      et_robocon_P.LowPassFilter_DenCoef[1] *
      et_robocon_DW.LowPassFilter_states_h) /
      et_robocon_P.LowPassFilter_DenCoef[0];
    et_robocon_B.LowPassFilter = et_robocon_P.LowPassFilter_NumCoef *
      et_robocon_DW.LowPassFilter_tmp_d;
  } else {
    if (et_robocon_DW.Gyroinitialization_MODE) {
      et_robocon_DW.Gyroinitialization_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<S100>/Gyro initialization' */

  /* Sum: '<S100>/Sum' */
  Sum = Gain1 - et_robocon_B.LowPassFilter;

  /* Chart: '<S100>/Reset Subsystem' incorporates:
   *  Delay: '<Root>/Delay'
   */
  /* Gateway: State Estimation/Gyro Processing/Reset Subsystem */
  /* During: State Estimation/Gyro Processing/Reset Subsystem */
  if (et_robocon_DW.is_active_c1_et_robocon == 0U) {
    /* Entry: State Estimation/Gyro Processing/Reset Subsystem */
    et_robocon_DW.is_active_c1_et_robocon = 1U;

    /* Entry Internal: State Estimation/Gyro Processing/Reset Subsystem */
    /* Transition: '<S114>:2' */
    et_robocon_DW.is_c1_et_robocon = et_robocon_IN_CheckForReset;

    /* InitializeConditions for Function Call SubSystem: '<S100>/Compute psi' */

    /* Entry 'CheckForReset': '<S114>:1' */
    et_robocon_Computepsi_Init(&et_robocon_DW.Computepsi,
      (P_Computepsi_et_robocon_T *)&et_robocon_P.Computepsi);

    /* End of InitializeConditions for SubSystem: '<S100>/Compute psi' */

    /* Enable for Function Call SubSystem: '<S100>/Compute psi' */
    et_robocon_Computepsi_Enable(&et_robocon_DW.Computepsi);

    /* End of Enable for SubSystem: '<S100>/Compute psi' */

    /* Outputs for Function Call SubSystem: '<S100>/Compute psi' */

    /* Event: '<S114>:3' */
    et_robocon_Computepsi(et_robocon_M, Sum, &et_robocon_B.Computepsi,
                          &et_robocon_DW.Computepsi, (P_Computepsi_et_robocon_T *)
                          &et_robocon_P.Computepsi);

    /* End of Outputs for SubSystem: '<S100>/Compute psi' */
  } else {
    /* During 'CheckForReset': '<S114>:1' */
    if (et_robocon_DW.Delay_DSTATE.gyroReset == 1.0F) {
      /* Transition: '<S114>:4' */
      /* Exit 'CheckForReset': '<S114>:1' */
      et_robocon_DW.is_c1_et_robocon = et_robocon_IN_CheckForReset;

      /* InitializeConditions for Function Call SubSystem: '<S100>/Compute psi' */

      /* Entry 'CheckForReset': '<S114>:1' */
      et_robocon_Computepsi_Init(&et_robocon_DW.Computepsi,
        (P_Computepsi_et_robocon_T *)&et_robocon_P.Computepsi);

      /* End of InitializeConditions for SubSystem: '<S100>/Compute psi' */

      /* Enable for Function Call SubSystem: '<S100>/Compute psi' */
      et_robocon_Computepsi_Enable(&et_robocon_DW.Computepsi);

      /* End of Enable for SubSystem: '<S100>/Compute psi' */

      /* Outputs for Function Call SubSystem: '<S100>/Compute psi' */

      /* Event: '<S114>:3' */
      et_robocon_Computepsi(et_robocon_M, Sum, &et_robocon_B.Computepsi,
                            &et_robocon_DW.Computepsi,
                            (P_Computepsi_et_robocon_T *)
                            &et_robocon_P.Computepsi);

      /* End of Outputs for SubSystem: '<S100>/Compute psi' */
    } else {
      /* Outputs for Function Call SubSystem: '<S100>/Compute psi' */

      /* Event: '<S114>:3' */
      et_robocon_Computepsi(et_robocon_M, Sum, &et_robocon_B.Computepsi,
                            &et_robocon_DW.Computepsi,
                            (P_Computepsi_et_robocon_T *)
                            &et_robocon_P.Computepsi);

      /* End of Outputs for SubSystem: '<S100>/Compute psi' */
    }
  }

  /* End of Chart: '<S100>/Reset Subsystem' */

  /* S-Function (nxt_encoder): '<S22>/Encoder Left' */
  k = getEncoderValueNoReset(3U);

  /* Gain: '<S102>/Gain1' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion8'
   *  S-Function (nxt_encoder): '<S22>/Encoder Left'
   */
  Gain1_o = et_robocon_P.Gain1_Gain_g * (real32_T)k;

  /* S-Function (nxt_encoder): '<S22>/Encoder Right' */
  k = getEncoderValueNoReset(2U);

  /* Gain: '<S103>/Gain1' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion7'
   *  S-Function (nxt_encoder): '<S22>/Encoder Right'
   */
  Gain1_a = et_robocon_P.Gain1_Gain_c * (real32_T)k;

  /* Chart: '<S101>/Reset Subsystem' incorporates:
   *  Delay: '<Root>/Delay'
   */
  /* Gateway: State Estimation/StateEstimation/Reset Subsystem */
  /* During: State Estimation/StateEstimation/Reset Subsystem */
  if (et_robocon_DW.is_active_c3_et_robocon == 0U) {
    /* Entry: State Estimation/StateEstimation/Reset Subsystem */
    et_robocon_DW.is_active_c3_et_robocon = 1U;

    /* Entry Internal: State Estimation/StateEstimation/Reset Subsystem */
    /* Transition: '<S118>:2' */
    et_robocon_DW.is_c3_et_robocon = et_robocon_IN_CheckForReset;

    /* InitializeConditions for Function Call SubSystem: '<S101>/Process theta1' */

    /* Entry 'CheckForReset': '<S118>:1' */
    et_robocon_Processtheta1_Init(&et_robocon_DW.Processtheta1,
      (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

    /* End of InitializeConditions for SubSystem: '<S101>/Process theta1' */

    /* Enable for Function Call SubSystem: '<S101>/Process theta1' */
    et_robocon_Processtheta1_Enable(&et_robocon_DW.Processtheta1);

    /* End of Enable for SubSystem: '<S101>/Process theta1' */

    /* Outputs for Function Call SubSystem: '<S101>/Process theta1' */

    /* Event: '<S118>:3' */
    et_robocon_Processtheta1(et_robocon_M,
      et_robocon_B.Computepsi.OutportBufferForpsi, Gain1_o, Gain1_a,
      &et_robocon_B.Processtheta1, &et_robocon_DW.Processtheta1,
      (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

    /* End of Outputs for SubSystem: '<S101>/Process theta1' */
  } else {
    /* During 'CheckForReset': '<S118>:1' */
    if (et_robocon_DW.Delay_DSTATE.theta == 1.0F) {
      /* Disable for Function Call SubSystem: '<S101>/Process theta1' */

      /* Transition: '<S118>:4' */
      /* Exit 'CheckForReset': '<S118>:1' */
      et_roboco_Processtheta1_Disable(&et_robocon_B.Processtheta1,
        (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

      /* End of Disable for SubSystem: '<S101>/Process theta1' */
      et_robocon_DW.is_c3_et_robocon = et_robocon_IN_CheckForReset;

      /* InitializeConditions for Function Call SubSystem: '<S101>/Process theta1' */

      /* Entry 'CheckForReset': '<S118>:1' */
      et_robocon_Processtheta1_Init(&et_robocon_DW.Processtheta1,
        (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

      /* End of InitializeConditions for SubSystem: '<S101>/Process theta1' */

      /* Enable for Function Call SubSystem: '<S101>/Process theta1' */
      et_robocon_Processtheta1_Enable(&et_robocon_DW.Processtheta1);

      /* End of Enable for SubSystem: '<S101>/Process theta1' */

      /* Outputs for Function Call SubSystem: '<S101>/Process theta1' */

      /* Event: '<S118>:3' */
      et_robocon_Processtheta1(et_robocon_M,
        et_robocon_B.Computepsi.OutportBufferForpsi, Gain1_o, Gain1_a,
        &et_robocon_B.Processtheta1, &et_robocon_DW.Processtheta1,
        (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

      /* End of Outputs for SubSystem: '<S101>/Process theta1' */
    } else {
      /* Outputs for Function Call SubSystem: '<S101>/Process theta1' */

      /* Event: '<S118>:3' */
      et_robocon_Processtheta1(et_robocon_M,
        et_robocon_B.Computepsi.OutportBufferForpsi, Gain1_o, Gain1_a,
        &et_robocon_B.Processtheta1, &et_robocon_DW.Processtheta1,
        (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

      /* End of Outputs for SubSystem: '<S101>/Process theta1' */
    }
  }

  /* End of Chart: '<S101>/Reset Subsystem' */

  /* BusCreator: '<Root>/BusConversion_InsertedFor_Main Controller_at_inport_0' */
  et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.theta =
    et_robocon_B.Processtheta1.theta;
  et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.psi =
    et_robocon_B.Processtheta1.psi;
  et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.theta_dot =
    et_robocon_B.Processtheta1.Sum3_j;
  et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.psi_dot = Sum;
  et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.int_theta =
    et_robocon_B.Processtheta1.int_theta_f;

  /* BusCreator: '<Root>/BusConversion_InsertedFor_Main Controller_at_inport_0' */
  et_robocon_B.BusConversion_InsertedFor_Mai_g.phi =
    et_robocon_B.Processtheta1.Gain7;
  et_robocon_B.BusConversion_InsertedFor_Mai_g.phi_dot =
    et_robocon_B.Processtheta1.Sum3;
  et_robocon_B.BusConversion_InsertedFor_Mai_g.theta_dot_dot =
    et_robocon_B.Processtheta1.Sum3_c;

  /* S-Function (nxt_encoder): '<S22>/Encoder Tail' */
  k = getEncoderValueNoReset(1U);

  /* Gain: '<S105>/Gain1' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion6'
   *  S-Function (nxt_encoder): '<S22>/Encoder Tail'
   */
  rtb_Gain1_a = et_robocon_P.Gain1_Gain_gi * (real32_T)k;

  /* Outputs for Triggered SubSystem: '<S109>/tail initialization' incorporates:
   *  TriggerPort: '<S111>/Trigger'
   */
  /* Delay: '<Root>/Delay' */
  zcEvent = rt_ZCFcn(RISING_ZERO_CROSSING,
                     &et_robocon_PrevZCX.tailinitialization_Trig_ZCE,
                     (et_robocon_DW.Delay_DSTATE.tail));
  if (zcEvent != NO_ZCEVENT) {
    /* Inport: '<S111>/tail' */
    et_robocon_B.tail = rtb_Gain1_a;
  }

  /* End of Outputs for SubSystem: '<S109>/tail initialization' */

  /* Sum: '<S109>/Sum' */
  et_robocon_B.BusConversion_InsertedFor_MainC.theta_T = rtb_Gain1_a -
    et_robocon_B.tail;

  /* S-Function (nxt_light_sensor): '<S22>/Light Sensor' */
  rtb_touch_h_0 = getLightSensorValue(3U, 2U);

  /* RateTransition: '<S22>/Rate Transition' */
  if (et_robocon_M->Timing.TaskCounters.TID[1] == 0) {
    et_robocon_B.sonar = et_robocon_DW.RateTransition_Buffer0;
  }

  /* End of RateTransition: '<S22>/Rate Transition' */

  /* DataTypeConversion: '<S22>/Data Type Conversion3' */
  et_robocon_B.BusConversion_InsertedFor_MainC.sonar = (real32_T)
    et_robocon_B.sonar;

  /* RateTransition: '<S22>/Rate Transition1' */
  if (et_robocon_M->Timing.TaskCounters.TID[3] == 0) {
    et_robocon_B.RateTransition1 = et_robocon_DW.RateTransition1_Buffer0;
  }

  /* End of RateTransition: '<S22>/Rate Transition1' */

  /* Outputs for Enabled SubSystem: '<S106>/Store Offset' */

  /* Memory: '<S106>/Memory' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion2'
   */
  et_robocon_StoreOffset(et_robocon_DW.Memory_PreviousInput, (real32_T)
    et_robocon_B.RateTransition1, &et_robocon_B.StoreOffset);

  /* End of Outputs for SubSystem: '<S106>/Store Offset' */

  /* DiscreteFilter: '<S106>/Low Pass Filter' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion2'
   *  Sum: '<S106>/Sum2'
   */
  et_robocon_DW.LowPassFilter_tmp = (((real32_T)et_robocon_B.RateTransition1 -
    et_robocon_B.StoreOffset.x) - et_robocon_P.LowPassFilter_DenCoef_e[1] *
    et_robocon_DW.LowPassFilter_states) / et_robocon_P.LowPassFilter_DenCoef_e[0];

  /* Sum: '<S108>/Sum' incorporates:
   *  Constant: '<S108>/Constant'
   *  DiscreteFilter: '<S106>/Low Pass Filter'
   *  Gain: '<S108>/Gain1'
   *  Sum: '<S106>/Sum1'
   */
  et_robocon_B.BusConversion_InsertedFor_MainC.battery =
    (et_robocon_P.LowPassFilter_NumCoef_m * et_robocon_DW.LowPassFilter_tmp +
     et_robocon_B.StoreOffset.x) * et_robocon_P.Gain1_Gain_j -
    et_robocon_P.Constant_Value_ei;

  /* S-Function (nxt_touch_sensor): '<S22>/Touch Sensor' */
  rtb_touch_h_1 = getTouchSensorValue(4U);

  /* S-Function (nxt_timer): '<S22>/Timer' */
  rtb_time_b_0 = getTime();

  /* DataTypeConversion: '<S22>/Data Type Conversion' incorporates:
   *  S-Function (nxt_timer): '<S22>/Timer'
   */
  et_robocon_B.BusConversion_InsertedFor_MainC.time = (real32_T)rtb_time_b_0;

  /* RateTransition: '<S22>/Rate Transition2' */
  if (et_robocon_M->Timing.TaskCounters.TID[2] == 0) {
    et_robocon_B.RateTransition2 = et_robocon_DW.RateTransition2_Buffer0;
  }

  /* End of RateTransition: '<S22>/Rate Transition2' */

  /* DataTypeConversion: '<S22>/Data Type Conversion9' */
  et_robocon_B.BusConversion_InsertedFor_MainC.ok_button =
    et_robocon_B.RateTransition2;

  /* BusCreator: '<Root>/BusConversion_InsertedFor_Main Controller_at_inport_1' incorporates:
   *  Constant: '<S31>/Constant'
   *  DataTypeConversion: '<S22>/Data Type Conversion1'
   *  DataTypeConversion: '<S22>/Data Type Conversion5'
   *  S-Function (nxt_light_sensor): '<S22>/Light Sensor'
   *  S-Function (nxt_touch_sensor): '<S22>/Touch Sensor'
   */
  et_robocon_B.BusConversion_InsertedFor_MainC.theta_L = Gain1_o;
  et_robocon_B.BusConversion_InsertedFor_MainC.theta_R = Gain1_a;
  et_robocon_B.BusConversion_InsertedFor_MainC.light = rtb_touch_h_0;
  et_robocon_B.BusConversion_InsertedFor_MainC.gyro = Gain1;
  et_robocon_B.BusConversion_InsertedFor_MainC.touch = rtb_touch_h_1;
  et_robocon_B.BusConversion_InsertedFor_MainC.BT_status_in =
    et_robocon_P.Constant_Value_b;

  /* Chart: '<Root>/Main Controller' incorporates:
   *  Constant: '<S17>/Constant'
   *  Constant: '<S17>/Constant1'
   *  Saturate: '<S17>/Saturation'
   */
  if (et_robocon_DW.temporalCounter_i1_c < 2047U) {
    et_robocon_DW.temporalCounter_i1_c++;
  }

  if (et_robocon_DW.temporalCounter_i1_n < 511U) {
    et_robocon_DW.temporalCounter_i1_n++;
  }

  if (et_robocon_DW.temporalCounter_i1 < 511U) {
    et_robocon_DW.temporalCounter_i1++;
  }

  /* Gateway: Main Controller */
  /* During: Main Controller */
  if (et_robocon_DW.is_active_c5_et_robocon == 0U) {
    /* Entry: Main Controller */
    et_robocon_DW.is_active_c5_et_robocon = 1U;

    /* Entry Internal: Main Controller */
    /* Transition: '<S2>:48' */
    et_robocon_B.initFlags = Init_Bus0;
    do {
      /* Transition: '<S2>:51' */
      et_robocon_DW.current_mode_index = 0U;

      /* Transition: '<S2>:54' */
      current_mode_status = NOT_STARTED;
      do {
        k = 0;

        /* Transition: '<S2>:57' */
        i = (int32_T)(et_robocon_DW.current_mode_index + 1U);
        if ((uint32_T)i > 255U) {
          i = 255;
        }

        et_robocon_DW.current_mode_index = (uint8_T)i;
        if (3 < et_robocon_DW.current_mode_index) {
          /* Transition: '<S2>:59' */
          /*  If the "current_mode_index" has exceeded the number */
          /*  of elements in the list, it should "wrap" back to the start. */
          /* Transition: '<S2>:50' */
          /* Transition: '<S2>:49' */
          k = 2;
        } else {
          /* Transition: '<S2>:60' */
          /* Transition: '<S2>:61' */
          current_mode =
            rtCP_MainController_TRACK_[et_robocon_DW.current_mode_index - 1];
          if (!(current_mode == SKIP)) {
            k = 1;
          } else {
            /* Transition: '<S2>:64' */
            /* Transition: '<S2>:58' */
            /* Transition: '<S2>:56' */
          }
        }
      } while (k == 0);
    } while (!(k == 1));

    /* Transition: '<S2>:65' */
    et_robocon_DW.is_c5_et_robocon = et_ro_IN_normal_operation_modes;
    enter_internal_normal_operation();
  } else if (et_robocon_DW.is_c5_et_robocon == et_robocon_IN_emergency_stop) {
    /* During 'emergency_stop': '<S2>:97' */
    /* Transition: '<S2>:63' */
    /* Transition: '<S2>:52' */
    do {
      /* Transition: '<S2>:54' */
      current_mode_status = NOT_STARTED;
      do {
        k = 0;

        /* Transition: '<S2>:57' */
        i = (int32_T)(et_robocon_DW.current_mode_index + 1U);
        if ((uint32_T)i > 255U) {
          i = 255;
        }

        et_robocon_DW.current_mode_index = (uint8_T)i;
        if (3 < et_robocon_DW.current_mode_index) {
          /* Transition: '<S2>:59' */
          /*  If the "current_mode_index" has exceeded the number */
          /*  of elements in the list, it should "wrap" back to the start. */
          /* Transition: '<S2>:50' */
          /* Transition: '<S2>:49' */
          /* Transition: '<S2>:51' */
          et_robocon_DW.current_mode_index = 0U;
          k = 2;
        } else {
          /* Transition: '<S2>:60' */
          /* Transition: '<S2>:61' */
          current_mode =
            rtCP_MainController_TRACK_[et_robocon_DW.current_mode_index - 1];
          if (!(current_mode == SKIP)) {
            k = 1;
          } else {
            /* Transition: '<S2>:64' */
            /* Transition: '<S2>:58' */
            /* Transition: '<S2>:56' */
          }
        }
      } while (k == 0);
    } while (!(k == 1));

    /* Transition: '<S2>:65' */
    et_robocon_DW.is_c5_et_robocon = et_ro_IN_normal_operation_modes;
    enter_internal_normal_operation();
  } else {
    /* During 'normal_operation_modes': '<S2>:9' */
    if (et_robocon_B.BusConversion_InsertedFor_MainC.ok_button != 0.0F) {
      /* Transition: '<S2>:66' */
      current_mode_status = ABORTED;

      /* Exit Internal 'normal_operation_modes': '<S2>:9' */
      switch (et_robocon_DW.is_normal_operation_modes) {
       case et_r_IN_gyro_calibration_mode_l:
        /* Exit Internal: gyro_calibration_mode */
        /* Exit Internal 'gyro_calibration_mode': '<S9>:1' */
        if (et_robocon_DW.is_gyro_calibration_mode ==
            et_robocon_IN_GyroCalibration) {
          /* Exit Internal 'GyroCalibration': '<S9>:21' */
          et_robocon_DW.is_GyroCalibration = et_robocon_IN_NO_ACTIVE_CHILD;

          /* Exit 'GyroCalibration': '<S9>:21' */
          tail_controller(et_robocon_B.BusConversion_InsertedFor_MainC.theta_T,
                          et_robocon_DW.desired_tail_c, &et_robocon_B.PWM.tail);
          et_robocon_DW.is_gyro_calibration_mode = et_robocon_IN_NO_ACTIVE_CHILD;
        } else {
          et_robocon_DW.is_gyro_calibration_mode = et_robocon_IN_NO_ACTIVE_CHILD;
        }

        et_robocon_DW.is_c2_gyro_calibration_algorith =
          et_robocon_IN_NO_ACTIVE_CHILD;
        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
        break;

       case et_robo_IN_light_calibration_up:
        /* Exit Internal: light_calibration_up */
        if (et_robocon_DW.is_c4_light_sensor_calibration_ == et_robocon_IN_Reset)
        {
          /* Exit 'Reset': '<S10>:33' */
          et_robocon_B.initFlags.tail = 0.0F;
          et_robocon_DW.is_c4_light_sensor_calibration_ =
            et_robocon_IN_NO_ACTIVE_CHILD;
        } else {
          et_robocon_DW.is_c4_light_sensor_calibration_ =
            et_robocon_IN_NO_ACTIVE_CHILD;

          /* Exit Internal 'light_sensor_calibration_up': '<S10>:1' */
          et_robocon_DW.is_light_sensor_calibration_up =
            et_robocon_IN_NO_ACTIVE_CHILD;
        }

        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
        break;

       case et_robocon_IN_line_following:
        /* Exit Internal: Main Controller/normal_operation_modes.line_following */
        /* Exit Internal 'see_saw_mode': '<S11>:96' */
        /* Exit Internal 'Balancing': '<S11>:108' */
        et_robocon_DW.is_active_After = 0U;

        /* Exit Internal 'SeesawLogic': '<S11>:100' */
        et_robocon_DW.is_SeesawLogic = et_robocon_IN_NO_ACTIVE_CHILD;
        et_robocon_DW.is_active_SeesawLogic = 0U;
        et_robocon_DW.is_see_saw_mode = et_robocon_IN_NO_ACTIVE_CHILD;

        /* Exit 'see_saw_mode': '<S11>:96' */
        et_robocon_DW.is_c6_et_robocon = et_robocon_IN_NO_ACTIVE_CHILD;
        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
        break;

       default:
        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
        break;
      }

      et_robocon_DW.is_c5_et_robocon = et_robocon_IN_emergency_stop;

      /* Entry 'emergency_stop': '<S2>:97' */
      StatusLCD(9999U);
    } else if (current_mode_status == SUCCESSFULLY_COMPLETED) {
      /* Transition: '<S2>:55' */
      /* Transition: '<S2>:52' */
      do {
        /* Transition: '<S2>:54' */
        current_mode_status = NOT_STARTED;
        do {
          k = 0;

          /* Transition: '<S2>:57' */
          i = (int32_T)(et_robocon_DW.current_mode_index + 1U);
          if ((uint32_T)i > 255U) {
            i = 255;
          }

          et_robocon_DW.current_mode_index = (uint8_T)i;
          if (3 < et_robocon_DW.current_mode_index) {
            /* Transition: '<S2>:59' */
            /*  If the "current_mode_index" has exceeded the number */
            /*  of elements in the list, it should "wrap" back to the start. */
            /* Transition: '<S2>:50' */
            /* Transition: '<S2>:49' */
            /* Transition: '<S2>:51' */
            et_robocon_DW.current_mode_index = 0U;
            k = 2;
          } else {
            /* Transition: '<S2>:60' */
            /* Transition: '<S2>:61' */
            current_mode =
              rtCP_MainController_TRACK_[et_robocon_DW.current_mode_index - 1];
            if (!(current_mode == SKIP)) {
              k = 1;
            } else {
              /* Transition: '<S2>:64' */
              /* Transition: '<S2>:58' */
              /* Transition: '<S2>:56' */
            }
          }
        } while (k == 0);
      } while (!(k == 1));

      /* Transition: '<S2>:65' */
      /* Exit Internal 'normal_operation_modes': '<S2>:9' */
      switch (et_robocon_DW.is_normal_operation_modes) {
       case et_r_IN_gyro_calibration_mode_l:
        /* Exit Internal: gyro_calibration_mode */
        /* Exit Internal 'gyro_calibration_mode': '<S9>:1' */
        if (et_robocon_DW.is_gyro_calibration_mode ==
            et_robocon_IN_GyroCalibration) {
          /* Exit Internal 'GyroCalibration': '<S9>:21' */
          et_robocon_DW.is_GyroCalibration = et_robocon_IN_NO_ACTIVE_CHILD;

          /* Exit 'GyroCalibration': '<S9>:21' */
          tail_controller(et_robocon_B.BusConversion_InsertedFor_MainC.theta_T,
                          et_robocon_DW.desired_tail_c, &et_robocon_B.PWM.tail);
          et_robocon_DW.is_gyro_calibration_mode = et_robocon_IN_NO_ACTIVE_CHILD;
        } else {
          et_robocon_DW.is_gyro_calibration_mode = et_robocon_IN_NO_ACTIVE_CHILD;
        }

        et_robocon_DW.is_c2_gyro_calibration_algorith =
          et_robocon_IN_NO_ACTIVE_CHILD;
        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
        break;

       case et_robo_IN_light_calibration_up:
        /* Exit Internal: light_calibration_up */
        if (et_robocon_DW.is_c4_light_sensor_calibration_ == et_robocon_IN_Reset)
        {
          /* Exit 'Reset': '<S10>:33' */
          et_robocon_B.initFlags.tail = 0.0F;
          et_robocon_DW.is_c4_light_sensor_calibration_ =
            et_robocon_IN_NO_ACTIVE_CHILD;
        } else {
          et_robocon_DW.is_c4_light_sensor_calibration_ =
            et_robocon_IN_NO_ACTIVE_CHILD;

          /* Exit Internal 'light_sensor_calibration_up': '<S10>:1' */
          et_robocon_DW.is_light_sensor_calibration_up =
            et_robocon_IN_NO_ACTIVE_CHILD;
        }

        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
        break;

       case et_robocon_IN_line_following:
        /* Exit Internal: Main Controller/normal_operation_modes.line_following */
        /* Exit Internal 'see_saw_mode': '<S11>:96' */
        /* Exit Internal 'Balancing': '<S11>:108' */
        et_robocon_DW.is_active_After = 0U;

        /* Exit Internal 'SeesawLogic': '<S11>:100' */
        et_robocon_DW.is_SeesawLogic = et_robocon_IN_NO_ACTIVE_CHILD;
        et_robocon_DW.is_active_SeesawLogic = 0U;
        et_robocon_DW.is_see_saw_mode = et_robocon_IN_NO_ACTIVE_CHILD;

        /* Exit 'see_saw_mode': '<S11>:96' */
        et_robocon_DW.is_c6_et_robocon = et_robocon_IN_NO_ACTIVE_CHILD;
        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
        break;

       default:
        et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
        break;
      }

      et_robocon_DW.is_c5_et_robocon = et_ro_IN_normal_operation_modes;
      enter_internal_normal_operation();
    } else {
      switch (et_robocon_DW.is_normal_operation_modes) {
       case et_robocon_IN_WeShouldNotBeHere:
        /* During 'WeShouldNotBeHere': '<S2>:98' */
        break;

       case et_r_IN_gyro_calibration_mode_l:
        /* During 'gyro_calibration_mode': '<S2>:179' */
        /* During: gyro_calibration_mode */
        et_robocon_DW.isStable_k = true;

        /* During 'gyro_calibration_mode': '<S9>:1' */
        if (et_robocon_DW.is_gyro_calibration_mode ==
            et_robocon_IN_GyroCalibration) {
          /* During 'GyroCalibration': '<S9>:21' */
          tail_controller(et_robocon_B.BusConversion_InsertedFor_MainC.theta_T,
                          et_robocon_DW.desired_tail_c, &et_robocon_B.PWM.tail);
          switch (et_robocon_DW.is_GyroCalibration) {
           case et_robocon_IN_CalibComplete:
            /* During 'CalibComplete': '<S9>:29' */
            break;

           case et_robocon_IN_MakeNoise:
            /* During 'MakeNoise': '<S9>:26' */
            if (et_robocon_DW.temporalCounter_i1_c >= 125U) {
              /* Transition: '<S9>:28' */
              et_robocon_DW.isStable_k = false;
              et_robocon_DW.is_GyroCalibration = et_robocon_IN_StartCalibration1;

              /* Entry 'StartCalibration1': '<S9>:27' */
              StatusLCD(102U);
              et_robocon_B.initFlags.gyroInit = 0.0F;
              et_robocon_B.initFlags.gyroReset = 0.0F;
              et_robocon_B.initFlags.theta = 0.0F;
            } else {
              Speak();
            }
            break;

           case et_robocon_IN_MoveTailDown:
            /* During 'MoveTailDown': '<S9>:18' */
            if (et_robocon_DW.desired_tail_c >= 1.75F) {
              /* Transition: '<S9>:20' */
              et_robocon_DW.isStable_k = false;
              et_robocon_DW.is_GyroCalibration = et_roboco_IN_StartCalibration_l;

              /* Entry 'StartCalibration': '<S9>:19' */
              StatusLCD(101U);
              et_robocon_B.initFlags.gyroInit = 1.0F;
              et_robocon_B.initFlags.gyroReset = 1.0F;
              et_robocon_B.initFlags.theta = 1.0F;
            } else {
              et_robocon_DW.desired_tail_c += 0.008F;
            }
            break;

           case et_roboco_IN_StartCalibration_l:
            /* During 'StartCalibration': '<S9>:19' */
            if (et_robocon_B.BusConversion_InsertedFor_MainC.touch != 0.0F) {
              /* Transition: '<S9>:25' */
              Speak();
              et_robocon_DW.isStable_k = false;
              et_robocon_DW.is_GyroCalibration = et_robocon_IN_Wait;
              et_robocon_DW.temporalCounter_i1_c = 0U;

              /* Entry 'Wait': '<S9>:23' */
              Speak();
            }
            break;

           case et_robocon_IN_StartCalibration1:
            /* During 'StartCalibration1': '<S9>:27' */
            /* Transition: '<S9>:30' */
            et_robocon_DW.isStable_k = false;
            et_robocon_DW.is_GyroCalibration = et_robocon_IN_CalibComplete;

            /* Entry 'CalibComplete': '<S9>:29' */
            StatusLCD(103U);
            current_mode_status = SUCCESSFULLY_COMPLETED;
            break;

           case et_robocon_IN_Wait:
            /* During 'Wait': '<S9>:23' */
            if (et_robocon_DW.temporalCounter_i1_c >= 1250U) {
              /* Transition: '<S9>:24' */
              et_robocon_DW.isStable_k = false;
              et_robocon_DW.is_GyroCalibration = et_robocon_IN_MakeNoise;
              et_robocon_DW.temporalCounter_i1_c = 0U;
            }
            break;

           default:
            /* During 'Waiting': '<S9>:38' */
            if (et_robocon_DW.temporalCounter_i1_c >= 250U) {
              /* Transition: '<S9>:39' */
              et_robocon_DW.isStable_k = false;
              et_robocon_DW.is_GyroCalibration = et_roboco_IN_StartCalibration_l;

              /* Entry 'StartCalibration': '<S9>:19' */
              StatusLCD(101U);
              et_robocon_B.initFlags.gyroInit = 1.0F;
              et_robocon_B.initFlags.gyroReset = 1.0F;
              et_robocon_B.initFlags.theta = 1.0F;
            }
            break;
          }
        } else {
          /* During 'StartCalibration': '<S9>:41' */
          if (et_robocon_B.BusConversion_InsertedFor_MainC.touch != 0.0F) {
            /* Transition: '<S9>:42' */
            et_robocon_DW.is_gyro_calibration_mode =
              et_robocon_IN_GyroCalibration;

            /* Entry 'GyroCalibration': '<S9>:21' */
            et_robocon_DW.desired_tail_c = 0.0F;

            /* Entry Internal 'GyroCalibration': '<S9>:21' */
            /* Transition: '<S9>:50' */
            et_robocon_DW.isStable_k = false;
            et_robocon_DW.is_GyroCalibration = et_robocon_IN_MoveTailDown;

            /* Entry 'MoveTailDown': '<S9>:18' */
            StatusLCD(100U);
          }
        }
        break;

       case et_robo_IN_light_calibration_up:
        /* During 'light_calibration_up': '<S2>:180' */
        /* During: light_calibration_up */
        et_robocon_DW.isStable_m = true;
        switch (et_robocon_DW.is_c4_light_sensor_calibration_) {
         case et_robocon_IN_MoveUp:
          /* During 'MoveUp': '<S10>:35' */
          if (et_robocon_DW.temporalCounter_i1_n >= 500U) {
            /* Transition: '<S10>:31' */
            et_robocon_DW.isStable_m = false;
            et_robocon_DW.is_c4_light_sensor_calibration_ = et_robocon_IN_Reset;
            et_robocon_DW.temporalCounter_i1_n = 0U;

            /* Entry 'Reset': '<S10>:33' */
            StatusLCD(202U);
            et_robocon_B.PWM.tail = 0.0F;
            et_robocon_B.initFlags.tail = 1.0F;
          }
          break;

         case et_robocon_IN_Reset:
          /* During 'Reset': '<S10>:33' */
          if (et_robocon_DW.temporalCounter_i1_n >= 250U) {
            /* Transition: '<S10>:37' */
            Speak();

            /* Exit 'Reset': '<S10>:33' */
            et_robocon_B.initFlags.tail = 0.0F;
            et_robocon_DW.is_c4_light_sensor_calibration_ =
              IN_light_sensor_calibration_up;

            /* Entry 'light_sensor_calibration_up': '<S10>:1' */
            /* during, exit: PWM.tail = tail_controller(sensors.theta_T,single(1.6)) */
            /* Entry Internal 'light_sensor_calibration_up': '<S10>:1' */
            /* Transition: '<S10>:5' */
            et_robocon_DW.isStable_m = false;
            et_robocon_DW.is_light_sensor_calibration_up =
              et_robocon_IN_WaitForBlack;

            /* Entry 'WaitForBlack': '<S10>:6' */
            StatusLCD(203U);
          }
          break;

         case IN_light_sensor_calibration_up:
          /* During 'light_sensor_calibration_up': '<S10>:1' */
          switch (et_robocon_DW.is_light_sensor_calibration_up) {
           case et_robocon_IN_CalibComplete:
            /* During 'CalibComplete': '<S10>:4' */
            break;

           case et_robocon_IN_StoreBlack:
            /* During 'StoreBlack': '<S10>:21' */
            if (et_robocon_DW.temporalCounter_i1_n >= 50U) {
              /* Transition: '<S10>:19' */
              Speak();
              et_robocon_DW.isStable_m = false;
              et_robocon_DW.is_light_sensor_calibration_up =
                et_robocon_IN_WaitForWhite;

              /* Entry 'WaitForWhite': '<S10>:22' */
              StatusLCD(205U);
            }
            break;

           case et_robocon_IN_StoreWhite:
            /* During 'StoreWhite': '<S10>:20' */
            if (et_robocon_DW.temporalCounter_i1_n >= 50U) {
              /* Transition: '<S10>:24' */
              Speak();
              et_robocon_DW.isStable_m = false;
              et_robocon_DW.is_light_sensor_calibration_up =
                et_robocon_IN_CalibComplete;

              /* Entry 'CalibComplete': '<S10>:4' */
              StatusLCD(207U);
              current_mode_status = SUCCESSFULLY_COMPLETED;
            }
            break;

           case et_robocon_IN_WaitForBlack:
            /* During 'WaitForBlack': '<S10>:6' */
            if (et_robocon_B.BusConversion_InsertedFor_MainC.touch != 0.0F) {
              /* Transition: '<S10>:11' */
              Speak();
              et_robocon_DW.isStable_m = false;
              et_robocon_DW.is_light_sensor_calibration_up =
                et_robocon_IN_StoreBlack;
              et_robocon_DW.temporalCounter_i1_n = 0U;

              /* Entry 'StoreBlack': '<S10>:21' */
              lightCalib.black =
                et_robocon_B.BusConversion_InsertedFor_MainC.light;
              StatusLCD(204U);
            }
            break;

           default:
            /* During 'WaitForWhite': '<S10>:22' */
            if (et_robocon_B.BusConversion_InsertedFor_MainC.touch != 0.0F) {
              /* Transition: '<S10>:18' */
              Speak();
              et_robocon_DW.isStable_m = false;
              et_robocon_DW.is_light_sensor_calibration_up =
                et_robocon_IN_StoreWhite;
              et_robocon_DW.temporalCounter_i1_n = 0U;

              /* Entry 'StoreWhite': '<S10>:20' */
              lightCalib.white =
                et_robocon_B.BusConversion_InsertedFor_MainC.light;
              StatusLCD(206U);
            }
            break;
          }
          break;

         default:
          /* During 'wait': '<S10>:32' */
          if (et_robocon_B.BusConversion_InsertedFor_MainC.touch != 0.0F) {
            /* Transition: '<S10>:36' */
            Speak();
            et_robocon_DW.isStable_m = false;
            et_robocon_DW.is_c4_light_sensor_calibration_ = et_robocon_IN_MoveUp;
            et_robocon_DW.temporalCounter_i1_n = 0U;

            /* Entry 'MoveUp': '<S10>:35' */
            StatusLCD(201U);
            et_robocon_B.PWM.tail = -50.0F;
          }
          break;
        }
        break;

       default:
        /* During 'line_following': '<S2>:181' */
        /* During: Main Controller/normal_operation_modes.line_following */
        et_robocon_DW.isStable = true;

        /* Outputs for Function Call SubSystem: '<S11>/see_saw_mode.processLight' */
        /* Sum: '<S19>/Sum2' incorporates:
         *  Gain: '<S19>/Gain'
         *  Sum: '<S19>/Sum'
         *  Sum: '<S19>/Sum1'
         */
        /* During 'see_saw_mode': '<S11>:96' */
        /* Simulink Function 'processLight': '<S11>:46' */
        Sum = et_robocon_B.BusConversion_InsertedFor_MainC.light -
          ((lightCalib.black - lightCalib.white) * et_robocon_P.Gain_Gain_d +
           lightCalib.white);

        /* DataTypeConversion: '<S21>/Data Type Conversion' */
        Gain1_o = (real32_T)floor(Sum);
        if (rtIsNaNF(Gain1_o) || rtIsInfF(Gain1_o)) {
          Gain1_o = 0.0F;
        } else {
          Gain1_o = (real32_T)fmod(Gain1_o, 4.2949673E+9F);
        }

        /* S-Function (nxt_lcd): '<S21>/LCD' incorporates:
         *  DataTypeConversion: '<S21>/Data Type Conversion'
         */
        lcdDisplay(Gain1_o < 0.0F ? -(int32_T)(uint32_T)-Gain1_o : (int32_T)
                   (uint32_T)Gain1_o, rtCP_LCD_p1, 5U, 1U);

        /* Gain: '<S19>/Gain1' */
        Sum *= et_robocon_P.Gain1_Gain;

        /* End of Outputs for SubSystem: '<S11>/see_saw_mode.processLight' */
        tail_controller(et_robocon_B.BusConversion_InsertedFor_MainC.theta_T,
                        et_robocon_DW.desired_tail, &et_robocon_B.PWM.tail);
        switch (et_robocon_DW.is_see_saw_mode) {
         case et_robocon_IN_Balancing:
          /* During 'Balancing': '<S11>:108' */
          /* During 'SeesawLogic': '<S11>:100' */
          switch (et_robocon_DW.is_SeesawLogic) {
           case et_robocon_IN_ApproachtoRamp_1:
            /* During 'ApproachtoRamp_1': '<S11>:209' */
            /* Simulink Function 'lineTracker': '<S11>:52' */
            et_robocon_B.VectorConcatenate_h[0] = -0.1F;

            /* Outputs for Function Call SubSystem: '<S11>/see_saw_mode.lineTracker' */
            et_robo_see_saw_modelineTracker(Sum, 1.0F, (real_T)
              et_robocon_B.BusConversion_InsertedFor_MainC.battery,
              et_robocon_B.VectorConcatenate_h,
              &et_robocon_B.see_saw_modelineTracker,
              &et_robocon_DW.see_saw_modelineTracker,
              (P_see_saw_modelineTracker_et__T *)
              &et_robocon_P.see_saw_modelineTracker);

            /* End of Outputs for SubSystem: '<S11>/see_saw_mode.lineTracker' */
            phiController(et_robocon_DW.desired_phi,
                          et_robocon_B.BusConversion_InsertedFor_Mai_g.phi,
                          et_robocon_B.BusConversion_InsertedFor_MainC.battery,
                          &Sum);
            et_robocon_DW.turningPWM =
              et_robocon_B.see_saw_modelineTracker.switchsideofline + Sum;
            break;

           case et_robocon_IN_ConstantSpeed:
            /* During 'ConstantSpeed': '<S11>:217' */
            if ((et_robocon_B.BusConversion_InsertedFor_MainC.touch != 0.0F) ||
                (et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.theta_dot
                 < 1.0F)) {
              /* Transition: '<S11>:219' */
              et_robocon_DW.isStable = false;
              et_robocon_DW.is_SeesawLogic = et_robocon_IN_ApproachtoRamp_1;

              /* Entry 'ApproachtoRamp_1': '<S11>:209' */
              et_robocon_DW.desired_phi =
                et_robocon_B.BusConversion_InsertedFor_Mai_g.phi;
              Speak();
              StatusLCD(304U);
              et_robocon_DW.des_vel = 0.1F;
            } else {
              /* Simulink Function 'lineTracker': '<S11>:52' */
              et_robocon_B.VectorConcatenate_h[0] = -0.1F;

              /* Outputs for Function Call SubSystem: '<S11>/see_saw_mode.lineTracker' */
              et_robo_see_saw_modelineTracker(Sum, 1.3F, (real_T)
                et_robocon_B.BusConversion_InsertedFor_MainC.battery,
                et_robocon_B.VectorConcatenate_h,
                &et_robocon_B.see_saw_modelineTracker,
                &et_robocon_DW.see_saw_modelineTracker,
                (P_see_saw_modelineTracker_et__T *)
                &et_robocon_P.see_saw_modelineTracker);

              /* End of Outputs for SubSystem: '<S11>/see_saw_mode.lineTracker' */
              et_robocon_DW.turningPWM =
                et_robocon_B.see_saw_modelineTracker.switchsideofline;
            }
            break;

           case et_robocon_IN_MoveForwardSlowly:
            /* During 'MoveForwardSlowly': '<S11>:107' */
            if (et_robocon_DW.temporalCounter_i1 >= 50U) {
              /* Transition: '<S11>:213' */
              et_robocon_DW.isStable = false;
              et_robocon_DW.is_SeesawLogic = et_roboco_IN_StationnaryBalance;
              et_robocon_DW.temporalCounter_i1 = 0U;

              /* Entry 'StationnaryBalance': '<S11>:200' */
              Speak();
              StatusLCD(303U);

              /* StatusLCD(uint16(single(0.15))); */
              et_robocon_DW.des_vel = 0.001F;
            }
            break;

           case et_robocon_IN_SpeedUp:
            /* During 'SpeedUp': '<S11>:211' */
            if (et_robocon_DW.des_vel >= 0.2) {
              /* Transition: '<S11>:218' */
              et_robocon_DW.isStable = false;
              et_robocon_DW.is_SeesawLogic = et_robocon_IN_ConstantSpeed;

              /* Entry 'ConstantSpeed': '<S11>:217' */
              Speak();
              StatusLCD(305U);
            } else {
              et_robocon_DW.des_vel += 0.0005F;

              /* Simulink Function 'lineTracker': '<S11>:52' */
              et_robocon_B.VectorConcatenate_h[0] = -0.1F;

              /* Outputs for Function Call SubSystem: '<S11>/see_saw_mode.lineTracker' */
              et_robo_see_saw_modelineTracker(Sum, 1.3F, (real_T)
                et_robocon_B.BusConversion_InsertedFor_MainC.battery,
                et_robocon_B.VectorConcatenate_h,
                &et_robocon_B.see_saw_modelineTracker,
                &et_robocon_DW.see_saw_modelineTracker,
                (P_see_saw_modelineTracker_et__T *)
                &et_robocon_P.see_saw_modelineTracker);

              /* End of Outputs for SubSystem: '<S11>/see_saw_mode.lineTracker' */
              et_robocon_DW.turningPWM =
                et_robocon_B.see_saw_modelineTracker.switchsideofline;
            }
            break;

           default:
            /* During 'StationnaryBalance': '<S11>:200' */
            if (et_robocon_DW.temporalCounter_i1 >= 375U) {
              /* Transition: '<S11>:214' */
              et_robocon_DW.isStable = false;
              et_robocon_DW.is_SeesawLogic = et_robocon_IN_SpeedUp;

              /* Entry 'SpeedUp': '<S11>:211' */
              Speak();
              StatusLCD(304U);
              et_robocon_DW.des_vel = 0.001F;
            } else {
              /* Simulink Function 'lineTracker': '<S11>:52' */
              et_robocon_B.VectorConcatenate_h[0] = -0.1F;

              /* Outputs for Function Call SubSystem: '<S11>/see_saw_mode.lineTracker' */
              et_robo_see_saw_modelineTracker(Sum, 1.3F, (real_T)
                et_robocon_B.BusConversion_InsertedFor_MainC.battery,
                et_robocon_B.VectorConcatenate_h,
                &et_robocon_B.see_saw_modelineTracker,
                &et_robocon_DW.see_saw_modelineTracker,
                (P_see_saw_modelineTracker_et__T *)
                &et_robocon_P.see_saw_modelineTracker);

              /* End of Outputs for SubSystem: '<S11>/see_saw_mode.lineTracker' */
              et_robocon_DW.turningPWM =
                et_robocon_B.see_saw_modelineTracker.switchsideofline;
            }
            break;
          }

          /* Outputs for Function Call SubSystem: '<S11>/see_saw_mode.balance_ctrl' */
          /* During 'After': '<S11>:41' */
          /* Simulink Function 'balance_ctrl': '<S11>:106' */
          if (et_robocon_DW.see_saw_modebalance_ctrl_RESET_) {
            et_robocon_DW.see_saw_modebalance_ctrl_ELAPS_ = 0U;
          } else {
            et_robocon_DW.see_saw_modebalance_ctrl_ELAPS_ =
              et_robocon_M->Timing.clockTick0 -
              et_robocon_DW.see_saw_modebalance_ctrl_PREV_T;
          }

          et_robocon_DW.see_saw_modebalance_ctrl_PREV_T =
            et_robocon_M->Timing.clockTick0;
          et_robocon_DW.see_saw_modebalance_ctrl_RESET_ = false;

          /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
          if (et_robocon_DW.DiscreteTimeIntegrator_SYSTEM_E != 0) {
            rtb_Gain1_a = et_robocon_DW.DiscreteTimeIntegrator_DSTATE;
          } else {
            rtb_Gain1_a = et_robocon_P.DiscreteTimeIntegrator_gainval *
              (real32_T)et_robocon_DW.see_saw_modebalance_ctrl_ELAPS_ *
              et_robocon_DW.DiscreteTimeIntegrator_PREV_U +
              et_robocon_DW.DiscreteTimeIntegrator_DSTATE;
          }

          /* End of DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */

          /* SignalConversion: '<S17>/ConcatBufferAtVector ConcatenateIn1' */
          VectorConcatenate[0] = rtb_Gain1_a;

          /* DiscreteFilter: '<S17>/LPF' incorporates:
           *  Gain: '<S17>/m//s --> rad//s'
           */
          Gain1 = (et_robocon_P.msrads_Gain * et_robocon_DW.des_vel -
                   et_robocon_P.LPF_DenCoef[1] * et_robocon_DW.LPF_states) /
            et_robocon_P.LPF_DenCoef[0];
          Sum = et_robocon_P.LPF_NumCoef * Gain1;

          /* SignalConversion: '<S17>/ConcatBufferAtVector ConcatenateIn3' */
          VectorConcatenate[2] = Sum;
          VectorConcatenate[1] = et_robocon_P.Constant_Value_e;
          VectorConcatenate[3] = et_robocon_P.Constant1_Value;

          /* DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' incorporates:
           *  Constant: '<S17>/Constant'
           *  Constant: '<S17>/Constant1'
           */
          if (et_robocon_DW.DiscreteTimeIntegrator1_SYSTEM_ != 0) {
            VectorConcatenate[4] = et_robocon_DW.DiscreteTimeIntegrator1_DSTATE;
          } else {
            VectorConcatenate[4] = et_robocon_P.DiscreteTimeIntegrator1_gainval *
              (real32_T)et_robocon_DW.see_saw_modebalance_ctrl_ELAPS_ *
              et_robocon_DW.DiscreteTimeIntegrator1_PREV_U +
              et_robocon_DW.DiscreteTimeIntegrator1_DSTATE;
          }

          /* End of DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */

          /* Sum: '<S17>/Sum1' */
          tmp[0] =
            et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.theta;
          tmp[1] =
            et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.psi;
          tmp[2] =
            et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.theta_dot;
          tmp[3] =
            et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.psi_dot;
          tmp[4] =
            et_robocon_B.BusConversion_InsertedFor_Mai_g.balancerStates.int_theta;

          /* Gain: '<S17>/Gain1' incorporates:
           *  Sum: '<S17>/Sum1'
           */
          Gain1_o = 0.0F;
          for (i = 0; i < 5; i++) {
            Gain1_o += (VectorConcatenate[i] - tmp[i]) * et_robocon_P.K[i];
          }

          /* Gain: '<S17>/Gain' incorporates:
           *  Gain: '<S17>/Gain1'
           *  Product: '<S17>/Divide'
           */
          u0 = (real_T)Gain1_o /
            et_robocon_B.BusConversion_InsertedFor_MainC.battery *
            et_robocon_P.Gain_Gain;

          /* Saturate: '<S17>/Saturation' */
          if (u0 > et_robocon_P.Saturation_UpperSat) {
            u0 = et_robocon_P.Saturation_UpperSat;
          } else {
            if (u0 < et_robocon_P.Saturation_LowerSat) {
              u0 = et_robocon_P.Saturation_LowerSat;
            }
          }

          /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
          et_robocon_DW.DiscreteTimeIntegrator_SYSTEM_E = 0U;
          et_robocon_DW.DiscreteTimeIntegrator_DSTATE = rtb_Gain1_a;
          et_robocon_DW.DiscreteTimeIntegrator_PREV_U = Sum;

          /* Update for DiscreteFilter: '<S17>/LPF' */
          et_robocon_DW.LPF_states = Gain1;

          /* Update for DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */
          et_robocon_DW.DiscreteTimeIntegrator1_SYSTEM_ = 0U;
          et_robocon_DW.DiscreteTimeIntegrator1_DSTATE = VectorConcatenate[4];
          et_robocon_DW.DiscreteTimeIntegrator1_PREV_U = rtb_Gain1_a;
          et_robocon_B.PWM.left = (real32_T)u0 + et_robocon_DW.turningPWM;
          et_robocon_B.PWM.right = (real32_T)u0 - et_robocon_DW.turningPWM;

          /* End of Outputs for SubSystem: '<S11>/see_saw_mode.balance_ctrl' */
          break;

         case et_robocon_IN_StandUp:
          /* During 'StandUp': '<S11>:53' */
          /* Transition: '<S11>:109' */
          et_robocon_DW.is_see_saw_mode = et_robocon_IN_Balancing;

          /* Entry Internal 'Balancing': '<S11>:108' */
          et_robocon_DW.is_active_SeesawLogic = 1U;

          /* Entry Internal 'SeesawLogic': '<S11>:100' */
          /* Transition: '<S11>:99' */
          et_robocon_DW.isStable = false;
          et_robocon_DW.is_SeesawLogic = et_robocon_IN_MoveForwardSlowly;
          et_robocon_DW.temporalCounter_i1 = 0U;

          /* Entry 'MoveForwardSlowly': '<S11>:107' */
          StatusLCD(302U);
          et_robocon_B.initFlags.theta = 0.0F;
          et_robocon_B.initFlags.gyroReset = 0.0F;

          /* desired_states = balancerStates_Bus0; */
          et_robocon_DW.turningPWM = 0.0F;
          et_robocon_DW.isStable = false;
          et_robocon_DW.is_active_After = 1U;
          break;

         default:
          /* During 'Waiting': '<S11>:207' */
          if (et_robocon_B.BusConversion_InsertedFor_MainC.touch != 0.0F) {
            /* Transition: '<S11>:208' */
            et_robocon_DW.isStable = false;
            et_robocon_DW.is_see_saw_mode = et_robocon_IN_StandUp;

            /* Entry 'StandUp': '<S11>:53' */
            StatusLCD(301U);
            et_robocon_B.initFlags.theta = 1.0F;
            et_robocon_B.initFlags.gyroReset = 1.0F;
          } else {
            StatusLCD(300U);
          }
          break;
        }
        break;
      }
    }
  }

  /* End of Chart: '<Root>/Main Controller' */

  /* S-Function (nxt_lcd): '<S24>/LCD' incorporates:
   *  DataTypeConversion: '<S24>/Data Type Conversion'
   */
  lcdDisplay(et_robocon_B.RateTransition1, rtCP_LCD_p1_i, 3U, 1U);

  /* DataTypeConversion: '<S25>/Data Type Conversion' incorporates:
   *  Constant: '<S31>/Constant'
   */
  Gain1_o = (real32_T)floor(et_robocon_P.Constant_Value_b);
  if (rtIsNaNF(Gain1_o) || rtIsInfF(Gain1_o)) {
    Gain1_o = 0.0F;
  } else {
    Gain1_o = (real32_T)fmod(Gain1_o, 4.2949673E+9F);
  }

  /* S-Function (nxt_lcd): '<S25>/LCD' incorporates:
   *  DataTypeConversion: '<S25>/Data Type Conversion'
   */
  lcdDisplay(Gain1_o < 0.0F ? -(int32_T)(uint32_T)-Gain1_o : (int32_T)(uint32_T)
             Gain1_o, rtCP_LCD_p1_c, 2U, 1U);
  if (et_robocon_M->Timing.TaskCounters.TID[3] == 0) {
    /* S-Function (nxt_battery): '<S22>/Battery' */
    et_robocon_B.battery_n = getBattery();
  }

  if (et_robocon_M->Timing.TaskCounters.TID[2] == 0) {
    /* S-Function (nxt_button): '<S22>/Button' */
    et_robocon_B.Button = pressButton(1U);
  }

  if (et_robocon_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (nxt_ultrasonic_sensor): '<S22>/Ultrasonic Sensor' */
    et_robocon_B.sonar_h = getUltrasonicSensorValue(2U);
  }

  /* DataTypeConversion: '<S22>/Data Type Conversion10' */
  Gain1_o = (real32_T)floor(et_robocon_B.PWM.left);
  if (Gain1_o < 128.0F) {
    if (Gain1_o >= -128.0F) {
      rtb_DataTypeConversion12_0 = (int8_T)Gain1_o;
    } else {
      rtb_DataTypeConversion12_0 = MIN_int8_T;
    }
  } else {
    rtb_DataTypeConversion12_0 = MAX_int8_T;
  }

  /* S-Function (nxt_motor): '<S26>/Motor' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion10'
   */
  setMotor(&rtb_DataTypeConversion12_0, 3U, 2U);

  /* DataTypeConversion: '<S22>/Data Type Conversion11' */
  Gain1_o = (real32_T)floor(et_robocon_B.PWM.right);
  if (Gain1_o < 128.0F) {
    if (Gain1_o >= -128.0F) {
      rtb_DataTypeConversion12_0 = (int8_T)Gain1_o;
    } else {
      rtb_DataTypeConversion12_0 = MIN_int8_T;
    }
  } else {
    rtb_DataTypeConversion12_0 = MAX_int8_T;
  }

  /* S-Function (nxt_motor): '<S27>/Motor' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion11'
   */
  setMotor(&rtb_DataTypeConversion12_0, 2U, 2U);

  /* DataTypeConversion: '<S22>/Data Type Conversion12' */
  Gain1_o = (real32_T)floor(et_robocon_B.PWM.tail);
  if (Gain1_o < 128.0F) {
    if (Gain1_o >= -128.0F) {
      rtb_DataTypeConversion12_0 = (int8_T)Gain1_o;
    } else {
      rtb_DataTypeConversion12_0 = MIN_int8_T;
    }
  } else {
    rtb_DataTypeConversion12_0 = MAX_int8_T;
  }

  /* S-Function (nxt_motor): '<S28>/Motor' incorporates:
   *  DataTypeConversion: '<S22>/Data Type Conversion12'
   */
  setMotor(&rtb_DataTypeConversion12_0, 1U, 2U);
}

/* Model update function */
void et_robocon_update(void)
{
  /* Update for Delay: '<Root>/Delay' */
  et_robocon_DW.Delay_DSTATE = et_robocon_B.initFlags;

  /* Update for Enabled SubSystem: '<S100>/Gyro initialization' incorporates:
   *  Update for EnablePort: '<S113>/Enable'
   */
  if (et_robocon_DW.Gyroinitialization_MODE) {
    /* Update for DiscreteFilter: '<S113>/Low Pass Filter' */
    et_robocon_DW.LowPassFilter_states_h = et_robocon_DW.LowPassFilter_tmp_d;
  }

  /* End of Update for SubSystem: '<S100>/Gyro initialization' */

  /* Update for RateTransition: '<S22>/Rate Transition' */
  if (et_robocon_M->Timing.TaskCounters.TID[1] == 0) {
    et_robocon_DW.RateTransition_Buffer0 = et_robocon_B.sonar_h;
  }

  /* End of Update for RateTransition: '<S22>/Rate Transition' */

  /* Update for RateTransition: '<S22>/Rate Transition1' */
  if (et_robocon_M->Timing.TaskCounters.TID[3] == 0) {
    et_robocon_DW.RateTransition1_Buffer0 = et_robocon_B.battery_n;
  }

  /* End of Update for RateTransition: '<S22>/Rate Transition1' */

  /* Update for Memory: '<S106>/Memory' incorporates:
   *  Constant: '<S106>/Constant'
   */
  et_robocon_DW.Memory_PreviousInput = et_robocon_P.Constant_Value_g;

  /* Update for DiscreteFilter: '<S106>/Low Pass Filter' */
  et_robocon_DW.LowPassFilter_states = et_robocon_DW.LowPassFilter_tmp;

  /* Update for RateTransition: '<S22>/Rate Transition2' */
  if (et_robocon_M->Timing.TaskCounters.TID[2] == 0) {
    et_robocon_DW.RateTransition2_Buffer0 = et_robocon_B.Button;
  }

  /* End of Update for RateTransition: '<S22>/Rate Transition2' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.004, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  et_robocon_M->Timing.clockTick0++;
  rate_scheduler();
}

/* Model initialize function */
void et_robocon_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)et_robocon_M, 0,
                sizeof(RT_MODEL_et_robocon_T));

  /* block I/O */
  (void) memset(((void *) &et_robocon_B), 0,
                sizeof(B_et_robocon_T));

  /* states (dwork) */
  (void) memset((void *)&et_robocon_DW, 0,
                sizeof(DW_et_robocon_T));

  /* exported global states */
  lightCalib = et_robocon_rtZLight_Bus;
  phi_des = 0.0F;
  current_mode = LINE_TRACKING;
  current_mode_status = NOT_STARTED;

  /* InitializeConditions for Enabled SubSystem: '<S100>/Gyro initialization' */
  /* InitializeConditions for DiscreteFilter: '<S113>/Low Pass Filter' */
  et_robocon_DW.LowPassFilter_states_h =
    et_robocon_P.LowPassFilter_InitialStates;

  /* End of InitializeConditions for SubSystem: '<S100>/Gyro initialization' */

  /* Start for Enabled SubSystem: '<S100>/Gyro initialization' */
  /* VirtualOutportStart for Outport: '<S113>/psi_dot_0' */
  et_robocon_B.LowPassFilter = et_robocon_P.psi_dot_0_Y0;

  /* End of Start for SubSystem: '<S100>/Gyro initialization' */

  /* Start for Chart: '<S100>/Reset Subsystem' incorporates:
   *  Start for SubSystem: '<S100>/Compute psi'
   */
  et_robocon_Computepsi_Start(&et_robocon_B.Computepsi,
    (P_Computepsi_et_robocon_T *)&et_robocon_P.Computepsi);

  /* Start for Chart: '<S101>/Reset Subsystem' incorporates:
   *  Start for SubSystem: '<S101>/Process theta1'
   */
  et_robocon_Processtheta1_Start(&et_robocon_B.Processtheta1,
    (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

  /* Start for Triggered SubSystem: '<S109>/tail initialization' */
  /* VirtualOutportStart for Outport: '<S111>/tail_0' */
  et_robocon_B.tail = et_robocon_P.tail_0_Y0;

  /* End of Start for SubSystem: '<S109>/tail initialization' */

  /* Start for S-Function (nxt_light_sensor): '<S22>/Light Sensor' */
  initLightSensor(3U);

  /* Start for RateTransition: '<S22>/Rate Transition' */
  et_robocon_B.sonar = et_robocon_P.RateTransition_X0;

  /* Start for RateTransition: '<S22>/Rate Transition1' */
  et_robocon_B.RateTransition1 = et_robocon_P.RateTransition1_X0;

  /* Start for Enabled SubSystem: '<S106>/Store Offset' */
  et_robocon_StoreOffset_Start(&et_robocon_B.StoreOffset,
    (P_StoreOffset_et_robocon_T *)&et_robocon_P.StoreOffset);

  /* End of Start for SubSystem: '<S106>/Store Offset' */

  /* Start for RateTransition: '<S22>/Rate Transition2' */
  et_robocon_B.RateTransition2 = et_robocon_P.RateTransition2_X0;

  /* Start for Chart: '<S2>/normal_operation_modes.line_following' incorporates:
   *  Start for SubSystem: '<S11>/see_saw_mode.lineTracker'
   */
  /* Start for Chart: '<Root>/Main Controller' */
  e_see_saw_modelineTracker_Start(&et_robocon_B.see_saw_modelineTracker,
    (P_see_saw_modelineTracker_et__T *)&et_robocon_P.see_saw_modelineTracker);

  /* Start for S-Function (nxt_ultrasonic_sensor): '<S22>/Ultrasonic Sensor' */
  initUltrasonicSensor(2U);

  /* Start for DataStoreMemory: '<Root>/phi_des' */
  phi_des = et_robocon_P.phi_des_InitialValue;

  /* Start for DataStoreMemory: '<Root>/lightCalib' */
  lightCalib = et_robocon_P.lightCalib_InitialValue;

  /* Start for DataStoreMemory: '<Root>/current_mode_status' */
  current_mode_status = et_robocon_P.current_mode_status_InitialValu;

  /* Start for DataStoreMemory: '<Root>/current_mode' */
  current_mode = et_robocon_P.current_mode_InitialValue;
  et_robocon_PrevZCX.tailinitialization_Trig_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Delay: '<Root>/Delay' */
  et_robocon_DW.Delay_DSTATE = et_robocon_P.Delay_InitialCondition;
  et_robocon_DW.is_active_c1_et_robocon = 0U;
  et_robocon_DW.is_c1_et_robocon = et_robocon_IN_NO_ACTIVE_CHILD;

  /* InitializeConditions for Chart: '<S100>/Reset Subsystem' incorporates:
   *  InitializeConditions for SubSystem: '<S100>/Compute psi'
   */
  et_robocon_Computepsi_Init(&et_robocon_DW.Computepsi,
    (P_Computepsi_et_robocon_T *)&et_robocon_P.Computepsi);
  et_robocon_DW.is_active_c3_et_robocon = 0U;
  et_robocon_DW.is_c3_et_robocon = et_robocon_IN_NO_ACTIVE_CHILD;

  /* InitializeConditions for Chart: '<S101>/Reset Subsystem' incorporates:
   *  InitializeConditions for SubSystem: '<S101>/Process theta1'
   */
  et_robocon_Processtheta1_Init(&et_robocon_DW.Processtheta1,
    (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

  /* InitializeConditions for RateTransition: '<S22>/Rate Transition' */
  et_robocon_DW.RateTransition_Buffer0 = et_robocon_P.RateTransition_X0;

  /* InitializeConditions for RateTransition: '<S22>/Rate Transition1' */
  et_robocon_DW.RateTransition1_Buffer0 = et_robocon_P.RateTransition1_X0;

  /* InitializeConditions for Memory: '<S106>/Memory' */
  et_robocon_DW.Memory_PreviousInput = et_robocon_P.Memory_X0;

  /* InitializeConditions for DiscreteFilter: '<S106>/Low Pass Filter' */
  et_robocon_DW.LowPassFilter_states =
    et_robocon_P.LowPassFilter_InitialStates_f;

  /* InitializeConditions for RateTransition: '<S22>/Rate Transition2' */
  et_robocon_DW.RateTransition2_Buffer0 = et_robocon_P.RateTransition2_X0;

  /* InitializeConditions for Chart: '<Root>/Main Controller' */
  et_robocon_DW.is_gyro_calibration_mode = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.is_GyroCalibration = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.temporalCounter_i1_c = 0U;
  et_robocon_DW.is_c2_gyro_calibration_algorith = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.is_light_sensor_calibration_up = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.temporalCounter_i1_n = 0U;
  et_robocon_DW.is_c4_light_sensor_calibration_ = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.is_see_saw_mode = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.is_active_After = 0U;
  et_robocon_DW.is_active_SeesawLogic = 0U;
  et_robocon_DW.is_SeesawLogic = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.temporalCounter_i1 = 0U;
  et_robocon_DW.is_c6_et_robocon = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.is_normal_operation_modes = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_DW.is_active_c5_et_robocon = 0U;
  et_robocon_DW.is_c5_et_robocon = et_robocon_IN_NO_ACTIVE_CHILD;
  et_robocon_B.PWM.left = 0.0F;
  et_robocon_B.PWM.right = 0.0F;
  et_robocon_B.PWM.tail = 0.0F;
  et_robocon_B.initFlags.fall = false;
  et_robocon_B.initFlags.gyroInit = 0.0F;
  et_robocon_B.initFlags.gyroReset = 0.0F;
  et_robocon_B.initFlags.theta = 0.0F;
  et_robocon_B.initFlags.tail = 0.0F;

  /* InitializeConditions for Chart: '<S2>/normal_operation_modes.line_following' incorporates:
   *  InitializeConditions for SubSystem: '<S11>/see_saw_mode.lineTracker'
   */
  et_see_saw_modelineTracker_Init(&et_robocon_DW.see_saw_modelineTracker,
    (P_see_saw_modelineTracker_et__T *)&et_robocon_P.see_saw_modelineTracker);

  /* InitializeConditions for Chart: '<S2>/normal_operation_modes.line_following' incorporates:
   *  InitializeConditions for SubSystem: '<S11>/see_saw_mode.balance_ctrl'
   */
  /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' incorporates:
   *  InitializeConditions for Chart: '<Root>/Main Controller'
   */
  et_robocon_DW.DiscreteTimeIntegrator_DSTATE =
    et_robocon_P.DiscreteTimeIntegrator_IC;
  et_robocon_DW.DiscreteTimeIntegrator_PREV_U = 0.0F;

  /* InitializeConditions for DiscreteFilter: '<S17>/LPF' incorporates:
   *  InitializeConditions for Chart: '<Root>/Main Controller'
   */
  et_robocon_DW.LPF_states = et_robocon_P.LPF_InitialStates;

  /* InitializeConditions for DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' incorporates:
   *  InitializeConditions for Chart: '<Root>/Main Controller'
   */
  et_robocon_DW.DiscreteTimeIntegrator1_DSTATE =
    et_robocon_P.DiscreteTimeIntegrator1_IC;
  et_robocon_DW.DiscreteTimeIntegrator1_PREV_U = 0.0F;

  /* Enable for Chart: '<S100>/Reset Subsystem' */
  if (et_robocon_DW.is_c1_et_robocon == et_robocon_IN_CheckForReset) {
    /* InitializeConditions for Function Call SubSystem: '<S100>/Compute psi' */
    et_robocon_Computepsi_Init(&et_robocon_DW.Computepsi,
      (P_Computepsi_et_robocon_T *)&et_robocon_P.Computepsi);

    /* End of InitializeConditions for SubSystem: '<S100>/Compute psi' */

    /* Enable for Function Call SubSystem: '<S100>/Compute psi' */
    et_robocon_Computepsi_Enable(&et_robocon_DW.Computepsi);

    /* End of Enable for SubSystem: '<S100>/Compute psi' */
  }

  /* End of Enable for Chart: '<S100>/Reset Subsystem' */

  /* Enable for Chart: '<S101>/Reset Subsystem' */
  if (et_robocon_DW.is_c3_et_robocon == et_robocon_IN_CheckForReset) {
    /* InitializeConditions for Function Call SubSystem: '<S101>/Process theta1' */
    et_robocon_Processtheta1_Init(&et_robocon_DW.Processtheta1,
      (P_Processtheta1_et_robocon_T *)&et_robocon_P.Processtheta1);

    /* End of InitializeConditions for SubSystem: '<S101>/Process theta1' */

    /* Enable for Function Call SubSystem: '<S101>/Process theta1' */
    et_robocon_Processtheta1_Enable(&et_robocon_DW.Processtheta1);

    /* End of Enable for SubSystem: '<S101>/Process theta1' */
  }

  /* End of Enable for Chart: '<S101>/Reset Subsystem' */

  /* Enable for Chart: '<Root>/Main Controller' */
  if ((et_robocon_DW.is_normal_operation_modes == et_robocon_IN_line_following) &&
      (et_robocon_DW.is_c6_et_robocon == et_robocon_IN_see_saw_mode)) {
    /* Enable for Function Call SubSystem: '<S11>/see_saw_mode.balance_ctrl' */
    et_robocon_DW.see_saw_modebalance_ctrl_RESET_ = true;

    /* Enable for DiscreteIntegrator: '<S17>/Discrete-Time Integrator' */
    et_robocon_DW.DiscreteTimeIntegrator_SYSTEM_E = 1U;

    /* Enable for DiscreteIntegrator: '<S17>/Discrete-Time Integrator1' */
    et_robocon_DW.DiscreteTimeIntegrator1_SYSTEM_ = 1U;

    /* End of Enable for SubSystem: '<S11>/see_saw_mode.balance_ctrl' */
  }

  /* End of Enable for Chart: '<Root>/Main Controller' */
}

/* Model terminate function */
void et_robocon_terminate(void)
{
  /* Terminate for S-Function (nxt_light_sensor): '<S22>/Light Sensor' */
  terminateLightSensor(3U);

  /* Terminate for S-Function (nxt_ultrasonic_sensor): '<S22>/Ultrasonic Sensor' */
  terminateUltrasonicSensor(2U);

  /* Terminate for S-Function (nxt_motor): '<S26>/Motor' */
  terminateMotor(3U, 2U);

  /* Terminate for S-Function (nxt_motor): '<S27>/Motor' */
  terminateMotor(2U, 2U);

  /* Terminate for S-Function (nxt_motor): '<S28>/Motor' */
  terminateMotor(1U, 2U);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
