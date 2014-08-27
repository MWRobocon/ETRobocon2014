/* Include files */

#include <stddef.h>
#include "blas.h"
#include "et_robocon_sfun.h"
#include "c6_et_robocon.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "et_robocon_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c6_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c6_IN_see_saw_mode             ((uint8_T)1U)
#define c6_IN_Balancing                ((uint8_T)1U)
#define c6_IN_StandUp                  ((uint8_T)2U)
#define c6_IN_Waiting                  ((uint8_T)3U)
#define c6_IN_ConstantSpeed            ((uint8_T)1U)
#define c6_IN_Curvature                ((uint8_T)2U)
#define c6_IN_MoveForwardSlowly        ((uint8_T)3U)
#define c6_IN_Ramp                     ((uint8_T)4U)
#define c6_IN_SpeedUp                  ((uint8_T)5U)
#define c6_IN_StationnaryBalance       ((uint8_T)6U)
#define c6_IN_Const                    ((uint8_T)1U)
#define c6_IN_Slowdown                 ((uint8_T)2U)
#define c6_IN_BridgeTest               ((uint8_T)1U)
#define c6_IN_RampUpOne                ((uint8_T)2U)
#define c6_IN_RampUpTwo                ((uint8_T)3U)
#define c6_IN_RotateInPlace            ((uint8_T)4U)
#define c6_IN_SlowtoRotate             ((uint8_T)5U)
#define c6_IN_Stop                     ((uint8_T)6U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c6_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_d_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_e_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_f_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_g_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_h_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_i_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_j_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_k_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_l_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_m_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_n_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_o_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_p_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_q_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_r_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_s_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_t_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_u_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_v_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_w_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_x_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_y_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_ab_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_bb_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_cb_debug_family_names[2] = { "nargin", "nargout" };

static const char * c6_db_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_eb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_fb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_gb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_hb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_ib_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_jb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_kb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_lb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_mb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_nb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_ob_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_pb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_qb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_rb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_sb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_tb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_ub_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_vb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_wb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_xb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_yb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_ac_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_bc_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_cc_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c6_dc_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

/* Function Declarations */
static void initialize_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void initialize_params_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void enable_c6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void disable_c6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void c6_update_debugger_state_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c6_et_robocon(SFc6_et_roboconInstanceStruct *
  chartInstance);
static void set_sim_state_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_st);
static void c6_set_sim_state_side_effects_c6_et_robocon
  (SFc6_et_roboconInstanceStruct *chartInstance);
static void finalize_c6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void sf_gateway_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void mdl_start_c6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static boolean_T isStablec6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void duringc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void enterc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void exitc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void gatewayc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void enablec6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void disablec6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void initBuffersc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void stepBuffersc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void initc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance);
static void activate_callc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void deactivate_callc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void increment_call_counterc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void reset_call_counterc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void check_state_inconsistency_c6_et_robocon
  (SFc6_et_roboconInstanceStruct *chartInstance);
static void initSimStructsc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void c6_see_saw_mode(SFc6_et_roboconInstanceStruct *chartInstance);
static void c6_SeesawLogic(SFc6_et_roboconInstanceStruct *chartInstance);
static void c6_exit_atomic_StationnaryBalance(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void c6_exit_internal_Curvature(SFc6_et_roboconInstanceStruct
  *chartInstance);
static void c6_SpeedUp(SFc6_et_roboconInstanceStruct *chartInstance);
static void c6_Ramp(SFc6_et_roboconInstanceStruct *chartInstance);
static void c6_SlowtoRotate(SFc6_et_roboconInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static real_T c6_emlrt_marshallIn(SFc6_et_roboconInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static boolean_T c6_b_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real32_T c6_c_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_sf_internal_predicateOutput, const char_T
  *c6_identifier);
static real32_T c6_d_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static real32_T c6_lineTracker(SFc6_et_roboconInstanceStruct *chartInstance,
  real32_T c6_b_desiredLight, real32_T c6_c_light, real32_T c6_b_trackingPower,
  real_T c6_c_battery);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_e_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static uint8_T c6_f_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_tp_see_saw_mode, const char_T
  *c6_identifier);
static uint8_T c6_g_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_sensors_bus_io(void *chartInstanceVoid, void *c6_pData);
static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_lightCalib_bus_io(void *chartInstanceVoid, void
  *c6_pData);
static const mxArray *c6_g_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static c6_Light_Bus c6_h_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_h_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static c6_OperationModeStatusEnum c6_i_emlrt_marshallIn
  (SFc6_et_roboconInstanceStruct *chartInstance, const mxArray *c6_u, const
   emlrtMsgIdentifier *c6_parentId);
static void c6_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_PWM_bus_io(void *chartInstanceVoid, void *c6_pData);
static const mxArray *c6_i_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static c6_PWM_bus c6_j_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_PWM, const char_T *c6_identifier);
static c6_PWM_bus c6_k_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_initFlags_bus_io(void *chartInstanceVoid, void
  *c6_pData);
static const mxArray *c6_j_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static c6_Init_Bus c6_l_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_initFlags, const char_T *c6_identifier);
static c6_Init_Bus c6_m_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_k_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static c6_struct_FjjrIT366yeIj3aqvn0HfE c6_n_emlrt_marshallIn
  (SFc6_et_roboconInstanceStruct *chartInstance, const mxArray *c6_u, const
   emlrtMsgIdentifier *c6_parentId);
static void c6_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_states_bus_io(void *chartInstanceVoid, void *c6_pData);
static const mxArray *c6_l_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_balancerStates_bus_io(void *chartInstanceVoid, void
  *c6_pData);
static const mxArray *c6_m_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static c6_Balancer_States_Bus c6_o_emlrt_marshallIn
  (SFc6_et_roboconInstanceStruct *chartInstance, const mxArray *c6_u, const
   emlrtMsgIdentifier *c6_parentId);
static void c6_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static uint16_T c6_p_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_temporalCounter_i1, const char_T
  *c6_identifier);
static uint16_T c6_q_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_r_emlrt_marshallIn(SFc6_et_roboconInstanceStruct *chartInstance,
  const mxArray *c6_b_dataWrittenToVector, const char_T *c6_identifier,
  boolean_T c6_y[13]);
static void c6_s_emlrt_marshallIn(SFc6_et_roboconInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, boolean_T c6_y[13]);
static const mxArray *c6_t_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_setSimStateSideEffectsInfo, const char_T
  *c6_identifier);
static const mxArray *c6_u_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_updateDataWrittenToVector(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_vectorIndex);
static void c6_errorIfDataNotWrittenToFcn(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_vectorIndex, uint32_T c6_dataNumber, uint32_T
  c6_ssIdOfSourceObject, int32_T c6_offsetInSourceObject, int32_T
  c6_lengthInSourceObject);
static void c6_bus_rd_access_lightCalib_2(SFc6_et_roboconInstanceStruct
  *chartInstance, int32_T c6_u0, int32_T c6_u1, int32_T c6_u2, int32_T c6_u3);
static c6_OperationModeStatusEnum c6_get_current_task_operation_status
  (SFc6_et_roboconInstanceStruct *chartInstance, uint32_T c6_elementIndex);
static void c6_set_current_task_operation_status(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_elementIndex, c6_OperationModeStatusEnum
  c6_elementValue);
static c6_OperationModeStatusEnum *c6_access_current_task_operation_status
  (SFc6_et_roboconInstanceStruct *chartInstance, uint32_T c6_rdOnly);
static c6_Light_Bus c6_get_lightCalib(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_elementIndex);
static void c6_set_lightCalib(SFc6_et_roboconInstanceStruct *chartInstance,
  uint32_T c6_elementIndex, c6_Light_Bus c6_elementValue);
static c6_Light_Bus *c6_access_lightCalib(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_rdOnly);
static void init_dsm_address_info(SFc6_et_roboconInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc6_et_roboconInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void initialize_params_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  const mxArray *c6_m0 = NULL;
  const mxArray *c6_mxField;
  c6_struct_FjjrIT366yeIj3aqvn0HfE c6_r0;
  c6_m0 = sf_mex_get_sfun_param(chartInstance->S, 0, 1);
  c6_mxField = sf_mex_getfield(c6_m0, "theta", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c6_mxField),
                      &c6_r0.theta, 1, 1, 0U, 0, 0U, 0);
  c6_mxField = sf_mex_getfield(c6_m0, "psi", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c6_mxField), &c6_r0.psi,
                      1, 1, 0U, 0, 0U, 0);
  c6_mxField = sf_mex_getfield(c6_m0, "theta_dot", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c6_mxField),
                      &c6_r0.theta_dot, 1, 1, 0U, 0, 0U, 0);
  c6_mxField = sf_mex_getfield(c6_m0, "psi_dot", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c6_mxField),
                      &c6_r0.psi_dot, 1, 1, 0U, 0, 0U, 0);
  c6_mxField = sf_mex_getfield(c6_m0, "int_theta", "balancerStates_Bus0", 0);
  sf_mex_import_named("balancerStates_Bus0", sf_mex_dup(c6_mxField),
                      &c6_r0.int_theta, 1, 1, 0U, 0, 0U, 0);
  sf_mex_destroy(&c6_m0);
  chartInstance->c6_balancerStates_Bus0 = c6_r0;
}

