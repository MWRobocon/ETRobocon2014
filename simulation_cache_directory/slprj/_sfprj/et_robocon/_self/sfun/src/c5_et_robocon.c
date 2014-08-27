/* Include files */

#include <stddef.h>
#include "blas.h"
#include "et_robocon_sfun.h"
#include "c5_et_robocon.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "et_robocon_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c5_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c5_IN_emergency_stop           ((uint8_T)1U)
#define c5_IN_normal_operation_modes   ((uint8_T)2U)
#define c5_IN_WeShouldNotBeHere        ((uint8_T)1U)
#define c5_IN_gyro_calibration_mode    ((uint8_T)2U)
#define c5_IN_light_calibration_up     ((uint8_T)3U)
#define c5_IN_line_following           ((uint8_T)4U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const mxArray *c5_subchartSimStateInfo;
static const mxArray *c5_b_subchartSimStateInfo;
static const mxArray *c5_c_subchartSimStateInfo;
static const char * c5_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_c_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_d_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_e_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_f_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_g_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_h_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_i_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_j_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_k_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_l_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_m_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_n_debug_family_names[2] = { "nargin", "nargout" };

static const char * c5_o_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_p_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_q_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_r_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_s_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_t_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_u_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c5_v_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

/* Function Declarations */
static void initialize_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance);
static void initialize_params_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance);
static void enable_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance);
static void disable_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c5_et_robocon(SFc5_et_roboconInstanceStruct *
  chartInstance);
static void set_sim_state_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_st);
static void c5_set_sim_state_side_effects_c5_et_robocon
  (SFc5_et_roboconInstanceStruct *chartInstance);
static void finalize_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance);
static void sf_gateway_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance);
static void mdl_start_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance);
static void c5_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance);
static void initSimStructsc5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance);
static void c5_enter_internal_normal_operation_modes
  (SFc5_et_roboconInstanceStruct *chartInstance);
static void c5_normal_operation_modes(SFc5_et_roboconInstanceStruct
  *chartInstance);
static void c5_exit_internal_normal_operation_modes
  (SFc5_et_roboconInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static real_T c5_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static boolean_T c5_b_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real32_T c5_c_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_sf_internal_predicateOutput, const char_T
  *c5_identifier);
static real32_T c5_d_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static void c5_info_helper(const mxArray **c5_info);
static const mxArray *c5_emlrt_marshallOut(const char * c5_u);
static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_e_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint8_T c5_f_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_b_tp_emergency_stop, const char_T
  *c5_identifier);
static uint8_T c5_g_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_PWM_bus_io(void *chartInstanceVoid, void *c5_pData);
static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static c5_PWM_bus c5_h_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_b_PWM, const char_T *c5_identifier);
static c5_PWM_bus c5_i_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_j_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  c5_OperationModeEnum c5_y[3]);
static void c5_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static c5_OperationModeEnum c5_k_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *
  chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_states_bus_io(void *chartInstanceVoid, void *c5_pData);
static const mxArray *c5_c_emlrt_marshallOut(SFc5_et_roboconInstanceStruct
  *chartInstance, const c5_Balancer_States_Bus c5_u);
static const mxArray *c5_i_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_j_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static c5_OperationModeStatusEnum c5_l_emlrt_marshallIn
  (SFc5_et_roboconInstanceStruct *chartInstance, const mxArray *c5_u, const
   emlrtMsgIdentifier *c5_parentId);
static void c5_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_sensors_bus_io(void *chartInstanceVoid, void *c5_pData);
static const mxArray *c5_k_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_lightCalib_bus_io(void *chartInstanceVoid, void
  *c5_pData);
static const mxArray *c5_l_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static c5_Light_Bus c5_m_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_initFlags_bus_io(void *chartInstanceVoid, void
  *c5_pData);
static const mxArray *c5_d_emlrt_marshallOut(SFc5_et_roboconInstanceStruct
  *chartInstance, const c5_Init_Bus c5_u);
static const mxArray *c5_m_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static c5_Init_Bus c5_n_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_b_initFlags, const char_T *c5_identifier);
static c5_Init_Bus c5_o_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_n_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static c5_Balancer_States_Bus c5_p_emlrt_marshallIn
  (SFc5_et_roboconInstanceStruct *chartInstance, const mxArray *c5_u, const
   emlrtMsgIdentifier *c5_parentId);
static void c5_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_q_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_d_subchartSimStateInfo, const char_T
  *c5_identifier);
static const mxArray *c5_r_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_s_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *chartInstance,
  const mxArray *c5_b_dataWrittenToVector, const char_T *c5_identifier,
  boolean_T c5_y[1]);
static void c5_t_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T c5_y[1]);
static void c5_updateDataWrittenToVector(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_vectorIndex);
static void c5_errorIfDataNotWrittenToFcn(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_vectorIndex, uint32_T c5_dataNumber, uint32_T
  c5_ssIdOfSourceObject, int32_T c5_offsetInSourceObject, int32_T
  c5_lengthInSourceObject);
static c5_OperationModeEnum c5_get_current_mode(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_elementIndex);
static void c5_set_current_mode(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_elementIndex, c5_OperationModeEnum c5_elementValue);
static c5_OperationModeEnum *c5_access_current_mode
  (SFc5_et_roboconInstanceStruct *chartInstance, uint32_T c5_rdOnly);
static c5_OperationModeStatusEnum c5_get_current_mode_status
  (SFc5_et_roboconInstanceStruct *chartInstance, uint32_T c5_elementIndex);
static void c5_set_current_mode_status(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_elementIndex, c5_OperationModeStatusEnum
  c5_elementValue);
static c5_OperationModeStatusEnum *c5_access_current_mode_status
  (SFc5_et_roboconInstanceStruct *chartInstance, uint32_T c5_rdOnly);
static c5_Light_Bus c5_get_lightCalib(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_elementIndex);
static void c5_set_lightCalib(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_elementIndex, c5_Light_Bus c5_elementValue);
static c5_Light_Bus *c5_access_lightCalib(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_rdOnly);
static real32_T c5_get_phi_des(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_elementIndex);
static void c5_set_phi_des(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_elementIndex, real32_T c5_elementValue);
static real32_T *c5_access_phi_des(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_rdOnly);
static void init_dsm_address_info(SFc5_et_roboconInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc5_et_roboconInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance)
{
  void *c5_original_io_vars[1];
  void *c5_b_original_io_vars[1];
  void *c5_c_original_io_vars[1];
  sf_call_atomic_subchart_auto_fcn(71, (void *)
    chartInstance->c5_subchartSimstruct, (void *)&c5_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(71, (void *)
    chartInstance->c5_b_subchartSimstruct, (void *)&c5_b_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(71, (void *)
    chartInstance->c5_c_subchartSimstruct, (void *)&c5_c_original_io_vars);
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  c5_subchartSimStateInfo = NULL;
  c5_b_subchartSimStateInfo = NULL;
  c5_c_subchartSimStateInfo = NULL;
  chartInstance->c5_doSetSimStateSideEffects = 0U;
  chartInstance->c5_setSimStateSideEffectsInfo = NULL;
  chartInstance->c5_tp_emergency_stop = 0U;
  chartInstance->c5_is_normal_operation_modes = c5_IN_NO_ACTIVE_CHILD;
  chartInstance->c5_tp_normal_operation_modes = 0U;
  chartInstance->c5_tp_WeShouldNotBeHere = 0U;
  chartInstance->c5_tp_gyro_calibration_mode = 0U;
  chartInstance->c5_tp_light_calibration_up = 0U;
  chartInstance->c5_tp_line_following = 0U;
  chartInstance->c5_is_active_c5_et_robocon = 0U;
  chartInstance->c5_is_c5_et_robocon = c5_IN_NO_ACTIVE_CHILD;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *(real32_T *)&((char_T *)chartInstance->c5_PWM)[0] = 0.0F;
    *(real32_T *)&((char_T *)chartInstance->c5_PWM)[4] = 0.0F;
    *(real32_T *)&((char_T *)chartInstance->c5_PWM)[8] = 0.0F;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c5_BT_status_out = 0.0F;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *(boolean_T *)&((char_T *)chartInstance->c5_initFlags)[0] = false;
    *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[4] = 0.0F;
    *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[8] = 0.0F;
    *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[12] = 0.0F;
    *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[16] = 0.0F;
  }
}

static void initialize_params_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance)
{
  real_T c5_dv0[3];
  int32_T c5_i0;
  const mxArray *c5_m0 = NULL;
  const mxArray *c5_mxField;
  c5_Init_Bus c5_r0;
  const mxArray *c5_m1 = NULL;
  const mxArray *c5_b_mxField;
  c5_Balancer_States_Bus c5_r1;
  sf_mex_import_named("TRACK_MODE_LIST", sf_mex_get_sfun_param(chartInstance->S,
    1, 0), c5_dv0, 0, 0, 0U, 1, 0U, 1, 3);
  for (c5_i0 = 0; c5_i0 < 3; c5_i0++) {
    chartInstance->c5_TRACK_MODE_LIST[c5_i0] = (c5_OperationModeEnum)(int32_T)
      c5_dv0[c5_i0];
  }

  c5_m0 = sf_mex_get_sfun_param(chartInstance->S, 0, 1);
  c5_mxField = sf_mex_getfield(c5_m0, "fall", "Init_Bus0", 0);
  sf_mex_import_named("Init_Bus0", sf_mex_dup(c5_mxField), &c5_r0.fall, 1, 11,
                      0U, 0, 0U, 0);
  c5_mxField = sf_mex_getfield(c5_m0, "gyroInit", "Init_Bus0", 0);
  sf_mex_import_named("Init_Bus0", sf_mex_dup(c5_mxField), &c5_r0.gyroInit, 1, 1,
                      0U, 0, 0U, 0);
  c5_mxField = sf_mex_getfield(c5_m0, "gyroReset", "Init_Bus0", 0);
  sf_mex_import_named("Init_Bus0", sf_mex_dup(c5_mxField), &c5_r0.gyroReset, 1,
                      1, 0U, 0, 0U, 0);
  c5_mxField = sf_mex_getfield(c5_m0, "theta", "Init_Bus0", 0);
  sf_mex_import_named("Init_Bus0", sf_mex_dup(c5_mxField), &c5_r0.theta, 1, 1,
                      0U, 0, 0U, 0);
  c5_mxField = sf_mex_getfield(c5_m0, "tail", "Init_Bus0", 0);
  sf_mex_import_named("Init_Bus0", sf_mex_dup(c5_mxField), &c5_r0.tail, 1, 1, 0U,
                      0, 0U, 0);
  sf_mex_destroy(&c5_m0);
  chartInstance->c5_Init_Bus0 = c5_r0;
  c5_m1 = sf_mex_get_sfun_param(chartInstance->S, 2, 1);
  c5_b_mxField = sf_mex_getfield(c5_m1, "theta", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c5_b_mxField),
                      &c5_r1.theta, 1, 1, 0U, 0, 0U, 0);
  c5_b_mxField = sf_mex_getfield(c5_m1, "psi", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c5_b_mxField),
                      &c5_r1.psi, 1, 1, 0U, 0, 0U, 0);
  c5_b_mxField = sf_mex_getfield(c5_m1, "theta_dot", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c5_b_mxField),
                      &c5_r1.theta_dot, 1, 1, 0U, 0, 0U, 0);
  c5_b_mxField = sf_mex_getfield(c5_m1, "psi_dot", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c5_b_mxField),
                      &c5_r1.psi_dot, 1, 1, 0U, 0, 0U, 0);
  c5_b_mxField = sf_mex_getfield(c5_m1, "int_theta", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c5_b_mxField),
                      &c5_r1.int_theta, 1, 1, 0U, 0, 0U, 0);
  sf_mex_destroy(&c5_m1);
  chartInstance->c5_balancerStates_Bus0 = c5_r1;
}

static void enable_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance)
{
  void *c5_original_io_vars[1];
  void *c5_b_original_io_vars[1];
  void *c5_c_original_io_vars[1];
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c5_is_normal_operation_modes == c5_IN_gyro_calibration_mode)
  {
    sf_call_atomic_subchart_auto_fcn(66, (void *)
      chartInstance->c5_subchartSimstruct, (void *)&c5_original_io_vars);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_light_calibration_up)
  {
    sf_call_atomic_subchart_auto_fcn(66, (void *)
      chartInstance->c5_b_subchartSimstruct, (void *)&c5_b_original_io_vars);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_line_following) {
    sf_call_atomic_subchart_auto_fcn(66, (void *)
      chartInstance->c5_c_subchartSimstruct, (void *)&c5_c_original_io_vars);
  }
}

