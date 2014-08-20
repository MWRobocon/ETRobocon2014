/*
 * File: et_robocon_data.c
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

/* Block parameters (auto storage) */
P_et_robocon_T et_robocon_P = {
  {
    0.0F,
    0.0F,
    0.0F,
    0.0F,
    0.0F
  },                                   /* Variable: balancerStates_Bus0
                                        * Referenced by: '<S2>/normal_operation_modes.line_following'
                                        */

  /*  Variable: K
   * Referenced by: '<S17>/Gain1'
   */
  { -0.835082F, -34.1896F, -1.09951F, -2.81409F, -0.447214F },
  800U,                                /* Mask Parameter: Speaker_speakerFreq
                                        * Referenced by: '<S97>/Speaker'
                                        */

  {
    0.0F,                              /* whiteOnLimbo */
    0.0F,                              /* blackOnLimbo */
    0.0F,                              /* black */
    0.0F,                              /* white */
    0.0F,                              /* black_white */
    0.0F,                              /* gray */
    0.0F,                              /* blackOnTail */
    0.0F,                              /* whiteOnTail */
    0.0F,                              /* flashingBlack */
    0.0F,                              /* flashingWhite */
    0.0F,                              /* flashingMapBlack */
    0.0F                               /* flashingMapWhite */
  },                                   /* Computed Parameter: lightCalib_InitialValue
                                        * Referenced by: synthesized block
                                        */

  {
    false,                             /* fall */
    0.0F,                              /* gyroInit */
    0.0F,                              /* gyroReset */
    0.0F,                              /* theta */
    0.0F                               /* tail */
  },                                   /* Computed Parameter: Delay_InitialCondition
                                        * Referenced by: '<Root>/Delay'
                                        */
  100.0,                               /* Expression: 100
                                        * Referenced by: '<S17>/Gain'
                                        */
  50.0,                                /* Expression: 50
                                        * Referenced by: '<S5>/Constant'
                                        */
  0.0F,                                /* Computed Parameter: light_Y0
                                        * Referenced by: '<S19>/light'
                                        */
  0.3F,                                /* Computed Parameter: Gain_Gain_d
                                        * Referenced by: '<S19>/Gain'
                                        */
  0.01F,                               /* Computed Parameter: Gain1_Gain
                                        * Referenced by: '<S19>/Gain1'
                                        */
  0.0F,                                /* Computed Parameter: cmd_Y0
                                        * Referenced by: '<S17>/cmd'
                                        */
  0.004F,                              /* Computed Parameter: DiscreteTimeIntegrator_gainval
                                        * Referenced by: '<S17>/Discrete-Time Integrator'
                                        */
  0.0F,                                /* Computed Parameter: DiscreteTimeIntegrator_IC
                                        * Referenced by: '<S17>/Discrete-Time Integrator'
                                        */
  25.0F,                               /* Expression: 1/R
                                        * Referenced by: '<S17>/m//s --> rad//s'
                                        */
  0.15F,                               /* Computed Parameter: LPF_NumCoef
                                        * Referenced by: '<S17>/LPF'
                                        */

  /*  Computed Parameter: LPF_DenCoef
   * Referenced by: '<S17>/LPF'
   */
  { 1.0F, -0.85F },
  0.0F,                                /* Computed Parameter: LPF_InitialStates
                                        * Referenced by: '<S17>/LPF'
                                        */
  0.0F,                                /* Computed Parameter: Constant_Value_e
                                        * Referenced by: '<S17>/Constant'
                                        */
  0.0F,                                /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S17>/Constant1'
                                        */
  0.004F,                              /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                        * Referenced by: '<S17>/Discrete-Time Integrator1'
                                        */
  0.0F,                                /* Computed Parameter: DiscreteTimeIntegrator1_IC
                                        * Referenced by: '<S17>/Discrete-Time Integrator1'
                                        */
  100.0F,                              /* Computed Parameter: Saturation_UpperSat
                                        * Referenced by: '<S17>/Saturation'
                                        */
  -100.0F,                             /* Computed Parameter: Saturation_LowerSat
                                        * Referenced by: '<S17>/Saturation'
                                        */
  0.0F,                                /* Computed Parameter: tail_0_Y0
                                        * Referenced by: '<S111>/tail_0'
                                        */
  0.0F,                                /* Computed Parameter: psi_dot_0_Y0
                                        * Referenced by: '<S113>/psi_dot_0'
                                        */
  0.01F,                               /* Computed Parameter: LowPassFilter_NumCoef
                                        * Referenced by: '<S113>/Low Pass Filter'
                                        */

  /*  Computed Parameter: LowPassFilter_DenCoef
   * Referenced by: '<S113>/Low Pass Filter'
   */
  { 1.0F, -0.99F },
  0.0F,                                /* Computed Parameter: LowPassFilter_InitialStates
                                        * Referenced by: '<S113>/Low Pass Filter'
                                        */
  -10.0F,                              /* Computed Parameter: Gain1_Gain_k
                                        * Referenced by: '<S4>/Gain1'
                                        */
  100.0F,                              /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S4>/Gain2'
                                        */
  100.0F,                              /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S4>/Saturation1'
                                        */
  -100.0F,                             /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S4>/Saturation1'
                                        */
  250.0F,                              /* Computed Parameter: Gain_Gain_m
                                        * Referenced by: '<S7>/Gain'
                                        */
  100.0F,                              /* Computed Parameter: Saturation_UpperSat_o
                                        * Referenced by: '<S7>/Saturation'
                                        */
  -100.0F,                             /* Computed Parameter: Saturation_LowerSat_j
                                        * Referenced by: '<S7>/Saturation'
                                        */
  0.0174532924F,                       /* Computed Parameter: Gain1_Gain_n
                                        * Referenced by: '<S104>/Gain1'
                                        */
  0.0174532924F,                       /* Computed Parameter: Gain1_Gain_g
                                        * Referenced by: '<S102>/Gain1'
                                        */
  0.0174532924F,                       /* Computed Parameter: Gain1_Gain_c
                                        * Referenced by: '<S103>/Gain1'
                                        */
  0.0174532924F,                       /* Computed Parameter: Gain1_Gain_gi
                                        * Referenced by: '<S105>/Gain1'
                                        */
  0.01F,                               /* Computed Parameter: LowPassFilter_NumCoef_m
                                        * Referenced by: '<S106>/Low Pass Filter'
                                        */

  /*  Computed Parameter: LowPassFilter_DenCoef_e
   * Referenced by: '<S106>/Low Pass Filter'
   */
  { 1.0F, -0.99F },
  0.0F,                                /* Computed Parameter: LowPassFilter_InitialStates_f
                                        * Referenced by: '<S106>/Low Pass Filter'
                                        */
  0.001089F,                           /* Computed Parameter: Gain1_Gain_j
                                        * Referenced by: '<S108>/Gain1'
                                        */
  0.625F,                              /* Computed Parameter: Constant_Value_ei
                                        * Referenced by: '<S108>/Constant'
                                        */
  0.0F,                                /* Expression: single(0)
                                        * Referenced by: '<S31>/Constant'
                                        */
  0.0F,                                /* Computed Parameter: phi_des_InitialValue
                                        * Referenced by: synthesized block
                                        */
  0,                                   /* Computed Parameter: RateTransition_X0
                                        * Referenced by: '<S22>/Rate Transition'
                                        */
  50U,                                 /* Computed Parameter: Speaker_p3
                                        * Referenced by: '<S97>/Speaker'
                                        */
  100U,                                /* Computed Parameter: Speaker_p4
                                        * Referenced by: '<S97>/Speaker'
                                        */
  1U,                                  /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<Root>/Delay'
                                        */
  SKIP,                                /* Expression: []
                                        * Referenced by: synthesized block
                                        */
  NOT_STARTED,                         /* Expression: []
                                        * Referenced by: synthesized block
                                        */
  0U,                                  /* Computed Parameter: RateTransition1_X0
                                        * Referenced by: '<S22>/Rate Transition1'
                                        */
  0,                                   /* Computed Parameter: RateTransition2_X0
                                        * Referenced by: '<S22>/Rate Transition2'
                                        */
  2U,                                  /* Computed Parameter: Speaker_p1
                                        * Referenced by: '<S97>/Speaker'
                                        */
  1,                                   /* Computed Parameter: Memory_X0
                                        * Referenced by: '<S106>/Memory'
                                        */
  0,                                   /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S106>/Constant'
                                        */

  /* Start of '<S101>/Process theta1' */
  {
    0.0F,                              /* Computed Parameter: x0_Y0
                                        * Referenced by: '<S123>/x0'
                                        */
    0.0F,                              /* Computed Parameter: theta_Y0
                                        * Referenced by: '<S117>/theta'
                                        */
    0.0F,                              /* Computed Parameter: psi_out_Y0
                                        * Referenced by: '<S117>/psi_out'
                                        */
    0.0F,                              /* Computed Parameter: theta_dot_Y0
                                        * Referenced by: '<S117>/theta_dot'
                                        */
    0.0F,                              /* Computed Parameter: int_theta_Y0
                                        * Referenced by: '<S117>/int_theta'
                                        */
    0.0F,                              /* Computed Parameter: phi_Y0
                                        * Referenced by: '<S117>/phi'
                                        */
    0.0F,                              /* Computed Parameter: phi_dot_Y0
                                        * Referenced by: '<S117>/phi_dot'
                                        */
    0.0F,                              /* Computed Parameter: theta_dot_dot_Y0
                                        * Referenced by: '<S117>/theta_dot_dot'
                                        */
    0.004F,                            /* Computed Parameter: DiscreteTimeIntegrator2_gainval
                                        * Referenced by: '<S117>/Discrete-Time Integrator2'
                                        */
    0.0F,                              /* Computed Parameter: DiscreteTimeIntegrator2_IC
                                        * Referenced by: '<S117>/Discrete-Time Integrator2'
                                        */
    1.0F,                              /* Computed Parameter: UsePhiInTheta_Gain
                                        * Referenced by: '<S117>/UsePhiInTheta'
                                        */
    0.5F,                              /* Computed Parameter: Gain2_Gain
                                        * Referenced by: '<S117>/Gain2'
                                        */
    0.266666651F,                      /* Expression: R/W
                                        * Referenced by: '<S117>/Gain7'
                                        */
    0.2F,                              /* Computed Parameter: LowPassFilter1_NumCoef
                                        * Referenced by: '<S120>/Low Pass Filter1'
                                        */

    /*  Computed Parameter: LowPassFilter1_DenCoef
     * Referenced by: '<S120>/Low Pass Filter1'
     */
    { 1.0F, -0.8F },
    0.0F,                              /* Computed Parameter: LowPassFilter1_InitialStates
                                        * Referenced by: '<S120>/Low Pass Filter1'
                                        */
    250.0F,                            /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S120>/Gain'
                                        */
    0.0F,                              /* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S120>/Unit Delay'
                                        */
    0.2F,                              /* Computed Parameter: LowPassFilter1_NumCoef_f
                                        * Referenced by: '<S122>/Low Pass Filter1'
                                        */

    /*  Computed Parameter: LowPassFilter1_DenCoef_e
     * Referenced by: '<S122>/Low Pass Filter1'
     */
    { 1.0F, -0.8F },
    0.0F,                              /* Computed Parameter: LowPassFilter1_InitialStates_h
                                        * Referenced by: '<S122>/Low Pass Filter1'
                                        */
    250.0F,                            /* Computed Parameter: Gain_Gain_f
                                        * Referenced by: '<S122>/Gain'
                                        */
    0.0F,                              /* Computed Parameter: UnitDelay_InitialCondition_a
                                        * Referenced by: '<S122>/Unit Delay'
                                        */
    0.2F,                              /* Computed Parameter: LowPassFilter1_NumCoef_n
                                        * Referenced by: '<S121>/Low Pass Filter1'
                                        */

    /*  Computed Parameter: LowPassFilter1_DenCoef_f
     * Referenced by: '<S121>/Low Pass Filter1'
     */
    { 1.0F, -0.8F },
    0.0F,                              /* Computed Parameter: LowPassFilter1_InitialStates_k
                                        * Referenced by: '<S121>/Low Pass Filter1'
                                        */
    250.0F,                            /* Computed Parameter: Gain_Gain_h
                                        * Referenced by: '<S121>/Gain'
                                        */
    0.0F,                              /* Computed Parameter: UnitDelay_InitialCondition_i
                                        * Referenced by: '<S121>/Unit Delay'
                                        */
    0,                                 /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S117>/Constant'
                                        */
    0,                                 /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S117>/Constant1'
                                        */
    1,                                 /* Computed Parameter: Enableoninit_X0
                                        * Referenced by: '<S117>/Enable on init'
                                        */
    1,                                 /* Computed Parameter: Enableoninit1_X0
                                        * Referenced by: '<S117>/Enable on init1'
                                        */

    /* Start of '<S117>/Enabled Subsystem' */
    {
      0.0F                             /* Computed Parameter: x0_Y0
                                        * Referenced by: '<S119>/x0'
                                        */
    }
    /* End of '<S117>/Enabled Subsystem' */
  }
  /* End of '<S101>/Process theta1' */
  ,

  /* Start of '<S100>/Compute psi' */
  {
    0.0F,                              /* Computed Parameter: psi_Y0
                                        * Referenced by: '<S112>/psi'
                                        */
    0.0F,                              /* Computed Parameter: Filtered_Y0
                                        * Referenced by: '<S112>/Filtered'
                                        */
    0.004F,                            /* Computed Parameter: DiscreteTimeIntegrator1_gainval
                                        * Referenced by: '<S112>/Discrete-Time Integrator1'
                                        */
    0.0F                               /* Computed Parameter: DiscreteTimeIntegrator1_IC
                                        * Referenced by: '<S112>/Discrete-Time Integrator1'
                                        */
  }
  /* End of '<S100>/Compute psi' */
  ,

  /* Start of '<S106>/Store Offset' */
  {
    0.0F                               /* Computed Parameter: x0_Y0
                                        * Referenced by: '<S110>/x0'
                                        */
  }
  /* End of '<S106>/Store Offset' */
  ,

  /* Start of '<S11>/see_saw_mode.lineTracker' */
  {
    100.0,                             /* Expression: 100
                                        * Referenced by: '<S18>/Gain'
                                        */
    0.0F,                              /* Computed Parameter: cmd_Y0
                                        * Referenced by: '<S18>/cmd'
                                        */
    0.0F,                              /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S18>/Constant'
                                        */
    0.05F,                             /* Computed Parameter: DiscreteFilter_NumCoef
                                        * Referenced by: '<S20>/Discrete Filter'
                                        */

    /*  Computed Parameter: DiscreteFilter_DenCoef
     * Referenced by: '<S20>/Discrete Filter'
     */
    { 1.0F, -0.95F },
    0.0F,                              /* Computed Parameter: DiscreteFilter_InitialStates
                                        * Referenced by: '<S20>/Discrete Filter'
                                        */
    250.0F,                            /* Computed Parameter: Gain_Gain_j
                                        * Referenced by: '<S20>/Gain'
                                        */
    0.0F,                              /* Computed Parameter: UnitDelay_InitialCondition
                                        * Referenced by: '<S20>/Unit Delay'
                                        */
    -0.02F,                            /* Computed Parameter: DeadZone_Start
                                        * Referenced by: '<S18>/Dead Zone'
                                        */
    0.02F,                             /* Computed Parameter: DeadZone_End
                                        * Referenced by: '<S18>/Dead Zone'
                                        */

    /*  Computed Parameter: PD_Gain
     * Referenced by: '<S18>/PD'
     */
    { 2.0F, 0.01F },
    6.0F,                              /* Computed Parameter: Saturation_UpperSat
                                        * Referenced by: '<S18>/Saturation'
                                        */
    -6.0F,                             /* Computed Parameter: Saturation_LowerSat
                                        * Referenced by: '<S18>/Saturation'
                                        */
    100.0F,                            /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S18>/Saturation1'
                                        */
    -100.0F,                           /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S18>/Saturation1'
                                        */
    -1.0F                              /* Computed Parameter: switchsideofline_Gain
                                        * Referenced by: '<S18>/switch side of line'
                                        */
  }
  /* End of '<S11>/see_saw_mode.lineTracker' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