static void enable_c6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void disable_c6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c6_update_debugger_state_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  uint32_T c6_prevAniVal;
  c6_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c6_is_active_c6_et_robocon == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_c6_et_robocon == c6_IN_see_saw_mode) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_see_saw_mode == c6_IN_Waiting) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_see_saw_mode == c6_IN_StandUp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_see_saw_mode == c6_IN_Balancing) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_active_SeesawLogic == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_SeesawLogic == c6_IN_MoveForwardSlowly) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_SeesawLogic == c6_IN_StationnaryBalance) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_SeesawLogic == c6_IN_Curvature) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_Curvature == c6_IN_Slowdown) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_Curvature == c6_IN_Const) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_SeesawLogic == c6_IN_SpeedUp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_SeesawLogic == c6_IN_ConstantSpeed) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_active_After == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_SeesawLogic == c6_IN_Ramp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_Ramp == c6_IN_RampUpOne) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_Ramp == c6_IN_BridgeTest) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_Ramp == c6_IN_RampUpTwo) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_Ramp == c6_IN_RotateInPlace) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_Ramp == c6_IN_SlowtoRotate) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_Ramp == c6_IN_Stop) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c6_sfEvent);
  }

  _SFD_SET_ANIMATION(c6_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c6_et_robocon(SFc6_et_roboconInstanceStruct *
  chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  real32_T c6_hoistedGlobal;
  real32_T c6_u;
  const mxArray *c6_b_y = NULL;
  const mxArray *c6_c_y = NULL;
  real32_T c6_b_u;
  const mxArray *c6_d_y = NULL;
  real32_T c6_c_u;
  const mxArray *c6_e_y = NULL;
  real32_T c6_d_u;
  const mxArray *c6_f_y = NULL;
  const mxArray *c6_g_y = NULL;
  boolean_T c6_e_u;
  const mxArray *c6_h_y = NULL;
  real32_T c6_f_u;
  const mxArray *c6_i_y = NULL;
  real32_T c6_g_u;
  const mxArray *c6_j_y = NULL;
  real32_T c6_h_u;
  const mxArray *c6_k_y = NULL;
  real32_T c6_i_u;
  const mxArray *c6_l_y = NULL;
  real32_T c6_b_hoistedGlobal;
  real32_T c6_j_u;
  const mxArray *c6_m_y = NULL;
  real32_T c6_c_hoistedGlobal;
  real32_T c6_k_u;
  const mxArray *c6_n_y = NULL;
  real32_T c6_d_hoistedGlobal;
  real32_T c6_l_u;
  const mxArray *c6_o_y = NULL;
  real32_T c6_e_hoistedGlobal;
  real32_T c6_m_u;
  const mxArray *c6_p_y = NULL;
  real32_T c6_f_hoistedGlobal;
  real32_T c6_n_u;
  const mxArray *c6_q_y = NULL;
  real32_T c6_g_hoistedGlobal;
  real32_T c6_o_u;
  const mxArray *c6_r_y = NULL;
  real32_T c6_h_hoistedGlobal;
  real32_T c6_p_u;
  const mxArray *c6_s_y = NULL;
  uint8_T c6_i_hoistedGlobal;
  uint8_T c6_q_u;
  const mxArray *c6_t_y = NULL;
  uint8_T c6_j_hoistedGlobal;
  uint8_T c6_r_u;
  const mxArray *c6_u_y = NULL;
  uint8_T c6_k_hoistedGlobal;
  uint8_T c6_s_u;
  const mxArray *c6_v_y = NULL;
  uint8_T c6_l_hoistedGlobal;
  uint8_T c6_t_u;
  const mxArray *c6_w_y = NULL;
  uint8_T c6_m_hoistedGlobal;
  uint8_T c6_u_u;
  const mxArray *c6_x_y = NULL;
  uint8_T c6_n_hoistedGlobal;
  uint8_T c6_v_u;
  const mxArray *c6_y_y = NULL;
  uint8_T c6_o_hoistedGlobal;
  uint8_T c6_w_u;
  const mxArray *c6_ab_y = NULL;
  uint8_T c6_p_hoistedGlobal;
  uint8_T c6_x_u;
  const mxArray *c6_bb_y = NULL;
  uint16_T c6_q_hoistedGlobal;
  uint16_T c6_y_u;
  const mxArray *c6_cb_y = NULL;
  int32_T c6_i0;
  boolean_T c6_ab_u[13];
  const mxArray *c6_db_y = NULL;
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellmatrix(20, 1), false);
  c6_hoistedGlobal = *chartInstance->c6_BT_status_out;
  c6_u = c6_hoistedGlobal;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_b_u = *(real32_T *)&((char_T *)chartInstance->c6_PWM)[0];
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_c_y, c6_d_y, "left", "left", 0);
  c6_c_u = *(real32_T *)&((char_T *)chartInstance->c6_PWM)[4];
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_c_y, c6_e_y, "right", "right", 0);
  c6_d_u = *(real32_T *)&((char_T *)chartInstance->c6_PWM)[8];
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_c_y, c6_f_y, "tail", "tail", 0);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  c6_g_y = NULL;
  sf_mex_assign(&c6_g_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_e_u = *(boolean_T *)&((char_T *)chartInstance->c6_initFlags)[0];
  c6_h_y = NULL;
  sf_mex_assign(&c6_h_y, sf_mex_create("y", &c6_e_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_g_y, c6_h_y, "fall", "fall", 0);
  c6_f_u = *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[4];
  c6_i_y = NULL;
  sf_mex_assign(&c6_i_y, sf_mex_create("y", &c6_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_g_y, c6_i_y, "gyroInit", "gyroInit", 0);
  c6_g_u = *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[8];
  c6_j_y = NULL;
  sf_mex_assign(&c6_j_y, sf_mex_create("y", &c6_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_g_y, c6_j_y, "gyroReset", "gyroReset", 0);
  c6_h_u = *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[12];
  c6_k_y = NULL;
  sf_mex_assign(&c6_k_y, sf_mex_create("y", &c6_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_g_y, c6_k_y, "theta", "theta", 0);
  c6_i_u = *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[16];
  c6_l_y = NULL;
  sf_mex_assign(&c6_l_y, sf_mex_create("y", &c6_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_g_y, c6_l_y, "tail", "tail", 0);
  sf_mex_setcell(c6_y, 2, c6_g_y);
  c6_b_hoistedGlobal = chartInstance->c6_des_vel;
  c6_j_u = c6_b_hoistedGlobal;
  c6_m_y = NULL;
  sf_mex_assign(&c6_m_y, sf_mex_create("y", &c6_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 3, c6_m_y);
  c6_c_hoistedGlobal = chartInstance->c6_desired_phi;
  c6_k_u = c6_c_hoistedGlobal;
  c6_n_y = NULL;
  sf_mex_assign(&c6_n_y, sf_mex_create("y", &c6_k_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 4, c6_n_y);
  c6_d_hoistedGlobal = chartInstance->c6_desired_tail;
  c6_l_u = c6_d_hoistedGlobal;
  c6_o_y = NULL;
  sf_mex_assign(&c6_o_y, sf_mex_create("y", &c6_l_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 5, c6_o_y);
  c6_e_hoistedGlobal = chartInstance->c6_desiredangle;
  c6_m_u = c6_e_hoistedGlobal;
  c6_p_y = NULL;
  sf_mex_assign(&c6_p_y, sf_mex_create("y", &c6_m_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 6, c6_p_y);
  c6_f_hoistedGlobal = chartInstance->c6_forwardPWM;
  c6_n_u = c6_f_hoistedGlobal;
  c6_q_y = NULL;
  sf_mex_assign(&c6_q_y, sf_mex_create("y", &c6_n_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 7, c6_q_y);
  c6_g_hoistedGlobal = chartInstance->c6_normalizedLight;
  c6_o_u = c6_g_hoistedGlobal;
  c6_r_y = NULL;
  sf_mex_assign(&c6_r_y, sf_mex_create("y", &c6_o_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 8, c6_r_y);
  c6_h_hoistedGlobal = chartInstance->c6_turningPWM;
  c6_p_u = c6_h_hoistedGlobal;
  c6_s_y = NULL;
  sf_mex_assign(&c6_s_y, sf_mex_create("y", &c6_p_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 9, c6_s_y);
  c6_i_hoistedGlobal = chartInstance->c6_is_active_c6_et_robocon;
  c6_q_u = c6_i_hoistedGlobal;
  c6_t_y = NULL;
  sf_mex_assign(&c6_t_y, sf_mex_create("y", &c6_q_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 10, c6_t_y);
  c6_j_hoistedGlobal = chartInstance->c6_is_active_After;
  c6_r_u = c6_j_hoistedGlobal;
  c6_u_y = NULL;
  sf_mex_assign(&c6_u_y, sf_mex_create("y", &c6_r_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 11, c6_u_y);
  c6_k_hoistedGlobal = chartInstance->c6_is_active_SeesawLogic;
  c6_s_u = c6_k_hoistedGlobal;
  c6_v_y = NULL;
  sf_mex_assign(&c6_v_y, sf_mex_create("y", &c6_s_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 12, c6_v_y);
  c6_l_hoistedGlobal = chartInstance->c6_is_c6_et_robocon;
  c6_t_u = c6_l_hoistedGlobal;
  c6_w_y = NULL;
  sf_mex_assign(&c6_w_y, sf_mex_create("y", &c6_t_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 13, c6_w_y);
  c6_m_hoistedGlobal = chartInstance->c6_is_see_saw_mode;
  c6_u_u = c6_m_hoistedGlobal;
  c6_x_y = NULL;
  sf_mex_assign(&c6_x_y, sf_mex_create("y", &c6_u_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 14, c6_x_y);
  c6_n_hoistedGlobal = chartInstance->c6_is_SeesawLogic;
  c6_v_u = c6_n_hoistedGlobal;
  c6_y_y = NULL;
  sf_mex_assign(&c6_y_y, sf_mex_create("y", &c6_v_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 15, c6_y_y);
  c6_o_hoistedGlobal = chartInstance->c6_is_Curvature;
  c6_w_u = c6_o_hoistedGlobal;
  c6_ab_y = NULL;
  sf_mex_assign(&c6_ab_y, sf_mex_create("y", &c6_w_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 16, c6_ab_y);
  c6_p_hoistedGlobal = chartInstance->c6_is_Ramp;
  c6_x_u = c6_p_hoistedGlobal;
  c6_bb_y = NULL;
  sf_mex_assign(&c6_bb_y, sf_mex_create("y", &c6_x_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 17, c6_bb_y);
  c6_q_hoistedGlobal = chartInstance->c6_temporalCounter_i1;
  c6_y_u = c6_q_hoistedGlobal;
  c6_cb_y = NULL;
  sf_mex_assign(&c6_cb_y, sf_mex_create("y", &c6_y_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 18, c6_cb_y);
  for (c6_i0 = 0; c6_i0 < 13; c6_i0++) {
    c6_ab_u[c6_i0] = chartInstance->c6_dataWrittenToVector[c6_i0];
  }

  c6_db_y = NULL;
  sf_mex_assign(&c6_db_y, sf_mex_create("y", c6_ab_u, 11, 0U, 1U, 0U, 1, 13),
                false);
  sf_mex_setcell(c6_y, 19, c6_db_y);
  sf_mex_assign(&c6_st, c6_y, false);
  return c6_st;
}

static void set_sim_state_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  c6_PWM_bus c6_r1;
  c6_Init_Bus c6_r2;
  boolean_T c6_bv0[13];
  int32_T c6_i1;
  c6_u = sf_mex_dup(c6_st);
  *chartInstance->c6_BT_status_out = c6_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 0)), "BT_status_out");
  c6_r1 = c6_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 1)),
    "PWM");
  *(real32_T *)&((char_T *)chartInstance->c6_PWM)[0] = c6_r1.left;
  *(real32_T *)&((char_T *)chartInstance->c6_PWM)[4] = c6_r1.right;
  *(real32_T *)&((char_T *)chartInstance->c6_PWM)[8] = c6_r1.tail;
  c6_r2 = c6_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 2)),
    "initFlags");
  *(boolean_T *)&((char_T *)chartInstance->c6_initFlags)[0] = c6_r2.fall;
  *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[4] = c6_r2.gyroInit;
  *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[8] = c6_r2.gyroReset;
  *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[12] = c6_r2.theta;
  *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[16] = c6_r2.tail;
  chartInstance->c6_des_vel = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 3)), "des_vel");
  chartInstance->c6_desired_phi = c6_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 4)), "desired_phi");
  chartInstance->c6_desired_tail = c6_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 5)), "desired_tail");
  chartInstance->c6_desiredangle = c6_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 6)), "desiredangle");
  chartInstance->c6_forwardPWM = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 7)), "forwardPWM");
  chartInstance->c6_normalizedLight = c6_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 8)), "normalizedLight");
  chartInstance->c6_turningPWM = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 9)), "turningPWM");
  chartInstance->c6_is_active_c6_et_robocon = c6_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 10)),
     "is_active_c6_et_robocon");
  chartInstance->c6_is_active_After = c6_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 11)), "is_active_After");
  chartInstance->c6_is_active_SeesawLogic = c6_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 12)), "is_active_SeesawLogic");
  chartInstance->c6_is_c6_et_robocon = c6_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 13)), "is_c6_et_robocon");
  chartInstance->c6_is_see_saw_mode = c6_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 14)), "is_see_saw_mode");
  chartInstance->c6_is_SeesawLogic = c6_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 15)), "is_SeesawLogic");
  chartInstance->c6_is_Curvature = c6_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 16)), "is_Curvature");
  chartInstance->c6_is_Ramp = c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 17)), "is_Ramp");
  chartInstance->c6_temporalCounter_i1 = c6_p_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 18)), "temporalCounter_i1");
  c6_r_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 19)),
                        "dataWrittenToVector", c6_bv0);
  for (c6_i1 = 0; c6_i1 < 13; c6_i1++) {
    chartInstance->c6_dataWrittenToVector[c6_i1] = c6_bv0[c6_i1];
  }

  sf_mex_assign(&chartInstance->c6_setSimStateSideEffectsInfo,
                c6_t_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c6_u, 20)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c6_u);
  chartInstance->c6_doSetSimStateSideEffects = 1U;
  c6_update_debugger_state_c6_et_robocon(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void c6_set_sim_state_side_effects_c6_et_robocon
  (SFc6_et_roboconInstanceStruct *chartInstance)
{
  if (chartInstance->c6_doSetSimStateSideEffects != 0) {
    if (chartInstance->c6_is_c6_et_robocon == c6_IN_see_saw_mode) {
      chartInstance->c6_tp_see_saw_mode = 1U;
      if (sf_mex_sub(chartInstance->c6_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 2) == 0.0) {
        sf_call_output_fcn_enable(chartInstance->S, 1, "balance_ctrl", 0);
        sf_call_output_fcn_enable(chartInstance->S, 2, "lineTracker", 0);
        sf_call_output_fcn_enable(chartInstance->S, 0, "processLight", 0);
      }
    } else {
      chartInstance->c6_tp_see_saw_mode = 0U;
      if (sf_mex_sub(chartInstance->c6_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 2) > 0.0) {
        sf_call_output_fcn_disable(chartInstance->S, 1, "balance_ctrl", 0);
        sf_call_output_fcn_disable(chartInstance->S, 2, "lineTracker", 0);
        sf_call_output_fcn_disable(chartInstance->S, 0, "processLight", 0);
      }
    }

    if (chartInstance->c6_is_see_saw_mode == c6_IN_Balancing) {
      chartInstance->c6_tp_Balancing = 1U;
    } else {
      chartInstance->c6_tp_Balancing = 0U;
    }

    if (chartInstance->c6_is_active_After == 1U) {
      chartInstance->c6_tp_After = 1U;
    } else {
      chartInstance->c6_tp_After = 0U;
    }

    if (chartInstance->c6_is_active_SeesawLogic == 1U) {
      chartInstance->c6_tp_SeesawLogic = 1U;
    } else {
      chartInstance->c6_tp_SeesawLogic = 0U;
    }

    if (chartInstance->c6_is_SeesawLogic == c6_IN_ConstantSpeed) {
      chartInstance->c6_tp_ConstantSpeed = 1U;
    } else {
      chartInstance->c6_tp_ConstantSpeed = 0U;
    }

    if (chartInstance->c6_is_SeesawLogic == c6_IN_Curvature) {
      chartInstance->c6_tp_Curvature = 1U;
    } else {
      chartInstance->c6_tp_Curvature = 0U;
    }

    if (chartInstance->c6_is_Curvature == c6_IN_Const) {
      chartInstance->c6_tp_Const = 1U;
    } else {
      chartInstance->c6_tp_Const = 0U;
    }

    if (chartInstance->c6_is_Curvature == c6_IN_Slowdown) {
      chartInstance->c6_tp_Slowdown = 1U;
    } else {
      chartInstance->c6_tp_Slowdown = 0U;
    }

    if (chartInstance->c6_is_SeesawLogic == c6_IN_MoveForwardSlowly) {
      chartInstance->c6_tp_MoveForwardSlowly = 1U;
      if (sf_mex_sub(chartInstance->c6_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 10) == 0.0) {
        chartInstance->c6_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c6_tp_MoveForwardSlowly = 0U;
    }

    if (chartInstance->c6_is_SeesawLogic == c6_IN_Ramp) {
      chartInstance->c6_tp_Ramp = 1U;
    } else {
      chartInstance->c6_tp_Ramp = 0U;
    }

    if (chartInstance->c6_is_Ramp == c6_IN_BridgeTest) {
      chartInstance->c6_tp_BridgeTest = 1U;
      if (sf_mex_sub(chartInstance->c6_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 12) == 0.0) {
        chartInstance->c6_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c6_tp_BridgeTest = 0U;
    }

    if (chartInstance->c6_is_Ramp == c6_IN_RampUpOne) {
      chartInstance->c6_tp_RampUpOne = 1U;
    } else {
      chartInstance->c6_tp_RampUpOne = 0U;
    }

    if (chartInstance->c6_is_Ramp == c6_IN_RampUpTwo) {
      chartInstance->c6_tp_RampUpTwo = 1U;
      if (sf_mex_sub(chartInstance->c6_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 14) == 0.0) {
        chartInstance->c6_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c6_tp_RampUpTwo = 0U;
    }

    if (chartInstance->c6_is_Ramp == c6_IN_RotateInPlace) {
      chartInstance->c6_tp_RotateInPlace = 1U;
    } else {
      chartInstance->c6_tp_RotateInPlace = 0U;
    }

    if (chartInstance->c6_is_Ramp == c6_IN_SlowtoRotate) {
      chartInstance->c6_tp_SlowtoRotate = 1U;
    } else {
      chartInstance->c6_tp_SlowtoRotate = 0U;
    }

    if (chartInstance->c6_is_Ramp == c6_IN_Stop) {
      chartInstance->c6_tp_Stop = 1U;
    } else {
      chartInstance->c6_tp_Stop = 0U;
    }

    if (chartInstance->c6_is_SeesawLogic == c6_IN_SpeedUp) {
      chartInstance->c6_tp_SpeedUp = 1U;
    } else {
      chartInstance->c6_tp_SpeedUp = 0U;
    }

    if (chartInstance->c6_is_SeesawLogic == c6_IN_StationnaryBalance) {
      chartInstance->c6_tp_StationnaryBalance = 1U;
      if (sf_mex_sub(chartInstance->c6_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 19) == 0.0) {
        chartInstance->c6_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c6_tp_StationnaryBalance = 0U;
    }

    if (chartInstance->c6_is_see_saw_mode == c6_IN_StandUp) {
      chartInstance->c6_tp_StandUp = 1U;
    } else {
      chartInstance->c6_tp_StandUp = 0U;
    }

    if (chartInstance->c6_is_see_saw_mode == c6_IN_Waiting) {
      chartInstance->c6_tp_Waiting = 1U;
    } else {
      chartInstance->c6_tp_Waiting = 0U;
    }

    chartInstance->c6_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c6_setSimStateSideEffectsInfo);
}

static void sf_gateway_c6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  c6_set_sim_state_side_effects_c6_et_robocon(chartInstance);
}

static void mdl_start_c6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static boolean_T isStablec6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  return chartInstance->c6_isStable;
}

static void duringc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c6_isStable = true;
  c6_see_saw_mode(chartInstance);
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
}

static void enterc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  uint32_T c6_debug_family_var_map[2];
  real_T c6_nargin = 0.0;
  real_T c6_nargout = 0.0;
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
  chartInstance->c6_is_active_c6_et_robocon = 1U;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
  chartInstance->c6_isStable = false;
  chartInstance->c6_is_c6_et_robocon = c6_IN_see_saw_mode;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
  chartInstance->c6_tp_see_saw_mode = 1U;
  sf_call_output_fcn_enable(chartInstance->S, 1, "balance_ctrl", 0);
  sf_call_output_fcn_enable(chartInstance->S, 2, "lineTracker", 0);
  sf_call_output_fcn_enable(chartInstance->S, 0, "processLight", 0);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 0U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 1U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  chartInstance->c6_des_vel = 0.0F;
  c6_updateDataWrittenToVector(chartInstance, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
  chartInstance->c6_desired_tail = 0.0F;
  c6_updateDataWrittenToVector(chartInstance, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_tail, 5U);
  *chartInstance->c6_BT_status_out = 11.0F;
  c6_updateDataWrittenToVector(chartInstance, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_BT_status_out, 9U);
  sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL, NULL);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
  chartInstance->c6_isStable = false;
  chartInstance->c6_is_see_saw_mode = c6_IN_Waiting;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 19U, chartInstance->c6_sfEvent);
  chartInstance->c6_tp_Waiting = 1U;
}

static void exitc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  switch (chartInstance->c6_is_see_saw_mode) {
   case c6_IN_Balancing:
    CV_STATE_EVAL(0, 1, 1);
    switch (chartInstance->c6_is_SeesawLogic) {
     case c6_IN_ConstantSpeed:
      CV_STATE_EVAL(3, 1, 1);
      chartInstance->c6_tp_ConstantSpeed = 0U;
      chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
      break;

     case c6_IN_Curvature:
      CV_STATE_EVAL(3, 1, 2);
      c6_exit_internal_Curvature(chartInstance);
      chartInstance->c6_tp_Curvature = 0U;
      chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
      break;

     case c6_IN_MoveForwardSlowly:
      CV_STATE_EVAL(3, 1, 3);
      chartInstance->c6_tp_MoveForwardSlowly = 0U;
      chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
      break;

     case c6_IN_Ramp:
      CV_STATE_EVAL(3, 1, 4);
      switch (chartInstance->c6_is_Ramp) {
       case c6_IN_BridgeTest:
        CV_STATE_EVAL(9, 1, 1);
        chartInstance->c6_tp_BridgeTest = 0U;
        chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
        break;

       case c6_IN_RampUpOne:
        CV_STATE_EVAL(9, 1, 2);
        chartInstance->c6_tp_RampUpOne = 0U;
        chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
        break;

       case c6_IN_RampUpTwo:
        CV_STATE_EVAL(9, 1, 3);
        chartInstance->c6_tp_RampUpTwo = 0U;
        chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
        break;

       case c6_IN_RotateInPlace:
        CV_STATE_EVAL(9, 1, 4);
        chartInstance->c6_tp_RotateInPlace = 0U;
        chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
        break;

       case c6_IN_SlowtoRotate:
        CV_STATE_EVAL(9, 1, 5);
        chartInstance->c6_tp_SlowtoRotate = 0U;
        chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
        break;

       case c6_IN_Stop:
        CV_STATE_EVAL(9, 1, 6);
        chartInstance->c6_tp_Stop = 0U;
        chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c6_sfEvent);
        break;

       default:
        CV_STATE_EVAL(9, 1, 0);
        chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
        break;
      }

      chartInstance->c6_tp_Ramp = 0U;
      chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
      break;

     case c6_IN_SpeedUp:
      CV_STATE_EVAL(3, 1, 5);
      chartInstance->c6_tp_SpeedUp = 0U;
      chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c6_sfEvent);
      break;

     case c6_IN_StationnaryBalance:
      CV_STATE_EVAL(3, 1, 6);
      chartInstance->c6_tp_StationnaryBalance = 0U;
      c6_exit_atomic_StationnaryBalance(chartInstance);
      chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c6_sfEvent);
      break;

     default:
      CV_STATE_EVAL(3, 1, 0);
      chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
      break;
    }

    chartInstance->c6_tp_SeesawLogic = 0U;
    chartInstance->c6_is_active_SeesawLogic = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_After = 0U;
    chartInstance->c6_is_active_After = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_Balancing = 0U;
    chartInstance->c6_is_see_saw_mode = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_StandUp:
    CV_STATE_EVAL(0, 1, 2);
    chartInstance->c6_tp_StandUp = 0U;
    chartInstance->c6_is_see_saw_mode = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_Waiting:
    CV_STATE_EVAL(0, 1, 3);
    chartInstance->c6_tp_Waiting = 0U;
    chartInstance->c6_is_see_saw_mode = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 1, 0);
    chartInstance->c6_is_see_saw_mode = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
    break;
  }

  chartInstance->c6_tp_see_saw_mode = 0U;
  _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
  sf_call_output_fcn_disable(chartInstance->S, 1, "balance_ctrl", 0);
  sf_call_output_fcn_disable(chartInstance->S, 2, "lineTracker", 0);
  sf_call_output_fcn_disable(chartInstance->S, 0, "processLight", 0);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
  chartInstance->c6_is_c6_et_robocon = c6_IN_NO_ACTIVE_CHILD;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
}

static void gatewayc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c6_temporalCounter_i1 < 8191U) {
    chartInstance->c6_temporalCounter_i1++;
  }
}

static void enablec6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c6_is_c6_et_robocon == c6_IN_see_saw_mode) {
    sf_call_output_fcn_enable(chartInstance->S, 1, "balance_ctrl", 0);
    sf_call_output_fcn_enable(chartInstance->S, 2, "lineTracker", 0);
    sf_call_output_fcn_enable(chartInstance->S, 0, "processLight", 0);
  }
}

static void disablec6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c6_temporalCounter_i1 < 8191U) {
    chartInstance->c6_temporalCounter_i1++;
  }

  if (chartInstance->c6_is_c6_et_robocon == c6_IN_see_saw_mode) {
    sf_call_output_fcn_disable(chartInstance->S, 1, "balance_ctrl", 0);
    sf_call_output_fcn_disable(chartInstance->S, 2, "lineTracker", 0);
    sf_call_output_fcn_disable(chartInstance->S, 0, "processLight", 0);
  }
}