static void disable_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance)
{
  void *c5_original_io_vars[1];
  void *c5_b_original_io_vars[1];
  void *c5_c_original_io_vars[1];
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c5_is_normal_operation_modes == c5_IN_gyro_calibration_mode)
  {
    sf_call_atomic_subchart_auto_fcn(67, (void *)
      chartInstance->c5_subchartSimstruct, (void *)&c5_original_io_vars);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_light_calibration_up)
  {
    sf_call_atomic_subchart_auto_fcn(67, (void *)
      chartInstance->c5_b_subchartSimstruct, (void *)&c5_b_original_io_vars);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_line_following) {
    sf_call_atomic_subchart_auto_fcn(67, (void *)
      chartInstance->c5_c_subchartSimstruct, (void *)&c5_c_original_io_vars);
  }
}

static void c5_update_debugger_state_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance)
{
  uint32_T c5_prevAniVal;
  c5_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c5_is_active_c5_et_robocon == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
  }

  if (chartInstance->c5_is_c5_et_robocon == c5_IN_emergency_stop) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
  }

  if (chartInstance->c5_is_c5_et_robocon == c5_IN_normal_operation_modes) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_gyro_calibration_mode)
  {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c5_sfEvent);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_light_calibration_up)
  {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c5_sfEvent);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_line_following) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c5_sfEvent);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_WeShouldNotBeHere) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
  }

  _SFD_SET_ANIMATION(c5_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c5_et_robocon(SFc5_et_roboconInstanceStruct *
  chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real32_T c5_hoistedGlobal;
  real32_T c5_u;
  const mxArray *c5_b_y = NULL;
  const mxArray *c5_c_y = NULL;
  real32_T c5_b_u;
  const mxArray *c5_d_y = NULL;
  real32_T c5_c_u;
  const mxArray *c5_e_y = NULL;
  real32_T c5_d_u;
  const mxArray *c5_f_y = NULL;
  c5_Init_Bus c5_r2;
  uint8_T c5_b_hoistedGlobal;
  uint8_T c5_e_u;
  const mxArray *c5_g_y = NULL;
  uint8_T c5_c_hoistedGlobal;
  uint8_T c5_f_u;
  const mxArray *c5_h_y = NULL;
  uint8_T c5_d_hoistedGlobal;
  uint8_T c5_g_u;
  const mxArray *c5_i_y = NULL;
  uint8_T c5_e_hoistedGlobal;
  uint8_T c5_h_u;
  const mxArray *c5_j_y = NULL;
  const mxArray *c5_i_u;
  const mxArray *c5_k_y = NULL;
  const mxArray *c5_j_u;
  const mxArray *c5_l_y = NULL;
  const mxArray *c5_k_u;
  const mxArray *c5_m_y = NULL;
  boolean_T c5_l_u[1];
  const mxArray *c5_n_y = NULL;
  c5_st = NULL;
  c5_st = NULL;
  sf_mex_assign(&c5_subchartSimStateInfo, sf_get_high_sim_state
                (chartInstance->c5_subchartSimstruct), true);
  sf_mex_assign(&c5_b_subchartSimStateInfo, sf_get_high_sim_state
                (chartInstance->c5_b_subchartSimstruct), true);
  sf_mex_assign(&c5_c_subchartSimStateInfo, sf_get_high_sim_state
                (chartInstance->c5_c_subchartSimstruct), true);
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(11, 1), false);
  c5_hoistedGlobal = *chartInstance->c5_BT_status_out;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c5_b_u = *(real32_T *)&((char_T *)chartInstance->c5_PWM)[0];
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_c_y, c5_d_y, "left", "left", 0);
  c5_c_u = *(real32_T *)&((char_T *)chartInstance->c5_PWM)[4];
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_c_y, c5_e_y, "right", "right", 0);
  c5_d_u = *(real32_T *)&((char_T *)chartInstance->c5_PWM)[8];
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_c_y, c5_f_y, "tail", "tail", 0);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_r2.fall = *(boolean_T *)&((char_T *)chartInstance->c5_initFlags)[0];
  c5_r2.gyroInit = *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[4];
  c5_r2.gyroReset = *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[8];
  c5_r2.theta = *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[12];
  c5_r2.tail = *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[16];
  sf_mex_setcell(c5_y, 2, c5_d_emlrt_marshallOut(chartInstance, c5_r2));
  c5_b_hoistedGlobal = chartInstance->c5_current_mode_index;
  c5_e_u = c5_b_hoistedGlobal;
  c5_g_y = NULL;
  sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 3, c5_g_y);
  c5_c_hoistedGlobal = chartInstance->c5_is_active_c5_et_robocon;
  c5_f_u = c5_c_hoistedGlobal;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 4, c5_h_y);
  c5_d_hoistedGlobal = chartInstance->c5_is_c5_et_robocon;
  c5_g_u = c5_d_hoistedGlobal;
  c5_i_y = NULL;
  sf_mex_assign(&c5_i_y, sf_mex_create("y", &c5_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 5, c5_i_y);
  c5_e_hoistedGlobal = chartInstance->c5_is_normal_operation_modes;
  c5_h_u = c5_e_hoistedGlobal;
  c5_j_y = NULL;
  sf_mex_assign(&c5_j_y, sf_mex_create("y", &c5_h_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 6, c5_j_y);
  c5_i_u = sf_mex_dup(c5_subchartSimStateInfo);
  c5_k_y = NULL;
  sf_mex_assign(&c5_k_y, sf_mex_duplicatearraysafe(&c5_i_u), false);
  sf_mex_destroy(&c5_i_u);
  sf_mex_setcell(c5_y, 7, c5_k_y);
  c5_j_u = sf_mex_dup(c5_b_subchartSimStateInfo);
  c5_l_y = NULL;
  sf_mex_assign(&c5_l_y, sf_mex_duplicatearraysafe(&c5_j_u), false);
  sf_mex_destroy(&c5_j_u);
  sf_mex_setcell(c5_y, 8, c5_l_y);
  c5_k_u = sf_mex_dup(c5_c_subchartSimStateInfo);
  c5_m_y = NULL;
  sf_mex_assign(&c5_m_y, sf_mex_duplicatearraysafe(&c5_k_u), false);
  sf_mex_destroy(&c5_k_u);
  sf_mex_setcell(c5_y, 9, c5_m_y);
  c5_l_u[0] = chartInstance->c5_dataWrittenToVector[0];
  c5_n_y = NULL;
  sf_mex_assign(&c5_n_y, sf_mex_create("y", c5_l_u, 11, 0U, 1U, 0U, 1, 1), false);
  sf_mex_setcell(c5_y, 10, c5_n_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  c5_PWM_bus c5_r3;
  c5_Init_Bus c5_r4;
  boolean_T c5_bv0[1];
  c5_u = sf_mex_dup(c5_st);
  *chartInstance->c5_BT_status_out = c5_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 0)), "BT_status_out");
  c5_r3 = c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 1)),
    "PWM");
  *(real32_T *)&((char_T *)chartInstance->c5_PWM)[0] = c5_r3.left;
  *(real32_T *)&((char_T *)chartInstance->c5_PWM)[4] = c5_r3.right;
  *(real32_T *)&((char_T *)chartInstance->c5_PWM)[8] = c5_r3.tail;
  c5_r4 = c5_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 2)),
    "initFlags");
  *(boolean_T *)&((char_T *)chartInstance->c5_initFlags)[0] = c5_r4.fall;
  *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[4] = c5_r4.gyroInit;
  *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[8] = c5_r4.gyroReset;
  *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[12] = c5_r4.theta;
  *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[16] = c5_r4.tail;
  chartInstance->c5_current_mode_index = c5_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 3)), "current_mode_index");
  chartInstance->c5_is_active_c5_et_robocon = c5_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 4)),
     "is_active_c5_et_robocon");
  chartInstance->c5_is_c5_et_robocon = c5_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 5)), "is_c5_et_robocon");
  chartInstance->c5_is_normal_operation_modes = c5_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 6)),
     "is_normal_operation_modes");
  sf_mex_assign(&c5_subchartSimStateInfo, c5_q_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 7)), "subchartSimStateInfo"), true);
  sf_mex_assign(&c5_b_subchartSimStateInfo, c5_q_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 8)), "subchartSimStateInfo"), true);
  sf_mex_assign(&c5_c_subchartSimStateInfo, c5_q_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 9)), "subchartSimStateInfo"), true);
  c5_s_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 10)),
                        "dataWrittenToVector", c5_bv0);
  chartInstance->c5_dataWrittenToVector[0] = c5_bv0[0];
  sf_mex_assign(&chartInstance->c5_setSimStateSideEffectsInfo,
                c5_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 11)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c5_u);
  chartInstance->c5_doSetSimStateSideEffects = 1U;
  c5_update_debugger_state_c5_et_robocon(chartInstance);
  sf_set_high_sim_state(chartInstance->c5_subchartSimstruct, sf_mex_dup
                        (c5_subchartSimStateInfo));
  sf_set_high_sim_state(chartInstance->c5_b_subchartSimstruct, sf_mex_dup
                        (c5_b_subchartSimStateInfo));
  sf_set_high_sim_state(chartInstance->c5_c_subchartSimstruct, sf_mex_dup
                        (c5_c_subchartSimStateInfo));
  sf_mex_destroy(&c5_st);
}