static void initBuffersc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void stepBuffersc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void initc6_et_robocon(SFc6_et_roboconInstanceStruct *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c6_doSetSimStateSideEffects = 0U;
  chartInstance->c6_setSimStateSideEffectsInfo = NULL;
  chartInstance->c6_is_see_saw_mode = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_see_saw_mode = 0U;
  chartInstance->c6_tp_Balancing = 0U;
  chartInstance->c6_is_active_After = 0U;
  chartInstance->c6_tp_After = 0U;
  chartInstance->c6_is_active_SeesawLogic = 0U;
  chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_SeesawLogic = 0U;
  chartInstance->c6_tp_ConstantSpeed = 0U;
  chartInstance->c6_is_Curvature = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_Curvature = 0U;
  chartInstance->c6_tp_Const = 0U;
  chartInstance->c6_tp_Slowdown = 0U;
  chartInstance->c6_tp_MoveForwardSlowly = 0U;
  chartInstance->c6_temporalCounter_i1 = 0U;
  chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
  chartInstance->c6_tp_Ramp = 0U;
  chartInstance->c6_tp_BridgeTest = 0U;
  chartInstance->c6_temporalCounter_i1 = 0U;
  chartInstance->c6_tp_RampUpOne = 0U;
  chartInstance->c6_tp_RampUpTwo = 0U;
  chartInstance->c6_temporalCounter_i1 = 0U;
  chartInstance->c6_tp_RotateInPlace = 0U;
  chartInstance->c6_tp_SlowtoRotate = 0U;
  chartInstance->c6_tp_Stop = 0U;
  chartInstance->c6_tp_SpeedUp = 0U;
  chartInstance->c6_tp_StationnaryBalance = 0U;
  chartInstance->c6_temporalCounter_i1 = 0U;
  chartInstance->c6_tp_StandUp = 0U;
  chartInstance->c6_tp_Waiting = 0U;
  chartInstance->c6_is_active_c6_et_robocon = 0U;
  chartInstance->c6_is_c6_et_robocon = c6_IN_NO_ACTIVE_CHILD;
}

static void activate_callc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
}

static void deactivate_callc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void increment_call_counterc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void reset_call_counterc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void check_state_inconsistency_c6_et_robocon
  (SFc6_et_roboconInstanceStruct *chartInstance)
{
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_et_roboconMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc6_et_robocon(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c6_see_saw_mode(SFc6_et_roboconInstanceStruct *chartInstance)
{
  uint32_T c6_debug_family_var_map[2];
  real_T c6_nargin = 0.0;
  real_T c6_nargout = 0.0;
  real32_T c6_b_rawLight;
  c6_Light_Bus c6_b_lightCalib;
  real32_T c6_c_light;
  real32_T c6_hoistedGlobal;
  real32_T c6_b_hoistedGlobal;
  real32_T c6_c_hoistedGlobal;
  void *c6_inputVarPtrs[2];
  int32_T c6_inputVarSizes[2];
  real32_T c6_f0;
  void *c6_outputVarPtrs[1];
  int32_T c6_outputVarSizes[1];
  real_T c6_b_nargin = 0.0;
  real_T c6_b_nargout = 0.0;
  real32_T c6_d_hoistedGlobal;
  c6_Balancer_States_Bus c6_b_balancerStates;
  real32_T c6_b_desired_velocity;
  real_T c6_c_battery;
  real32_T c6_c_cmd;
  real32_T c6_e_hoistedGlobal;
  real32_T c6_u;
  const mxArray *c6_y = NULL;
  real_T c6_c_nargin = 0.0;
  real_T c6_c_nargout = 0.0;
  uint16_T c6_u0;
  void *c6_b_inputVarPtrs[1];
  int32_T c6_b_inputVarSizes[1];
  uint32_T c6_b_debug_family_var_map[3];
  real_T c6_d_nargin = 0.0;
  real_T c6_d_nargout = 1.0;
  boolean_T c6_out;
  real_T c6_e_nargin = 0.0;
  real_T c6_e_nargout = 0.0;
  uint16_T c6_u1;
  real_T c6_f_nargin = 0.0;
  real_T c6_f_nargout = 0.0;
  uint16_T c6_u2;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_b_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 0U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 1U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  c6_b_rawLight = *(real32_T *)&((char_T *)chartInstance->c6_sensors)[12];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 0, 0);
  c6_b_lightCalib.whiteOnLimbo = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[0];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 1, 0);
  c6_b_lightCalib.blackOnLimbo = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[4];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 2, 0);
  c6_b_lightCalib.black = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[8];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 3, 0);
  c6_b_lightCalib.white = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[12];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 4, 0);
  c6_b_lightCalib.black_white = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[16];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 5, 0);
  c6_b_lightCalib.gray = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[20];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 6, 0);
  c6_b_lightCalib.blackOnTail = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[24];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 7, 0);
  c6_b_lightCalib.whiteOnTail = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[28];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 8, 0);
  c6_b_lightCalib.flashingBlack = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[32];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 9, 0);
  c6_b_lightCalib.flashingWhite = *(real32_T *)&((char_T *)c6_access_lightCalib
    (chartInstance, true))[36];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 10, 0);
  c6_b_lightCalib.flashingMapBlack = *(real32_T *)&((char_T *)
    c6_access_lightCalib(chartInstance, true))[40];
  c6_bus_rd_access_lightCalib_2(chartInstance, -1, 0, 11, 0);
  c6_b_lightCalib.flashingMapWhite = *(real32_T *)&((char_T *)
    c6_access_lightCalib(chartInstance, true))[44];
  _SFD_DATA_RANGE_CHECK((real_T)c6_b_rawLight, 15U);
  _SFD_SET_DATA_VALUE_PTR(17U, &c6_c_light);
  _SFD_SET_DATA_VALUE_PTR(16U, &c6_b_lightCalib);
  _SFD_SET_DATA_VALUE_PTR(15U, &c6_b_rawLight);
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 22U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH(3U, 0U);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("rawLight", &c6_b_rawLight,
    c6_c_sf_marshallOut, c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD("lightCalib", &c6_b_lightCalib, c6_lightCalib_bus_io);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("light", &c6_c_light, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 22U, chartInstance->c6_sfEvent);
  *chartInstance->c6_rawLight = c6_b_rawLight;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_rawLight, 15U);
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[0] =
    c6_b_lightCalib.whiteOnLimbo;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[4] =
    c6_b_lightCalib.blackOnLimbo;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[8] =
    c6_b_lightCalib.black;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[12] =
    c6_b_lightCalib.white;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[16] =
    c6_b_lightCalib.black_white;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[20] =
    c6_b_lightCalib.gray;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[24] =
    c6_b_lightCalib.blackOnTail;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[28] =
    c6_b_lightCalib.whiteOnTail;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[32] =
    c6_b_lightCalib.flashingBlack;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[36] =
    c6_b_lightCalib.flashingWhite;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[40] =
    c6_b_lightCalib.flashingMapBlack;
  *(real32_T *)&((char_T *)chartInstance->c6_lightCalib)[44] =
    c6_b_lightCalib.flashingMapWhite;
  sf_call_output_fcn_call(chartInstance->S, 0, "processLight", 0);
  c6_c_light = *chartInstance->c6_light;
  c6_updateDataWrittenToVector(chartInstance, 10U);
  _SFD_DATA_RANGE_CHECK((real_T)c6_c_light, 17U);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 22U, chartInstance->c6_sfEvent);
  _SFD_UNSET_DATA_VALUE_PTR(17U);
  _SFD_UNSET_DATA_VALUE_PTR(16U);
  _SFD_UNSET_DATA_VALUE_PTR(15U);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 22U, chartInstance->c6_sfEvent);
  chartInstance->c6_normalizedLight = c6_c_light;
  c6_updateDataWrittenToVector(chartInstance, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_normalizedLight, 10U);
  c6_errorIfDataNotWrittenToFcn(chartInstance, 2U, 5U, 96U, 216, 12);
  c6_hoistedGlobal = chartInstance->c6_desired_tail;
  c6_b_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_sensors)[8];
  c6_c_hoistedGlobal = c6_hoistedGlobal;
  c6_inputVarPtrs[0U] = (void *)&c6_b_hoistedGlobal;
  c6_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
  c6_inputVarPtrs[1U] = (void *)&c6_c_hoistedGlobal;
  c6_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
  c6_outputVarPtrs[0U] = (void *)&c6_f0;
  c6_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
  sfcs_request_service(chartInstance->S, "tail_controller", 2, (void *)
                       c6_inputVarPtrs, (void *)c6_inputVarSizes, 1, (void *)
                       c6_outputVarPtrs, (void *)c6_outputVarSizes);
  *(real32_T *)&((char_T *)chartInstance->c6_PWM)[8] = c6_f0;
  c6_updateDataWrittenToVector(chartInstance, 0U);
  _SFD_SYMBOL_SCOPE_POP();
  switch (chartInstance->c6_is_see_saw_mode) {
   case c6_IN_Balancing:
    CV_STATE_EVAL(0, 0, 1);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c6_sfEvent);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_p_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 7U, 12U, 41U, 63, 7);
    c6_d_hoistedGlobal = chartInstance->c6_des_vel;
    c6_b_balancerStates.theta = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus
      *)&((char_T *)chartInstance->c6_states)[0])[0];
    c6_b_balancerStates.psi = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)
      &((char_T *)chartInstance->c6_states)[0])[4];
    c6_b_balancerStates.theta_dot = *(real32_T *)&((char_T *)
      (c6_Balancer_States_Bus *)&((char_T *)chartInstance->c6_states)[0])[8];
    c6_b_balancerStates.psi_dot = *(real32_T *)&((char_T *)
      (c6_Balancer_States_Bus *)&((char_T *)chartInstance->c6_states)[0])[12];
    c6_b_balancerStates.int_theta = *(real32_T *)&((char_T *)
      (c6_Balancer_States_Bus *)&((char_T *)chartInstance->c6_states)[0])[16];
    c6_b_desired_velocity = c6_d_hoistedGlobal;
    c6_c_battery = *(real32_T *)&((char_T *)chartInstance->c6_sensors)[24];
    _SFD_DATA_RANGE_CHECK((real_T)c6_b_desired_velocity, 19U);
    _SFD_DATA_RANGE_CHECK(c6_c_battery, 20U);
    _SFD_SET_DATA_VALUE_PTR(21U, &c6_c_cmd);
    _SFD_SET_DATA_VALUE_PTR(20U, &c6_c_battery);
    _SFD_SET_DATA_VALUE_PTR(19U, &c6_b_desired_velocity);
    _SFD_SET_DATA_VALUE_PTR(18U, &c6_b_balancerStates);
    _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 20U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH(4U, 0U);
    _SFD_SYMBOL_SCOPE_ADD("balancerStates", &c6_b_balancerStates,
                          c6_balancerStates_bus_io);
    _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("desired_velocity", &c6_b_desired_velocity,
      c6_c_sf_marshallOut, c6_c_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("battery", &c6_c_battery, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("cmd", &c6_c_cmd, c6_c_sf_marshallOut,
      c6_c_sf_marshallIn);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 20U, chartInstance->c6_sfEvent);
    *(real32_T *)&((char_T *)chartInstance->c6_balancerStates)[0] =
      c6_b_balancerStates.theta;
    *(real32_T *)&((char_T *)chartInstance->c6_balancerStates)[4] =
      c6_b_balancerStates.psi;
    *(real32_T *)&((char_T *)chartInstance->c6_balancerStates)[8] =
      c6_b_balancerStates.theta_dot;
    *(real32_T *)&((char_T *)chartInstance->c6_balancerStates)[12] =
      c6_b_balancerStates.psi_dot;
    *(real32_T *)&((char_T *)chartInstance->c6_balancerStates)[16] =
      c6_b_balancerStates.int_theta;
    *chartInstance->c6_desired_velocity = c6_b_desired_velocity;
    _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_desired_velocity, 19U);
    *chartInstance->c6_battery = c6_c_battery;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c6_battery, 20U);
    sf_call_output_fcn_call(chartInstance->S, 1, "balance_ctrl", 0);
    c6_c_cmd = *chartInstance->c6_cmd;
    c6_updateDataWrittenToVector(chartInstance, 11U);
    _SFD_DATA_RANGE_CHECK((real_T)c6_c_cmd, 21U);
    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 20U, chartInstance->c6_sfEvent);
    _SFD_UNSET_DATA_VALUE_PTR(21U);
    _SFD_UNSET_DATA_VALUE_PTR(20U);
    _SFD_UNSET_DATA_VALUE_PTR(19U);
    _SFD_UNSET_DATA_VALUE_PTR(18U);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 20U, chartInstance->c6_sfEvent);
    chartInstance->c6_forwardPWM = c6_c_cmd;
    c6_updateDataWrittenToVector(chartInstance, 6U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_forwardPWM, 11U);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 6U, 11U, 41U, 14, 10);
    sf_mex_printf("%s =\\n", "forwardPWM");
    c6_e_hoistedGlobal = chartInstance->c6_forwardPWM;
    c6_u = c6_e_hoistedGlobal;
    c6_y = NULL;
    sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 1, 0U, 0U, 0U, 0), false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c6_y);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 6U, 11U, 41U, 100, 10);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 3U, 7U, 41U, 113, 10);
    *(real32_T *)&((char_T *)chartInstance->c6_PWM)[0] =
      chartInstance->c6_forwardPWM + chartInstance->c6_turningPWM;
    c6_updateDataWrittenToVector(chartInstance, 0U);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 6U, 11U, 41U, 137, 10);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 3U, 7U, 41U, 150, 10);
    *(real32_T *)&((char_T *)chartInstance->c6_PWM)[4] =
      chartInstance->c6_forwardPWM - chartInstance->c6_turningPWM;
    c6_updateDataWrittenToVector(chartInstance, 0U);
    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c6_sfEvent);
    c6_SeesawLogic(chartInstance);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_StandUp:
    CV_STATE_EVAL(0, 0, 2);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_StandUp = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 18U, chartInstance->c6_sfEvent);
    chartInstance->c6_isStable = false;
    chartInstance->c6_is_see_saw_mode = c6_IN_Balancing;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_Balancing = 1U;
    chartInstance->c6_isStable = false;
    chartInstance->c6_is_active_After = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_After = 1U;
    chartInstance->c6_isStable = false;
    chartInstance->c6_is_active_SeesawLogic = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_SeesawLogic = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
    chartInstance->c6_isStable = false;
    chartInstance->c6_is_SeesawLogic = c6_IN_MoveForwardSlowly;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
    chartInstance->c6_temporalCounter_i1 = 0U;
    chartInstance->c6_tp_MoveForwardSlowly = 1U;
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_e_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    c6_u0 = 302U;
    c6_b_inputVarPtrs[0U] = (void *)&c6_u0;
    c6_b_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
    sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                         c6_b_inputVarPtrs, (void *)c6_b_inputVarSizes, 0, NULL,
                         NULL);
    *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[12] = 0.0F;
    c6_updateDataWrittenToVector(chartInstance, 1U);
    *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[8] = 0.0F;
    c6_updateDataWrittenToVector(chartInstance, 1U);
    chartInstance->c6_des_vel = 0.0005F;
    c6_updateDataWrittenToVector(chartInstance, 7U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 18U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_Waiting:
    CV_STATE_EVAL(0, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_db_debug_family_names,
      c6_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_d_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_d_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    c6_out = CV_EML_IF(3, 0, 0, *(real32_T *)&((char_T *)
      chartInstance->c6_sensors)[28] != 0.0F);
    _SFD_SYMBOL_SCOPE_POP();
    if (c6_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_Waiting = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 19U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_see_saw_mode = c6_IN_StandUp;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 18U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_StandUp = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_d_debug_family_names,
        c6_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_e_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_e_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      c6_u1 = 301U;
      c6_b_inputVarPtrs[0U] = (void *)&c6_u1;
      c6_b_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_b_inputVarPtrs, (void *)c6_b_inputVarSizes, 0,
                           NULL, NULL);
      *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[12] = 1.0F;
      c6_updateDataWrittenToVector(chartInstance, 1U);
      *(real32_T *)&((char_T *)chartInstance->c6_initFlags)[8] = 1.0F;
      c6_updateDataWrittenToVector(chartInstance, 1U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 19U,
                   chartInstance->c6_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_c_debug_family_names,
        c6_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_f_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_f_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      c6_u2 = 300U;
      c6_b_inputVarPtrs[0U] = (void *)&c6_u2;
      c6_b_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_b_inputVarPtrs, (void *)c6_b_inputVarSizes, 0,
                           NULL, NULL);
      _SFD_SYMBOL_SCOPE_POP();
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 19U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 0, 0);
    chartInstance->c6_is_see_saw_mode = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
}

static void c6_SeesawLogic(SFc6_et_roboconInstanceStruct *chartInstance)
{
  uint32_T c6_debug_family_var_map[3];
  real_T c6_nargin = 0.0;
  real_T c6_nargout = 1.0;
  boolean_T c6_out;
  uint32_T c6_b_debug_family_var_map[2];
  real_T c6_b_nargin = 0.0;
  real_T c6_b_nargout = 0.0;
  real_T c6_c_nargin = 0.0;
  real_T c6_c_nargout = 0.0;
  real_T c6_d_nargin = 0.0;
  real_T c6_d_nargout = 1.0;
  boolean_T c6_b_out;
  real_T c6_e_nargin = 0.0;
  real_T c6_e_nargout = 0.0;
  uint16_T c6_u3;
  void *c6_inputVarPtrs[1];
  int32_T c6_inputVarSizes[1];
  real_T c6_f_nargin = 0.0;
  real_T c6_f_nargout = 0.0;
  real_T c6_g_nargin = 0.0;
  real_T c6_g_nargout = 1.0;
  boolean_T c6_c_out;
  real_T c6_h_nargin = 0.0;
  real_T c6_h_nargout = 0.0;
  uint16_T c6_u4;
  real_T c6_i_nargin = 0.0;
  real_T c6_i_nargout = 0.0;
  real_T c6_j_nargin = 0.0;
  real_T c6_j_nargout = 1.0;
  boolean_T c6_d_out;
  real_T c6_k_nargin = 0.0;
  real_T c6_k_nargout = 0.0;
  real_T c6_l_nargin = 0.0;
  real_T c6_l_nargout = 1.0;
  boolean_T c6_e_out;
  real_T c6_m_nargin = 0.0;
  real_T c6_m_nargout = 0.0;
  uint16_T c6_u5;
  real_T c6_n_nargin = 0.0;
  real_T c6_n_nargout = 1.0;
  boolean_T c6_f_out;
  real_T c6_o_nargin = 0.0;
  real_T c6_o_nargout = 0.0;
  uint16_T c6_u6;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
  switch (chartInstance->c6_is_SeesawLogic) {
   case c6_IN_ConstantSpeed:
    CV_STATE_EVAL(3, 0, 1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_ib_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    guard3 = false;
    if (CV_EML_COND(7, 0, 0, CV_RELATIONAL_EVAL(5U, 7U, 0, 30.0, (real_T)
          *(real32_T *)&((char_T *)chartInstance->c6_states)[24], -1, 2U, 30.0F <
          *(real32_T *)&((char_T *)chartInstance->c6_states)[24]))) {
      guard3 = true;
    } else {
      if (CV_EML_COND(7, 0, 1, CV_RELATIONAL_EVAL(5U, 7U, 1, (real_T)*(real32_T *)
            &((char_T *)chartInstance->c6_states)[24], -30.0, -1, 2U, *(real32_T
             *)&((char_T *)chartInstance->c6_states)[24] < -30.0F))) {
        guard3 = true;
      }
    }

    if (guard3 == true) {
      CV_EML_COND(7, 0, 2, false);
    }

    CV_EML_MCDC(7, 0, 0, false);
    CV_EML_IF(7, 0, 0, false);
    c6_out = false;
    _SFD_SYMBOL_SCOPE_POP();
    if (c6_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_ConstantSpeed = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_SeesawLogic = c6_IN_Curvature;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_Curvature = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_h_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_Curvature = c6_IN_Slowdown;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_Slowdown = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_i_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      chartInstance->c6_des_vel = 0.2F;
      c6_updateDataWrittenToVector(chartInstance, 7U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 16U,
                   chartInstance->c6_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_pb_debug_family_names,
        c6_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_d_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_d_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_out, 2U, c6_b_sf_marshallOut,
        c6_b_sf_marshallIn);
      guard2 = false;
      if (CV_EML_COND(16, 0, 0, *(real32_T *)&((char_T *)
            chartInstance->c6_sensors)[28] != 0.0F)) {
        guard2 = true;
      } else if (CV_EML_COND(16, 0, 1, CV_RELATIONAL_EVAL(5U, 16U, 0, (real_T)
                   *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)&((char_T *)
          chartInstance->c6_states)[0])[8], 0.800000011920929, -3, 2U,
                   *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)&((char_T *)
          chartInstance->c6_states)[0])[8] < 0.8F))) {
        guard2 = true;
      } else {
        CV_EML_MCDC(16, 0, 0, false);
        CV_EML_IF(16, 0, 0, false);
        c6_b_out = false;
      }

      if (guard2 == true) {
        CV_EML_MCDC(16, 0, 0, true);
        CV_EML_IF(16, 0, 0, true);
        c6_b_out = true;
      }

      _SFD_SYMBOL_SCOPE_POP();
      if (c6_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_ConstantSpeed = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
        chartInstance->c6_isStable = false;
        chartInstance->c6_is_SeesawLogic = c6_IN_Ramp;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_Ramp = 1U;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c6_sfEvent);
        chartInstance->c6_isStable = false;
        chartInstance->c6_is_Ramp = c6_IN_RampUpOne;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
        chartInstance->c6_tp_RampUpOne = 1U;
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_q_debug_family_names,
          c6_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_e_nargin, 0U, c6_sf_marshallOut,
          c6_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_e_nargout, 1U,
          c6_sf_marshallOut, c6_sf_marshallIn);
        chartInstance->c6_desired_phi = *(real32_T *)&((char_T *)
          chartInstance->c6_states)[24];
        c6_updateDataWrittenToVector(chartInstance, 8U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_phi, 13U);
        sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                             NULL);
        c6_u3 = 3061U;
        c6_inputVarPtrs[0U] = (void *)&c6_u3;
        c6_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
        sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                             c6_inputVarPtrs, (void *)c6_inputVarSizes, 0, NULL,
                             NULL);
        chartInstance->c6_des_vel = 0.05F;
        c6_updateDataWrittenToVector(chartInstance, 7U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
        _SFD_SYMBOL_SCOPE_POP();
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                     chartInstance->c6_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_o_debug_family_names,
          c6_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_f_nargin, 0U, c6_sf_marshallOut,
          c6_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_f_nargout, 1U,
          c6_sf_marshallOut, c6_sf_marshallIn);
        c6_errorIfDataNotWrittenToFcn(chartInstance, 5U, 10U, 217U, 100, 15);
        chartInstance->c6_turningPWM = c6_lineTracker(chartInstance, -0.15F,
          chartInstance->c6_normalizedLight, 1.2F, (real_T)*(real32_T *)
          &((char_T *)chartInstance->c6_sensors)[24]);
        c6_updateDataWrittenToVector(chartInstance, 3U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
        _SFD_SYMBOL_SCOPE_POP();
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_Curvature:
    CV_STATE_EVAL(3, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                 chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_gb_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_g_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_g_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    guard1 = false;
    if (CV_EML_COND(10, 0, 0, CV_RELATIONAL_EVAL(5U, 10U, 0, (real_T)*(real32_T *)
          &((char_T *)chartInstance->c6_states)[24], 15.0, -1, 2U, *(real32_T *)
          &((char_T *)chartInstance->c6_states)[24] < 15.0F))) {
      if (CV_EML_COND(10, 0, 1, CV_RELATIONAL_EVAL(5U, 10U, 1, -15.0, (real_T)
            *(real32_T *)&((char_T *)chartInstance->c6_states)[24], -1, 2U,
            -15.0F < *(real32_T *)&((char_T *)chartInstance->c6_states)[24]))) {
        CV_EML_MCDC(10, 0, 0, true);
        CV_EML_IF(10, 0, 0, true);
        c6_c_out = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1 == true) {
      CV_EML_MCDC(10, 0, 0, false);
      CV_EML_IF(10, 0, 0, false);
      c6_c_out = false;
    }

    _SFD_SYMBOL_SCOPE_POP();
    if (c6_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
      c6_exit_internal_Curvature(chartInstance);
      chartInstance->c6_tp_Curvature = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_SeesawLogic = c6_IN_SpeedUp;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_SpeedUp = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_l_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_h_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_h_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      c6_u4 = 304U;
      c6_inputVarPtrs[0U] = (void *)&c6_u4;
      c6_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_inputVarPtrs, (void *)c6_inputVarSizes, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                   chartInstance->c6_sfEvent);
      switch (chartInstance->c6_is_Curvature) {
       case c6_IN_Const:
        CV_STATE_EVAL(5, 0, 1);
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                     chartInstance->c6_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_k_debug_family_names,
          c6_b_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_i_nargin, 0U, c6_sf_marshallOut,
          c6_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_i_nargout, 1U,
          c6_sf_marshallOut, c6_sf_marshallIn);
        c6_errorIfDataNotWrittenToFcn(chartInstance, 5U, 10U, 238U, 53, 15);
        chartInstance->c6_turningPWM = c6_lineTracker(chartInstance, -0.1F,
          chartInstance->c6_normalizedLight, 1.2F, (real_T)*(real32_T *)
          &((char_T *)chartInstance->c6_sensors)[24]);
        c6_updateDataWrittenToVector(chartInstance, 3U);
        _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
        _SFD_SYMBOL_SCOPE_POP();
        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c6_sfEvent);
        break;

       case c6_IN_Slowdown:
        CV_STATE_EVAL(5, 0, 2);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U,
                     chartInstance->c6_sfEvent);
        _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_jb_debug_family_names,
          c6_debug_family_var_map);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_j_nargin, 0U, c6_sf_marshallOut,
          c6_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_j_nargout, 1U,
          c6_sf_marshallOut, c6_sf_marshallIn);
        _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_d_out, 2U, c6_b_sf_marshallOut,
          c6_b_sf_marshallIn);
        c6_errorIfDataNotWrittenToFcn(chartInstance, 7U, 12U, 239U, 1, 7);
        c6_d_out = CV_EML_IF(9, 0, 0, CV_RELATIONAL_EVAL(5U, 9U, 0, (real_T)
          chartInstance->c6_des_vel, 0.09, -1, 3U, (real_T)
          chartInstance->c6_des_vel <= 0.09));
        _SFD_SYMBOL_SCOPE_POP();
        if (c6_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
          chartInstance->c6_tp_Slowdown = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
          chartInstance->c6_isStable = false;
          chartInstance->c6_is_Curvature = c6_IN_Const;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
          chartInstance->c6_tp_Const = 1U;
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                       chartInstance->c6_sfEvent);
          _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_j_debug_family_names,
            c6_b_debug_family_var_map);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_k_nargin, 0U,
            c6_sf_marshallOut, c6_sf_marshallIn);
          _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_k_nargout, 1U,
            c6_sf_marshallOut, c6_sf_marshallIn);
          c6_errorIfDataNotWrittenToFcn(chartInstance, 7U, 12U, 235U, 56, 7);
          chartInstance->c6_des_vel -= 0.0005F;
          c6_updateDataWrittenToVector(chartInstance, 7U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
          c6_errorIfDataNotWrittenToFcn(chartInstance, 5U, 10U, 235U, 119, 15);
          chartInstance->c6_turningPWM = c6_lineTracker(chartInstance, -0.1F,
            chartInstance->c6_normalizedLight, 0.8F, (real_T)*(real32_T *)
            &((char_T *)chartInstance->c6_sensors)[24]);
          c6_updateDataWrittenToVector(chartInstance, 3U);
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
          _SFD_SYMBOL_SCOPE_POP();
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c6_sfEvent);
        break;

       default:
        CV_STATE_EVAL(5, 0, 0);
        chartInstance->c6_is_Curvature = c6_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
        break;
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_MoveForwardSlowly:
    CV_STATE_EVAL(3, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_eb_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_l_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_l_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_e_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    c6_e_out = CV_EML_IF(4, 0, 0, chartInstance->c6_temporalCounter_i1 >= 500);
    _SFD_SYMBOL_SCOPE_POP();
    if (c6_e_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_MoveForwardSlowly = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_SeesawLogic = c6_IN_StationnaryBalance;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 17U, chartInstance->c6_sfEvent);
      chartInstance->c6_temporalCounter_i1 = 0U;
      chartInstance->c6_tp_StationnaryBalance = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_f_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_m_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_m_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      c6_u5 = 303U;
      c6_inputVarPtrs[0U] = (void *)&c6_u5;
      c6_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_inputVarPtrs, (void *)c6_inputVarSizes, 0, NULL,
                           NULL);
      chartInstance->c6_des_vel = 0.0005F;
      c6_updateDataWrittenToVector(chartInstance, 7U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
      chartInstance->c6_desired_phi = *(real32_T *)&((char_T *)
        chartInstance->c6_states)[24];
      c6_updateDataWrittenToVector(chartInstance, 8U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_phi, 13U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                   chartInstance->c6_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_Ramp:
    CV_STATE_EVAL(3, 0, 4);
    c6_Ramp(chartInstance);
    break;

   case c6_IN_SpeedUp:
    CV_STATE_EVAL(3, 0, 5);
    c6_SpeedUp(chartInstance);
    break;

   case c6_IN_StationnaryBalance:
    CV_STATE_EVAL(3, 0, 6);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_fb_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_n_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_n_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_f_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    c6_f_out = CV_EML_IF(5, 0, 0, chartInstance->c6_temporalCounter_i1 >= 20);
    _SFD_SYMBOL_SCOPE_POP();
    if (c6_f_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_StationnaryBalance = 0U;
      c6_exit_atomic_StationnaryBalance(chartInstance);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 17U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_SeesawLogic = c6_IN_SpeedUp;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_SpeedUp = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_l_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_o_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_o_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      c6_u6 = 304U;
      c6_inputVarPtrs[0U] = (void *)&c6_u6;
      c6_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_inputVarPtrs, (void *)c6_inputVarSizes, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 17U,
                   chartInstance->c6_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(3, 0, 0);
    chartInstance->c6_is_SeesawLogic = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c6_sfEvent);
}

static void c6_exit_atomic_StationnaryBalance(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  uint32_T c6_debug_family_var_map[2];
  real_T c6_nargin = 0.0;
  real_T c6_nargout = 0.0;
  real32_T c6_hoistedGlobal;
  real32_T c6_b_hoistedGlobal;
  real32_T c6_c_hoistedGlobal;
  real32_T c6_d_hoistedGlobal;
  void *c6_inputVarPtrs[3];
  int32_T c6_inputVarSizes[3];
  real32_T c6_f1;
  void *c6_outputVarPtrs[1];
  int32_T c6_outputVarSizes[1];
  _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 17U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_g_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 0U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 1U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  c6_errorIfDataNotWrittenToFcn(chartInstance, 8U, 13U, 200U, 180, 11);
  c6_hoistedGlobal = chartInstance->c6_desired_phi;
  c6_b_hoistedGlobal = c6_hoistedGlobal;
  c6_c_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_states)[24];
  c6_d_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_sensors)[24];
  c6_inputVarPtrs[0U] = (void *)&c6_b_hoistedGlobal;
  c6_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
  c6_inputVarPtrs[1U] = (void *)&c6_c_hoistedGlobal;
  c6_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
  c6_inputVarPtrs[2U] = (void *)&c6_d_hoistedGlobal;
  c6_inputVarSizes[2U] = (int32_T)sizeof(real32_T);
  c6_outputVarPtrs[0U] = (void *)&c6_f1;
  c6_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
  sfcs_request_service(chartInstance->S, "phiController", 3, (void *)
                       c6_inputVarPtrs, (void *)c6_inputVarSizes, 1, (void *)
                       c6_outputVarPtrs, (void *)c6_outputVarSizes);
  chartInstance->c6_turningPWM = c6_f1;
  c6_updateDataWrittenToVector(chartInstance, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 17U, chartInstance->c6_sfEvent);
}

static void c6_exit_internal_Curvature(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c6_is_Curvature) {
   case c6_IN_Const:
    CV_STATE_EVAL(5, 1, 1);
    chartInstance->c6_tp_Const = 0U;
    chartInstance->c6_is_Curvature = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_Slowdown:
    CV_STATE_EVAL(5, 1, 2);
    chartInstance->c6_tp_Slowdown = 0U;
    chartInstance->c6_is_Curvature = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(5, 1, 0);
    chartInstance->c6_is_Curvature = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
    break;
  }
}

static void c6_SpeedUp(SFc6_et_roboconInstanceStruct *chartInstance)
{
  uint32_T c6_debug_family_var_map[3];
  real_T c6_nargin = 0.0;
  real_T c6_nargout = 1.0;
  boolean_T c6_out;
  uint32_T c6_b_debug_family_var_map[2];
  real_T c6_b_nargin = 0.0;
  real_T c6_b_nargout = 0.0;
  uint16_T c6_u7;
  void *c6_inputVarPtrs[1];
  int32_T c6_inputVarSizes[1];
  real_T c6_c_nargin = 0.0;
  real_T c6_c_nargout = 0.0;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_hb_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 0U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 1U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_out, 2U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  c6_errorIfDataNotWrittenToFcn(chartInstance, 7U, 12U, 218U, 1, 7);
  c6_out = CV_EML_IF(6, 0, 0, CV_RELATIONAL_EVAL(5U, 6U, 0, (real_T)
    chartInstance->c6_des_vel, 0.15, -1, 5U, (real_T)chartInstance->c6_des_vel >=
    0.15));
  _SFD_SYMBOL_SCOPE_POP();
  if (c6_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_SpeedUp = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c6_sfEvent);
    chartInstance->c6_isStable = false;
    chartInstance->c6_is_SeesawLogic = c6_IN_ConstantSpeed;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_ConstantSpeed = 1U;
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_n_debug_family_names,
      c6_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL, NULL);
    c6_u7 = 305U;
    c6_inputVarPtrs[0U] = (void *)&c6_u7;
    c6_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
    sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                         c6_inputVarPtrs, (void *)c6_inputVarSizes, 0, NULL,
                         NULL);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 16U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_m_debug_family_names,
      c6_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 7U, 12U, 211U, 90, 7);
    chartInstance->c6_des_vel += 0.0005F;
    c6_updateDataWrittenToVector(chartInstance, 7U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 5U, 10U, 211U, 154, 15);
    chartInstance->c6_turningPWM = c6_lineTracker(chartInstance, -0.15F,
      chartInstance->c6_normalizedLight, 1.2F, (real_T)*(real32_T *)&((char_T *)
      chartInstance->c6_sensors)[24]);
    c6_updateDataWrittenToVector(chartInstance, 3U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
    _SFD_SYMBOL_SCOPE_POP();
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c6_sfEvent);
}