static void c5_set_sim_state_side_effects_c5_et_robocon
  (SFc5_et_roboconInstanceStruct *chartInstance)
{
  if (chartInstance->c5_doSetSimStateSideEffects != 0) {
    if (chartInstance->c5_is_c5_et_robocon == c5_IN_emergency_stop) {
      chartInstance->c5_tp_emergency_stop = 1U;
    } else {
      chartInstance->c5_tp_emergency_stop = 0U;
    }

    if (chartInstance->c5_is_c5_et_robocon == c5_IN_normal_operation_modes) {
      chartInstance->c5_tp_normal_operation_modes = 1U;
    } else {
      chartInstance->c5_tp_normal_operation_modes = 0U;
    }

    if (chartInstance->c5_is_normal_operation_modes == c5_IN_WeShouldNotBeHere)
    {
      chartInstance->c5_tp_WeShouldNotBeHere = 1U;
    } else {
      chartInstance->c5_tp_WeShouldNotBeHere = 0U;
    }

    if (chartInstance->c5_is_normal_operation_modes ==
        c5_IN_gyro_calibration_mode) {
      chartInstance->c5_tp_gyro_calibration_mode = 1U;
    } else {
      chartInstance->c5_tp_gyro_calibration_mode = 0U;
    }

    if (chartInstance->c5_is_normal_operation_modes ==
        c5_IN_light_calibration_up) {
      chartInstance->c5_tp_light_calibration_up = 1U;
    } else {
      chartInstance->c5_tp_light_calibration_up = 0U;
    }

    if (chartInstance->c5_is_normal_operation_modes == c5_IN_line_following) {
      chartInstance->c5_tp_line_following = 1U;
    } else {
      chartInstance->c5_tp_line_following = 0U;
    }

    chartInstance->c5_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance)
{
  sf_mex_destroy(&c5_subchartSimStateInfo);
  sf_mex_destroy(&c5_b_subchartSimStateInfo);
  sf_mex_destroy(&c5_c_subchartSimStateInfo);
  sf_mex_destroy(&chartInstance->c5_setSimStateSideEffectsInfo);
}

static void sf_gateway_c5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance)
{
  void *c5_original_io_vars[1];
  void *c5_b_original_io_vars[1];
  void *c5_c_original_io_vars[1];
  void *c5_d_original_io_vars[1];
  void *c5_e_original_io_vars[1];
  void *c5_f_original_io_vars[1];
  void *c5_g_original_io_vars[1];
  void *c5_h_original_io_vars[1];
  void *c5_i_original_io_vars[1];
  void *c5_j_original_io_vars[1];
  void *c5_k_original_io_vars[1];
  void *c5_l_original_io_vars[1];
  void *c5_m_original_io_vars[1];
  void *c5_n_original_io_vars[1];
  void *c5_o_original_io_vars[1];
  c5_set_sim_state_side_effects_c5_et_robocon(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  sf_call_atomic_subchart_auto_fcn(65, (void *)
    chartInstance->c5_subchartSimstruct, (void *)&c5_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(65, (void *)
    chartInstance->c5_b_subchartSimstruct, (void *)&c5_b_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(65, (void *)
    chartInstance->c5_c_subchartSimstruct, (void *)&c5_c_original_io_vars);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c5_current_mode_index, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c5_BT_status_out, 8U);
  chartInstance->c5_sfEvent = CALL_EVENT;
  sf_call_atomic_subchart_auto_fcn(74, (void *)
    chartInstance->c5_subchartSimstruct, (void *)&c5_d_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(74, (void *)
    chartInstance->c5_b_subchartSimstruct, (void *)&c5_e_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(74, (void *)
    chartInstance->c5_c_subchartSimstruct, (void *)&c5_f_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(69, (void *)
    chartInstance->c5_subchartSimstruct, (void *)&c5_g_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(69, (void *)
    chartInstance->c5_b_subchartSimstruct, (void *)&c5_h_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(69, (void *)
    chartInstance->c5_c_subchartSimstruct, (void *)&c5_i_original_io_vars);
  c5_c5_et_robocon(chartInstance);
  sf_call_atomic_subchart_auto_fcn(75, (void *)
    chartInstance->c5_subchartSimstruct, (void *)&c5_j_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(75, (void *)
    chartInstance->c5_b_subchartSimstruct, (void *)&c5_k_original_io_vars);
  sf_call_atomic_subchart_auto_fcn(75, (void *)
    chartInstance->c5_c_subchartSimstruct, (void *)&c5_l_original_io_vars);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_et_roboconMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  if (chartInstance->c5_is_normal_operation_modes == c5_IN_gyro_calibration_mode)
  {
    sf_call_atomic_subchart_auto_fcn(76, (void *)
      chartInstance->c5_subchartSimstruct, (void *)&c5_m_original_io_vars);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_light_calibration_up)
  {
    sf_call_atomic_subchart_auto_fcn(76, (void *)
      chartInstance->c5_b_subchartSimstruct, (void *)&c5_n_original_io_vars);
  }

  if (chartInstance->c5_is_normal_operation_modes == c5_IN_line_following) {
    sf_call_atomic_subchart_auto_fcn(76, (void *)
      chartInstance->c5_c_subchartSimstruct, (void *)&c5_o_original_io_vars);
  }
}

static void mdl_start_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance)
{
  chartInstance->c5_subchartSimstruct = sf_get_subchart_simstruct((void *)
    chartInstance->S, "normal_operation_modes.gyro_calibration_mode");
  chartInstance->c5_b_subchartSimstruct = sf_get_subchart_simstruct((void *)
    chartInstance->S, "normal_operation_modes.light_calibration_up");
  chartInstance->c5_c_subchartSimstruct = sf_get_subchart_simstruct((void *)
    chartInstance->S, "normal_operation_modes.line_following");
}

static void c5_c5_et_robocon(SFc5_et_roboconInstanceStruct *chartInstance)
{
  void *c5_original_io_vars[1];
  void *c5_b_original_io_vars[1];
  void *c5_c_original_io_vars[1];
  uint32_T c5_debug_family_var_map[2];
  real_T c5_nargin = 0.0;
  real_T c5_nargout = 0.0;
  real32_T c5_hoistedGlobal;
  real32_T c5_u;
  const mxArray *c5_y = NULL;
  real_T c5_b_nargin = 0.0;
  real_T c5_b_nargout = 0.0;
  real_T c5_c_nargin = 0.0;
  real_T c5_c_nargout = 0.0;
  real_T c5_d_nargin = 0.0;
  real_T c5_d_nargout = 0.0;
  uint32_T c5_u0;
  uint32_T c5_b_debug_family_var_map[3];
  real_T c5_e_nargin = 0.0;
  real_T c5_e_nargout = 1.0;
  boolean_T c5_out;
  real_T c5_f_nargin = 0.0;
  real_T c5_f_nargout = 0.0;
  real_T c5_g_nargin = 0.0;
  real_T c5_g_nargout = 1.0;
  boolean_T c5_b_out;
  real_T c5_h_nargin = 0.0;
  real_T c5_h_nargout = 0.0;
  real_T c5_i_nargin = 0.0;
  real_T c5_i_nargout = 0.0;
  uint32_T c5_u1;
  real_T c5_j_nargin = 0.0;
  real_T c5_j_nargout = 1.0;
  boolean_T c5_c_out;
  real_T c5_k_nargin = 0.0;
  real_T c5_k_nargout = 0.0;
  real_T c5_l_nargin = 0.0;
  real_T c5_l_nargout = 0.0;
  real_T c5_m_nargin = 0.0;
  real_T c5_m_nargout = 1.0;
  boolean_T c5_d_out;
  int32_T exitg1;
  int32_T exitg2;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c5_sfEvent);
  if (chartInstance->c5_is_active_c5_et_robocon == 0U) {
    sf_call_atomic_subchart_auto_fcn(68, (void *)
      chartInstance->c5_subchartSimstruct, (void *)&c5_original_io_vars);
    sf_call_atomic_subchart_auto_fcn(68, (void *)
      chartInstance->c5_b_subchartSimstruct, (void *)&c5_b_original_io_vars);
    sf_call_atomic_subchart_auto_fcn(68, (void *)
      chartInstance->c5_c_subchartSimstruct, (void *)&c5_c_original_io_vars);
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 2U, chartInstance->c5_sfEvent);
    chartInstance->c5_is_active_c5_et_robocon = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c5_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c5_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_f_debug_family_names,
      c5_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 0U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 1U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    *(boolean_T *)&((char_T *)chartInstance->c5_initFlags)[0] =
      chartInstance->c5_Init_Bus0.fall;
    *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[4] =
      chartInstance->c5_Init_Bus0.gyroInit;
    *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[8] =
      chartInstance->c5_Init_Bus0.gyroReset;
    *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[12] =
      chartInstance->c5_Init_Bus0.theta;
    *(real32_T *)&((char_T *)chartInstance->c5_initFlags)[16] =
      chartInstance->c5_Init_Bus0.tail;
    *chartInstance->c5_BT_status_out = 0.0F;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c5_BT_status_out, 8U);
    sf_mex_printf("%s =\\n", "BT_status_out");
    c5_hoistedGlobal = *chartInstance->c5_BT_status_out;
    c5_u = c5_hoistedGlobal;
    c5_y = NULL;
    sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 1, 0U, 0U, 0U, 0), false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c5_y);
    _SFD_SYMBOL_SCOPE_POP();
    do {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_g_debug_family_names,
        c5_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      chartInstance->c5_current_mode_index = 0U;
      c5_updateDataWrittenToVector(chartInstance, 0U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c5_current_mode_index, 2U);
      _SFD_SYMBOL_SCOPE_POP();
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_h_debug_family_names,
        c5_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      c5_set_current_mode_status(chartInstance, 0,
        OperationModeStatusEnum_NOT_STARTED);
      ssUpdateDataStoreLog(chartInstance->S, 1);
      _SFD_SYMBOL_SCOPE_POP();
      do {
        exitg2 = 0;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_l_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 57U, 23, 18);
        c5_u0 = (uint32_T)chartInstance->c5_current_mode_index + 1U;
        if (CV_SATURATION_EVAL(5, 13, 0, 0, c5_u0 > 255U)) {
          c5_u0 = 255U;
        }

        chartInstance->c5_current_mode_index = (uint8_T)c5_u0;
        c5_updateDataWrittenToVector(chartInstance, 0U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c5_current_mode_index, 2U);
        _SFD_SYMBOL_SCOPE_POP();
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                     chartInstance->c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_m_debug_family_names,
          c5_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_e_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_e_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_out, 2U, c5_b_sf_marshallOut,
          c5_b_sf_marshallIn);
        c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 59U, 29, 18);
        c5_out = CV_EML_IF(15, 0, 0, 3.0 < (real_T)
                           chartInstance->c5_current_mode_index);
        _SFD_SYMBOL_SCOPE_POP();
        if (c5_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c5_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c5_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c5_sfEvent);
          _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
          exitg2 = 2;
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c5_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c5_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_n_debug_family_names,
            c5_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_f_nargin, 0U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_f_nargout, 1U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 61U, 34, 18);
          c5_set_current_mode(chartInstance, 0,
                              chartInstance->
                              c5_TRACK_MODE_LIST[_SFD_ARRAY_BOUNDS_CHECK(1U,
            (uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
            "Transition #97 in Chart \'Main Controller\' (#47): current_mode = TRACK_MODE_LIST( current_mode_index );\n                         "
            "                                       ^^^^^^^^^^^^^^^", (int32_T)
            (uint8_T)_SFD_INTEGER_CHECK(
            "Transition #97 in Chart \'Main Controller\' (#47): current_mode = TRACK_MODE_LIST( current_mode_index );\n                         "
            "                                                        ^^^^^^^^^^^^^^^^^^",
                                 (real_T)chartInstance->c5_current_mode_index),
            1, 3, 1, 0) - 1, 0, 2, 1, 0)]);
          ssUpdateDataStoreLog(chartInstance->S, 0);
          _SFD_SYMBOL_SCOPE_POP();
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
                       chartInstance->c5_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_o_debug_family_names,
            c5_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_g_nargin, 0U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_g_nargout, 1U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_out, 2U,
            c5_b_sf_marshallOut, c5_b_sf_marshallIn);
          c5_b_out = CV_EML_IF(19, 0, 0, c5_get_current_mode(chartInstance, 0) ==
                               OperationModeEnum_SKIP);
          _SFD_SYMBOL_SCOPE_POP();
          if (c5_b_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c5_sfEvent);
            _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
          } else {
            exitg2 = 1;
          }
        }
      } while (exitg2 == 0);
    } while (!(exitg2 == 1));

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c5_sfEvent);
    chartInstance->c5_is_c5_et_robocon = c5_IN_normal_operation_modes;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
    chartInstance->c5_tp_normal_operation_modes = 1U;
    c5_enter_internal_normal_operation_modes(chartInstance);
  } else {
    switch (chartInstance->c5_is_c5_et_robocon) {
     case c5_IN_emergency_stop:
      CV_CHART_EVAL(2, 0, 1);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c5_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c5_sfEvent);
      do {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_h_debug_family_names,
          c5_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_h_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_h_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        c5_set_current_mode_status(chartInstance, 0,
          OperationModeStatusEnum_NOT_STARTED);
        ssUpdateDataStoreLog(chartInstance->S, 1);
        _SFD_SYMBOL_SCOPE_POP();
        do {
          exitg1 = 0;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c5_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_l_debug_family_names,
            c5_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_i_nargin, 0U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_i_nargout, 1U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 57U, 23, 18);
          c5_u1 = (uint32_T)chartInstance->c5_current_mode_index + 1U;
          if (CV_SATURATION_EVAL(5, 13, 0, 0, c5_u1 > 255U)) {
            c5_u1 = 255U;
          }

          chartInstance->c5_current_mode_index = (uint8_T)c5_u1;
          c5_updateDataWrittenToVector(chartInstance, 0U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c5_current_mode_index, 2U);
          _SFD_SYMBOL_SCOPE_POP();
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                       chartInstance->c5_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_m_debug_family_names,
            c5_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_j_nargin, 0U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_j_nargout, 1U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_out, 2U,
            c5_b_sf_marshallOut, c5_b_sf_marshallIn);
          c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 59U, 29, 18);
          c5_c_out = CV_EML_IF(15, 0, 0, 3.0 < (real_T)
                               chartInstance->c5_current_mode_index);
          _SFD_SYMBOL_SCOPE_POP();
          if (c5_c_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c5_sfEvent);
            _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_g_debug_family_names,
              c5_debug_family_var_map);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_k_nargin, 0U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_k_nargout, 1U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            chartInstance->c5_current_mode_index = 0U;
            c5_updateDataWrittenToVector(chartInstance, 0U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c5_current_mode_index,
                                  2U);
            _SFD_SYMBOL_SCOPE_POP();
            _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
            exitg1 = 2;
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c5_sfEvent);
            _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_n_debug_family_names,
              c5_debug_family_var_map);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_l_nargin, 0U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_l_nargout, 1U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 61U, 34, 18);
            c5_set_current_mode(chartInstance, 0,
                                chartInstance->
                                c5_TRACK_MODE_LIST[_SFD_ARRAY_BOUNDS_CHECK(1U,
              (uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
              "Transition #97 in Chart \'Main Controller\' (#47): current_mode = TRACK_MODE_LIST( current_mode_index );\n                         "
              "                                       ^^^^^^^^^^^^^^^", (int32_T)
                                  (uint8_T)_SFD_INTEGER_CHECK(
              "Transition #97 in Chart \'Main Controller\' (#47): current_mode = TRACK_MODE_LIST( current_mode_index );\n                         "
              "                                                        ^^^^^^^^^^^^^^^^^^",
                                   (real_T)chartInstance->c5_current_mode_index),
              1, 3, 1, 0) - 1, 0, 2, 1, 0)]);
            ssUpdateDataStoreLog(chartInstance->S, 0);
            _SFD_SYMBOL_SCOPE_POP();
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
                         chartInstance->c5_sfEvent);
            _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_o_debug_family_names,
              c5_b_debug_family_var_map);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_m_nargin, 0U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_m_nargout, 1U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_out, 2U,
              c5_b_sf_marshallOut, c5_b_sf_marshallIn);
            c5_d_out = CV_EML_IF(19, 0, 0, c5_get_current_mode(chartInstance, 0)
                                 == OperationModeEnum_SKIP);
            _SFD_SYMBOL_SCOPE_POP();
            if (c5_d_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c5_sfEvent);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c5_sfEvent);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c5_sfEvent);
              _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
            } else {
              exitg1 = 1;
            }
          }
        } while (exitg1 == 0);
      } while (!(exitg1 == 1));

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c5_sfEvent);
      chartInstance->c5_tp_emergency_stop = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
      chartInstance->c5_is_c5_et_robocon = c5_IN_normal_operation_modes;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
      chartInstance->c5_tp_normal_operation_modes = 1U;
      c5_enter_internal_normal_operation_modes(chartInstance);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c5_sfEvent);
      break;

     case c5_IN_normal_operation_modes:
      CV_CHART_EVAL(2, 0, 2);
      c5_normal_operation_modes(chartInstance);
      break;

     default:
      CV_CHART_EVAL(2, 0, 0);
      chartInstance->c5_is_c5_et_robocon = c5_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c5_sfEvent);
}

static void initSimStructsc5_et_robocon(SFc5_et_roboconInstanceStruct
  *chartInstance)
{
  chartInstance->c5_subchartSimstruct = sf_get_subchart_simstruct((void *)
    chartInstance->S, "normal_operation_modes.gyro_calibration_mode");
  chartInstance->c5_b_subchartSimstruct = sf_get_subchart_simstruct((void *)
    chartInstance->S, "normal_operation_modes.light_calibration_up");
  chartInstance->c5_c_subchartSimstruct = sf_get_subchart_simstruct((void *)
    chartInstance->S, "normal_operation_modes.line_following");
}

static void c5_enter_internal_normal_operation_modes
  (SFc5_et_roboconInstanceStruct *chartInstance)
{
  uint32_T c5_debug_family_var_map[2];
  real_T c5_nargin = 0.0;
  real_T c5_nargout = 0.0;
  uint32_T c5_b_debug_family_var_map[3];
  real_T c5_b_nargin = 0.0;
  real_T c5_b_nargout = 1.0;
  boolean_T c5_out;
  void *c5_original_io_vars[1];
  real_T c5_c_nargin = 0.0;
  real_T c5_c_nargout = 1.0;
  boolean_T c5_b_out;
  void *c5_b_original_io_vars[1];
  real_T c5_d_nargin = 0.0;
  real_T c5_d_nargout = 1.0;
  boolean_T c5_c_out;
  void *c5_c_original_io_vars[1];
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_b_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 0U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 1U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  c5_set_current_mode_status(chartInstance, 0,
    OperationModeStatusEnum_IN_PROGRESS);
  ssUpdateDataStoreLog(chartInstance->S, 1);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_c_debug_family_names,
    c5_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargin, 0U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargout, 1U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_out, 2U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  c5_out = CV_EML_IF(1, 0, 0, c5_get_current_mode(chartInstance, 0) ==
                     OperationModeEnum_GYRO_CALIBRATION);
  _SFD_SYMBOL_SCOPE_POP();
  if (c5_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
    chartInstance->c5_is_normal_operation_modes = c5_IN_gyro_calibration_mode;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c5_sfEvent);
    chartInstance->c5_tp_gyro_calibration_mode = 1U;
    sf_call_atomic_subchart_auto_fcn(63, (void *)
      chartInstance->c5_subchartSimstruct, (void *)&c5_original_io_vars);
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 24U,
                 chartInstance->c5_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_d_debug_family_names,
      c5_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargin, 0U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargout, 1U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_out, 2U, c5_b_sf_marshallOut,
      c5_b_sf_marshallIn);
    c5_b_out = CV_EML_IF(24, 0, 0, c5_get_current_mode(chartInstance, 0) ==
                         OperationModeEnum_LIGHT_CALIBRATION_UP);
    _SFD_SYMBOL_SCOPE_POP();
    if (c5_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c5_sfEvent);
      chartInstance->c5_is_normal_operation_modes = c5_IN_light_calibration_up;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c5_sfEvent);
      chartInstance->c5_tp_light_calibration_up = 1U;
      sf_call_atomic_subchart_auto_fcn(63, (void *)
        chartInstance->c5_b_subchartSimstruct, (void *)&c5_b_original_io_vars);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c5_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c5_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 26U,
                   chartInstance->c5_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_e_debug_family_names,
        c5_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargin, 0U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargout, 1U, c5_sf_marshallOut,
        c5_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_out, 2U, c5_b_sf_marshallOut,
        c5_b_sf_marshallIn);
      c5_c_out = CV_EML_IF(26, 0, 0, c5_get_current_mode(chartInstance, 0) ==
                           OperationModeEnum_SEE_SAW_MARIO);
      _SFD_SYMBOL_SCOPE_POP();
      if (c5_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U, chartInstance->c5_sfEvent);
        chartInstance->c5_is_normal_operation_modes = c5_IN_line_following;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c5_sfEvent);
        chartInstance->c5_tp_line_following = 1U;
        sf_call_atomic_subchart_auto_fcn(63, (void *)
          chartInstance->c5_c_subchartSimstruct, (void *)&c5_c_original_io_vars);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c5_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c5_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c5_sfEvent);
        chartInstance->c5_is_normal_operation_modes = c5_IN_WeShouldNotBeHere;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
        chartInstance->c5_tp_WeShouldNotBeHere = 1U;
      }
    }
  }
}

static void c5_normal_operation_modes(SFc5_et_roboconInstanceStruct
  *chartInstance)
{
  uint32_T c5_debug_family_var_map[3];
  real_T c5_nargin = 0.0;
  real_T c5_nargout = 1.0;
  boolean_T c5_out;
  uint32_T c5_b_debug_family_var_map[2];
  real_T c5_b_nargin = 0.0;
  real_T c5_b_nargout = 0.0;
  real_T c5_c_nargin = 0.0;
  real_T c5_c_nargout = 0.0;
  uint16_T c5_u2;
  void *c5_inputVarPtrs[1];
  int32_T c5_inputVarSizes[1];
  real_T c5_d_nargin = 0.0;
  real_T c5_d_nargout = 1.0;
  boolean_T c5_b_out;
  real_T c5_e_nargin = 0.0;
  real_T c5_e_nargout = 0.0;
  real_T c5_f_nargin = 0.0;
  real_T c5_f_nargout = 0.0;
  uint32_T c5_u3;
  real_T c5_g_nargin = 0.0;
  real_T c5_g_nargout = 1.0;
  boolean_T c5_c_out;
  real_T c5_h_nargin = 0.0;
  real_T c5_h_nargout = 0.0;
  real_T c5_i_nargin = 0.0;
  real_T c5_i_nargout = 0.0;
  real_T c5_j_nargin = 0.0;
  real_T c5_j_nargout = 1.0;
  boolean_T c5_d_out;
  void *c5_original_io_vars[1];
  void *c5_b_original_io_vars[1];
  void *c5_c_original_io_vars[1];
  int32_T exitg1;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 21U, chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_j_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 0U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 1U, c5_sf_marshallOut,
    c5_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_out, 2U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  c5_out = CV_EML_IF(21, 0, 0, *(real32_T *)&((char_T *)
    chartInstance->c5_sensors)[36] != 0.0F);
  _SFD_SYMBOL_SCOPE_POP();
  if (c5_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c5_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_k_debug_family_names,
      c5_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargin, 0U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_nargout, 1U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    c5_set_current_mode_status(chartInstance, 0, OperationModeStatusEnum_ABORTED);
    ssUpdateDataStoreLog(chartInstance->S, 1);
    _SFD_SYMBOL_SCOPE_POP();
    c5_exit_internal_normal_operation_modes(chartInstance);
    chartInstance->c5_tp_normal_operation_modes = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
    chartInstance->c5_is_c5_et_robocon = c5_IN_emergency_stop;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
    chartInstance->c5_tp_emergency_stop = 1U;
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_debug_family_names,
      c5_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargin, 0U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_nargout, 1U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    c5_u2 = 9999U;
    c5_inputVarPtrs[0U] = (void *)&c5_u2;
    c5_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
    sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                         c5_inputVarPtrs, (void *)c5_inputVarSizes, 0, NULL,
                         NULL);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                 chartInstance->c5_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_i_debug_family_names,
      c5_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargin, 0U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_nargout, 1U, c5_sf_marshallOut,
      c5_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_b_out, 2U, c5_b_sf_marshallOut,
      c5_b_sf_marshallIn);
    c5_b_out = CV_EML_IF(11, 0, 0, c5_get_current_mode_status(chartInstance, 0) ==
                         OperationModeStatusEnum_SUCCESSFULLY_COMPLETED);
    _SFD_SYMBOL_SCOPE_POP();
    if (c5_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c5_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c5_sfEvent);
      do {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c5_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_h_debug_family_names,
          c5_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_e_nargin, 0U, c5_sf_marshallOut,
          c5_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_e_nargout, 1U,
          c5_sf_marshallOut, c5_sf_marshallIn);
        c5_set_current_mode_status(chartInstance, 0,
          OperationModeStatusEnum_NOT_STARTED);
        ssUpdateDataStoreLog(chartInstance->S, 1);
        _SFD_SYMBOL_SCOPE_POP();
        do {
          exitg1 = 0;
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c5_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_l_debug_family_names,
            c5_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_f_nargin, 0U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_f_nargout, 1U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 57U, 23, 18);
          c5_u3 = (uint32_T)chartInstance->c5_current_mode_index + 1U;
          if (CV_SATURATION_EVAL(5, 13, 0, 0, c5_u3 > 255U)) {
            c5_u3 = 255U;
          }

          chartInstance->c5_current_mode_index = (uint8_T)c5_u3;
          c5_updateDataWrittenToVector(chartInstance, 0U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c5_current_mode_index, 2U);
          _SFD_SYMBOL_SCOPE_POP();
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                       chartInstance->c5_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_m_debug_family_names,
            c5_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_g_nargin, 0U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_g_nargout, 1U,
            c5_sf_marshallOut, c5_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_c_out, 2U,
            c5_b_sf_marshallOut, c5_b_sf_marshallIn);
          c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 59U, 29, 18);
          c5_c_out = CV_EML_IF(15, 0, 0, 3.0 < (real_T)
                               chartInstance->c5_current_mode_index);
          _SFD_SYMBOL_SCOPE_POP();
          if (c5_c_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c5_sfEvent);
            _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_g_debug_family_names,
              c5_b_debug_family_var_map);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_h_nargin, 0U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_h_nargout, 1U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            chartInstance->c5_current_mode_index = 0U;
            c5_updateDataWrittenToVector(chartInstance, 0U);
            _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c5_current_mode_index,
                                  2U);
            _SFD_SYMBOL_SCOPE_POP();
            _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
            exitg1 = 2;
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c5_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c5_sfEvent);
            _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c5_n_debug_family_names,
              c5_b_debug_family_var_map);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_i_nargin, 0U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_i_nargout, 1U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            c5_errorIfDataNotWrittenToFcn(chartInstance, 0U, 2U, 61U, 34, 18);
            c5_set_current_mode(chartInstance, 0,
                                chartInstance->
                                c5_TRACK_MODE_LIST[_SFD_ARRAY_BOUNDS_CHECK(1U,
              (uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
              "Transition #97 in Chart \'Main Controller\' (#47): current_mode = TRACK_MODE_LIST( current_mode_index );\n                         "
              "                                       ^^^^^^^^^^^^^^^", (int32_T)
                                  (uint8_T)_SFD_INTEGER_CHECK(
              "Transition #97 in Chart \'Main Controller\' (#47): current_mode = TRACK_MODE_LIST( current_mode_index );\n                         "
              "                                                        ^^^^^^^^^^^^^^^^^^",
                                   (real_T)chartInstance->c5_current_mode_index),
              1, 3, 1, 0) - 1, 0, 2, 1, 0)]);
            ssUpdateDataStoreLog(chartInstance->S, 0);
            _SFD_SYMBOL_SCOPE_POP();
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 19U,
                         chartInstance->c5_sfEvent);
            _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c5_o_debug_family_names,
              c5_debug_family_var_map);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_j_nargin, 0U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_j_nargout, 1U,
              c5_sf_marshallOut, c5_sf_marshallIn);
            _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_d_out, 2U,
              c5_b_sf_marshallOut, c5_b_sf_marshallIn);
            c5_d_out = CV_EML_IF(19, 0, 0, c5_get_current_mode(chartInstance, 0)
                                 == OperationModeEnum_SKIP);
            _SFD_SYMBOL_SCOPE_POP();
            if (c5_d_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c5_sfEvent);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c5_sfEvent);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c5_sfEvent);
              _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
            } else {
              exitg1 = 1;
            }
          }
        } while (exitg1 == 0);
      } while (!(exitg1 == 1));

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c5_sfEvent);
      c5_exit_internal_normal_operation_modes(chartInstance);
      chartInstance->c5_tp_normal_operation_modes = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
      chartInstance->c5_is_c5_et_robocon = c5_IN_normal_operation_modes;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
      chartInstance->c5_tp_normal_operation_modes = 1U;
      c5_enter_internal_normal_operation_modes(chartInstance);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                   chartInstance->c5_sfEvent);
      switch (chartInstance->c5_is_normal_operation_modes) {
       case c5_IN_WeShouldNotBeHere:
        CV_STATE_EVAL(1, 0, 1);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                     chartInstance->c5_sfEvent);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c5_sfEvent);
        break;

       case c5_IN_gyro_calibration_mode:
        CV_STATE_EVAL(1, 0, 2);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                     chartInstance->c5_sfEvent);
        sf_call_atomic_subchart_auto_fcn(62, (void *)
          chartInstance->c5_subchartSimstruct, (void *)&c5_original_io_vars);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
        break;

       case c5_IN_light_calibration_up:
        CV_STATE_EVAL(1, 0, 3);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                     chartInstance->c5_sfEvent);
        sf_call_atomic_subchart_auto_fcn(62, (void *)
          chartInstance->c5_b_subchartSimstruct, (void *)&c5_b_original_io_vars);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
        break;

       case c5_IN_line_following:
        CV_STATE_EVAL(1, 0, 4);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                     chartInstance->c5_sfEvent);
        sf_call_atomic_subchart_auto_fcn(62, (void *)
          chartInstance->c5_c_subchartSimstruct, (void *)&c5_c_original_io_vars);
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c5_sfEvent);
        break;

       default:
        CV_STATE_EVAL(1, 0, 0);
        chartInstance->c5_is_normal_operation_modes = c5_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c5_sfEvent);
}