static void c6_Ramp(SFc6_et_roboconInstanceStruct *chartInstance)
{
  uint32_T c6_debug_family_var_map[3];
  real_T c6_nargin = 0.0;
  real_T c6_nargout = 1.0;
  boolean_T c6_out;
  uint32_T c6_b_debug_family_var_map[2];
  real_T c6_b_nargin = 0.0;
  real_T c6_b_nargout = 0.0;
  uint16_T c6_u8;
  void *c6_outputVarPtrs[1];
  int32_T c6_outputVarSizes[1];
  real_T c6_c_nargin = 0.0;
  real_T c6_c_nargout = 0.0;
  real32_T c6_hoistedGlobal;
  real32_T c6_b_hoistedGlobal;
  real32_T c6_c_hoistedGlobal;
  real32_T c6_d_hoistedGlobal;
  void *c6_inputVarPtrs[3];
  int32_T c6_inputVarSizes[3];
  real32_T c6_f2;
  real_T c6_d_nargin = 0.0;
  real_T c6_d_nargout = 1.0;
  boolean_T c6_b_out;
  real_T c6_e_nargin = 0.0;
  real_T c6_e_nargout = 0.0;
  uint16_T c6_u9;
  real_T c6_f_nargin = 0.0;
  real_T c6_f_nargout = 0.0;
  real32_T c6_e_hoistedGlobal;
  c6_Sensors_Bus c6_f_hoistedGlobal;
  real32_T c6_g_hoistedGlobal;
  real32_T c6_h_hoistedGlobal;
  real32_T c6_i_hoistedGlobal;
  real32_T c6_j_hoistedGlobal;
  real32_T c6_f3;
  real_T c6_g_nargin = 0.0;
  real_T c6_g_nargout = 1.0;
  boolean_T c6_c_out;
  real_T c6_h_nargin = 0.0;
  real_T c6_h_nargout = 0.0;
  uint16_T c6_u10;
  real_T c6_i_nargin = 0.0;
  real_T c6_i_nargout = 0.0;
  real32_T c6_k_hoistedGlobal;
  real32_T c6_l_hoistedGlobal;
  real32_T c6_m_hoistedGlobal;
  real32_T c6_n_hoistedGlobal;
  real32_T c6_o_hoistedGlobal;
  real32_T c6_f4;
  real_T c6_j_nargin = 0.0;
  real_T c6_j_nargout = 1.0;
  boolean_T c6_d_out;
  real_T c6_k_nargin = 0.0;
  real_T c6_k_nargout = 0.0;
  uint16_T c6_u11;
  real_T c6_l_nargin = 0.0;
  real_T c6_l_nargout = 0.0;
  real32_T c6_p_hoistedGlobal;
  real32_T c6_q_hoistedGlobal;
  real32_T c6_r_hoistedGlobal;
  real32_T c6_s_hoistedGlobal;
  real32_T c6_f5;
  real_T c6_m_nargin = 0.0;
  real_T c6_m_nargout = 0.0;
  real32_T c6_t_hoistedGlobal;
  real32_T c6_u_hoistedGlobal;
  real32_T c6_v_hoistedGlobal;
  real32_T c6_w_hoistedGlobal;
  real32_T c6_f6;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U, chartInstance->c6_sfEvent);
  switch (chartInstance->c6_is_Ramp) {
   case c6_IN_BridgeTest:
    CV_STATE_EVAL(9, 0, 1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                 chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_lb_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    c6_out = CV_EML_IF(12, 0, 0, chartInstance->c6_temporalCounter_i1 >= 5500);
    _SFD_SYMBOL_SCOPE_POP();
    if (c6_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_BridgeTest = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_Ramp = c6_IN_RampUpTwo;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
      chartInstance->c6_temporalCounter_i1 = 0U;
      chartInstance->c6_tp_RampUpTwo = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_u_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      chartInstance->c6_desired_phi = *(real32_T *)&((char_T *)
        chartInstance->c6_states)[24];
      c6_updateDataWrittenToVector(chartInstance, 8U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_phi, 13U);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      c6_u8 = 3063U;
      c6_outputVarPtrs[0U] = (void *)&c6_u8;
      c6_outputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_outputVarPtrs, (void *)c6_outputVarSizes, 0, NULL,
                           NULL);
      chartInstance->c6_des_vel = 0.04F;
      c6_updateDataWrittenToVector(chartInstance, 7U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                   chartInstance->c6_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_t_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      chartInstance->c6_des_vel = 0.04F;
      c6_updateDataWrittenToVector(chartInstance, 7U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
      c6_errorIfDataNotWrittenToFcn(chartInstance, 8U, 13U, 248U, 166, 11);
      c6_hoistedGlobal = chartInstance->c6_desired_phi;
      c6_b_hoistedGlobal = c6_hoistedGlobal;
      c6_c_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_states)[24];
      c6_d_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_sensors)
        [24];
      c6_inputVarPtrs[0U] = (void *)&c6_b_hoistedGlobal;
      c6_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
      c6_inputVarPtrs[1U] = (void *)&c6_c_hoistedGlobal;
      c6_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
      c6_inputVarPtrs[2U] = (void *)&c6_d_hoistedGlobal;
      c6_inputVarSizes[2U] = (int32_T)sizeof(real32_T);
      c6_outputVarPtrs[0U] = (void *)&c6_f2;
      c6_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
      sfcs_request_service(chartInstance->S, "phiController", 3, (void *)
                           c6_inputVarPtrs, (void *)c6_inputVarSizes, 1, (void *)
                           c6_outputVarPtrs, (void *)c6_outputVarSizes);
      chartInstance->c6_turningPWM = c6_f2;
      c6_updateDataWrittenToVector(chartInstance, 3U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
      _SFD_SYMBOL_SCOPE_POP();
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_RampUpOne:
    CV_STATE_EVAL(9, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                 chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_kb_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_d_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_d_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    c6_b_out = CV_EML_IF(11, 0, 0, *(real32_T *)&((char_T *)
      chartInstance->c6_sensors)[28] != 0.0F);
    _SFD_SYMBOL_SCOPE_POP();
    if (c6_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_RampUpOne = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_Ramp = c6_IN_BridgeTest;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
      chartInstance->c6_temporalCounter_i1 = 0U;
      chartInstance->c6_tp_BridgeTest = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_s_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_e_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_e_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      c6_u9 = 3062U;
      c6_outputVarPtrs[0U] = (void *)&c6_u9;
      c6_outputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_outputVarPtrs, (void *)c6_outputVarSizes, 0, NULL,
                           NULL);
      chartInstance->c6_des_vel = 0.04F;
      c6_updateDataWrittenToVector(chartInstance, 7U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
      chartInstance->c6_desired_phi = *(real32_T *)&((char_T *)
        chartInstance->c6_states)[24];
      c6_updateDataWrittenToVector(chartInstance, 8U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_phi, 13U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                   chartInstance->c6_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_r_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_f_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_f_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      c6_errorIfDataNotWrittenToFcn(chartInstance, 5U, 10U, 247U, 145, 15);
      c6_errorIfDataNotWrittenToFcn(chartInstance, 8U, 13U, 247U, 212, 11);
      c6_e_hoistedGlobal = chartInstance->c6_normalizedLight;
      c6_f_hoistedGlobal.theta_L = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[0];
      c6_f_hoistedGlobal.theta_R = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[4];
      c6_f_hoistedGlobal.theta_T = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[8];
      c6_f_hoistedGlobal.light = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[12];
      c6_f_hoistedGlobal.gyro = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[16];
      c6_f_hoistedGlobal.sonar = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[20];
      c6_f_hoistedGlobal.battery = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[24];
      c6_f_hoistedGlobal.touch = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[28];
      c6_f_hoistedGlobal.time = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[32];
      c6_f_hoistedGlobal.ok_button = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[36];
      c6_f_hoistedGlobal.BT_status_in = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[40];
      c6_g_hoistedGlobal = chartInstance->c6_desired_phi;
      c6_h_hoistedGlobal = c6_g_hoistedGlobal;
      c6_i_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_states)[24];
      c6_j_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_sensors)
        [24];
      c6_inputVarPtrs[0U] = (void *)&c6_h_hoistedGlobal;
      c6_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
      c6_inputVarPtrs[1U] = (void *)&c6_i_hoistedGlobal;
      c6_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
      c6_inputVarPtrs[2U] = (void *)&c6_j_hoistedGlobal;
      c6_inputVarSizes[2U] = (int32_T)sizeof(real32_T);
      c6_outputVarPtrs[0U] = (void *)&c6_f3;
      c6_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
      sfcs_request_service(chartInstance->S, "phiController", 3, (void *)
                           c6_inputVarPtrs, (void *)c6_inputVarSizes, 1, (void *)
                           c6_outputVarPtrs, (void *)c6_outputVarSizes);
      chartInstance->c6_turningPWM = c6_lineTracker(chartInstance, -0.1F,
        c6_e_hoistedGlobal, 0.5F, (real_T)c6_f_hoistedGlobal.battery) + c6_f3;
      c6_updateDataWrittenToVector(chartInstance, 3U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
      _SFD_SYMBOL_SCOPE_POP();
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_RampUpTwo:
    CV_STATE_EVAL(9, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 13U,
                 chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_mb_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_g_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_g_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    c6_c_out = CV_EML_IF(13, 0, 0, chartInstance->c6_temporalCounter_i1 >= 250);
    _SFD_SYMBOL_SCOPE_POP();
    if (c6_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_RampUpTwo = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_Ramp = c6_IN_SlowtoRotate;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_SlowtoRotate = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_y_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_h_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_h_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      c6_u10 = 3064U;
      c6_outputVarPtrs[0U] = (void *)&c6_u10;
      c6_outputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_outputVarPtrs, (void *)c6_outputVarSizes, 0, NULL,
                           NULL);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      chartInstance->c6_des_vel = 0.03F;
      c6_updateDataWrittenToVector(chartInstance, 7U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
      chartInstance->c6_desired_phi = *(real32_T *)&((char_T *)
        chartInstance->c6_states)[24];
      c6_updateDataWrittenToVector(chartInstance, 8U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_phi, 13U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                   chartInstance->c6_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_v_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_i_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_i_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      c6_errorIfDataNotWrittenToFcn(chartInstance, 5U, 10U, 250U, 145, 15);
      c6_errorIfDataNotWrittenToFcn(chartInstance, 8U, 13U, 250U, 212, 11);
      c6_k_hoistedGlobal = chartInstance->c6_normalizedLight;
      c6_f_hoistedGlobal.theta_L = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[0];
      c6_f_hoistedGlobal.theta_R = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[4];
      c6_f_hoistedGlobal.theta_T = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[8];
      c6_f_hoistedGlobal.light = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[12];
      c6_f_hoistedGlobal.gyro = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[16];
      c6_f_hoistedGlobal.sonar = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[20];
      c6_f_hoistedGlobal.battery = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[24];
      c6_f_hoistedGlobal.touch = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[28];
      c6_f_hoistedGlobal.time = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[32];
      c6_f_hoistedGlobal.ok_button = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[36];
      c6_f_hoistedGlobal.BT_status_in = *(real32_T *)&((char_T *)
        chartInstance->c6_sensors)[40];
      c6_l_hoistedGlobal = chartInstance->c6_desired_phi;
      c6_m_hoistedGlobal = c6_l_hoistedGlobal;
      c6_n_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_states)[24];
      c6_o_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_sensors)
        [24];
      c6_inputVarPtrs[0U] = (void *)&c6_m_hoistedGlobal;
      c6_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
      c6_inputVarPtrs[1U] = (void *)&c6_n_hoistedGlobal;
      c6_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
      c6_inputVarPtrs[2U] = (void *)&c6_o_hoistedGlobal;
      c6_inputVarSizes[2U] = (int32_T)sizeof(real32_T);
      c6_outputVarPtrs[0U] = (void *)&c6_f4;
      c6_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
      sfcs_request_service(chartInstance->S, "phiController", 3, (void *)
                           c6_inputVarPtrs, (void *)c6_inputVarSizes, 1, (void *)
                           c6_outputVarPtrs, (void *)c6_outputVarSizes);
      chartInstance->c6_turningPWM = c6_lineTracker(chartInstance, -0.1F,
        c6_k_hoistedGlobal, 0.0F, (real_T)c6_f_hoistedGlobal.battery) + c6_f4;
      c6_updateDataWrittenToVector(chartInstance, 3U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
      _SFD_SYMBOL_SCOPE_POP();
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_RotateInPlace:
    CV_STATE_EVAL(9, 0, 4);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 15U,
                 chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_ob_debug_family_names,
      c6_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_j_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_j_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_d_out, 2U, c6_b_sf_marshallOut,
      c6_b_sf_marshallIn);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 9U, 14U, 259U, 13, 12);
    c6_d_out = CV_EML_IF(15, 0, 0, CV_RELATIONAL_EVAL(5U, 15U, 0, (real_T)
      *(real32_T *)&((char_T *)chartInstance->c6_states)[24], (real_T)
      chartInstance->c6_desiredangle, -3, 5U, *(real32_T *)&((char_T *)
      chartInstance->c6_states)[24] >= chartInstance->c6_desiredangle));
    _SFD_SYMBOL_SCOPE_POP();
    if (c6_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_RotateInPlace = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
      chartInstance->c6_isStable = false;
      chartInstance->c6_is_Ramp = c6_IN_Stop;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c6_sfEvent);
      chartInstance->c6_tp_Stop = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_bb_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_k_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_k_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      c6_u11 = 3066U;
      c6_outputVarPtrs[0U] = (void *)&c6_u11;
      c6_outputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c6_outputVarPtrs, (void *)c6_outputVarSizes, 0, NULL,
                           NULL);
      chartInstance->c6_des_vel = 0.0F;
      c6_updateDataWrittenToVector(chartInstance, 7U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
      chartInstance->c6_desired_phi = *(real32_T *)&((char_T *)
        chartInstance->c6_states)[24];
      c6_updateDataWrittenToVector(chartInstance, 8U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_phi, 13U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                   chartInstance->c6_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_x_debug_family_names,
        c6_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_l_nargin, 0U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_l_nargout, 1U, c6_sf_marshallOut,
        c6_sf_marshallIn);
      c6_errorIfDataNotWrittenToFcn(chartInstance, 8U, 13U, 252U, 244, 11);
      c6_p_hoistedGlobal = chartInstance->c6_desired_phi;
      c6_q_hoistedGlobal = c6_p_hoistedGlobal;
      c6_r_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_states)[24];
      c6_s_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_sensors)
        [24];
      c6_inputVarPtrs[0U] = (void *)&c6_q_hoistedGlobal;
      c6_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
      c6_inputVarPtrs[1U] = (void *)&c6_r_hoistedGlobal;
      c6_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
      c6_inputVarPtrs[2U] = (void *)&c6_s_hoistedGlobal;
      c6_inputVarSizes[2U] = (int32_T)sizeof(real32_T);
      c6_outputVarPtrs[0U] = (void *)&c6_f5;
      c6_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
      sfcs_request_service(chartInstance->S, "phiController", 3, (void *)
                           c6_inputVarPtrs, (void *)c6_inputVarSizes, 1, (void *)
                           c6_outputVarPtrs, (void *)c6_outputVarSizes);
      chartInstance->c6_turningPWM = c6_f5;
      c6_updateDataWrittenToVector(chartInstance, 3U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
      c6_errorIfDataNotWrittenToFcn(chartInstance, 8U, 13U, 252U, 299, 11);
      chartInstance->c6_desired_phi += 0.5F;
      c6_updateDataWrittenToVector(chartInstance, 8U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_phi, 13U);
      _SFD_SYMBOL_SCOPE_POP();
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c6_sfEvent);
    break;

   case c6_IN_SlowtoRotate:
    CV_STATE_EVAL(9, 0, 5);
    c6_SlowtoRotate(chartInstance);
    break;

   case c6_IN_Stop:
    CV_STATE_EVAL(9, 0, 6);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 15U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_cb_debug_family_names,
      c6_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_m_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_m_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 8U, 13U, 258U, 124, 11);
    c6_t_hoistedGlobal = chartInstance->c6_desired_phi;
    c6_u_hoistedGlobal = c6_t_hoistedGlobal;
    c6_v_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_states)[24];
    c6_w_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_sensors)[24];
    c6_inputVarPtrs[0U] = (void *)&c6_u_hoistedGlobal;
    c6_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
    c6_inputVarPtrs[1U] = (void *)&c6_v_hoistedGlobal;
    c6_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
    c6_inputVarPtrs[2U] = (void *)&c6_w_hoistedGlobal;
    c6_inputVarSizes[2U] = (int32_T)sizeof(real32_T);
    c6_outputVarPtrs[0U] = (void *)&c6_f6;
    c6_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
    sfcs_request_service(chartInstance->S, "phiController", 3, (void *)
                         c6_inputVarPtrs, (void *)c6_inputVarSizes, 1, (void *)
                         c6_outputVarPtrs, (void *)c6_outputVarSizes);
    chartInstance->c6_turningPWM = c6_f6;
    c6_updateDataWrittenToVector(chartInstance, 3U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c6_sfEvent);
    break;

   default:
    CV_STATE_EVAL(9, 0, 0);
    chartInstance->c6_is_Ramp = c6_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c6_sfEvent);
}

static void c6_SlowtoRotate(SFc6_et_roboconInstanceStruct *chartInstance)
{
  uint32_T c6_debug_family_var_map[3];
  real_T c6_nargin = 0.0;
  real_T c6_nargout = 1.0;
  boolean_T c6_out;
  uint32_T c6_b_debug_family_var_map[2];
  real_T c6_b_nargin = 0.0;
  real_T c6_b_nargout = 0.0;
  uint16_T c6_u12;
  void *c6_outputVarPtrs[1];
  int32_T c6_outputVarSizes[1];
  real_T c6_c_nargin = 0.0;
  real_T c6_c_nargout = 0.0;
  real32_T c6_hoistedGlobal;
  real32_T c6_b_hoistedGlobal;
  real32_T c6_c_hoistedGlobal;
  real32_T c6_d_hoistedGlobal;
  void *c6_inputVarPtrs[3];
  int32_T c6_inputVarSizes[3];
  real32_T c6_f7;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 14U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c6_nb_debug_family_names,
    c6_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargin, 0U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_nargout, 1U, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_out, 2U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  c6_errorIfDataNotWrittenToFcn(chartInstance, 7U, 12U, 257U, 1, 7);
  c6_out = CV_EML_IF(14, 0, 0, CV_RELATIONAL_EVAL(5U, 14U, 0, (real_T)
    chartInstance->c6_des_vel, 0.01, -1, 3U, (real_T)chartInstance->c6_des_vel <=
    0.01));
  _SFD_SYMBOL_SCOPE_POP();
  if (c6_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_SlowtoRotate = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c6_sfEvent);
    chartInstance->c6_isStable = false;
    chartInstance->c6_is_Ramp = c6_IN_RotateInPlace;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_RotateInPlace = 1U;
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_w_debug_family_names,
      c6_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_b_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    c6_u12 = 3065U;
    c6_outputVarPtrs[0U] = (void *)&c6_u12;
    c6_outputVarSizes[0U] = (int32_T)sizeof(uint16_T);
    sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                         c6_outputVarPtrs, (void *)c6_outputVarSizes, 0, NULL,
                         NULL);
    chartInstance->c6_des_vel = 0.0F;
    c6_updateDataWrittenToVector(chartInstance, 7U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
    chartInstance->c6_desiredangle = *(real32_T *)&((char_T *)
      chartInstance->c6_states)[24] + 180.0F;
    c6_updateDataWrittenToVector(chartInstance, 9U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desiredangle, 14U);
    chartInstance->c6_desired_phi = *(real32_T *)&((char_T *)
      chartInstance->c6_states)[24] + 0.5F;
    c6_updateDataWrittenToVector(chartInstance, 8U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_desired_phi, 13U);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U, chartInstance->c6_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c6_ab_debug_family_names,
      c6_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargin, 0U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c6_c_nargout, 1U, c6_sf_marshallOut,
      c6_sf_marshallIn);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 7U, 12U, 254U, 123, 7);
    chartInstance->c6_des_vel -= 0.01F;
    c6_updateDataWrittenToVector(chartInstance, 7U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_des_vel, 12U);
    c6_errorIfDataNotWrittenToFcn(chartInstance, 8U, 13U, 254U, 172, 11);
    c6_hoistedGlobal = chartInstance->c6_desired_phi;
    c6_b_hoistedGlobal = c6_hoistedGlobal;
    c6_c_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_states)[24];
    c6_d_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c6_sensors)[24];
    c6_inputVarPtrs[0U] = (void *)&c6_b_hoistedGlobal;
    c6_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
    c6_inputVarPtrs[1U] = (void *)&c6_c_hoistedGlobal;
    c6_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
    c6_inputVarPtrs[2U] = (void *)&c6_d_hoistedGlobal;
    c6_inputVarSizes[2U] = (int32_T)sizeof(real32_T);
    c6_outputVarPtrs[0U] = (void *)&c6_f7;
    c6_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
    sfcs_request_service(chartInstance->S, "phiController", 3, (void *)
                         c6_inputVarPtrs, (void *)c6_inputVarSizes, 1, (void *)
                         c6_outputVarPtrs, (void *)c6_outputVarSizes);
    chartInstance->c6_turningPWM = c6_f7;
    c6_updateDataWrittenToVector(chartInstance, 3U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c6_turningPWM, 7U);
    _SFD_SYMBOL_SCOPE_POP();
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c6_sfEvent);
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber)
{
  (void)c6_machineNumber;
  (void)c6_chartNumber;
  (void)c6_instanceNumber;
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static real_T c6_emlrt_marshallIn(SFc6_et_roboconInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_nargout;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_nargout = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nargout), &c6_thisId);
  sf_mex_destroy(&c6_nargout);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  boolean_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(boolean_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static boolean_T c6_b_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  boolean_T c6_y;
  boolean_T c6_b0;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_b0, 1, 11, 0U, 0, 0U, 0);
  c6_y = c6_b0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_sf_internal_predicateOutput;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  boolean_T c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_sf_internal_predicateOutput = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_sf_internal_predicateOutput), &c6_thisId);
  sf_mex_destroy(&c6_sf_internal_predicateOutput);
  *(boolean_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static real32_T c6_c_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_sf_internal_predicateOutput, const char_T
  *c6_identifier)
{
  real32_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_sf_internal_predicateOutput), &c6_thisId);
  sf_mex_destroy(&c6_sf_internal_predicateOutput);
  return c6_y;
}