static void c5_exit_internal_normal_operation_modes
  (SFc5_et_roboconInstanceStruct *chartInstance)
{
  void *c5_original_io_vars[1];
  void *c5_b_original_io_vars[1];
  void *c5_c_original_io_vars[1];
  switch (chartInstance->c5_is_normal_operation_modes) {
   case c5_IN_WeShouldNotBeHere:
    CV_STATE_EVAL(1, 1, 1);
    chartInstance->c5_tp_WeShouldNotBeHere = 0U;
    chartInstance->c5_is_normal_operation_modes = c5_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
    break;

   case c5_IN_gyro_calibration_mode:
    CV_STATE_EVAL(1, 1, 2);
    sf_call_atomic_subchart_auto_fcn(64, (void *)
      chartInstance->c5_subchartSimstruct, (void *)&c5_original_io_vars);
    chartInstance->c5_tp_gyro_calibration_mode = 0U;
    chartInstance->c5_is_normal_operation_modes = c5_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c5_sfEvent);
    break;

   case c5_IN_light_calibration_up:
    CV_STATE_EVAL(1, 1, 3);
    sf_call_atomic_subchart_auto_fcn(64, (void *)
      chartInstance->c5_b_subchartSimstruct, (void *)&c5_b_original_io_vars);
    chartInstance->c5_tp_light_calibration_up = 0U;
    chartInstance->c5_is_normal_operation_modes = c5_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c5_sfEvent);
    break;

   case c5_IN_line_following:
    CV_STATE_EVAL(1, 1, 4);
    sf_call_atomic_subchart_auto_fcn(64, (void *)
      chartInstance->c5_c_subchartSimstruct, (void *)&c5_c_original_io_vars);
    chartInstance->c5_tp_line_following = 0U;
    chartInstance->c5_is_normal_operation_modes = c5_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c5_sfEvent);
    break;

   default:
    CV_STATE_EVAL(1, 1, 0);
    chartInstance->c5_is_normal_operation_modes = c5_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
    break;
  }
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  (void)c5_chartNumber;
  (void)c5_instanceNumber;
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nargout;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_nargout = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  boolean_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(boolean_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static boolean_T c5_b_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  boolean_T c5_y;
  boolean_T c5_b0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_b0, 1, 11, 0U, 0, 0U, 0);
  c5_y = c5_b0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_sf_internal_predicateOutput;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  boolean_T c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_sf_internal_predicateOutput = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_sf_internal_predicateOutput), &c5_thisId);
  sf_mex_destroy(&c5_sf_internal_predicateOutput);
  *(boolean_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real32_T c5_c_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_sf_internal_predicateOutput, const char_T
  *c5_identifier)
{
  real32_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_sf_internal_predicateOutput), &c5_thisId);
  sf_mex_destroy(&c5_sf_internal_predicateOutput);
  return c5_y;
}

static real32_T c5_d_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real32_T c5_y;
  real32_T c5_f0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_f0, 1, 1, 0U, 0, 0U, 0);
  c5_y = c5_f0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_sf_internal_predicateOutput;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real32_T c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_sf_internal_predicateOutput = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_sf_internal_predicateOutput), &c5_thisId);
  sf_mex_destroy(&c5_sf_internal_predicateOutput);
  *(real32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

const mxArray *sf_c5_et_robocon_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_createstruct("structure", 2, 2, 1),
                false);
  c5_info_helper(&c5_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c5_nameCaptureInfo);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(const mxArray **c5_info)
{
  const mxArray *c5_rhs0 = NULL;
  const mxArray *c5_lhs0 = NULL;
  const mxArray *c5_rhs1 = NULL;
  const mxArray *c5_lhs1 = NULL;
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("OperationModeStatusEnum"),
                  "name", "name", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[N]C:/ETRobocon2014/Repository/data_types/enumerations/OperationModeStatusEnum.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1409161942U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c5_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("OperationModeEnum"), "name",
                  "name", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[N]C:/ETRobocon2014/Repository/data_types/enumerations/OperationModeEnum.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1409161942U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c5_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs1), "lhs", "lhs", 1);
  sf_mex_destroy(&c5_rhs0);
  sf_mex_destroy(&c5_lhs0);
  sf_mex_destroy(&c5_rhs1);
  sf_mex_destroy(&c5_lhs1);
}

static const mxArray *c5_emlrt_marshallOut(const char * c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c5_u)), false);
  return c5_y;
}

static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 7, 0U, 0U, 0U, 0), false);
  return c5_y;
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_e_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i1;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i1, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i1;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint8_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint8_T c5_f_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_b_tp_emergency_stop, const char_T
  *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_tp_emergency_stop),
    &c5_thisId);
  sf_mex_destroy(&c5_b_tp_emergency_stop);
  return c5_y;
}

static uint8_T c5_g_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u4;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u4, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u4;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_tp_emergency_stop;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_b_tp_emergency_stop = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_tp_emergency_stop),
    &c5_thisId);
  sf_mex_destroy(&c5_b_tp_emergency_stop);
  *(uint8_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_PWM_bus_io(void *chartInstanceVoid, void *c5_pData)
{
  const mxArray *c5_mxVal = NULL;
  c5_PWM_bus c5_tmp;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxVal = NULL;
  c5_tmp.left = *(real32_T *)&((char_T *)(c5_PWM_bus *)c5_pData)[0];
  c5_tmp.right = *(real32_T *)&((char_T *)(c5_PWM_bus *)c5_pData)[4];
  c5_tmp.tail = *(real32_T *)&((char_T *)(c5_PWM_bus *)c5_pData)[8];
  sf_mex_assign(&c5_mxVal, c5_f_sf_marshallOut(chartInstance, &c5_tmp), false);
  return c5_mxVal;
}

static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  c5_PWM_bus c5_u;
  const mxArray *c5_y = NULL;
  real32_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  real32_T c5_c_u;
  const mxArray *c5_c_y = NULL;
  real32_T c5_d_u;
  const mxArray *c5_d_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(c5_PWM_bus *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c5_b_u = c5_u.left;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_b_y, "left", "left", 0);
  c5_c_u = c5_u.right;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_c_y, "right", "right", 0);
  c5_d_u = c5_u.tail;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_d_y, "tail", "tail", 0);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static c5_PWM_bus c5_h_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_b_PWM, const char_T *c5_identifier)
{
  c5_PWM_bus c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_PWM), &c5_thisId);
  sf_mex_destroy(&c5_b_PWM);
  return c5_y;
}

static c5_PWM_bus c5_i_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  c5_PWM_bus c5_y;
  emlrtMsgIdentifier c5_thisId;
  static const char * c5_fieldNames[3] = { "left", "right", "tail" };

  c5_thisId.fParent = c5_parentId;
  sf_mex_check_struct(c5_parentId, c5_u, 3, c5_fieldNames, 0U, NULL);
  c5_thisId.fIdentifier = "left";
  c5_y.left = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "left", "left", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "right";
  c5_y.right = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "right", "right", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "tail";
  c5_y.tail = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "tail", "tail", 0)), &c5_thisId);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_PWM;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  c5_PWM_bus c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_b_PWM = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_PWM), &c5_thisId);
  sf_mex_destroy(&c5_b_PWM);
  *(c5_PWM_bus *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i2;
  c5_OperationModeEnum c5_u[3];
  const mxArray *c5_y = NULL;
  static const int32_T c5_enumValues[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15 };

  static const char * c5_enumNames[16] = { "SKIP", "GYRO_CALIBRATION",
    "LIGHT_CALIBRATION_ON_TAIL", "LIGHT_CALIBRATION_UP", "LINE_TRACKING",
    "SEE_SAW", "LIMBO", "SEE_SAW_MARIO", "SEE_SAW_PRINCESS", "YOSHI", "PARKING",
    "LIGHT_CALIBRATION_LIMBO", "LINE_TRACKING_LIMBO", "LINE_TRACKING_ON_MAP",
    "LIGHT_CALIBRATION_UP_FLASHING", "LIGHT_CALIBRATION_UP_FLASHING_ON_MAP" };

  int32_T c5_i3;
  int32_T c5_b_u[3];
  const mxArray *c5_b_y = NULL;
  const mxArray *c5_m2 = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i2 = 0; c5_i2 < 3; c5_i2++) {
    c5_u[c5_i2] = (*(c5_OperationModeEnum (*)[3])c5_inData)[c5_i2];
  }

  c5_y = NULL;
  sf_mex_check_enum("OperationModeEnum", 16, c5_enumNames, c5_enumValues);
  for (c5_i3 = 0; c5_i3 < 3; c5_i3++) {
    c5_b_u[c5_i3] = (int32_T)c5_u[c5_i3];
  }

  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_b_u, 6, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c5_m2, c5_b_y, false);
  sf_mex_assign(&c5_y, sf_mex_create_enum("OperationModeEnum", c5_m2), false);
  sf_mex_destroy(&c5_m2);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_j_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  c5_OperationModeEnum c5_y[3])
{
  static uint32_T c5_uv0[1] = { 3U };

  uint32_T c5_uv1[1];
  static const int32_T c5_enumValues[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15 };

  static const char * c5_enumNames[16] = { "SKIP", "GYRO_CALIBRATION",
    "LIGHT_CALIBRATION_ON_TAIL", "LIGHT_CALIBRATION_UP", "LINE_TRACKING",
    "SEE_SAW", "LIMBO", "SEE_SAW_MARIO", "SEE_SAW_PRINCESS", "YOSHI", "PARKING",
    "LIGHT_CALIBRATION_LIMBO", "LINE_TRACKING_LIMBO", "LINE_TRACKING_ON_MAP",
    "LIGHT_CALIBRATION_UP_FLASHING", "LIGHT_CALIBRATION_UP_FLASHING_ON_MAP" };

  c5_OperationModeEnum (*c5_r5)[3];
  int32_T c5_i4;
  (void)chartInstance;
  c5_uv1[0] = c5_uv0[0];
  sf_mex_check_enum("OperationModeEnum", 16, c5_enumNames, c5_enumValues);
  sf_mex_check_builtin(c5_parentId, c5_u, "OperationModeEnum", 0, 1U, c5_uv1);
  c5_r5 = (c5_OperationModeEnum (*)[3])c5_y;
  for (c5_i4 = 0; c5_i4 < 3; c5_i4++) {
    (*c5_r5)[c5_i4] = (c5_OperationModeEnum)sf_mex_get_enum_element(c5_u, c5_i4);
  }

  sf_mex_destroy(&c5_u);
}

static void c5_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_TRACK_MODE_LIST;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  c5_OperationModeEnum c5_y[3];
  int32_T c5_i5;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_b_TRACK_MODE_LIST = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_TRACK_MODE_LIST),
                        &c5_thisId, c5_y);
  sf_mex_destroy(&c5_b_TRACK_MODE_LIST);
  for (c5_i5 = 0; c5_i5 < 3; c5_i5++) {
    (*(c5_OperationModeEnum (*)[3])c5_outData)[c5_i5] = c5_y[c5_i5];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  c5_OperationModeEnum c5_u;
  const mxArray *c5_y = NULL;
  static const int32_T c5_enumValues[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15 };

  static const char * c5_enumNames[16] = { "SKIP", "GYRO_CALIBRATION",
    "LIGHT_CALIBRATION_ON_TAIL", "LIGHT_CALIBRATION_UP", "LINE_TRACKING",
    "SEE_SAW", "LIMBO", "SEE_SAW_MARIO", "SEE_SAW_PRINCESS", "YOSHI", "PARKING",
    "LIGHT_CALIBRATION_LIMBO", "LINE_TRACKING_LIMBO", "LINE_TRACKING_ON_MAP",
    "LIGHT_CALIBRATION_UP_FLASHING", "LIGHT_CALIBRATION_UP_FLASHING_ON_MAP" };

  int32_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  const mxArray *c5_m3 = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(c5_OperationModeEnum *)c5_inData;
  c5_y = NULL;
  sf_mex_check_enum("OperationModeEnum", 16, c5_enumNames, c5_enumValues);
  c5_b_u = (int32_T)c5_u;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_m3, c5_b_y, false);
  sf_mex_assign(&c5_y, sf_mex_create_enum("OperationModeEnum", c5_m3), false);
  sf_mex_destroy(&c5_m3);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static c5_OperationModeEnum c5_k_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *
  chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  c5_OperationModeEnum c5_y;
  static const int32_T c5_enumValues[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15 };

  static const char * c5_enumNames[16] = { "SKIP", "GYRO_CALIBRATION",
    "LIGHT_CALIBRATION_ON_TAIL", "LIGHT_CALIBRATION_UP", "LINE_TRACKING",
    "SEE_SAW", "LIMBO", "SEE_SAW_MARIO", "SEE_SAW_PRINCESS", "YOSHI", "PARKING",
    "LIGHT_CALIBRATION_LIMBO", "LINE_TRACKING_LIMBO", "LINE_TRACKING_ON_MAP",
    "LIGHT_CALIBRATION_UP_FLASHING", "LIGHT_CALIBRATION_UP_FLASHING_ON_MAP" };

  (void)chartInstance;
  sf_mex_check_enum("OperationModeEnum", 16, c5_enumNames, c5_enumValues);
  sf_mex_check_builtin(c5_parentId, c5_u, "OperationModeEnum", 0, 0U, NULL);
  c5_y = (c5_OperationModeEnum)sf_mex_get_enum_element(c5_u, 0);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_current_mode;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  c5_OperationModeEnum c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_current_mode = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_current_mode),
    &c5_thisId);
  sf_mex_destroy(&c5_current_mode);
  *(c5_OperationModeEnum *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_states_bus_io(void *chartInstanceVoid, void *c5_pData)
{
  const mxArray *c5_mxVal = NULL;
  c5_States_Bus c5_tmp;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxVal = NULL;
  c5_tmp.balancerStates.theta = *(real32_T *)&((char_T *)(c5_Balancer_States_Bus
    *)&((char_T *)(c5_States_Bus *)c5_pData)[0])[0];
  c5_tmp.balancerStates.psi = *(real32_T *)&((char_T *)(c5_Balancer_States_Bus *)
    &((char_T *)(c5_States_Bus *)c5_pData)[0])[4];
  c5_tmp.balancerStates.theta_dot = *(real32_T *)&((char_T *)
    (c5_Balancer_States_Bus *)&((char_T *)(c5_States_Bus *)c5_pData)[0])[8];
  c5_tmp.balancerStates.psi_dot = *(real32_T *)&((char_T *)
    (c5_Balancer_States_Bus *)&((char_T *)(c5_States_Bus *)c5_pData)[0])[12];
  c5_tmp.balancerStates.int_theta = *(real32_T *)&((char_T *)
    (c5_Balancer_States_Bus *)&((char_T *)(c5_States_Bus *)c5_pData)[0])[16];
  c5_tmp.phi = *(real32_T *)&((char_T *)(c5_States_Bus *)c5_pData)[24];
  c5_tmp.phi_dot = *(real32_T *)&((char_T *)(c5_States_Bus *)c5_pData)[28];
  c5_tmp.theta_dot_dot = *(real32_T *)&((char_T *)(c5_States_Bus *)c5_pData)[32];
  sf_mex_assign(&c5_mxVal, c5_i_sf_marshallOut(chartInstance, &c5_tmp), false);
  return c5_mxVal;
}

static const mxArray *c5_c_emlrt_marshallOut(SFc5_et_roboconInstanceStruct
  *chartInstance, const c5_Balancer_States_Bus c5_u)
{
  const mxArray *c5_y = NULL;
  real32_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  real32_T c5_c_u;
  const mxArray *c5_c_y = NULL;
  real32_T c5_d_u;
  const mxArray *c5_d_y = NULL;
  real32_T c5_e_u;
  const mxArray *c5_e_y = NULL;
  real32_T c5_f_u;
  const mxArray *c5_f_y = NULL;
  (void)chartInstance;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c5_b_u = c5_u.theta;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_b_y, "theta", "theta", 0);
  c5_c_u = c5_u.psi;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_c_y, "psi", "psi", 0);
  c5_d_u = c5_u.theta_dot;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_d_y, "theta_dot", "theta_dot", 0);
  c5_e_u = c5_u.psi_dot;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_e_y, "psi_dot", "psi_dot", 0);
  c5_f_u = c5_u.int_theta;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_f_y, "int_theta", "int_theta", 0);
  return c5_y;
}