static real32_T c6_d_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real32_T c6_y;
  real32_T c6_f8;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_f8, 1, 1, 0U, 0, 0U, 0);
  c6_y = c6_f8;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_sf_internal_predicateOutput;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real32_T c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_sf_internal_predicateOutput = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_sf_internal_predicateOutput), &c6_thisId);
  sf_mex_destroy(&c6_sf_internal_predicateOutput);
  *(real32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

const mxArray *sf_c6_et_robocon_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  sf_mex_assign(&c6_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c6_nameCaptureInfo;
}

void sf_exported_auto_userFcnGatewayc6_et_robocon(SimStruct *c6_S, int32_T
  c6_ssidNumber, void *c6_ioVarPtrs)
{
  SFc6_et_roboconInstanceStruct *chartInstance;
  (void)c6_ssidNumber;
  (void)c6_ioVarPtrs;
  chartInstance = (SFc6_et_roboconInstanceStruct *)((ChartInfoStruct *)
    ((ChartRunTimeInfo *)ssGetUserData(c6_S))->instanceInfo)->chartInstance;
}

void sf_exported_auto_autoFcnGatewayc6_et_robocon(SimStruct *c6_S, int32_T
  c6_fcnNumber, void *c6_ioVarPtrs)
{
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)((ChartInfoStruct *)
    ((ChartRunTimeInfo *)ssGetUserData(c6_S))->instanceInfo)->chartInstance;
  if (c6_fcnNumber == -1) {
  } else if (c6_fcnNumber == 61) {
    *(boolean_T *)(*(void *(*)[1])c6_ioVarPtrs)[0] = isStablec6_et_robocon
      (chartInstance);
  } else if (c6_fcnNumber == 62) {
    duringc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 63) {
    enterc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 64) {
    exitc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 65) {
    gatewayc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 66) {
    enablec6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 67) {
    disablec6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 68) {
    initBuffersc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 69) {
    stepBuffersc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 70) {
    initSimStructsc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 71) {
    initc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 72) {
    activate_callc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 73) {
    deactivate_callc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 74) {
    increment_call_counterc6_et_robocon(chartInstance);
  } else if (c6_fcnNumber == 75) {
    reset_call_counterc6_et_robocon(chartInstance);
  } else {
    if (c6_fcnNumber == 76) {
      check_state_inconsistency_c6_et_robocon(chartInstance);
    }
  }
}

static real32_T c6_lineTracker(SFc6_et_roboconInstanceStruct *chartInstance,
  real32_T c6_b_desiredLight, real32_T c6_c_light, real32_T c6_b_trackingPower,
  real_T c6_c_battery)
{
  real32_T c6_c_cmd;
  _SFD_DATA_RANGE_CHECK((real_T)c6_b_desiredLight, 23U);
  _SFD_DATA_RANGE_CHECK((real_T)c6_c_light, 24U);
  _SFD_DATA_RANGE_CHECK((real_T)c6_b_trackingPower, 25U);
  _SFD_DATA_RANGE_CHECK(c6_c_battery, 26U);
  _SFD_SET_DATA_VALUE_PTR(22U, &c6_c_cmd);
  _SFD_SET_DATA_VALUE_PTR(26U, &c6_c_battery);
  _SFD_SET_DATA_VALUE_PTR(25U, &c6_b_trackingPower);
  _SFD_SET_DATA_VALUE_PTR(24U, &c6_c_light);
  _SFD_SET_DATA_VALUE_PTR(23U, &c6_b_desiredLight);
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 21U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH(5U, 0U);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("desiredLight", &c6_b_desiredLight,
    c6_c_sf_marshallOut, c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("light", &c6_c_light, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("trackingPower", &c6_b_trackingPower,
    c6_c_sf_marshallOut, c6_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("battery", &c6_c_battery, c6_sf_marshallOut,
    c6_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_IMPORTABLE("cmd", &c6_c_cmd, c6_c_sf_marshallOut,
    c6_c_sf_marshallIn);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 21U, chartInstance->c6_sfEvent);
  *chartInstance->c6_desiredLight = c6_b_desiredLight;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_desiredLight, 23U);
  *chartInstance->c6_b_light = c6_c_light;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_b_light, 24U);
  *chartInstance->c6_trackingPower = c6_b_trackingPower;
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c6_trackingPower, 25U);
  *chartInstance->c6_b_battery = c6_c_battery;
  _SFD_DATA_RANGE_CHECK(*chartInstance->c6_b_battery, 26U);
  sf_call_output_fcn_call(chartInstance->S, 2, "lineTracker", 0);
  c6_c_cmd = *chartInstance->c6_b_cmd;
  c6_updateDataWrittenToVector(chartInstance, 12U);
  _SFD_DATA_RANGE_CHECK((real_T)c6_c_cmd, 22U);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 21U, chartInstance->c6_sfEvent);
  _SFD_UNSET_DATA_VALUE_PTR(22U);
  _SFD_UNSET_DATA_VALUE_PTR(26U);
  _SFD_UNSET_DATA_VALUE_PTR(25U);
  _SFD_UNSET_DATA_VALUE_PTR(24U);
  _SFD_UNSET_DATA_VALUE_PTR(23U);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 21U, chartInstance->c6_sfEvent);
  return c6_c_cmd;
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static int32_T c6_e_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i2;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i2, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i2;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  uint8_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(uint8_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static uint8_T c6_f_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_tp_see_saw_mode, const char_T
  *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_tp_see_saw_mode),
    &c6_thisId);
  sf_mex_destroy(&c6_b_tp_see_saw_mode);
  return c6_y;
}

static uint8_T c6_g_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u13;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u13, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u13;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_tp_see_saw_mode;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  uint8_T c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_b_tp_see_saw_mode = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_tp_see_saw_mode),
    &c6_thisId);
  sf_mex_destroy(&c6_b_tp_see_saw_mode);
  *(uint8_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_sensors_bus_io(void *chartInstanceVoid, void *c6_pData)
{
  const mxArray *c6_mxVal = NULL;
  c6_Sensors_Bus c6_tmp;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxVal = NULL;
  c6_tmp.theta_L = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[0];
  c6_tmp.theta_R = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[4];
  c6_tmp.theta_T = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[8];
  c6_tmp.light = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[12];
  c6_tmp.gyro = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[16];
  c6_tmp.sonar = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[20];
  c6_tmp.battery = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[24];
  c6_tmp.touch = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[28];
  c6_tmp.time = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[32];
  c6_tmp.ok_button = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[36];
  c6_tmp.BT_status_in = *(real32_T *)&((char_T *)(c6_Sensors_Bus *)c6_pData)[40];
  sf_mex_assign(&c6_mxVal, c6_f_sf_marshallOut(chartInstance, &c6_tmp), false);
  return c6_mxVal;
}

static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  c6_Sensors_Bus c6_u;
  const mxArray *c6_y = NULL;
  real32_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  real32_T c6_c_u;
  const mxArray *c6_c_y = NULL;
  real32_T c6_d_u;
  const mxArray *c6_d_y = NULL;
  real32_T c6_e_u;
  const mxArray *c6_e_y = NULL;
  real32_T c6_f_u;
  const mxArray *c6_f_y = NULL;
  real32_T c6_g_u;
  const mxArray *c6_g_y = NULL;
  real32_T c6_h_u;
  const mxArray *c6_h_y = NULL;
  real32_T c6_i_u;
  const mxArray *c6_i_y = NULL;
  real32_T c6_j_u;
  const mxArray *c6_j_y = NULL;
  real32_T c6_k_u;
  const mxArray *c6_k_y = NULL;
  real32_T c6_l_u;
  const mxArray *c6_l_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_Sensors_Bus *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_b_u = c6_u.theta_L;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_b_y, "theta_L", "theta_L", 0);
  c6_c_u = c6_u.theta_R;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_c_y, "theta_R", "theta_R", 0);
  c6_d_u = c6_u.theta_T;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_d_y, "theta_T", "theta_T", 0);
  c6_e_u = c6_u.light;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_e_y, "light", "light", 0);
  c6_f_u = c6_u.gyro;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_f_y, "gyro", "gyro", 0);
  c6_g_u = c6_u.sonar;
  c6_g_y = NULL;
  sf_mex_assign(&c6_g_y, sf_mex_create("y", &c6_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_g_y, "sonar", "sonar", 0);
  c6_h_u = c6_u.battery;
  c6_h_y = NULL;
  sf_mex_assign(&c6_h_y, sf_mex_create("y", &c6_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_h_y, "battery", "battery", 0);
  c6_i_u = c6_u.touch;
  c6_i_y = NULL;
  sf_mex_assign(&c6_i_y, sf_mex_create("y", &c6_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_i_y, "touch", "touch", 0);
  c6_j_u = c6_u.time;
  c6_j_y = NULL;
  sf_mex_assign(&c6_j_y, sf_mex_create("y", &c6_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_j_y, "time", "time", 0);
  c6_k_u = c6_u.ok_button;
  c6_k_y = NULL;
  sf_mex_assign(&c6_k_y, sf_mex_create("y", &c6_k_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_k_y, "ok_button", "ok_button", 0);
  c6_l_u = c6_u.BT_status_in;
  c6_l_y = NULL;
  sf_mex_assign(&c6_l_y, sf_mex_create("y", &c6_l_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_l_y, "BT_status_in", "BT_status_in", 0);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static const mxArray *c6_lightCalib_bus_io(void *chartInstanceVoid, void
  *c6_pData)
{
  const mxArray *c6_mxVal = NULL;
  c6_Light_Bus c6_tmp;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxVal = NULL;
  c6_tmp.whiteOnLimbo = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[0];
  c6_tmp.blackOnLimbo = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[4];
  c6_tmp.black = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[8];
  c6_tmp.white = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[12];
  c6_tmp.black_white = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[16];
  c6_tmp.gray = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[20];
  c6_tmp.blackOnTail = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[24];
  c6_tmp.whiteOnTail = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[28];
  c6_tmp.flashingBlack = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[32];
  c6_tmp.flashingWhite = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)[36];
  c6_tmp.flashingMapBlack = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)
    [40];
  c6_tmp.flashingMapWhite = *(real32_T *)&((char_T *)(c6_Light_Bus *)c6_pData)
    [44];
  sf_mex_assign(&c6_mxVal, c6_g_sf_marshallOut(chartInstance, &c6_tmp), false);
  return c6_mxVal;
}

static const mxArray *c6_g_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  c6_Light_Bus c6_u;
  const mxArray *c6_y = NULL;
  real32_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  real32_T c6_c_u;
  const mxArray *c6_c_y = NULL;
  real32_T c6_d_u;
  const mxArray *c6_d_y = NULL;
  real32_T c6_e_u;
  const mxArray *c6_e_y = NULL;
  real32_T c6_f_u;
  const mxArray *c6_f_y = NULL;
  real32_T c6_g_u;
  const mxArray *c6_g_y = NULL;
  real32_T c6_h_u;
  const mxArray *c6_h_y = NULL;
  real32_T c6_i_u;
  const mxArray *c6_i_y = NULL;
  real32_T c6_j_u;
  const mxArray *c6_j_y = NULL;
  real32_T c6_k_u;
  const mxArray *c6_k_y = NULL;
  real32_T c6_l_u;
  const mxArray *c6_l_y = NULL;
  real32_T c6_m_u;
  const mxArray *c6_m_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_Light_Bus *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_b_u = c6_u.whiteOnLimbo;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_b_y, "whiteOnLimbo", "whiteOnLimbo", 0);
  c6_c_u = c6_u.blackOnLimbo;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_c_y, "blackOnLimbo", "blackOnLimbo", 0);
  c6_d_u = c6_u.black;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_d_y, "black", "black", 0);
  c6_e_u = c6_u.white;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_e_y, "white", "white", 0);
  c6_f_u = c6_u.black_white;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_f_y, "black_white", "black_white", 0);
  c6_g_u = c6_u.gray;
  c6_g_y = NULL;
  sf_mex_assign(&c6_g_y, sf_mex_create("y", &c6_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_g_y, "gray", "gray", 0);
  c6_h_u = c6_u.blackOnTail;
  c6_h_y = NULL;
  sf_mex_assign(&c6_h_y, sf_mex_create("y", &c6_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_h_y, "blackOnTail", "blackOnTail", 0);
  c6_i_u = c6_u.whiteOnTail;
  c6_i_y = NULL;
  sf_mex_assign(&c6_i_y, sf_mex_create("y", &c6_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_i_y, "whiteOnTail", "whiteOnTail", 0);
  c6_j_u = c6_u.flashingBlack;
  c6_j_y = NULL;
  sf_mex_assign(&c6_j_y, sf_mex_create("y", &c6_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_j_y, "flashingBlack", "flashingBlack", 0);
  c6_k_u = c6_u.flashingWhite;
  c6_k_y = NULL;
  sf_mex_assign(&c6_k_y, sf_mex_create("y", &c6_k_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_k_y, "flashingWhite", "flashingWhite", 0);
  c6_l_u = c6_u.flashingMapBlack;
  c6_l_y = NULL;
  sf_mex_assign(&c6_l_y, sf_mex_create("y", &c6_l_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_l_y, "flashingMapBlack", "flashingMapBlack", 0);
  c6_m_u = c6_u.flashingMapWhite;
  c6_m_y = NULL;
  sf_mex_assign(&c6_m_y, sf_mex_create("y", &c6_m_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_m_y, "flashingMapWhite", "flashingMapWhite", 0);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static c6_Light_Bus c6_h_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  c6_Light_Bus c6_y;
  emlrtMsgIdentifier c6_thisId;
  static const char * c6_fieldNames[12] = { "whiteOnLimbo", "blackOnLimbo",
    "black", "white", "black_white", "gray", "blackOnTail", "whiteOnTail",
    "flashingBlack", "flashingWhite", "flashingMapBlack", "flashingMapWhite" };

  c6_thisId.fParent = c6_parentId;
  sf_mex_check_struct(c6_parentId, c6_u, 12, c6_fieldNames, 0U, NULL);
  c6_thisId.fIdentifier = "whiteOnLimbo";
  c6_y.whiteOnLimbo = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "whiteOnLimbo", "whiteOnLimbo", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "blackOnLimbo";
  c6_y.blackOnLimbo = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "blackOnLimbo", "blackOnLimbo", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "black";
  c6_y.black = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "black", "black", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "white";
  c6_y.white = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "white", "white", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "black_white";
  c6_y.black_white = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "black_white", "black_white", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "gray";
  c6_y.gray = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "gray", "gray", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "blackOnTail";
  c6_y.blackOnTail = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "blackOnTail", "blackOnTail", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "whiteOnTail";
  c6_y.whiteOnTail = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "whiteOnTail", "whiteOnTail", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "flashingBlack";
  c6_y.flashingBlack = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "flashingBlack", "flashingBlack", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "flashingWhite";
  c6_y.flashingWhite = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "flashingWhite", "flashingWhite", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "flashingMapBlack";
  c6_y.flashingMapBlack = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "flashingMapBlack", "flashingMapBlack", 0)),
    &c6_thisId);
  c6_thisId.fIdentifier = "flashingMapWhite";
  c6_y.flashingMapWhite = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "flashingMapWhite", "flashingMapWhite", 0)),
    &c6_thisId);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_lightCalib;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  c6_Light_Bus c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_b_lightCalib = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_lightCalib),
    &c6_thisId);
  sf_mex_destroy(&c6_b_lightCalib);
  *(c6_Light_Bus *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_h_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  c6_OperationModeStatusEnum c6_u;
  const mxArray *c6_y = NULL;
  static const int32_T c6_enumValues[4] = { 0, 1, 2, 3 };

  static const char * c6_enumNames[4] = { "NOT_STARTED", "IN_PROGRESS",
    "SUCCESSFULLY_COMPLETED", "ABORTED" };

  int32_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  const mxArray *c6_m1 = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_OperationModeStatusEnum *)c6_inData;
  c6_y = NULL;
  sf_mex_check_enum("OperationModeStatusEnum", 4, c6_enumNames, c6_enumValues);
  c6_b_u = (int32_T)c6_u;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_m1, c6_b_y, false);
  sf_mex_assign(&c6_y, sf_mex_create_enum("OperationModeStatusEnum", c6_m1),
                false);
  sf_mex_destroy(&c6_m1);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static c6_OperationModeStatusEnum c6_i_emlrt_marshallIn
  (SFc6_et_roboconInstanceStruct *chartInstance, const mxArray *c6_u, const
   emlrtMsgIdentifier *c6_parentId)
{
  c6_OperationModeStatusEnum c6_y;
  static const int32_T c6_enumValues[4] = { 0, 1, 2, 3 };

  static const char * c6_enumNames[4] = { "NOT_STARTED", "IN_PROGRESS",
    "SUCCESSFULLY_COMPLETED", "ABORTED" };

  (void)chartInstance;
  sf_mex_check_enum("OperationModeStatusEnum", 4, c6_enumNames, c6_enumValues);
  sf_mex_check_builtin(c6_parentId, c6_u, "OperationModeStatusEnum", 0, 0U, NULL);
  c6_y = (c6_OperationModeStatusEnum)sf_mex_get_enum_element(c6_u, 0);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_current_task_operation_status;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  c6_OperationModeStatusEnum c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_current_task_operation_status = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_current_task_operation_status), &c6_thisId);
  sf_mex_destroy(&c6_current_task_operation_status);
  *(c6_OperationModeStatusEnum *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_PWM_bus_io(void *chartInstanceVoid, void *c6_pData)
{
  const mxArray *c6_mxVal = NULL;
  c6_PWM_bus c6_tmp;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxVal = NULL;
  c6_tmp.left = *(real32_T *)&((char_T *)(c6_PWM_bus *)c6_pData)[0];
  c6_tmp.right = *(real32_T *)&((char_T *)(c6_PWM_bus *)c6_pData)[4];
  c6_tmp.tail = *(real32_T *)&((char_T *)(c6_PWM_bus *)c6_pData)[8];
  sf_mex_assign(&c6_mxVal, c6_i_sf_marshallOut(chartInstance, &c6_tmp), false);
  return c6_mxVal;
}

static const mxArray *c6_i_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  c6_PWM_bus c6_u;
  const mxArray *c6_y = NULL;
  real32_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  real32_T c6_c_u;
  const mxArray *c6_c_y = NULL;
  real32_T c6_d_u;
  const mxArray *c6_d_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_PWM_bus *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_b_u = c6_u.left;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_b_y, "left", "left", 0);
  c6_c_u = c6_u.right;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_c_y, "right", "right", 0);
  c6_d_u = c6_u.tail;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_d_y, "tail", "tail", 0);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static c6_PWM_bus c6_j_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_PWM, const char_T *c6_identifier)
{
  c6_PWM_bus c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_PWM), &c6_thisId);
  sf_mex_destroy(&c6_b_PWM);
  return c6_y;
}