static const mxArray *c5_i_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  c5_States_Bus c5_u;
  const mxArray *c5_y = NULL;
  real32_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  real32_T c5_c_u;
  const mxArray *c5_c_y = NULL;
  real32_T c5_d_u;
  const mxArray *c5_d_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(c5_States_Bus *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  sf_mex_addfield(c5_y, c5_c_emlrt_marshallOut(chartInstance,
    c5_u.balancerStates), "balancerStates", "balancerStates", 0);
  c5_b_u = c5_u.phi;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_b_y, "phi", "phi", 0);
  c5_c_u = c5_u.phi_dot;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_c_y, "phi_dot", "phi_dot", 0);
  c5_d_u = c5_u.theta_dot_dot;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_d_y, "theta_dot_dot", "theta_dot_dot", 0);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_j_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  c5_OperationModeStatusEnum c5_u;
  const mxArray *c5_y = NULL;
  static const int32_T c5_enumValues[4] = { 0, 1, 2, 3 };

  static const char * c5_enumNames[4] = { "NOT_STARTED", "IN_PROGRESS",
    "SUCCESSFULLY_COMPLETED", "ABORTED" };

  int32_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  const mxArray *c5_m4 = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(c5_OperationModeStatusEnum *)c5_inData;
  c5_y = NULL;
  sf_mex_check_enum("OperationModeStatusEnum", 4, c5_enumNames, c5_enumValues);
  c5_b_u = (int32_T)c5_u;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_m4, c5_b_y, false);
  sf_mex_assign(&c5_y, sf_mex_create_enum("OperationModeStatusEnum", c5_m4),
                false);
  sf_mex_destroy(&c5_m4);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static c5_OperationModeStatusEnum c5_l_emlrt_marshallIn
  (SFc5_et_roboconInstanceStruct *chartInstance, const mxArray *c5_u, const
   emlrtMsgIdentifier *c5_parentId)
{
  c5_OperationModeStatusEnum c5_y;
  static const int32_T c5_enumValues[4] = { 0, 1, 2, 3 };

  static const char * c5_enumNames[4] = { "NOT_STARTED", "IN_PROGRESS",
    "SUCCESSFULLY_COMPLETED", "ABORTED" };

  (void)chartInstance;
  sf_mex_check_enum("OperationModeStatusEnum", 4, c5_enumNames, c5_enumValues);
  sf_mex_check_builtin(c5_parentId, c5_u, "OperationModeStatusEnum", 0, 0U, NULL);
  c5_y = (c5_OperationModeStatusEnum)sf_mex_get_enum_element(c5_u, 0);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_current_mode_status;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  c5_OperationModeStatusEnum c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_current_mode_status = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_current_mode_status),
    &c5_thisId);
  sf_mex_destroy(&c5_current_mode_status);
  *(c5_OperationModeStatusEnum *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_sensors_bus_io(void *chartInstanceVoid, void *c5_pData)
{
  const mxArray *c5_mxVal = NULL;
  c5_Sensors_Bus c5_tmp;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxVal = NULL;
  c5_tmp.theta_L = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[0];
  c5_tmp.theta_R = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[4];
  c5_tmp.theta_T = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[8];
  c5_tmp.light = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[12];
  c5_tmp.gyro = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[16];
  c5_tmp.sonar = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[20];
  c5_tmp.battery = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[24];
  c5_tmp.touch = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[28];
  c5_tmp.time = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[32];
  c5_tmp.ok_button = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[36];
  c5_tmp.BT_status_in = *(real32_T *)&((char_T *)(c5_Sensors_Bus *)c5_pData)[40];
  sf_mex_assign(&c5_mxVal, c5_k_sf_marshallOut(chartInstance, &c5_tmp), false);
  return c5_mxVal;
}

static const mxArray *c5_k_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  c5_Sensors_Bus c5_u;
  const mxArray *c5_y = NULL;
  real32_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  real32_T c5_c_u;
  const mxArray *c5_c_y = NULL;
  real32_T c5_d_u;
  const mxArray *c5_d_y = NULL;
  real32_T c5_e_u;
  const mxArray *c5_e_y = NULL;
  real32_T c5_f_u;
  const mxArray *c5_f_y = NULL;
  real32_T c5_g_u;
  const mxArray *c5_g_y = NULL;
  real32_T c5_h_u;
  const mxArray *c5_h_y = NULL;
  real32_T c5_i_u;
  const mxArray *c5_i_y = NULL;
  real32_T c5_j_u;
  const mxArray *c5_j_y = NULL;
  real32_T c5_k_u;
  const mxArray *c5_k_y = NULL;
  real32_T c5_l_u;
  const mxArray *c5_l_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(c5_Sensors_Bus *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c5_b_u = c5_u.theta_L;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_b_y, "theta_L", "theta_L", 0);
  c5_c_u = c5_u.theta_R;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_c_y, "theta_R", "theta_R", 0);
  c5_d_u = c5_u.theta_T;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_d_y, "theta_T", "theta_T", 0);
  c5_e_u = c5_u.light;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_e_y, "light", "light", 0);
  c5_f_u = c5_u.gyro;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_f_y, "gyro", "gyro", 0);
  c5_g_u = c5_u.sonar;
  c5_g_y = NULL;
  sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_g_y, "sonar", "sonar", 0);
  c5_h_u = c5_u.battery;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_h_y, "battery", "battery", 0);
  c5_i_u = c5_u.touch;
  c5_i_y = NULL;
  sf_mex_assign(&c5_i_y, sf_mex_create("y", &c5_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_i_y, "touch", "touch", 0);
  c5_j_u = c5_u.time;
  c5_j_y = NULL;
  sf_mex_assign(&c5_j_y, sf_mex_create("y", &c5_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_j_y, "time", "time", 0);
  c5_k_u = c5_u.ok_button;
  c5_k_y = NULL;
  sf_mex_assign(&c5_k_y, sf_mex_create("y", &c5_k_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_k_y, "ok_button", "ok_button", 0);
  c5_l_u = c5_u.BT_status_in;
  c5_l_y = NULL;
  sf_mex_assign(&c5_l_y, sf_mex_create("y", &c5_l_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_l_y, "BT_status_in", "BT_status_in", 0);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_lightCalib_bus_io(void *chartInstanceVoid, void
  *c5_pData)
{
  const mxArray *c5_mxVal = NULL;
  c5_Light_Bus c5_tmp;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxVal = NULL;
  c5_tmp.whiteOnLimbo = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[0];
  c5_tmp.blackOnLimbo = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[4];
  c5_tmp.black = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[8];
  c5_tmp.white = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[12];
  c5_tmp.black_white = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[16];
  c5_tmp.gray = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[20];
  c5_tmp.blackOnTail = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[24];
  c5_tmp.whiteOnTail = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[28];
  c5_tmp.flashingBlack = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[32];
  c5_tmp.flashingWhite = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)[36];
  c5_tmp.flashingMapBlack = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)
    [40];
  c5_tmp.flashingMapWhite = *(real32_T *)&((char_T *)(c5_Light_Bus *)c5_pData)
    [44];
  sf_mex_assign(&c5_mxVal, c5_l_sf_marshallOut(chartInstance, &c5_tmp), false);
  return c5_mxVal;
}

static const mxArray *c5_l_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  c5_Light_Bus c5_u;
  const mxArray *c5_y = NULL;
  real32_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  real32_T c5_c_u;
  const mxArray *c5_c_y = NULL;
  real32_T c5_d_u;
  const mxArray *c5_d_y = NULL;
  real32_T c5_e_u;
  const mxArray *c5_e_y = NULL;
  real32_T c5_f_u;
  const mxArray *c5_f_y = NULL;
  real32_T c5_g_u;
  const mxArray *c5_g_y = NULL;
  real32_T c5_h_u;
  const mxArray *c5_h_y = NULL;
  real32_T c5_i_u;
  const mxArray *c5_i_y = NULL;
  real32_T c5_j_u;
  const mxArray *c5_j_y = NULL;
  real32_T c5_k_u;
  const mxArray *c5_k_y = NULL;
  real32_T c5_l_u;
  const mxArray *c5_l_y = NULL;
  real32_T c5_m_u;
  const mxArray *c5_m_y = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(c5_Light_Bus *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c5_b_u = c5_u.whiteOnLimbo;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_b_y, "whiteOnLimbo", "whiteOnLimbo", 0);
  c5_c_u = c5_u.blackOnLimbo;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_c_y, "blackOnLimbo", "blackOnLimbo", 0);
  c5_d_u = c5_u.black;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_d_y, "black", "black", 0);
  c5_e_u = c5_u.white;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_e_y, "white", "white", 0);
  c5_f_u = c5_u.black_white;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_f_y, "black_white", "black_white", 0);
  c5_g_u = c5_u.gray;
  c5_g_y = NULL;
  sf_mex_assign(&c5_g_y, sf_mex_create("y", &c5_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_g_y, "gray", "gray", 0);
  c5_h_u = c5_u.blackOnTail;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_h_y, "blackOnTail", "blackOnTail", 0);
  c5_i_u = c5_u.whiteOnTail;
  c5_i_y = NULL;
  sf_mex_assign(&c5_i_y, sf_mex_create("y", &c5_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_i_y, "whiteOnTail", "whiteOnTail", 0);
  c5_j_u = c5_u.flashingBlack;
  c5_j_y = NULL;
  sf_mex_assign(&c5_j_y, sf_mex_create("y", &c5_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_j_y, "flashingBlack", "flashingBlack", 0);
  c5_k_u = c5_u.flashingWhite;
  c5_k_y = NULL;
  sf_mex_assign(&c5_k_y, sf_mex_create("y", &c5_k_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_k_y, "flashingWhite", "flashingWhite", 0);
  c5_l_u = c5_u.flashingMapBlack;
  c5_l_y = NULL;
  sf_mex_assign(&c5_l_y, sf_mex_create("y", &c5_l_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_l_y, "flashingMapBlack", "flashingMapBlack", 0);
  c5_m_u = c5_u.flashingMapWhite;
  c5_m_y = NULL;
  sf_mex_assign(&c5_m_y, sf_mex_create("y", &c5_m_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_m_y, "flashingMapWhite", "flashingMapWhite", 0);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static c5_Light_Bus c5_m_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  c5_Light_Bus c5_y;
  emlrtMsgIdentifier c5_thisId;
  static const char * c5_fieldNames[12] = { "whiteOnLimbo", "blackOnLimbo",
    "black", "white", "black_white", "gray", "blackOnTail", "whiteOnTail",
    "flashingBlack", "flashingWhite", "flashingMapBlack", "flashingMapWhite" };

  c5_thisId.fParent = c5_parentId;
  sf_mex_check_struct(c5_parentId, c5_u, 12, c5_fieldNames, 0U, NULL);
  c5_thisId.fIdentifier = "whiteOnLimbo";
  c5_y.whiteOnLimbo = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "whiteOnLimbo", "whiteOnLimbo", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "blackOnLimbo";
  c5_y.blackOnLimbo = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "blackOnLimbo", "blackOnLimbo", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "black";
  c5_y.black = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "black", "black", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "white";
  c5_y.white = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "white", "white", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "black_white";
  c5_y.black_white = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "black_white", "black_white", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "gray";
  c5_y.gray = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "gray", "gray", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "blackOnTail";
  c5_y.blackOnTail = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "blackOnTail", "blackOnTail", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "whiteOnTail";
  c5_y.whiteOnTail = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "whiteOnTail", "whiteOnTail", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "flashingBlack";
  c5_y.flashingBlack = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "flashingBlack", "flashingBlack", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "flashingWhite";
  c5_y.flashingWhite = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "flashingWhite", "flashingWhite", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "flashingMapBlack";
  c5_y.flashingMapBlack = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "flashingMapBlack", "flashingMapBlack", 0)),
    &c5_thisId);
  c5_thisId.fIdentifier = "flashingMapWhite";
  c5_y.flashingMapWhite = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "flashingMapWhite", "flashingMapWhite", 0)),
    &c5_thisId);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_lightCalib;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  c5_Light_Bus c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_lightCalib = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_lightCalib),
    &c5_thisId);
  sf_mex_destroy(&c5_lightCalib);
  *(c5_Light_Bus *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_initFlags_bus_io(void *chartInstanceVoid, void
  *c5_pData)
{
  const mxArray *c5_mxVal = NULL;
  c5_Init_Bus c5_tmp;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxVal = NULL;
  c5_tmp.fall = *(boolean_T *)&((char_T *)(c5_Init_Bus *)c5_pData)[0];
  c5_tmp.gyroInit = *(real32_T *)&((char_T *)(c5_Init_Bus *)c5_pData)[4];
  c5_tmp.gyroReset = *(real32_T *)&((char_T *)(c5_Init_Bus *)c5_pData)[8];
  c5_tmp.theta = *(real32_T *)&((char_T *)(c5_Init_Bus *)c5_pData)[12];
  c5_tmp.tail = *(real32_T *)&((char_T *)(c5_Init_Bus *)c5_pData)[16];
  sf_mex_assign(&c5_mxVal, c5_m_sf_marshallOut(chartInstance, &c5_tmp), false);
  return c5_mxVal;
}

static const mxArray *c5_d_emlrt_marshallOut(SFc5_et_roboconInstanceStruct
  *chartInstance, const c5_Init_Bus c5_u)
{
  const mxArray *c5_y = NULL;
  boolean_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  real32_T c5_c_u;
  const mxArray *c5_c_y = NULL;
  real32_T c5_d_u;
  const mxArray *c5_d_y = NULL;
  real32_T c5_e_u;
  const mxArray *c5_e_y = NULL;
  real32_T c5_f_u;
  const mxArray *c5_f_y = NULL;
  (void)chartInstance;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c5_b_u = c5_u.fall;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_b_y, "fall", "fall", 0);
  c5_c_u = c5_u.gyroInit;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_c_y, "gyroInit", "gyroInit", 0);
  c5_d_u = c5_u.gyroReset;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_d_y, "gyroReset", "gyroReset", 0);
  c5_e_u = c5_u.theta;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_e_y, "theta", "theta", 0);
  c5_f_u = c5_u.tail;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c5_y, c5_f_y, "tail", "tail", 0);
  return c5_y;
}

static const mxArray *c5_m_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  sf_mex_assign(&c5_mxArrayOutData, c5_d_emlrt_marshallOut(chartInstance,
    *(c5_Init_Bus *)c5_inData), false);
  return c5_mxArrayOutData;
}

static c5_Init_Bus c5_n_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_b_initFlags, const char_T *c5_identifier)
{
  c5_Init_Bus c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_initFlags),
    &c5_thisId);
  sf_mex_destroy(&c5_b_initFlags);
  return c5_y;
}

static c5_Init_Bus c5_o_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  c5_Init_Bus c5_y;
  emlrtMsgIdentifier c5_thisId;
  static const char * c5_fieldNames[5] = { "fall", "gyroInit", "gyroReset",
    "theta", "tail" };

  c5_thisId.fParent = c5_parentId;
  sf_mex_check_struct(c5_parentId, c5_u, 5, c5_fieldNames, 0U, NULL);
  c5_thisId.fIdentifier = "fall";
  c5_y.fall = c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "fall", "fall", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "gyroInit";
  c5_y.gyroInit = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "gyroInit", "gyroInit", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "gyroReset";
  c5_y.gyroReset = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "gyroReset", "gyroReset", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "theta";
  c5_y.theta = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "theta", "theta", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "tail";
  c5_y.tail = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "tail", "tail", 0)), &c5_thisId);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_initFlags;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  c5_Init_Bus c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_b_initFlags = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_initFlags),
    &c5_thisId);
  sf_mex_destroy(&c5_b_initFlags);
  *(c5_Init_Bus *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_n_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  sf_mex_assign(&c5_mxArrayOutData, c5_c_emlrt_marshallOut(chartInstance,
    *(c5_Balancer_States_Bus *)c5_inData), false);
  return c5_mxArrayOutData;
}

static c5_Balancer_States_Bus c5_p_emlrt_marshallIn
  (SFc5_et_roboconInstanceStruct *chartInstance, const mxArray *c5_u, const
   emlrtMsgIdentifier *c5_parentId)
{
  c5_Balancer_States_Bus c5_y;
  emlrtMsgIdentifier c5_thisId;
  static const char * c5_fieldNames[5] = { "theta", "psi", "theta_dot",
    "psi_dot", "int_theta" };

  c5_thisId.fParent = c5_parentId;
  sf_mex_check_struct(c5_parentId, c5_u, 5, c5_fieldNames, 0U, NULL);
  c5_thisId.fIdentifier = "theta";
  c5_y.theta = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "theta", "theta", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "psi";
  c5_y.psi = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c5_u, "psi", "psi", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "theta_dot";
  c5_y.theta_dot = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "theta_dot", "theta_dot", 0)), &c5_thisId);
  c5_thisId.fIdentifier = "psi_dot";
  c5_y.psi_dot = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c5_u, "psi_dot", "psi_dot", 0)),
    &c5_thisId);
  c5_thisId.fIdentifier = "int_theta";
  c5_y.int_theta = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c5_u, "int_theta", "int_theta", 0)), &c5_thisId);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_balancerStates_Bus0;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  c5_Balancer_States_Bus c5_y;
  SFc5_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc5_et_roboconInstanceStruct *)chartInstanceVoid;
  c5_b_balancerStates_Bus0 = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_p_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_balancerStates_Bus0), &c5_thisId);
  sf_mex_destroy(&c5_b_balancerStates_Bus0);
  *(c5_Balancer_States_Bus *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_q_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_d_subchartSimStateInfo, const char_T
  *c5_identifier)
{
  const mxArray *c5_y = NULL;
  emlrtMsgIdentifier c5_thisId;
  c5_y = NULL;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  sf_mex_assign(&c5_y, c5_r_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_d_subchartSimStateInfo), &c5_thisId), false);
  sf_mex_destroy(&c5_d_subchartSimStateInfo);
  return c5_y;
}

static const mxArray *c5_r_emlrt_marshallIn(SFc5_et_roboconInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  const mxArray *c5_y = NULL;
  (void)chartInstance;
  (void)c5_parentId;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_duplicatearraysafe(&c5_u), false);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_s_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *chartInstance,
  const mxArray *c5_b_dataWrittenToVector, const char_T *c5_identifier,
  boolean_T c5_y[1])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_dataWrittenToVector),
                        &c5_thisId, c5_y);
  sf_mex_destroy(&c5_b_dataWrittenToVector);
}