static c6_PWM_bus c6_k_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  c6_PWM_bus c6_y;
  emlrtMsgIdentifier c6_thisId;
  static const char * c6_fieldNames[3] = { "left", "right", "tail" };

  c6_thisId.fParent = c6_parentId;
  sf_mex_check_struct(c6_parentId, c6_u, 3, c6_fieldNames, 0U, NULL);
  c6_thisId.fIdentifier = "left";
  c6_y.left = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "left", "left", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "right";
  c6_y.right = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "right", "right", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "tail";
  c6_y.tail = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "tail", "tail", 0)), &c6_thisId);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_PWM;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  c6_PWM_bus c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_b_PWM = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_PWM), &c6_thisId);
  sf_mex_destroy(&c6_b_PWM);
  *(c6_PWM_bus *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_initFlags_bus_io(void *chartInstanceVoid, void
  *c6_pData)
{
  const mxArray *c6_mxVal = NULL;
  c6_Init_Bus c6_tmp;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxVal = NULL;
  c6_tmp.fall = *(boolean_T *)&((char_T *)(c6_Init_Bus *)c6_pData)[0];
  c6_tmp.gyroInit = *(real32_T *)&((char_T *)(c6_Init_Bus *)c6_pData)[4];
  c6_tmp.gyroReset = *(real32_T *)&((char_T *)(c6_Init_Bus *)c6_pData)[8];
  c6_tmp.theta = *(real32_T *)&((char_T *)(c6_Init_Bus *)c6_pData)[12];
  c6_tmp.tail = *(real32_T *)&((char_T *)(c6_Init_Bus *)c6_pData)[16];
  sf_mex_assign(&c6_mxVal, c6_j_sf_marshallOut(chartInstance, &c6_tmp), false);
  return c6_mxVal;
}

static const mxArray *c6_j_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  c6_Init_Bus c6_u;
  const mxArray *c6_y = NULL;
  boolean_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  real32_T c6_c_u;
  const mxArray *c6_c_y = NULL;
  real32_T c6_d_u;
  const mxArray *c6_d_y = NULL;
  real32_T c6_e_u;
  const mxArray *c6_e_y = NULL;
  real32_T c6_f_u;
  const mxArray *c6_f_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_Init_Bus *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_b_u = c6_u.fall;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_b_y, "fall", "fall", 0);
  c6_c_u = c6_u.gyroInit;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_c_y, "gyroInit", "gyroInit", 0);
  c6_d_u = c6_u.gyroReset;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_d_y, "gyroReset", "gyroReset", 0);
  c6_e_u = c6_u.theta;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_e_y, "theta", "theta", 0);
  c6_f_u = c6_u.tail;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_f_y, "tail", "tail", 0);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static c6_Init_Bus c6_l_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_initFlags, const char_T *c6_identifier)
{
  c6_Init_Bus c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_initFlags),
    &c6_thisId);
  sf_mex_destroy(&c6_b_initFlags);
  return c6_y;
}

static c6_Init_Bus c6_m_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  c6_Init_Bus c6_y;
  emlrtMsgIdentifier c6_thisId;
  static const char * c6_fieldNames[5] = { "fall", "gyroInit", "gyroReset",
    "theta", "tail" };

  c6_thisId.fParent = c6_parentId;
  sf_mex_check_struct(c6_parentId, c6_u, 5, c6_fieldNames, 0U, NULL);
  c6_thisId.fIdentifier = "fall";
  c6_y.fall = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "fall", "fall", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "gyroInit";
  c6_y.gyroInit = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "gyroInit", "gyroInit", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "gyroReset";
  c6_y.gyroReset = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "gyroReset", "gyroReset", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "theta";
  c6_y.theta = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "theta", "theta", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "tail";
  c6_y.tail = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "tail", "tail", 0)), &c6_thisId);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_initFlags;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  c6_Init_Bus c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_b_initFlags = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_initFlags),
    &c6_thisId);
  sf_mex_destroy(&c6_b_initFlags);
  *(c6_Init_Bus *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_k_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  c6_struct_FjjrIT366yeIj3aqvn0HfE c6_u;
  const mxArray *c6_y = NULL;
  real32_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  real32_T c6_c_u;
  const mxArray *c6_c_y = NULL;
  real32_T c6_d_u;
  const mxArray *c6_d_y = NULL;
  real32_T c6_e_u;
  const mxArray *c6_e_y = NULL;
  real32_T c6_f_u;
  const mxArray *c6_f_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_struct_FjjrIT366yeIj3aqvn0HfE *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_b_u = c6_u.theta;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_b_y, "theta", "theta", 0);
  c6_c_u = c6_u.psi;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_c_y, "psi", "psi", 0);
  c6_d_u = c6_u.theta_dot;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_d_y, "theta_dot", "theta_dot", 0);
  c6_e_u = c6_u.psi_dot;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_e_y, "psi_dot", "psi_dot", 0);
  c6_f_u = c6_u.int_theta;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_f_y, "int_theta", "int_theta", 0);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static c6_struct_FjjrIT366yeIj3aqvn0HfE c6_n_emlrt_marshallIn
  (SFc6_et_roboconInstanceStruct *chartInstance, const mxArray *c6_u, const
   emlrtMsgIdentifier *c6_parentId)
{
  c6_struct_FjjrIT366yeIj3aqvn0HfE c6_y;
  emlrtMsgIdentifier c6_thisId;
  static const char * c6_fieldNames[5] = { "theta", "psi", "theta_dot",
    "psi_dot", "int_theta" };

  c6_thisId.fParent = c6_parentId;
  sf_mex_check_struct(c6_parentId, c6_u, 5, c6_fieldNames, 0U, NULL);
  c6_thisId.fIdentifier = "theta";
  c6_y.theta = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "theta", "theta", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "psi";
  c6_y.psi = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "psi", "psi", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "theta_dot";
  c6_y.theta_dot = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "theta_dot", "theta_dot", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "psi_dot";
  c6_y.psi_dot = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c6_u, "psi_dot", "psi_dot", 0)),
    &c6_thisId);
  c6_thisId.fIdentifier = "int_theta";
  c6_y.int_theta = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "int_theta", "int_theta", 0)), &c6_thisId);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_balancerStates_Bus0;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  c6_struct_FjjrIT366yeIj3aqvn0HfE c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_b_balancerStates_Bus0 = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_n_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_balancerStates_Bus0), &c6_thisId);
  sf_mex_destroy(&c6_b_balancerStates_Bus0);
  *(c6_struct_FjjrIT366yeIj3aqvn0HfE *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_states_bus_io(void *chartInstanceVoid, void *c6_pData)
{
  const mxArray *c6_mxVal = NULL;
  c6_States_Bus c6_tmp;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxVal = NULL;
  c6_tmp.balancerStates.theta = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus
    *)&((char_T *)(c6_States_Bus *)c6_pData)[0])[0];
  c6_tmp.balancerStates.psi = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)
    &((char_T *)(c6_States_Bus *)c6_pData)[0])[4];
  c6_tmp.balancerStates.theta_dot = *(real32_T *)&((char_T *)
    (c6_Balancer_States_Bus *)&((char_T *)(c6_States_Bus *)c6_pData)[0])[8];
  c6_tmp.balancerStates.psi_dot = *(real32_T *)&((char_T *)
    (c6_Balancer_States_Bus *)&((char_T *)(c6_States_Bus *)c6_pData)[0])[12];
  c6_tmp.balancerStates.int_theta = *(real32_T *)&((char_T *)
    (c6_Balancer_States_Bus *)&((char_T *)(c6_States_Bus *)c6_pData)[0])[16];
  c6_tmp.phi = *(real32_T *)&((char_T *)(c6_States_Bus *)c6_pData)[24];
  c6_tmp.phi_dot = *(real32_T *)&((char_T *)(c6_States_Bus *)c6_pData)[28];
  c6_tmp.theta_dot_dot = *(real32_T *)&((char_T *)(c6_States_Bus *)c6_pData)[32];
  sf_mex_assign(&c6_mxVal, c6_l_sf_marshallOut(chartInstance, &c6_tmp), false);
  return c6_mxVal;
}

static const mxArray *c6_l_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  c6_States_Bus c6_u;
  const mxArray *c6_y = NULL;
  c6_Balancer_States_Bus c6_b_u;
  const mxArray *c6_b_y = NULL;
  real32_T c6_c_u;
  const mxArray *c6_c_y = NULL;
  real32_T c6_d_u;
  const mxArray *c6_d_y = NULL;
  real32_T c6_e_u;
  const mxArray *c6_e_y = NULL;
  real32_T c6_f_u;
  const mxArray *c6_f_y = NULL;
  real32_T c6_g_u;
  const mxArray *c6_g_y = NULL;
  real32_T c6_h_u;
  const mxArray *c6_h_y = NULL;
  real32_T c6_i_u;
  const mxArray *c6_i_y = NULL;
  real32_T c6_j_u;
  const mxArray *c6_j_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_States_Bus *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_b_u = c6_u.balancerStates;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_c_u = c6_b_u.theta;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_b_y, c6_c_y, "theta", "theta", 0);
  c6_d_u = c6_b_u.psi;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_b_y, c6_d_y, "psi", "psi", 0);
  c6_e_u = c6_b_u.theta_dot;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_b_y, c6_e_y, "theta_dot", "theta_dot", 0);
  c6_f_u = c6_b_u.psi_dot;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_b_y, c6_f_y, "psi_dot", "psi_dot", 0);
  c6_g_u = c6_b_u.int_theta;
  c6_g_y = NULL;
  sf_mex_assign(&c6_g_y, sf_mex_create("y", &c6_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_b_y, c6_g_y, "int_theta", "int_theta", 0);
  sf_mex_addfield(c6_y, c6_b_y, "balancerStates", "balancerStates", 0);
  c6_h_u = c6_u.phi;
  c6_h_y = NULL;
  sf_mex_assign(&c6_h_y, sf_mex_create("y", &c6_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_h_y, "phi", "phi", 0);
  c6_i_u = c6_u.phi_dot;
  c6_i_y = NULL;
  sf_mex_assign(&c6_i_y, sf_mex_create("y", &c6_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_i_y, "phi_dot", "phi_dot", 0);
  c6_j_u = c6_u.theta_dot_dot;
  c6_j_y = NULL;
  sf_mex_assign(&c6_j_y, sf_mex_create("y", &c6_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_j_y, "theta_dot_dot", "theta_dot_dot", 0);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static const mxArray *c6_balancerStates_bus_io(void *chartInstanceVoid, void
  *c6_pData)
{
  const mxArray *c6_mxVal = NULL;
  c6_Balancer_States_Bus c6_tmp;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxVal = NULL;
  c6_tmp.theta = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)c6_pData)[0];
  c6_tmp.psi = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)c6_pData)[4];
  c6_tmp.theta_dot = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)c6_pData)
    [8];
  c6_tmp.psi_dot = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)c6_pData)
    [12];
  c6_tmp.int_theta = *(real32_T *)&((char_T *)(c6_Balancer_States_Bus *)c6_pData)
    [16];
  sf_mex_assign(&c6_mxVal, c6_m_sf_marshallOut(chartInstance, &c6_tmp), false);
  return c6_mxVal;
}

static const mxArray *c6_m_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  c6_Balancer_States_Bus c6_u;
  const mxArray *c6_y = NULL;
  real32_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  real32_T c6_c_u;
  const mxArray *c6_c_y = NULL;
  real32_T c6_d_u;
  const mxArray *c6_d_y = NULL;
  real32_T c6_e_u;
  const mxArray *c6_e_y = NULL;
  real32_T c6_f_u;
  const mxArray *c6_f_y = NULL;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(c6_Balancer_States_Bus *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c6_b_u = c6_u.theta;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_b_y, "theta", "theta", 0);
  c6_c_u = c6_u.psi;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_c_y, "psi", "psi", 0);
  c6_d_u = c6_u.theta_dot;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_d_y, "theta_dot", "theta_dot", 0);
  c6_e_u = c6_u.psi_dot;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_e_y, "psi_dot", "psi_dot", 0);
  c6_f_u = c6_u.int_theta;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c6_y, c6_f_y, "int_theta", "int_theta", 0);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static c6_Balancer_States_Bus c6_o_emlrt_marshallIn
  (SFc6_et_roboconInstanceStruct *chartInstance, const mxArray *c6_u, const
   emlrtMsgIdentifier *c6_parentId)
{
  c6_Balancer_States_Bus c6_y;
  emlrtMsgIdentifier c6_thisId;
  static const char * c6_fieldNames[5] = { "theta", "psi", "theta_dot",
    "psi_dot", "int_theta" };

  c6_thisId.fParent = c6_parentId;
  sf_mex_check_struct(c6_parentId, c6_u, 5, c6_fieldNames, 0U, NULL);
  c6_thisId.fIdentifier = "theta";
  c6_y.theta = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "theta", "theta", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "psi";
  c6_y.psi = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c6_u, "psi", "psi", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "theta_dot";
  c6_y.theta_dot = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "theta_dot", "theta_dot", 0)), &c6_thisId);
  c6_thisId.fIdentifier = "psi_dot";
  c6_y.psi_dot = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c6_u, "psi_dot", "psi_dot", 0)),
    &c6_thisId);
  c6_thisId.fIdentifier = "int_theta";
  c6_y.int_theta = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c6_u, "int_theta", "int_theta", 0)), &c6_thisId);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_balancerStates;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  c6_Balancer_States_Bus c6_y;
  SFc6_et_roboconInstanceStruct *chartInstance;
  chartInstance = (SFc6_et_roboconInstanceStruct *)chartInstanceVoid;
  c6_b_balancerStates = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_balancerStates),
    &c6_thisId);
  sf_mex_destroy(&c6_b_balancerStates);
  *(c6_Balancer_States_Bus *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static uint16_T c6_p_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_temporalCounter_i1, const char_T
  *c6_identifier)
{
  uint16_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_temporalCounter_i1),
    &c6_thisId);
  sf_mex_destroy(&c6_b_temporalCounter_i1);
  return c6_y;
}

static uint16_T c6_q_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint16_T c6_y;
  uint16_T c6_u14;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u14, 1, 5, 0U, 0, 0U, 0);
  c6_y = c6_u14;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_r_emlrt_marshallIn(SFc6_et_roboconInstanceStruct *chartInstance,
  const mxArray *c6_b_dataWrittenToVector, const char_T *c6_identifier,
  boolean_T c6_y[13])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_dataWrittenToVector),
                        &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_dataWrittenToVector);
}

static void c6_s_emlrt_marshallIn(SFc6_et_roboconInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, boolean_T c6_y[13])
{
  boolean_T c6_bv1[13];
  int32_T c6_i3;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_bv1, 1, 11, 0U, 1, 0U, 1, 13);
  for (c6_i3 = 0; c6_i3 < 13; c6_i3++) {
    c6_y[c6_i3] = c6_bv1[c6_i3];
  }

  sf_mex_destroy(&c6_u);
}

static const mxArray *c6_t_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_b_setSimStateSideEffectsInfo, const char_T
  *c6_identifier)
{
  const mxArray *c6_y = NULL;
  emlrtMsgIdentifier c6_thisId;
  c6_y = NULL;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  sf_mex_assign(&c6_y, c6_u_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_setSimStateSideEffectsInfo), &c6_thisId), false);
  sf_mex_destroy(&c6_b_setSimStateSideEffectsInfo);
  return c6_y;
}