static void c5_t_emlrt_marshallIn(SFc5_et_roboconInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, boolean_T c5_y[1])
{
  boolean_T c5_bv1[1];
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_bv1, 1, 11, 0U, 1, 0U, 1, 1);
  c5_y[0] = c5_bv1[0];
  sf_mex_destroy(&c5_u);
}

static void c5_updateDataWrittenToVector(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_vectorIndex)
{
  chartInstance->c5_dataWrittenToVector[(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK(0U,
    (int32_T)c5_vectorIndex, 0, 0, 1, 0)] = true;
}

static void c5_errorIfDataNotWrittenToFcn(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_vectorIndex, uint32_T c5_dataNumber, uint32_T
  c5_ssIdOfSourceObject, int32_T c5_offsetInSourceObject, int32_T
  c5_lengthInSourceObject)
{
  (void)c5_ssIdOfSourceObject;
  (void)c5_offsetInSourceObject;
  (void)c5_lengthInSourceObject;
  if (!chartInstance->c5_dataWrittenToVector[(uint32_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK(0U, (int32_T)c5_vectorIndex, 0, 0, 1, 0)]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(c5_dataNumber);
  }
}

static c5_OperationModeEnum c5_get_current_mode(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, NULL, c5_elementIndex);
  return *chartInstance->c5_current_mode_address;
}

static void c5_set_current_mode(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_elementIndex, c5_OperationModeEnum c5_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, NULL, c5_elementIndex);
  *chartInstance->c5_current_mode_address = c5_elementValue;
}

static c5_OperationModeEnum *c5_access_current_mode
  (SFc5_et_roboconInstanceStruct *chartInstance, uint32_T c5_rdOnly)
{
  c5_OperationModeEnum *c5_dsmAddr;
  ssReadFromDataStore_wrapper(chartInstance->S, 0, NULL);
  c5_dsmAddr = chartInstance->c5_current_mode_address;
  if (c5_rdOnly == 0U) {
    ssWriteToDataStore_wrapper(chartInstance->S, 0, NULL);
  }

  return c5_dsmAddr;
}

static c5_OperationModeStatusEnum c5_get_current_mode_status
  (SFc5_et_roboconInstanceStruct *chartInstance, uint32_T c5_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 1, NULL, c5_elementIndex);
  return *chartInstance->c5_current_mode_status_address;
}

static void c5_set_current_mode_status(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_elementIndex, c5_OperationModeStatusEnum
  c5_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 1, NULL, c5_elementIndex);
  *chartInstance->c5_current_mode_status_address = c5_elementValue;
}

static c5_OperationModeStatusEnum *c5_access_current_mode_status
  (SFc5_et_roboconInstanceStruct *chartInstance, uint32_T c5_rdOnly)
{
  c5_OperationModeStatusEnum *c5_dsmAddr;
  ssReadFromDataStore_wrapper(chartInstance->S, 1, NULL);
  c5_dsmAddr = chartInstance->c5_current_mode_status_address;
  if (c5_rdOnly == 0U) {
    ssWriteToDataStore_wrapper(chartInstance->S, 1, NULL);
  }

  return c5_dsmAddr;
}

static c5_Light_Bus c5_get_lightCalib(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 2, NULL, c5_elementIndex);
  return *chartInstance->c5_lightCalib_address;
}

static void c5_set_lightCalib(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_elementIndex, c5_Light_Bus c5_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 2, NULL, c5_elementIndex);
  *chartInstance->c5_lightCalib_address = c5_elementValue;
}

static c5_Light_Bus *c5_access_lightCalib(SFc5_et_roboconInstanceStruct
  *chartInstance, uint32_T c5_rdOnly)
{
  (void)c5_rdOnly;
  return chartInstance->c5_lightCalib_address;
}

static real32_T c5_get_phi_des(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 3, NULL, c5_elementIndex);
  return *chartInstance->c5_phi_des_address;
}

static void c5_set_phi_des(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_elementIndex, real32_T c5_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 3, NULL, c5_elementIndex);
  *chartInstance->c5_phi_des_address = c5_elementValue;
}

static real32_T *c5_access_phi_des(SFc5_et_roboconInstanceStruct *chartInstance,
  uint32_T c5_rdOnly)
{
  real32_T *c5_dsmAddr;
  ssReadFromDataStore_wrapper(chartInstance->S, 3, NULL);
  c5_dsmAddr = chartInstance->c5_phi_des_address;
  if (c5_rdOnly == 0U) {
    ssWriteToDataStore_wrapper(chartInstance->S, 3, NULL);
  }

  return c5_dsmAddr;
}

static void init_dsm_address_info(SFc5_et_roboconInstanceStruct *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "current_mode", (void **)
    &chartInstance->c5_current_mode_address,
    &chartInstance->c5_b_current_mode_index);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "current_mode_status",
                                        (void **)
    &chartInstance->c5_current_mode_status_address,
    &chartInstance->c5_current_mode_status_index);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "lightCalib", (void **)
    &chartInstance->c5_lightCalib_address, &chartInstance->c5_lightCalib_index);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "phi_des", (void **)
    &chartInstance->c5_phi_des_address, &chartInstance->c5_phi_des_index);
}

static void init_simulink_io_address(SFc5_et_roboconInstanceStruct
  *chartInstance)
{
  chartInstance->c5_PWM = (c5_PWM_bus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_states = (c5_States_Bus *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c5_sensors = (c5_Sensors_Bus *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_BT_status_out = (real32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c5_initFlags = (c5_Init_Bus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c5_et_robocon_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1822241006U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(304167474U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1451973090U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2802582964U);
}

mxArray* sf_c5_et_robocon_get_post_codegen_info(void);
mxArray *sf_c5_et_robocon_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("qNFFu9jZEgkqjbMsk9ENiG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(14));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxData);
  }

  {
    mxArray* mxPostCodegenInfo = sf_c5_et_robocon_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_et_robocon_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_et_robocon_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c5_et_robocon_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c5_et_robocon_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString(
      "wwF4mPBKdj9c8i6ywpA9uC");
    mwSize exp_dims[2] = { 1, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);

    {
      mxArray* mxFcnName = mxCreateString("StatusLCD");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 0, mxFcnName);
    }

    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c5_et_robocon(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[133],T\"BT_status_out\",},{M[1],M[122],T\"PWM\",},{M[1],M[107],T\"initFlags\",},{M[3],M[68],T\"current_mode_index\",},{M[8],M[0],T\"is_active_c5_et_robocon\",},{M[9],M[0],T\"is_c5_et_robocon\",},{M[9],M[9],T\"is_normal_operation_modes\",},{M[14],M[179],T\"subchartSimStateInfo\",},{M[14],M[180],T\"subchartSimStateInfo\",},{M[14],M[181],T\"subchartSimStateInfo\",}}",
    "100 S'type','srcId','name','auxInfo'{{M[15],M[0],T\"dataWrittenToVector\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 11, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_et_robocon_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_et_roboconInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_et_roboconInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _et_roboconMachineNumber_,
           5,
           6,
           27,
           0,
           13,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_et_roboconMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_et_roboconMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _et_roboconMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"PWM");
          _SFD_SET_DATA_PROPS(1,10,0,0,"TRACK_MODE_LIST");
          _SFD_SET_DATA_PROPS(2,0,0,0,"current_mode_index");
          _SFD_SET_DATA_PROPS(3,11,0,0,"current_mode");
          _SFD_SET_DATA_PROPS(4,1,1,0,"states");
          _SFD_SET_DATA_PROPS(5,11,0,0,"current_mode_status");
          _SFD_SET_DATA_PROPS(6,1,1,0,"sensors");
          _SFD_SET_DATA_PROPS(7,11,0,0,"lightCalib");
          _SFD_SET_DATA_PROPS(8,2,0,1,"BT_status_out");
          _SFD_SET_DATA_PROPS(9,2,0,1,"initFlags");
          _SFD_SET_DATA_PROPS(10,10,0,0,"Init_Bus0");
          _SFD_SET_DATA_PROPS(11,10,0,0,"balancerStates_Bus0");
          _SFD_SET_DATA_PROPS(12,11,0,0,"phi_des");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,4);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,3);
          _SFD_ST_SUBSTATE_INDEX(1,2,4);
          _SFD_ST_SUBSTATE_INDEX(1,3,5);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,4,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(18,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(21,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(15,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(19,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(24,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(25,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(26,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(22,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(23,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(0,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(1,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(1,0,0,1,53,1,48);
        _SFD_CV_INIT_EML(24,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(24,0,0,1,56,1,48);
        _SFD_CV_INIT_EML(26,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(26,0,0,1,49,1,48);
        _SFD_CV_INIT_EML(5,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(8,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(10,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(11,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(11,0,0,1,71,1,48);
        _SFD_CV_INIT_EML(21,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(21,0,0,1,19,1,19);
        _SFD_CV_INIT_EML(13,0,0,0,0,1,0,0,0,0,0);
        _SFD_CV_INIT_EML_SATURATION(13,0,0,23,-1,54);
        _SFD_CV_INIT_EML(15,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(15,0,0,1,47,1,47);
        _SFD_CV_INIT_EML(17,0,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(19,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(19,0,0,1,41,1,41);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_PWM_bus_io,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_INT32,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_g_sf_marshallOut,(MexInFcnForType)
            c5_g_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_e_sf_marshallOut,(MexInFcnForType)c5_e_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_h_sf_marshallOut,(MexInFcnForType)c5_h_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_states_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_j_sf_marshallOut,(MexInFcnForType)c5_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_sensors_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_lightCalib_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_initFlags_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_m_sf_marshallOut,(MexInFcnForType)c5_k_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_n_sf_marshallOut,(MexInFcnForType)c5_l_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c5_PWM);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c5_TRACK_MODE_LIST);
        _SFD_SET_DATA_VALUE_PTR(2U, &chartInstance->c5_current_mode_index);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c5_current_mode_address);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c5_states);
        _SFD_SET_DATA_VALUE_PTR(5U,
          chartInstance->c5_current_mode_status_address);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c5_sensors);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c5_lightCalib_address);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c5_BT_status_out);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c5_initFlags);
        _SFD_SET_DATA_VALUE_PTR(10U, &chartInstance->c5_Init_Bus0);
        _SFD_SET_DATA_VALUE_PTR(11U, &chartInstance->c5_balancerStates_Bus0);
        _SFD_SET_DATA_VALUE_PTR(12U, chartInstance->c5_phi_des_address);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _et_roboconMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "4si99QGgkJlWQnRBQM6VmC";
}

static void sf_opaque_initialize_c5_et_robocon(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_et_roboconInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c5_et_robocon((SFc5_et_roboconInstanceStruct*)
    chartInstanceVar);
  initialize_c5_et_robocon((SFc5_et_roboconInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_et_robocon(void *chartInstanceVar)
{
  enable_c5_et_robocon((SFc5_et_roboconInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_et_robocon(void *chartInstanceVar)
{
  disable_c5_et_robocon((SFc5_et_roboconInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_et_robocon(void *chartInstanceVar)
{
  sf_gateway_c5_et_robocon((SFc5_et_roboconInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c5_et_robocon(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c5_et_robocon((SFc5_et_roboconInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c5_et_robocon(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c5_et_robocon((SFc5_et_roboconInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c5_et_robocon(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_et_roboconInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_et_robocon_optimization_info();
    }

    finalize_c5_et_robocon((SFc5_et_roboconInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_et_robocon((SFc5_et_roboconInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_et_robocon(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c5_et_robocon((SFc5_et_roboconInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_et_robocon(SimStruct *S)
{
  /* Actual parameters from chart:
     Init_Bus0 TRACK_MODE_LIST balancerStates_Bus0
   */
  const char_T *rtParamNames[] = { "Init_Bus0", "TRACK_MODE_LIST",
    "balancerStates_Bus0" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for TRACK_MODE_LIST*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], sf_get_enum_data_type_id
                              (S,"?OperationModeEnum"));
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_et_robocon_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2542479347U));
  ssSetChecksum1(S,(2115419639U));
  ssSetChecksum2(S,(2943782012U));
  ssSetChecksum3(S,(1333649323U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c5_et_robocon(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c5_et_robocon(SimStruct *S)
{
  SFc5_et_roboconInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc5_et_roboconInstanceStruct *)utMalloc(sizeof
    (SFc5_et_roboconInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_et_roboconInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_et_robocon;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_et_robocon;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_et_robocon;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_et_robocon;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_et_robocon;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_et_robocon;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_et_robocon;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_et_robocon;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_et_robocon;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_et_robocon;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_et_robocon;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c5_et_robocon_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_et_robocon(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_et_robocon(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_et_robocon(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_et_robocon_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