static const mxArray *c6_u_emlrt_marshallIn(SFc6_et_roboconInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  const mxArray *c6_y = NULL;
  (void)chartInstance;
  (void)c6_parentId;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_duplicatearraysafe(&c6_u), false);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_updateDataWrittenToVector(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_vectorIndex)
{
  chartInstance->c6_dataWrittenToVector[(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK(0U,
    (int32_T)c6_vectorIndex, 0, 12, 1, 0)] = true;
}

static void c6_errorIfDataNotWrittenToFcn(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_vectorIndex, uint32_T c6_dataNumber, uint32_T
  c6_ssIdOfSourceObject, int32_T c6_offsetInSourceObject, int32_T
  c6_lengthInSourceObject)
{
  (void)c6_ssIdOfSourceObject;
  (void)c6_offsetInSourceObject;
  (void)c6_lengthInSourceObject;
  if (!chartInstance->c6_dataWrittenToVector[(uint32_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK(0U, (int32_T)c6_vectorIndex, 0, 12, 1, 0)]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(c6_dataNumber);
  }
}

static void c6_bus_rd_access_lightCalib_2(SFc6_et_roboconInstanceStruct
  *chartInstance, int32_T c6_u0, int32_T c6_u1, int32_T c6_u2, int32_T c6_u3)
{
  SFcnMemRegionInfo *c6_reg;
  c6_reg = (SFcnMemRegionInfo *)0U;
  ssMemRegionCreateDescriptor_wrapper(chartInstance->S, 2, &c6_reg);
  ssMemRegionSetFlatSubElement_wrapper(chartInstance->S, c6_reg, 0, c6_u0, 1,
    &c6_u1);
  ssMemRegionSetFlatSubElement_wrapper(chartInstance->S, c6_reg, 1, c6_u2, 1,
    &c6_u3);
  ssReadFromDataStoreRegion_wrapper(chartInstance->S, 1, 0, c6_reg);
  ssMemRegionDestroyDescriptor_wrapper(chartInstance->S, &c6_reg);
}

static c6_OperationModeStatusEnum c6_get_current_task_operation_status
  (SFc6_et_roboconInstanceStruct *chartInstance, uint32_T c6_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, NULL, c6_elementIndex);
  return *chartInstance->c6_current_task_operation_status_address;
}

static void c6_set_current_task_operation_status(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_elementIndex, c6_OperationModeStatusEnum
  c6_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, NULL, c6_elementIndex);
  *chartInstance->c6_current_task_operation_status_address = c6_elementValue;
}

static c6_OperationModeStatusEnum *c6_access_current_task_operation_status
  (SFc6_et_roboconInstanceStruct *chartInstance, uint32_T c6_rdOnly)
{
  c6_OperationModeStatusEnum *c6_dsmAddr;
  ssReadFromDataStore_wrapper(chartInstance->S, 0, NULL);
  c6_dsmAddr = chartInstance->c6_current_task_operation_status_address;
  if (c6_rdOnly == 0U) {
    ssWriteToDataStore_wrapper(chartInstance->S, 0, NULL);
  }

  return c6_dsmAddr;
}

static c6_Light_Bus c6_get_lightCalib(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 1, NULL, c6_elementIndex);
  return *chartInstance->c6_lightCalib_address;
}

static void c6_set_lightCalib(SFc6_et_roboconInstanceStruct *chartInstance,
  uint32_T c6_elementIndex, c6_Light_Bus c6_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 1, NULL, c6_elementIndex);
  *chartInstance->c6_lightCalib_address = c6_elementValue;
}

static c6_Light_Bus *c6_access_lightCalib(SFc6_et_roboconInstanceStruct
  *chartInstance, uint32_T c6_rdOnly)
{
  (void)c6_rdOnly;
  return chartInstance->c6_lightCalib_address;
}

static void init_dsm_address_info(SFc6_et_roboconInstanceStruct *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S,
    "current_task_operation_status", (void **)
    &chartInstance->c6_current_task_operation_status_address,
    &chartInstance->c6_current_task_operation_status_index);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "lightCalib", (void **)
    &chartInstance->c6_lightCalib_address, &chartInstance->c6_lightCalib_index);
}

static void init_simulink_io_address(SFc6_et_roboconInstanceStruct
  *chartInstance)
{
  chartInstance->c6_sensors = (c6_Sensors_Bus *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c6_PWM = (c6_PWM_bus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_initFlags = (c6_Init_Bus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c6_states = (c6_States_Bus *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_BT_status_out = (real32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c6_rawLight = (real32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c6_lightCalib = (c6_Light_Bus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c6_light = (real32_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c6_balancerStates = (c6_Balancer_States_Bus *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 6);
  chartInstance->c6_desired_velocity = (real32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c6_battery = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c6_cmd = (real32_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c6_b_cmd = (real32_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c6_desiredLight = (real32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c6_b_light = (real32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c6_trackingPower = (real32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c6_b_battery = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 12);
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

void sf_c6_et_robocon_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3291982842U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4113798690U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(724471698U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1788758608U);
}

mxArray* sf_c6_et_robocon_get_post_codegen_info(void);
mxArray *sf_c6_et_robocon_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("jnUWg4NzD0rcvza4KUhmPH");
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxData);
  }

  {
    mxArray* mxPostCodegenInfo = sf_c6_et_robocon_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_et_robocon_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c6_et_robocon_jit_fallback_info(void)
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

mxArray *sf_c6_et_robocon_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c6_et_robocon_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString(
      "60D9qPAyTAelCFSspJG23");
    mwSize exp_dims[2] = { 4, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);

    {
      mxArray* mxFcnName = mxCreateString("Speak");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 0, mxFcnName);
    }

    {
      mxArray* mxFcnName = mxCreateString("tail_controller");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 1, mxFcnName);
    }

    {
      mxArray* mxFcnName = mxCreateString("StatusLCD");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 2, mxFcnName);
    }

    {
      mxArray* mxFcnName = mxCreateString("phiController");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 3, mxFcnName);
    }

    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c6_et_robocon(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[194],T\"BT_status_out\",},{M[1],M[30],T\"PWM\",},{M[1],M[38],T\"initFlags\",},{M[3],M[199],T\"des_vel\",},{M[3],M[204],T\"desired_phi\",},{M[3],M[39],T\"desired_tail\",},{M[3],M[262],T\"desiredangle\",},{M[3],M[198],T\"forwardPWM\",},{M[3],M[195],T\"normalizedLight\",},{M[3],M[192],T\"turningPWM\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[8],M[0],T\"is_active_c6_et_robocon\",},{M[8],M[41],T\"is_active_After\",},{M[8],M[100],T\"is_active_SeesawLogic\",},{M[9],M[0],T\"is_c6_et_robocon\",},{M[9],M[96],T\"is_see_saw_mode\",},{M[9],M[100],T\"is_SeesawLogic\",},{M[9],M[231],T\"is_Curvature\",},{M[9],M[246],T\"is_Ramp\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"at\",M1x4[107 200 248 250],M[1]}}},{M[15],M[0],T\"dataWrittenToVector\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 20, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_et_robocon_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_et_roboconInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc6_et_roboconInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _et_roboconMachineNumber_,
           6,
           23,
           18,
           0,
           27,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"sensors");
          _SFD_SET_DATA_PROPS(1,11,0,0,"lightCalib");
          _SFD_SET_DATA_PROPS(2,11,0,0,"current_task_operation_status");
          _SFD_SET_DATA_PROPS(3,2,0,1,"PWM");
          _SFD_SET_DATA_PROPS(4,2,0,1,"initFlags");
          _SFD_SET_DATA_PROPS(5,0,0,0,"desired_tail");
          _SFD_SET_DATA_PROPS(6,10,0,0,"balancerStates_Bus0");
          _SFD_SET_DATA_PROPS(7,0,0,0,"turningPWM");
          _SFD_SET_DATA_PROPS(8,1,1,0,"states");
          _SFD_SET_DATA_PROPS(9,2,0,1,"BT_status_out");
          _SFD_SET_DATA_PROPS(10,0,0,0,"normalizedLight");
          _SFD_SET_DATA_PROPS(11,0,0,0,"forwardPWM");
          _SFD_SET_DATA_PROPS(12,0,0,0,"des_vel");
          _SFD_SET_DATA_PROPS(13,0,0,0,"desired_phi");
          _SFD_SET_DATA_PROPS(14,0,0,0,"desiredangle");
          _SFD_SET_DATA_PROPS(15,8,0,0,"");
          _SFD_SET_DATA_PROPS(16,8,0,0,"");
          _SFD_SET_DATA_PROPS(17,9,0,0,"");
          _SFD_SET_DATA_PROPS(18,8,0,0,"");
          _SFD_SET_DATA_PROPS(19,8,0,0,"");
          _SFD_SET_DATA_PROPS(20,8,0,0,"");
          _SFD_SET_DATA_PROPS(21,9,0,0,"");
          _SFD_SET_DATA_PROPS(22,9,0,0,"");
          _SFD_SET_DATA_PROPS(23,8,0,0,"");
          _SFD_SET_DATA_PROPS(24,8,0,0,"");
          _SFD_SET_DATA_PROPS(25,8,0,0,"");
          _SFD_SET_DATA_PROPS(26,8,0,0,"");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,1,0);
          _SFD_STATE_INFO(2,0,1);
          _SFD_STATE_INFO(3,0,1);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,0);
          _SFD_STATE_INFO(10,0,0);
          _SFD_STATE_INFO(11,0,0);
          _SFD_STATE_INFO(12,0,0);
          _SFD_STATE_INFO(13,0,0);
          _SFD_STATE_INFO(14,0,0);
          _SFD_STATE_INFO(15,0,0);
          _SFD_STATE_INFO(16,0,0);
          _SFD_STATE_INFO(17,0,0);
          _SFD_STATE_INFO(18,0,0);
          _SFD_STATE_INFO(19,0,0);
          _SFD_STATE_INFO(20,0,2);
          _SFD_STATE_INFO(21,0,2);
          _SFD_STATE_INFO(22,0,2);
          _SFD_CH_SUBSTATE_COUNT(1);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_ST_SUBSTATE_COUNT(0,3);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,18);
          _SFD_ST_SUBSTATE_INDEX(0,2,19);
          _SFD_ST_SUBSTATE_COUNT(1,2);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,3);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,6);
          _SFD_ST_SUBSTATE_INDEX(3,0,4);
          _SFD_ST_SUBSTATE_INDEX(3,1,5);
          _SFD_ST_SUBSTATE_INDEX(3,2,8);
          _SFD_ST_SUBSTATE_INDEX(3,3,9);
          _SFD_ST_SUBSTATE_INDEX(3,4,16);
          _SFD_ST_SUBSTATE_INDEX(3,5,17);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,2);
          _SFD_ST_SUBSTATE_INDEX(5,0,6);
          _SFD_ST_SUBSTATE_INDEX(5,1,7);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,6);
          _SFD_ST_SUBSTATE_INDEX(9,0,10);
          _SFD_ST_SUBSTATE_INDEX(9,1,11);
          _SFD_ST_SUBSTATE_INDEX(9,2,12);
          _SFD_ST_SUBSTATE_INDEX(9,3,13);
          _SFD_ST_SUBSTATE_INDEX(9,4,14);
          _SFD_ST_SUBSTATE_INDEX(9,5,15);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(12,0);
          _SFD_ST_SUBSTATE_COUNT(13,0);
          _SFD_ST_SUBSTATE_COUNT(14,0);
          _SFD_ST_SUBSTATE_COUNT(15,0);
          _SFD_ST_SUBSTATE_COUNT(16,0);
          _SFD_ST_SUBSTATE_COUNT(17,0);
          _SFD_ST_SUBSTATE_COUNT(18,0);
          _SFD_ST_SUBSTATE_COUNT(19,0);
        }

        _SFD_CV_INIT_CHART(1,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,2,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,6,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,6,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(12,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(14,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(15,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(16,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(17,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(18,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(19,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(20,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(21,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(22,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(15,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(19,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(18,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(8,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(17,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(5,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(7,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(6,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(16,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(4,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(11,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(10,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(12,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(13,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(14,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(15,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(3,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(3,0,0,1,14,1,14);
        _SFD_CV_INIT_EML(4,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(4,0,0,0,12,0,12);
        _SFD_CV_INIT_EML(5,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(5,0,0,0,15,0,15);
        _SFD_CV_INIT_EML(10,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(10,0,0,1,32,1,32);

        {
          static int condStart[] = { 1, 18 };

          static int condEnd[] = { 14, 32 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(10,0,0,1,32,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(10,0,0,1,14,-1,2);
        _SFD_CV_INIT_EML_RELATIONAL(10,0,1,18,32,-1,2);
        _SFD_CV_INIT_EML(6,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(6,0,0,1,14,1,14);
        _SFD_CV_INIT_EML_RELATIONAL(6,0,0,1,14,-1,5);
        _SFD_CV_INIT_EML(7,0,0,1,0,0,0,0,0,3,1);
        _SFD_CV_INIT_EML_IF(7,0,0,1,46,1,46);

        {
          static int condStart[] = { 3, 21, 40 };

          static int condEnd[] = { 17, 35, 46 };

          static int pfixExpr[] = { 0, 1, -2, 2, -3 };

          _SFD_CV_INIT_EML_MCDC(7,0,0,2,46,3,0,&(condStart[0]),&(condEnd[0]),5,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(7,0,0,3,17,-1,2);
        _SFD_CV_INIT_EML_RELATIONAL(7,0,1,21,35,-1,2);
        _SFD_CV_INIT_EML(9,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(9,0,0,1,14,1,14);
        _SFD_CV_INIT_EML_RELATIONAL(9,0,0,1,14,-1,3);
        _SFD_CV_INIT_EML(11,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(11,0,0,1,14,1,14);
        _SFD_CV_INIT_EML(12,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(12,0,0,0,13,0,13);
        _SFD_CV_INIT_EML(13,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(13,0,0,0,12,0,12);
        _SFD_CV_INIT_EML(14,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(14,0,0,1,14,1,14);
        _SFD_CV_INIT_EML_RELATIONAL(14,0,0,1,14,-1,3);
        _SFD_CV_INIT_EML(15,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(15,0,0,1,25,1,25);
        _SFD_CV_INIT_EML_RELATIONAL(15,0,0,1,25,-3,5);
        _SFD_CV_INIT_EML(16,0,0,1,0,0,0,0,0,2,1);
        _SFD_CV_INIT_EML_IF(16,0,0,1,61,1,48);

        {
          static int condStart[] = { 1, 18 };

          static int condEnd[] = { 14, 61 };

          static int pfixExpr[] = { 0, 1, -2 };

          _SFD_CV_INIT_EML_MCDC(16,0,0,1,61,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_CV_INIT_EML_RELATIONAL(16,0,0,18,61,-3,2);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sensors_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_lightCalib_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_h_sf_marshallOut,(MexInFcnForType)c6_g_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_PWM_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_initFlags_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_k_sf_marshallOut,(MexInFcnForType)c6_j_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_states_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_lightCalib_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_balancerStates_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_sf_marshallOut,(MexInFcnForType)c6_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(15,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(16,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(17,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(18,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(19,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(20,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(21,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(22,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(23,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(24,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(25,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(26,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c6_sensors);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c6_lightCalib_address);
        _SFD_SET_DATA_VALUE_PTR(2U,
          chartInstance->c6_current_task_operation_status_address);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c6_PWM);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c6_initFlags);
        _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c6_desired_tail);
        _SFD_SET_DATA_VALUE_PTR(6U, &chartInstance->c6_balancerStates_Bus0);
        _SFD_SET_DATA_VALUE_PTR(7U, &chartInstance->c6_turningPWM);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c6_states);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c6_BT_status_out);
        _SFD_SET_DATA_VALUE_PTR(10U, &chartInstance->c6_normalizedLight);
        _SFD_SET_DATA_VALUE_PTR(11U, &chartInstance->c6_forwardPWM);
        _SFD_SET_DATA_VALUE_PTR(12U, &chartInstance->c6_des_vel);
        _SFD_SET_DATA_VALUE_PTR(13U, &chartInstance->c6_desired_phi);
        _SFD_SET_DATA_VALUE_PTR(14U, &chartInstance->c6_desiredangle);
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
  return "v7AKAthIgjmREtY1dlgLkH";
}

static void sf_opaque_initialize_c6_et_robocon(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_et_roboconInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c6_et_robocon((SFc6_et_roboconInstanceStruct*)
    chartInstanceVar);
  initialize_c6_et_robocon((SFc6_et_roboconInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_et_robocon(void *chartInstanceVar)
{
  enable_c6_et_robocon((SFc6_et_roboconInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_et_robocon(void *chartInstanceVar)
{
  disable_c6_et_robocon((SFc6_et_roboconInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_et_robocon(void *chartInstanceVar)
{
  sf_gateway_c6_et_robocon((SFc6_et_roboconInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c6_et_robocon(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c6_et_robocon((SFc6_et_roboconInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c6_et_robocon(SimStruct* S, const mxArray
  *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c6_et_robocon((SFc6_et_roboconInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c6_et_robocon(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_et_roboconInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_et_robocon_optimization_info();
    }

    finalize_c6_et_robocon((SFc6_et_roboconInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_et_robocon((SFc6_et_roboconInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_et_robocon(SimStruct *S)
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
    initialize_params_c6_et_robocon((SFc6_et_roboconInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_et_robocon(SimStruct *S)
{
  /* Actual parameters from chart:
     balancerStates_Bus0
   */
  const char_T *rtParamNames[] = { "balancerStates_Bus0" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0],
    sf_get_param_data_type_id(S,0));
  ssSetModelReferenceSampleTimeDisallowInheritance(S);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_et_robocon_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,6,"RTWCG"));
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,6,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,6);
    sf_mark_output_events_with_multiple_callers(S,sf_get_instance_specialization
      (),infoStruct,6,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,12);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=12; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3089929208U));
  ssSetChecksum1(S,(759248024U));
  ssSetChecksum2(S,(265139019U));
  ssSetChecksum3(S,(2200757615U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c6_et_robocon(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c6_et_robocon(SimStruct *S)
{
  SFc6_et_roboconInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc6_et_roboconInstanceStruct *)utMalloc(sizeof
    (SFc6_et_roboconInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_et_roboconInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c6_et_robocon;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c6_et_robocon;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c6_et_robocon;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_et_robocon;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_et_robocon;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c6_et_robocon;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c6_et_robocon;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c6_et_robocon;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_et_robocon;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_et_robocon;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c6_et_robocon;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn =
    sf_exported_auto_userFcnGatewayc6_et_robocon;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn =
    sf_exported_auto_autoFcnGatewayc6_et_robocon;
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

void c6_et_robocon_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_et_robocon(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_et_robocon(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_et_robocon(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_et_robocon_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
