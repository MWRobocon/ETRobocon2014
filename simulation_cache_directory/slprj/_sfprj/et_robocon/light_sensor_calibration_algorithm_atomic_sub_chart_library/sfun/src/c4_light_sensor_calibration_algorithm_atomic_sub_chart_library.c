/* Include files */

#include <stddef.h>
#include "blas.h"
#include "light_sensor_calibration_algorithm_atomic_sub_chart_library_sfun.h"
#include "c4_light_sensor_calibration_algorithm_atomic_sub_chart_library.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "light_sensor_calibration_algorithm_atomic_sub_chart_library_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c4_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c4_IN_MoveUp                   ((uint8_T)1U)
#define c4_IN_Reset                    ((uint8_T)2U)
#define c4_IN_light_sensor_calibration_up ((uint8_T)3U)
#define c4_IN_wait                     ((uint8_T)4U)
#define c4_IN_CalibComplete            ((uint8_T)1U)
#define c4_IN_StoreBlack               ((uint8_T)2U)
#define c4_IN_StoreWhite               ((uint8_T)3U)
#define c4_IN_WaitForBlack             ((uint8_T)4U)
#define c4_IN_WaitForWhite             ((uint8_T)5U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c4_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_d_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_e_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_f_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_g_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_h_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_i_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_j_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_k_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_l_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_m_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_n_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_o_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_p_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_q_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_r_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_s_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_t_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_u_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_v_debug_family_names[2] = { "nargin", "nargout" };

static const char * c4_w_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_x_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_y_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_ab_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_bb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_cb_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c4_db_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

/* Function Declarations */
static void
  initialize_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  initialize_params_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  enable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  disable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void c4_update_debugger_state_c4_light_sensor_calibration_algorithm_a
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static const mxArray
  *get_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  set_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_st);
static void c4_set_sim_state_side_effects_c4_light_sensor_calibration_algori
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  finalize_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  sf_gateway_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  mdl_start_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void c4_c4_light_sensor_calibration_algorithm_atomic_sub_chart_librar
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static boolean_T
  isStablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void duringc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void enterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void exitc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  gatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void enablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  disablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  initBuffersc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  stepBuffersc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void initc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  activate_callc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  deactivate_callc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  increment_call_counterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  reset_call_counterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  check_state_inconsistency_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  initSimStructsc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void c4_light_sensor_calibration_up
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static real_T c4_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static boolean_T c4_b_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real32_T c4_c_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_sf_internal_predicateOutput, const char_T
   *c4_identifier);
static real32_T c4_d_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(const mxArray **c4_info);
static const mxArray *c4_emlrt_marshallOut(const char * c4_u);
static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_e_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static uint8_T c4_f_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_tp_wait, const char_T *c4_identifier);
static uint8_T c4_g_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_sensors_bus_io(void *chartInstanceVoid, void *c4_pData);
static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_lightCalib_bus_io(void *chartInstanceVoid, void
  *c4_pData);
static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static c4_Light_Bus c4_h_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static c4_OperationModeStatusEnum c4_i_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_PWM_bus_io(void *chartInstanceVoid, void *c4_pData);
static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static c4_PWM_bus c4_j_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_PWM, const char_T *c4_identifier);
static c4_PWM_bus c4_k_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_initFlags_bus_io(void *chartInstanceVoid, void
  *c4_pData);
static const mxArray *c4_c_emlrt_marshallOut
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const c4_Init_Bus c4_u);
static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static c4_Init_Bus c4_l_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_initFlags, const char_T *c4_identifier);
static c4_Init_Bus c4_m_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint16_T c4_n_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_temporalCounter_i1, const char_T
   *c4_identifier);
static uint16_T c4_o_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_p_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_dataWrittenToVector, const char_T
   *c4_identifier, boolean_T c4_y[3]);
static void c4_q_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
   boolean_T c4_y[3]);
static const mxArray *c4_r_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_setSimStateSideEffectsInfo, const char_T *
   c4_identifier);
static const mxArray *c4_s_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_updateDataWrittenToVector
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_vectorIndex);
static void c4_bus_wr_access_lightCalib_2
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, int32_T c4_u0, int32_T c4_u1, int32_T c4_u2, int32_T c4_u3);
static c4_OperationModeStatusEnum c4_get_current_task_operation_status
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_elementIndex);
static void c4_set_current_task_operation_status
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_elementIndex, c4_OperationModeStatusEnum
   c4_elementValue);
static c4_OperationModeStatusEnum *c4_access_current_task_operation_status
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_rdOnly);
static c4_Light_Bus c4_get_lightCalib
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_elementIndex);
static void c4_set_lightCalib
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_elementIndex, c4_Light_Bus c4_elementValue);
static c4_Light_Bus *c4_access_lightCalib
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_rdOnly);
static void init_dsm_address_info
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void init_simulink_io_address
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);

/* Function Definitions */
static void
  initialize_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  initialize_params_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  enable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  disable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void c4_update_debugger_state_c4_light_sensor_calibration_algorithm_a
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c4_prevAniVal;
  c4_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c4_is_active_c4_light_sensor_calibration_algorithm_atomic_sub_ch
      == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      == c4_IN_wait) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      == c4_IN_MoveUp) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      == c4_IN_Reset) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      == c4_IN_light_sensor_calibration_up) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_WaitForBlack) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_StoreBlack) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_WaitForWhite) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_StoreWhite) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
  }

  if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_CalibComplete) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
  }

  _SFD_SET_ANIMATION(c4_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray
  *get_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  const mxArray *c4_b_y = NULL;
  real32_T c4_u;
  const mxArray *c4_c_y = NULL;
  real32_T c4_b_u;
  const mxArray *c4_d_y = NULL;
  real32_T c4_c_u;
  const mxArray *c4_e_y = NULL;
  c4_Init_Bus c4_r0;
  real32_T c4_hoistedGlobal;
  real32_T c4_d_u;
  const mxArray *c4_f_y = NULL;
  uint8_T c4_b_hoistedGlobal;
  uint8_T c4_e_u;
  const mxArray *c4_g_y = NULL;
  uint8_T c4_c_hoistedGlobal;
  uint8_T c4_f_u;
  const mxArray *c4_h_y = NULL;
  uint8_T c4_d_hoistedGlobal;
  uint8_T c4_g_u;
  const mxArray *c4_i_y = NULL;
  uint16_T c4_e_hoistedGlobal;
  uint16_T c4_h_u;
  const mxArray *c4_j_y = NULL;
  int32_T c4_i0;
  boolean_T c4_i_u[3];
  const mxArray *c4_k_y = NULL;
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(8, 1), false);
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c4_u = *(real32_T *)&((char_T *)chartInstance->c4_PWM)[0];
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_b_y, c4_c_y, "left", "left", 0);
  c4_b_u = *(real32_T *)&((char_T *)chartInstance->c4_PWM)[4];
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_b_y, c4_d_y, "right", "right", 0);
  c4_c_u = *(real32_T *)&((char_T *)chartInstance->c4_PWM)[8];
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_b_y, c4_e_y, "tail", "tail", 0);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_r0.fall = *(boolean_T *)&((char_T *)chartInstance->c4_initFlags)[0];
  c4_r0.gyroInit = *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[4];
  c4_r0.gyroReset = *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[8];
  c4_r0.theta = *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[12];
  c4_r0.tail = *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[16];
  sf_mex_setcell(c4_y, 1, c4_c_emlrt_marshallOut(chartInstance, c4_r0));
  c4_hoistedGlobal = chartInstance->c4_desired_tail;
  c4_d_u = c4_hoistedGlobal;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 2, c4_f_y);
  c4_b_hoistedGlobal =
    chartInstance->c4_is_active_c4_light_sensor_calibration_algorithm_atomic_sub_ch;
  c4_e_u = c4_b_hoistedGlobal;
  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", &c4_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 3, c4_g_y);
  c4_c_hoistedGlobal =
    chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib;
  c4_f_u = c4_c_hoistedGlobal;
  c4_h_y = NULL;
  sf_mex_assign(&c4_h_y, sf_mex_create("y", &c4_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 4, c4_h_y);
  c4_d_hoistedGlobal = chartInstance->c4_is_light_sensor_calibration_up;
  c4_g_u = c4_d_hoistedGlobal;
  c4_i_y = NULL;
  sf_mex_assign(&c4_i_y, sf_mex_create("y", &c4_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 5, c4_i_y);
  c4_e_hoistedGlobal = chartInstance->c4_temporalCounter_i1;
  c4_h_u = c4_e_hoistedGlobal;
  c4_j_y = NULL;
  sf_mex_assign(&c4_j_y, sf_mex_create("y", &c4_h_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 6, c4_j_y);
  for (c4_i0 = 0; c4_i0 < 3; c4_i0++) {
    c4_i_u[c4_i0] = chartInstance->c4_dataWrittenToVector[c4_i0];
  }

  c4_k_y = NULL;
  sf_mex_assign(&c4_k_y, sf_mex_create("y", c4_i_u, 11, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c4_y, 7, c4_k_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void
  set_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  c4_PWM_bus c4_r1;
  c4_Init_Bus c4_r2;
  boolean_T c4_bv0[3];
  int32_T c4_i1;
  c4_u = sf_mex_dup(c4_st);
  c4_r1 = c4_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)),
    "PWM");
  *(real32_T *)&((char_T *)chartInstance->c4_PWM)[0] = c4_r1.left;
  *(real32_T *)&((char_T *)chartInstance->c4_PWM)[4] = c4_r1.right;
  *(real32_T *)&((char_T *)chartInstance->c4_PWM)[8] = c4_r1.tail;
  c4_r2 = c4_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
    "initFlags");
  *(boolean_T *)&((char_T *)chartInstance->c4_initFlags)[0] = c4_r2.fall;
  *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[4] = c4_r2.gyroInit;
  *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[8] = c4_r2.gyroReset;
  *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[12] = c4_r2.theta;
  *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[16] = c4_r2.tail;
  chartInstance->c4_desired_tail = c4_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 2)), "desired_tail");
  chartInstance->c4_is_active_c4_light_sensor_calibration_algorithm_atomic_sub_ch
    = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 3)),
    "is_active_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library");
  chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
    = c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 4)),
    "is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library");
  chartInstance->c4_is_light_sensor_calibration_up = c4_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 5)),
     "is_light_sensor_calibration_up");
  chartInstance->c4_temporalCounter_i1 = c4_n_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c4_u, 6)), "temporalCounter_i1");
  c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 7)),
                        "dataWrittenToVector", c4_bv0);
  for (c4_i1 = 0; c4_i1 < 3; c4_i1++) {
    chartInstance->c4_dataWrittenToVector[c4_i1] = c4_bv0[c4_i1];
  }

  sf_mex_assign(&chartInstance->c4_setSimStateSideEffectsInfo,
                c4_r_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c4_u, 8)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c4_u);
  chartInstance->c4_doSetSimStateSideEffects = 1U;
  c4_update_debugger_state_c4_light_sensor_calibration_algorithm_a(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void c4_set_sim_state_side_effects_c4_light_sensor_calibration_algori
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  if (chartInstance->c4_doSetSimStateSideEffects != 0) {
    if (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
        == c4_IN_MoveUp) {
      chartInstance->c4_tp_MoveUp = 1U;
      if (sf_mex_sub(chartInstance->c4_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 2) == 0.0) {
        chartInstance->c4_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c4_tp_MoveUp = 0U;
    }

    if (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
        == c4_IN_Reset) {
      chartInstance->c4_tp_Reset = 1U;
      if (sf_mex_sub(chartInstance->c4_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 3) == 0.0) {
        chartInstance->c4_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c4_tp_Reset = 0U;
    }

    if (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
        == c4_IN_light_sensor_calibration_up) {
      chartInstance->c4_tp_light_sensor_calibration_up = 1U;
    } else {
      chartInstance->c4_tp_light_sensor_calibration_up = 0U;
    }

    if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_CalibComplete)
    {
      chartInstance->c4_tp_CalibComplete = 1U;
    } else {
      chartInstance->c4_tp_CalibComplete = 0U;
    }

    if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_StoreBlack) {
      chartInstance->c4_tp_StoreBlack = 1U;
      if (sf_mex_sub(chartInstance->c4_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 6) == 0.0) {
        chartInstance->c4_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c4_tp_StoreBlack = 0U;
    }

    if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_StoreWhite) {
      chartInstance->c4_tp_StoreWhite = 1U;
      if (sf_mex_sub(chartInstance->c4_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 7) == 0.0) {
        chartInstance->c4_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c4_tp_StoreWhite = 0U;
    }

    if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_WaitForBlack)
    {
      chartInstance->c4_tp_WaitForBlack = 1U;
    } else {
      chartInstance->c4_tp_WaitForBlack = 0U;
    }

    if (chartInstance->c4_is_light_sensor_calibration_up == c4_IN_WaitForWhite)
    {
      chartInstance->c4_tp_WaitForWhite = 1U;
    } else {
      chartInstance->c4_tp_WaitForWhite = 0U;
    }

    if (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
        == c4_IN_wait) {
      chartInstance->c4_tp_wait = 1U;
    } else {
      chartInstance->c4_tp_wait = 0U;
    }

    chartInstance->c4_doSetSimStateSideEffects = 0U;
  }
}

static void
  finalize_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  sf_mex_destroy(&chartInstance->c4_setSimStateSideEffectsInfo);
}

static void
  sf_gateway_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  c4_set_sim_state_side_effects_c4_light_sensor_calibration_algori(chartInstance);
}

static void
  mdl_start_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void c4_c4_light_sensor_calibration_algorithm_atomic_sub_chart_librar
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c4_debug_family_var_map[3];
  real_T c4_nargin = 0.0;
  real_T c4_nargout = 1.0;
  boolean_T c4_out;
  uint32_T c4_b_debug_family_var_map[2];
  real_T c4_b_nargin = 0.0;
  real_T c4_b_nargout = 0.0;
  uint16_T c4_u0;
  void *c4_inputVarPtrs[1];
  int32_T c4_inputVarSizes[1];
  real_T c4_c_nargin = 0.0;
  real_T c4_c_nargout = 1.0;
  boolean_T c4_b_out;
  real_T c4_d_nargin = 0.0;
  real_T c4_d_nargout = 0.0;
  real_T c4_e_nargin = 0.0;
  real_T c4_e_nargout = 0.0;
  real_T c4_f_nargin = 0.0;
  real_T c4_f_nargout = 0.0;
  uint16_T c4_u1;
  real_T c4_g_nargin = 0.0;
  real_T c4_g_nargout = 1.0;
  boolean_T c4_c_out;
  real_T c4_h_nargin = 0.0;
  real_T c4_h_nargout = 0.0;
  real_T c4_i_nargin = 0.0;
  real_T c4_i_nargout = 0.0;
  uint16_T c4_u2;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_isStable = true;
  switch
    (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib)
  {
   case c4_IN_MoveUp:
    CV_CHART_EVAL(0, 0, 1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U, chartInstance->c4_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c4_t_debug_family_names,
      c4_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 0U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 1U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_out, 2U, c4_b_sf_marshallOut,
      c4_b_sf_marshallIn);
    c4_out = CV_EML_IF(5, 0, 0, chartInstance->c4_temporalCounter_i1 >= 500);
    _SFD_SYMBOL_SCOPE_POP();
    if (c4_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
      chartInstance->c4_tp_MoveUp = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
      chartInstance->c4_isStable = false;
      chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
        = c4_IN_Reset;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
      chartInstance->c4_temporalCounter_i1 = 0U;
      chartInstance->c4_tp_Reset = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_c_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      c4_u0 = 202U;
      c4_inputVarPtrs[0U] = (void *)&c4_u0;
      c4_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c4_inputVarPtrs, (void *)c4_inputVarSizes, 0, NULL,
                           NULL);
      *(real32_T *)&((char_T *)chartInstance->c4_PWM)[8] = 0.0F;
      c4_updateDataWrittenToVector(chartInstance, 0U);
      *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[16] = 1.0F;
      c4_updateDataWrittenToVector(chartInstance, 1U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                   chartInstance->c4_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_Reset:
    CV_CHART_EVAL(0, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U, chartInstance->c4_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c4_u_debug_family_names,
      c4_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_c_nargin, 0U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_c_nargout, 1U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_out, 2U, c4_b_sf_marshallOut,
      c4_b_sf_marshallIn);
    c4_b_out = CV_EML_IF(8, 0, 0, chartInstance->c4_temporalCounter_i1 >= 250);
    _SFD_SYMBOL_SCOPE_POP();
    if (c4_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_v_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_d_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_d_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
      chartInstance->c4_tp_Reset = 0U;
      _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_d_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_e_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_e_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[16] = 0.0F;
      c4_updateDataWrittenToVector(chartInstance, 1U);
      chartInstance->c4_desired_tail = 0.0F;
      c4_updateDataWrittenToVector(chartInstance, 2U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c4_desired_tail, 5U);
      _SFD_SYMBOL_SCOPE_POP();
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
      chartInstance->c4_isStable = false;
      chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
        = c4_IN_light_sensor_calibration_up;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
      chartInstance->c4_tp_light_sensor_calibration_up = 1U;
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
      chartInstance->c4_isStable = false;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_WaitForBlack;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
      chartInstance->c4_tp_WaitForBlack = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_e_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_f_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_f_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      c4_u1 = 203U;
      c4_inputVarPtrs[0U] = (void *)&c4_u1;
      c4_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c4_inputVarPtrs, (void *)c4_inputVarSizes, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U,
                   chartInstance->c4_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_light_sensor_calibration_up:
    CV_CHART_EVAL(0, 0, 3);
    c4_light_sensor_calibration_up(chartInstance);
    break;

   case c4_IN_wait:
    CV_CHART_EVAL(0, 0, 4);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U, chartInstance->c4_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c4_r_debug_family_names,
      c4_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_g_nargin, 0U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_g_nargout, 1U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_c_out, 2U, c4_b_sf_marshallOut,
      c4_b_sf_marshallIn);
    c4_c_out = CV_EML_IF(7, 0, 0, *(real32_T *)&((char_T *)
      chartInstance->c4_sensors)[28] != 0.0F);
    _SFD_SYMBOL_SCOPE_POP();
    if (c4_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_s_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_h_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_h_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
      chartInstance->c4_tp_wait = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
      chartInstance->c4_isStable = false;
      chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
        = c4_IN_MoveUp;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
      chartInstance->c4_temporalCounter_i1 = 0U;
      chartInstance->c4_tp_MoveUp = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_b_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_i_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_i_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      c4_u2 = 201U;
      c4_inputVarPtrs[0U] = (void *)&c4_u2;
      c4_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c4_inputVarPtrs, (void *)c4_inputVarSizes, 0, NULL,
                           NULL);
      *(real32_T *)&((char_T *)chartInstance->c4_PWM)[8] = -50.0F;
      c4_updateDataWrittenToVector(chartInstance, 0U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                   chartInstance->c4_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c4_sfEvent);
    break;

   default:
    CV_CHART_EVAL(0, 0, 0);
    chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
    break;
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
}

static boolean_T
  isStablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  return chartInstance->c4_isStable;
}

static void duringc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  c4_c4_light_sensor_calibration_algorithm_atomic_sub_chart_librar(chartInstance);
}

static void enterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c4_debug_family_var_map[2];
  real_T c4_nargin = 0.0;
  real_T c4_nargout = 0.0;
  uint16_T c4_u3;
  void *c4_inputVarPtrs[1];
  int32_T c4_inputVarSizes[1];
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
  chartInstance->c4_is_active_c4_light_sensor_calibration_algorithm_atomic_sub_ch
    = 1U;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c4_sfEvent);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
  chartInstance->c4_isStable = false;
  chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
    = c4_IN_wait;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
  chartInstance->c4_tp_wait = 1U;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 0U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 1U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  c4_u3 = 200U;
  c4_inputVarPtrs[0U] = (void *)&c4_u3;
  c4_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
  sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)c4_inputVarPtrs,
                       (void *)c4_inputVarSizes, 0, NULL, NULL);
  _SFD_SYMBOL_SCOPE_POP();
}

static void exitc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c4_debug_family_var_map[2];
  real_T c4_nargin = 0.0;
  real_T c4_nargout = 0.0;
  _sfTime_ = sf_get_time(chartInstance->S);
  switch
    (chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib)
  {
   case c4_IN_MoveUp:
    CV_CHART_EVAL(0, 0, 1);
    chartInstance->c4_tp_MoveUp = 0U;
    chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_Reset:
    CV_CHART_EVAL(0, 0, 2);
    chartInstance->c4_tp_Reset = 0U;
    _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_d_debug_family_names,
      c4_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 0U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 1U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    *(real32_T *)&((char_T *)chartInstance->c4_initFlags)[16] = 0.0F;
    c4_updateDataWrittenToVector(chartInstance, 1U);
    chartInstance->c4_desired_tail = 0.0F;
    c4_updateDataWrittenToVector(chartInstance, 2U);
    _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c4_desired_tail, 5U);
    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c4_sfEvent);
    chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_light_sensor_calibration_up:
    CV_CHART_EVAL(0, 0, 3);
    switch (chartInstance->c4_is_light_sensor_calibration_up) {
     case c4_IN_CalibComplete:
      CV_STATE_EVAL(2, 1, 1);
      chartInstance->c4_tp_CalibComplete = 0U;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_StoreBlack:
      CV_STATE_EVAL(2, 1, 2);
      chartInstance->c4_tp_StoreBlack = 0U;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_StoreWhite:
      CV_STATE_EVAL(2, 1, 3);
      chartInstance->c4_tp_StoreWhite = 0U;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_WaitForBlack:
      CV_STATE_EVAL(2, 1, 4);
      chartInstance->c4_tp_WaitForBlack = 0U;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
      break;

     case c4_IN_WaitForWhite:
      CV_STATE_EVAL(2, 1, 5);
      chartInstance->c4_tp_WaitForWhite = 0U;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
      break;

     default:
      CV_STATE_EVAL(2, 1, 0);
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
      break;
    }

    chartInstance->c4_tp_light_sensor_calibration_up = 0U;
    chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_wait:
    CV_CHART_EVAL(0, 0, 4);
    chartInstance->c4_tp_wait = 0U;
    chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c4_sfEvent);
    break;

   default:
    CV_CHART_EVAL(0, 0, 0);
    chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
      = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c4_sfEvent);
    break;
  }
}

static void
  gatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c4_temporalCounter_i1 < 511U) {
    chartInstance->c4_temporalCounter_i1++;
  }
}

static void enablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void
  disablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c4_temporalCounter_i1 < 511U) {
    chartInstance->c4_temporalCounter_i1++;
  }
}

static void
  initBuffersc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  stepBuffersc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void initc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_doSetSimStateSideEffects = 0U;
  chartInstance->c4_setSimStateSideEffectsInfo = NULL;
  chartInstance->c4_tp_MoveUp = 0U;
  chartInstance->c4_temporalCounter_i1 = 0U;
  chartInstance->c4_tp_Reset = 0U;
  chartInstance->c4_temporalCounter_i1 = 0U;
  chartInstance->c4_is_light_sensor_calibration_up = c4_IN_NO_ACTIVE_CHILD;
  chartInstance->c4_tp_light_sensor_calibration_up = 0U;
  chartInstance->c4_tp_CalibComplete = 0U;
  chartInstance->c4_tp_StoreBlack = 0U;
  chartInstance->c4_temporalCounter_i1 = 0U;
  chartInstance->c4_tp_StoreWhite = 0U;
  chartInstance->c4_temporalCounter_i1 = 0U;
  chartInstance->c4_tp_WaitForBlack = 0U;
  chartInstance->c4_tp_WaitForWhite = 0U;
  chartInstance->c4_tp_wait = 0U;
  chartInstance->c4_is_active_c4_light_sensor_calibration_algorithm_atomic_sub_ch
    = 0U;
  chartInstance->c4_is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_lib
    = c4_IN_NO_ACTIVE_CHILD;
}

static void
  activate_callc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
}

static void
  deactivate_callc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  increment_call_counterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  reset_call_counterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  check_state_inconsistency_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_light_sensor_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
     chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void
  initSimStructsc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void c4_light_sensor_calibration_up
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c4_debug_family_var_map[3];
  real_T c4_nargin = 0.0;
  real_T c4_nargout = 1.0;
  boolean_T c4_out;
  uint32_T c4_b_debug_family_var_map[2];
  real_T c4_b_nargin = 0.0;
  real_T c4_b_nargout = 0.0;
  real_T c4_c_nargin = 0.0;
  real_T c4_c_nargout = 0.0;
  uint16_T c4_u4;
  void *c4_inputVarPtrs[1];
  int32_T c4_inputVarSizes[1];
  real_T c4_d_nargin = 0.0;
  real_T c4_d_nargout = 1.0;
  boolean_T c4_b_out;
  real_T c4_e_nargin = 0.0;
  real_T c4_e_nargout = 0.0;
  real_T c4_f_nargin = 0.0;
  real_T c4_f_nargout = 0.0;
  uint16_T c4_u5;
  real_T c4_g_nargin = 0.0;
  real_T c4_g_nargout = 1.0;
  boolean_T c4_c_out;
  real_T c4_h_nargin = 0.0;
  real_T c4_h_nargout = 0.0;
  real_T c4_i_nargin = 0.0;
  real_T c4_i_nargout = 0.0;
  uint16_T c4_u6;
  real_T c4_j_nargin = 0.0;
  real_T c4_j_nargout = 1.0;
  boolean_T c4_d_out;
  real_T c4_k_nargin = 0.0;
  real_T c4_k_nargout = 0.0;
  real_T c4_l_nargin = 0.0;
  real_T c4_l_nargout = 0.0;
  uint16_T c4_u7;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
  switch (chartInstance->c4_is_light_sensor_calibration_up) {
   case c4_IN_CalibComplete:
    CV_STATE_EVAL(2, 0, 1);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_StoreBlack:
    CV_STATE_EVAL(2, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U, chartInstance->c4_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c4_l_debug_family_names,
      c4_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 0U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 1U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_out, 2U, c4_b_sf_marshallOut,
      c4_b_sf_marshallIn);
    c4_out = CV_EML_IF(3, 0, 0, chartInstance->c4_temporalCounter_i1 >= 50);
    _SFD_SYMBOL_SCOPE_POP();
    if (c4_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_m_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
      chartInstance->c4_tp_StoreBlack = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
      chartInstance->c4_isStable = false;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_WaitForWhite;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
      chartInstance->c4_tp_WaitForWhite = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_g_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_c_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_c_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      c4_u4 = 205U;
      c4_inputVarPtrs[0U] = (void *)&c4_u4;
      c4_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c4_inputVarPtrs, (void *)c4_inputVarSizes, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                   chartInstance->c4_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_StoreWhite:
    CV_STATE_EVAL(2, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U, chartInstance->c4_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c4_p_debug_family_names,
      c4_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_d_nargin, 0U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_d_nargout, 1U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_out, 2U, c4_b_sf_marshallOut,
      c4_b_sf_marshallIn);
    c4_b_out = CV_EML_IF(4, 0, 0, chartInstance->c4_temporalCounter_i1 >= 50);
    _SFD_SYMBOL_SCOPE_POP();
    if (c4_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_q_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_e_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_e_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
      chartInstance->c4_tp_StoreWhite = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
      chartInstance->c4_isStable = false;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_CalibComplete;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
      chartInstance->c4_tp_CalibComplete = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_i_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_f_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_f_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      c4_u5 = 207U;
      c4_inputVarPtrs[0U] = (void *)&c4_u5;
      c4_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c4_inputVarPtrs, (void *)c4_inputVarSizes, 0, NULL,
                           NULL);
      c4_set_current_task_operation_status(chartInstance, 0,
        OperationModeStatusEnum_SUCCESSFULLY_COMPLETED);
      ssUpdateDataStoreLog(chartInstance->S, 0);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                   chartInstance->c4_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_WaitForBlack:
    CV_STATE_EVAL(2, 0, 4);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, chartInstance->c4_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c4_j_debug_family_names,
      c4_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_g_nargin, 0U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_g_nargout, 1U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_c_out, 2U, c4_b_sf_marshallOut,
      c4_b_sf_marshallIn);
    c4_c_out = CV_EML_IF(1, 0, 0, *(real32_T *)&((char_T *)
      chartInstance->c4_sensors)[28] != 0.0F);
    _SFD_SYMBOL_SCOPE_POP();
    if (c4_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c4_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_k_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_h_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_h_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
      chartInstance->c4_tp_WaitForBlack = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c4_sfEvent);
      chartInstance->c4_isStable = false;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_StoreBlack;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c4_sfEvent);
      chartInstance->c4_temporalCounter_i1 = 0U;
      chartInstance->c4_tp_StoreBlack = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_f_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_i_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_i_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      c4_bus_wr_access_lightCalib_2(chartInstance, -1, 0, 2, 0);
      *(real32_T *)&((char_T *)c4_access_lightCalib(chartInstance, false))[8] = *
        (real32_T *)&((char_T *)chartInstance->c4_sensors)[12];
      ssUpdateDataStoreLog(chartInstance->S, 1);
      c4_u6 = 204U;
      c4_inputVarPtrs[0U] = (void *)&c4_u6;
      c4_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c4_inputVarPtrs, (void *)c4_inputVarSizes, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                   chartInstance->c4_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c4_sfEvent);
    break;

   case c4_IN_WaitForWhite:
    CV_STATE_EVAL(2, 0, 5);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, chartInstance->c4_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c4_n_debug_family_names,
      c4_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_j_nargin, 0U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_j_nargout, 1U, c4_sf_marshallOut,
      c4_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_d_out, 2U, c4_b_sf_marshallOut,
      c4_b_sf_marshallIn);
    c4_d_out = CV_EML_IF(2, 0, 0, *(real32_T *)&((char_T *)
      chartInstance->c4_sensors)[28] != 0.0F);
    _SFD_SYMBOL_SCOPE_POP();
    if (c4_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c4_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_o_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_k_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_k_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
      chartInstance->c4_tp_WaitForWhite = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c4_sfEvent);
      chartInstance->c4_isStable = false;
      chartInstance->c4_is_light_sensor_calibration_up = c4_IN_StoreWhite;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c4_sfEvent);
      chartInstance->c4_temporalCounter_i1 = 0U;
      chartInstance->c4_tp_StoreWhite = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c4_h_debug_family_names,
        c4_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_l_nargin, 0U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_l_nargout, 1U, c4_sf_marshallOut,
        c4_sf_marshallIn);
      c4_bus_wr_access_lightCalib_2(chartInstance, -1, 0, 3, 0);
      *(real32_T *)&((char_T *)c4_access_lightCalib(chartInstance, false))[12] =
        *(real32_T *)&((char_T *)chartInstance->c4_sensors)[12];
      ssUpdateDataStoreLog(chartInstance->S, 1);
      c4_u7 = 206U;
      c4_inputVarPtrs[0U] = (void *)&c4_u7;
      c4_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c4_inputVarPtrs, (void *)c4_inputVarSizes, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                   chartInstance->c4_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c4_sfEvent);
    break;

   default:
    CV_STATE_EVAL(2, 0, 0);
    chartInstance->c4_is_light_sensor_calibration_up = c4_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c4_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c4_sfEvent);
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)c4_machineNumber;
  (void)c4_chartNumber;
  (void)c4_instanceNumber;
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_nargout;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_nargout = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nargout), &c4_thisId);
  sf_mex_destroy(&c4_nargout);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  boolean_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(boolean_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static boolean_T c4_b_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  boolean_T c4_y;
  boolean_T c4_b0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_b0, 1, 11, 0U, 0, 0U, 0);
  c4_y = c4_b0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_sf_internal_predicateOutput;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  boolean_T c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_sf_internal_predicateOutput = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_sf_internal_predicateOutput), &c4_thisId);
  sf_mex_destroy(&c4_sf_internal_predicateOutput);
  *(boolean_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real32_T c4_c_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_sf_internal_predicateOutput, const char_T
   *c4_identifier)
{
  real32_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_sf_internal_predicateOutput), &c4_thisId);
  sf_mex_destroy(&c4_sf_internal_predicateOutput);
  return c4_y;
}

static real32_T c4_d_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real32_T c4_y;
  real32_T c4_f0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_f0, 1, 1, 0U, 0, 0U, 0);
  c4_y = c4_f0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_sf_internal_predicateOutput;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real32_T c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_sf_internal_predicateOutput = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_sf_internal_predicateOutput), &c4_thisId);
  sf_mex_destroy(&c4_sf_internal_predicateOutput);
  *(real32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray
  *sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_createstruct("structure", 2, 1, 1),
                false);
  c4_info_helper(&c4_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs0 = NULL;
  const mxArray *c4_lhs0 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("OperationModeStatusEnum"),
                  "name", "name", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[N]C:/ETRobocon2014/Repository/data_types/enumerations/OperationModeStatusEnum.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1409161942U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c4_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs0), "lhs", "lhs", 0);
  sf_mex_destroy(&c4_rhs0);
  sf_mex_destroy(&c4_lhs0);
}

static const mxArray *c4_emlrt_marshallOut(const char * c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c4_u)), false);
  return c4_y;
}

static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 7, 0U, 0U, 0U, 0), false);
  return c4_y;
}

void
  sf_exported_auto_userFcnGatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *c4_S, int32_T c4_ssidNumber, void *c4_ioVarPtrs)
{
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  (void)c4_ssidNumber;
  (void)c4_ioVarPtrs;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)((ChartInfoStruct *)((ChartRunTimeInfo *)ssGetUserData(c4_S))
        ->instanceInfo)->chartInstance;
}

void
  sf_exported_auto_autoFcnGatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *c4_S, int32_T c4_fcnNumber, void *c4_ioVarPtrs)
{
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)((ChartInfoStruct *)((ChartRunTimeInfo *)ssGetUserData(c4_S))
        ->instanceInfo)->chartInstance;
  if (c4_fcnNumber == -1) {
  } else if (c4_fcnNumber == 61) {
    *(boolean_T *)(*(void *(*)[1])c4_ioVarPtrs)[0] =
      isStablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 62) {
    duringc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 63) {
    enterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 64) {
    exitc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 65) {
    gatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 66) {
    enablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 67) {
    disablec4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 68) {
    initBuffersc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 69) {
    stepBuffersc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 70) {
    initSimStructsc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 71) {
    initc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 72) {
    activate_callc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 73) {
    deactivate_callc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 74) {
    increment_call_counterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c4_fcnNumber == 75) {
    reset_call_counterc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else {
    if (c4_fcnNumber == 76) {
      check_state_inconsistency_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
        (chartInstance);
    }
  }
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_e_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i2;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i2, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i2;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(uint8_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static uint8_T c4_f_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_tp_wait, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_tp_wait),
    &c4_thisId);
  sf_mex_destroy(&c4_b_tp_wait);
  return c4_y;
}

static uint8_T c4_g_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u8;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u8, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u8;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_tp_wait;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  uint8_T c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_b_tp_wait = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_tp_wait),
    &c4_thisId);
  sf_mex_destroy(&c4_b_tp_wait);
  *(uint8_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_sensors_bus_io(void *chartInstanceVoid, void *c4_pData)
{
  const mxArray *c4_mxVal = NULL;
  c4_Sensors_Bus c4_tmp;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxVal = NULL;
  c4_tmp.theta_L = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[0];
  c4_tmp.theta_R = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[4];
  c4_tmp.theta_T = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[8];
  c4_tmp.light = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[12];
  c4_tmp.gyro = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[16];
  c4_tmp.sonar = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[20];
  c4_tmp.battery = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[24];
  c4_tmp.touch = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[28];
  c4_tmp.time = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[32];
  c4_tmp.ok_button = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[36];
  c4_tmp.BT_status_in = *(real32_T *)&((char_T *)(c4_Sensors_Bus *)c4_pData)[40];
  sf_mex_assign(&c4_mxVal, c4_f_sf_marshallOut(chartInstance, &c4_tmp), false);
  return c4_mxVal;
}

static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  c4_Sensors_Bus c4_u;
  const mxArray *c4_y = NULL;
  real32_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  real32_T c4_c_u;
  const mxArray *c4_c_y = NULL;
  real32_T c4_d_u;
  const mxArray *c4_d_y = NULL;
  real32_T c4_e_u;
  const mxArray *c4_e_y = NULL;
  real32_T c4_f_u;
  const mxArray *c4_f_y = NULL;
  real32_T c4_g_u;
  const mxArray *c4_g_y = NULL;
  real32_T c4_h_u;
  const mxArray *c4_h_y = NULL;
  real32_T c4_i_u;
  const mxArray *c4_i_y = NULL;
  real32_T c4_j_u;
  const mxArray *c4_j_y = NULL;
  real32_T c4_k_u;
  const mxArray *c4_k_y = NULL;
  real32_T c4_l_u;
  const mxArray *c4_l_y = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(c4_Sensors_Bus *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c4_b_u = c4_u.theta_L;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_b_y, "theta_L", "theta_L", 0);
  c4_c_u = c4_u.theta_R;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_c_y, "theta_R", "theta_R", 0);
  c4_d_u = c4_u.theta_T;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_d_y, "theta_T", "theta_T", 0);
  c4_e_u = c4_u.light;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_e_y, "light", "light", 0);
  c4_f_u = c4_u.gyro;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_f_y, "gyro", "gyro", 0);
  c4_g_u = c4_u.sonar;
  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", &c4_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_g_y, "sonar", "sonar", 0);
  c4_h_u = c4_u.battery;
  c4_h_y = NULL;
  sf_mex_assign(&c4_h_y, sf_mex_create("y", &c4_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_h_y, "battery", "battery", 0);
  c4_i_u = c4_u.touch;
  c4_i_y = NULL;
  sf_mex_assign(&c4_i_y, sf_mex_create("y", &c4_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_i_y, "touch", "touch", 0);
  c4_j_u = c4_u.time;
  c4_j_y = NULL;
  sf_mex_assign(&c4_j_y, sf_mex_create("y", &c4_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_j_y, "time", "time", 0);
  c4_k_u = c4_u.ok_button;
  c4_k_y = NULL;
  sf_mex_assign(&c4_k_y, sf_mex_create("y", &c4_k_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_k_y, "ok_button", "ok_button", 0);
  c4_l_u = c4_u.BT_status_in;
  c4_l_y = NULL;
  sf_mex_assign(&c4_l_y, sf_mex_create("y", &c4_l_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_l_y, "BT_status_in", "BT_status_in", 0);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_lightCalib_bus_io(void *chartInstanceVoid, void
  *c4_pData)
{
  const mxArray *c4_mxVal = NULL;
  c4_Light_Bus c4_tmp;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxVal = NULL;
  c4_tmp.whiteOnLimbo = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[0];
  c4_tmp.blackOnLimbo = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[4];
  c4_tmp.black = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[8];
  c4_tmp.white = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[12];
  c4_tmp.black_white = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[16];
  c4_tmp.gray = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[20];
  c4_tmp.blackOnTail = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[24];
  c4_tmp.whiteOnTail = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[28];
  c4_tmp.flashingBlack = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[32];
  c4_tmp.flashingWhite = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)[36];
  c4_tmp.flashingMapBlack = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)
    [40];
  c4_tmp.flashingMapWhite = *(real32_T *)&((char_T *)(c4_Light_Bus *)c4_pData)
    [44];
  sf_mex_assign(&c4_mxVal, c4_g_sf_marshallOut(chartInstance, &c4_tmp), false);
  return c4_mxVal;
}

static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  c4_Light_Bus c4_u;
  const mxArray *c4_y = NULL;
  real32_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  real32_T c4_c_u;
  const mxArray *c4_c_y = NULL;
  real32_T c4_d_u;
  const mxArray *c4_d_y = NULL;
  real32_T c4_e_u;
  const mxArray *c4_e_y = NULL;
  real32_T c4_f_u;
  const mxArray *c4_f_y = NULL;
  real32_T c4_g_u;
  const mxArray *c4_g_y = NULL;
  real32_T c4_h_u;
  const mxArray *c4_h_y = NULL;
  real32_T c4_i_u;
  const mxArray *c4_i_y = NULL;
  real32_T c4_j_u;
  const mxArray *c4_j_y = NULL;
  real32_T c4_k_u;
  const mxArray *c4_k_y = NULL;
  real32_T c4_l_u;
  const mxArray *c4_l_y = NULL;
  real32_T c4_m_u;
  const mxArray *c4_m_y = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(c4_Light_Bus *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c4_b_u = c4_u.whiteOnLimbo;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_b_y, "whiteOnLimbo", "whiteOnLimbo", 0);
  c4_c_u = c4_u.blackOnLimbo;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_c_y, "blackOnLimbo", "blackOnLimbo", 0);
  c4_d_u = c4_u.black;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_d_y, "black", "black", 0);
  c4_e_u = c4_u.white;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_e_y, "white", "white", 0);
  c4_f_u = c4_u.black_white;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_f_y, "black_white", "black_white", 0);
  c4_g_u = c4_u.gray;
  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", &c4_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_g_y, "gray", "gray", 0);
  c4_h_u = c4_u.blackOnTail;
  c4_h_y = NULL;
  sf_mex_assign(&c4_h_y, sf_mex_create("y", &c4_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_h_y, "blackOnTail", "blackOnTail", 0);
  c4_i_u = c4_u.whiteOnTail;
  c4_i_y = NULL;
  sf_mex_assign(&c4_i_y, sf_mex_create("y", &c4_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_i_y, "whiteOnTail", "whiteOnTail", 0);
  c4_j_u = c4_u.flashingBlack;
  c4_j_y = NULL;
  sf_mex_assign(&c4_j_y, sf_mex_create("y", &c4_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_j_y, "flashingBlack", "flashingBlack", 0);
  c4_k_u = c4_u.flashingWhite;
  c4_k_y = NULL;
  sf_mex_assign(&c4_k_y, sf_mex_create("y", &c4_k_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_k_y, "flashingWhite", "flashingWhite", 0);
  c4_l_u = c4_u.flashingMapBlack;
  c4_l_y = NULL;
  sf_mex_assign(&c4_l_y, sf_mex_create("y", &c4_l_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_l_y, "flashingMapBlack", "flashingMapBlack", 0);
  c4_m_u = c4_u.flashingMapWhite;
  c4_m_y = NULL;
  sf_mex_assign(&c4_m_y, sf_mex_create("y", &c4_m_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_m_y, "flashingMapWhite", "flashingMapWhite", 0);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static c4_Light_Bus c4_h_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  c4_Light_Bus c4_y;
  emlrtMsgIdentifier c4_thisId;
  static const char * c4_fieldNames[12] = { "whiteOnLimbo", "blackOnLimbo",
    "black", "white", "black_white", "gray", "blackOnTail", "whiteOnTail",
    "flashingBlack", "flashingWhite", "flashingMapBlack", "flashingMapWhite" };

  c4_thisId.fParent = c4_parentId;
  sf_mex_check_struct(c4_parentId, c4_u, 12, c4_fieldNames, 0U, NULL);
  c4_thisId.fIdentifier = "whiteOnLimbo";
  c4_y.whiteOnLimbo = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "whiteOnLimbo", "whiteOnLimbo", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "blackOnLimbo";
  c4_y.blackOnLimbo = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "blackOnLimbo", "blackOnLimbo", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "black";
  c4_y.black = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "black", "black", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "white";
  c4_y.white = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "white", "white", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "black_white";
  c4_y.black_white = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "black_white", "black_white", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "gray";
  c4_y.gray = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "gray", "gray", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "blackOnTail";
  c4_y.blackOnTail = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "blackOnTail", "blackOnTail", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "whiteOnTail";
  c4_y.whiteOnTail = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "whiteOnTail", "whiteOnTail", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "flashingBlack";
  c4_y.flashingBlack = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "flashingBlack", "flashingBlack", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "flashingWhite";
  c4_y.flashingWhite = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "flashingWhite", "flashingWhite", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "flashingMapBlack";
  c4_y.flashingMapBlack = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "flashingMapBlack", "flashingMapBlack", 0)),
    &c4_thisId);
  c4_thisId.fIdentifier = "flashingMapWhite";
  c4_y.flashingMapWhite = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "flashingMapWhite", "flashingMapWhite", 0)),
    &c4_thisId);
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_lightCalib;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  c4_Light_Bus c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_lightCalib = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_lightCalib),
    &c4_thisId);
  sf_mex_destroy(&c4_lightCalib);
  *(c4_Light_Bus *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  c4_OperationModeStatusEnum c4_u;
  const mxArray *c4_y = NULL;
  static const int32_T c4_enumValues[4] = { 0, 1, 2, 3 };

  static const char * c4_enumNames[4] = { "NOT_STARTED", "IN_PROGRESS",
    "SUCCESSFULLY_COMPLETED", "ABORTED" };

  int32_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  const mxArray *c4_m0 = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(c4_OperationModeStatusEnum *)c4_inData;
  c4_y = NULL;
  sf_mex_check_enum("OperationModeStatusEnum", 4, c4_enumNames, c4_enumValues);
  c4_b_u = (int32_T)c4_u;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_m0, c4_b_y, false);
  sf_mex_assign(&c4_y, sf_mex_create_enum("OperationModeStatusEnum", c4_m0),
                false);
  sf_mex_destroy(&c4_m0);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static c4_OperationModeStatusEnum c4_i_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  c4_OperationModeStatusEnum c4_y;
  static const int32_T c4_enumValues[4] = { 0, 1, 2, 3 };

  static const char * c4_enumNames[4] = { "NOT_STARTED", "IN_PROGRESS",
    "SUCCESSFULLY_COMPLETED", "ABORTED" };

  (void)chartInstance;
  sf_mex_check_enum("OperationModeStatusEnum", 4, c4_enumNames, c4_enumValues);
  sf_mex_check_builtin(c4_parentId, c4_u, "OperationModeStatusEnum", 0, 0U, NULL);
  c4_y = (c4_OperationModeStatusEnum)sf_mex_get_enum_element(c4_u, 0);
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_current_task_operation_status;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  c4_OperationModeStatusEnum c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_current_task_operation_status = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_current_task_operation_status), &c4_thisId);
  sf_mex_destroy(&c4_current_task_operation_status);
  *(c4_OperationModeStatusEnum *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_PWM_bus_io(void *chartInstanceVoid, void *c4_pData)
{
  const mxArray *c4_mxVal = NULL;
  c4_PWM_bus c4_tmp;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxVal = NULL;
  c4_tmp.left = *(real32_T *)&((char_T *)(c4_PWM_bus *)c4_pData)[0];
  c4_tmp.right = *(real32_T *)&((char_T *)(c4_PWM_bus *)c4_pData)[4];
  c4_tmp.tail = *(real32_T *)&((char_T *)(c4_PWM_bus *)c4_pData)[8];
  sf_mex_assign(&c4_mxVal, c4_i_sf_marshallOut(chartInstance, &c4_tmp), false);
  return c4_mxVal;
}

static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  c4_PWM_bus c4_u;
  const mxArray *c4_y = NULL;
  real32_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  real32_T c4_c_u;
  const mxArray *c4_c_y = NULL;
  real32_T c4_d_u;
  const mxArray *c4_d_y = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(c4_PWM_bus *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c4_b_u = c4_u.left;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_b_y, "left", "left", 0);
  c4_c_u = c4_u.right;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_c_y, "right", "right", 0);
  c4_d_u = c4_u.tail;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_d_y, "tail", "tail", 0);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static c4_PWM_bus c4_j_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_PWM, const char_T *c4_identifier)
{
  c4_PWM_bus c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_PWM), &c4_thisId);
  sf_mex_destroy(&c4_b_PWM);
  return c4_y;
}

static c4_PWM_bus c4_k_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  c4_PWM_bus c4_y;
  emlrtMsgIdentifier c4_thisId;
  static const char * c4_fieldNames[3] = { "left", "right", "tail" };

  c4_thisId.fParent = c4_parentId;
  sf_mex_check_struct(c4_parentId, c4_u, 3, c4_fieldNames, 0U, NULL);
  c4_thisId.fIdentifier = "left";
  c4_y.left = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "left", "left", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "right";
  c4_y.right = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "right", "right", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "tail";
  c4_y.tail = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "tail", "tail", 0)), &c4_thisId);
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_PWM;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  c4_PWM_bus c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_b_PWM = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_PWM), &c4_thisId);
  sf_mex_destroy(&c4_b_PWM);
  *(c4_PWM_bus *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_initFlags_bus_io(void *chartInstanceVoid, void
  *c4_pData)
{
  const mxArray *c4_mxVal = NULL;
  c4_Init_Bus c4_tmp;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxVal = NULL;
  c4_tmp.fall = *(boolean_T *)&((char_T *)(c4_Init_Bus *)c4_pData)[0];
  c4_tmp.gyroInit = *(real32_T *)&((char_T *)(c4_Init_Bus *)c4_pData)[4];
  c4_tmp.gyroReset = *(real32_T *)&((char_T *)(c4_Init_Bus *)c4_pData)[8];
  c4_tmp.theta = *(real32_T *)&((char_T *)(c4_Init_Bus *)c4_pData)[12];
  c4_tmp.tail = *(real32_T *)&((char_T *)(c4_Init_Bus *)c4_pData)[16];
  sf_mex_assign(&c4_mxVal, c4_j_sf_marshallOut(chartInstance, &c4_tmp), false);
  return c4_mxVal;
}

static const mxArray *c4_c_emlrt_marshallOut
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const c4_Init_Bus c4_u)
{
  const mxArray *c4_y = NULL;
  boolean_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  real32_T c4_c_u;
  const mxArray *c4_c_y = NULL;
  real32_T c4_d_u;
  const mxArray *c4_d_y = NULL;
  real32_T c4_e_u;
  const mxArray *c4_e_y = NULL;
  real32_T c4_f_u;
  const mxArray *c4_f_y = NULL;
  (void)chartInstance;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c4_b_u = c4_u.fall;
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_b_y, "fall", "fall", 0);
  c4_c_u = c4_u.gyroInit;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_c_y, "gyroInit", "gyroInit", 0);
  c4_d_u = c4_u.gyroReset;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_d_y, "gyroReset", "gyroReset", 0);
  c4_e_u = c4_u.theta;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_e_y, "theta", "theta", 0);
  c4_f_u = c4_u.tail;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_f_y, "tail", "tail", 0);
  return c4_y;
}

static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  sf_mex_assign(&c4_mxArrayOutData, c4_c_emlrt_marshallOut(chartInstance,
    *(c4_Init_Bus *)c4_inData), false);
  return c4_mxArrayOutData;
}

static c4_Init_Bus c4_l_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_initFlags, const char_T *c4_identifier)
{
  c4_Init_Bus c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_initFlags),
    &c4_thisId);
  sf_mex_destroy(&c4_b_initFlags);
  return c4_y;
}

static c4_Init_Bus c4_m_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  c4_Init_Bus c4_y;
  emlrtMsgIdentifier c4_thisId;
  static const char * c4_fieldNames[5] = { "fall", "gyroInit", "gyroReset",
    "theta", "tail" };

  c4_thisId.fParent = c4_parentId;
  sf_mex_check_struct(c4_parentId, c4_u, 5, c4_fieldNames, 0U, NULL);
  c4_thisId.fIdentifier = "fall";
  c4_y.fall = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "fall", "fall", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "gyroInit";
  c4_y.gyroInit = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "gyroInit", "gyroInit", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "gyroReset";
  c4_y.gyroReset = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_u, "gyroReset", "gyroReset", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "theta";
  c4_y.theta = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "theta", "theta", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "tail";
  c4_y.tail = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_u, "tail", "tail", 0)), &c4_thisId);
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_initFlags;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  c4_Init_Bus c4_y;
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)chartInstanceVoid;
  c4_b_initFlags = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_initFlags),
    &c4_thisId);
  sf_mex_destroy(&c4_b_initFlags);
  *(c4_Init_Bus *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint16_T c4_n_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_temporalCounter_i1, const char_T
   *c4_identifier)
{
  uint16_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_temporalCounter_i1),
    &c4_thisId);
  sf_mex_destroy(&c4_b_temporalCounter_i1);
  return c4_y;
}

static uint16_T c4_o_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint16_T c4_y;
  uint16_T c4_u9;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u9, 1, 5, 0U, 0, 0U, 0);
  c4_y = c4_u9;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_p_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_dataWrittenToVector, const char_T
   *c4_identifier, boolean_T c4_y[3])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_dataWrittenToVector),
                        &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_dataWrittenToVector);
}

static void c4_q_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId,
   boolean_T c4_y[3])
{
  boolean_T c4_bv1[3];
  int32_T c4_i3;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_bv1, 1, 11, 0U, 1, 0U, 1, 3);
  for (c4_i3 = 0; c4_i3 < 3; c4_i3++) {
    c4_y[c4_i3] = c4_bv1[c4_i3];
  }

  sf_mex_destroy(&c4_u);
}

static const mxArray *c4_r_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_b_setSimStateSideEffectsInfo, const char_T *
   c4_identifier)
{
  const mxArray *c4_y = NULL;
  emlrtMsgIdentifier c4_thisId;
  c4_y = NULL;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  sf_mex_assign(&c4_y, c4_s_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_setSimStateSideEffectsInfo), &c4_thisId), false);
  sf_mex_destroy(&c4_b_setSimStateSideEffectsInfo);
  return c4_y;
}

static const mxArray *c4_s_emlrt_marshallIn
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  (void)c4_parentId;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_duplicatearraysafe(&c4_u), false);
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_updateDataWrittenToVector
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_vectorIndex)
{
  chartInstance->c4_dataWrittenToVector[(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK(0U,
    (int32_T)c4_vectorIndex, 0, 2, 1, 0)] = true;
}

static void c4_bus_wr_access_lightCalib_2
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, int32_T c4_u0, int32_T c4_u1, int32_T c4_u2, int32_T c4_u3)
{
  SFcnMemRegionInfo *c4_reg;
  c4_reg = (SFcnMemRegionInfo *)0U;
  ssMemRegionCreateDescriptor_wrapper(chartInstance->S, 2, &c4_reg);
  ssMemRegionSetFlatSubElement_wrapper(chartInstance->S, c4_reg, 0, c4_u0, 1,
    &c4_u1);
  ssMemRegionSetFlatSubElement_wrapper(chartInstance->S, c4_reg, 1, c4_u2, 1,
    &c4_u3);
  ssWriteToDataStoreRegion_wrapper(chartInstance->S, 1, 0, c4_reg);
  ssMemRegionDestroyDescriptor_wrapper(chartInstance->S, &c4_reg);
}

static c4_OperationModeStatusEnum c4_get_current_task_operation_status
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, NULL, c4_elementIndex);
  return *chartInstance->c4_current_task_operation_status_address;
}

static void c4_set_current_task_operation_status
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_elementIndex, c4_OperationModeStatusEnum
   c4_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, NULL, c4_elementIndex);
  *chartInstance->c4_current_task_operation_status_address = c4_elementValue;
}

static c4_OperationModeStatusEnum *c4_access_current_task_operation_status
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_rdOnly)
{
  c4_OperationModeStatusEnum *c4_dsmAddr;
  ssReadFromDataStore_wrapper(chartInstance->S, 0, NULL);
  c4_dsmAddr = chartInstance->c4_current_task_operation_status_address;
  if (c4_rdOnly == 0U) {
    ssWriteToDataStore_wrapper(chartInstance->S, 0, NULL);
  }

  return c4_dsmAddr;
}

static c4_Light_Bus c4_get_lightCalib
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 1, NULL, c4_elementIndex);
  return *chartInstance->c4_lightCalib_address;
}

static void c4_set_lightCalib
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_elementIndex, c4_Light_Bus c4_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 1, NULL, c4_elementIndex);
  *chartInstance->c4_lightCalib_address = c4_elementValue;
}

static c4_Light_Bus *c4_access_lightCalib
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c4_rdOnly)
{
  (void)c4_rdOnly;
  return chartInstance->c4_lightCalib_address;
}

static void init_dsm_address_info
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S,
    "current_task_operation_status", (void **)
    &chartInstance->c4_current_task_operation_status_address,
    &chartInstance->c4_current_task_operation_status_index);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "lightCalib", (void **)
    &chartInstance->c4_lightCalib_address, &chartInstance->c4_lightCalib_index);
}

static void init_simulink_io_address
  (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  chartInstance->c4_sensors = (c4_Sensors_Bus *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c4_PWM = (c4_PWM_bus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_initFlags = (c4_Init_Bus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
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

void
  sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_check_sum
  (mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4012105910U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(181854587U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3113137370U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2833901408U);
}

mxArray*
  sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_post_codegen_info
  (void);
mxArray
  *sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_autoinheritance_info
  (void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("WFjP8ch09GS51xh3ZdNnbB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxData);
  }

  {
    mxArray* mxPostCodegenInfo =
      sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_post_codegen_info
      ();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray
  *sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_third_party_uses_info
  (void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray
  *sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_jit_fallback_info
  (void)
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

mxArray
  *sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_updateBuildInfo_args_info
  (void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray*
  sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_post_codegen_info
  (void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString(
      "wwF4mPBKdj9c8i6ywpA9uC");
    mwSize exp_dims[2] = { 2, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);

    {
      mxArray* mxFcnName = mxCreateString("Speak");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 0, mxFcnName);
    }

    {
      mxArray* mxFcnName = mxCreateString("StatusLCD");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 1, mxFcnName);
    }

    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray
  *sf_get_sim_state_info_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[30],T\"PWM\",},{M[1],M[38],T\"initFlags\",},{M[3],M[39],T\"desired_tail\",},{M[8],M[0],T\"is_active_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library\",},{M[9],M[0],T\"is_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library\",},{M[9],M[1],T\"is_light_sensor_calibration_up\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"at\",M1x4[21 20 35 33],M[1]}}},{M[15],M[0],T\"dataWrittenToVector\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_get_check_sum
    (&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
      *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance =
      (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
       *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _light_sensor_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
           4,
           9,
           9,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation
          (_light_sensor_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
           chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _light_sensor_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _light_sensor_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
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
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_CH_SUBSTATE_COUNT(4);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,1);
          _SFD_CH_SUBSTATE_INDEX(2,2);
          _SFD_CH_SUBSTATE_INDEX(3,8);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,5);
          _SFD_ST_SUBSTATE_INDEX(2,0,3);
          _SFD_ST_SUBSTATE_INDEX(2,1,4);
          _SFD_ST_SUBSTATE_INDEX(2,2,5);
          _SFD_ST_SUBSTATE_INDEX(2,3,6);
          _SFD_ST_SUBSTATE_INDEX(2,4,7);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
        }

        _SFD_CV_INIT_CHART(4,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,5,1,1,0,0,NULL,NULL);
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

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(8,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(6,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(4,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(7,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(5,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(3,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(1,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(1,0,0,1,14,1,14);
        _SFD_CV_INIT_EML(3,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(3,0,0,0,14,0,14);
        _SFD_CV_INIT_EML(2,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(2,0,0,1,14,1,14);
        _SFD_CV_INIT_EML(4,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(4,0,0,0,14,0,14);
        _SFD_CV_INIT_EML(7,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(7,0,0,1,14,1,14);
        _SFD_CV_INIT_EML(5,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(5,0,0,0,12,0,12);
        _SFD_CV_INIT_EML(8,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(8,0,0,0,12,0,12);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sensors_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_lightCalib_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_h_sf_marshallOut,(MexInFcnForType)c4_g_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_PWM_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_initFlags_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)c4_c_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c4_sensors);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c4_lightCalib_address);
        _SFD_SET_DATA_VALUE_PTR(2U,
          chartInstance->c4_current_task_operation_status_address);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c4_PWM);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c4_initFlags);
        _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c4_desired_tail);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _light_sensor_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "9Jghf8ZT1ct66smKqOteo";
}

static void
  sf_opaque_initialize_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (void *chartInstanceVar)
{
  chart_debug_initialization
    (((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
      chartInstanceVar)->S,0);
  initialize_params_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
    ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
  initialize_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
    ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

static void
  sf_opaque_enable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (void *chartInstanceVar)
{
  enable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
    ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

static void
  sf_opaque_disable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (void *chartInstanceVar)
{
  disable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
    ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

static void
  sf_opaque_gateway_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (void *chartInstanceVar)
{
  sf_gateway_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
    ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

static const mxArray*
  sf_opaque_get_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return
    get_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
    ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
}

static void
  sf_opaque_set_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
    ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInfo->chartInstance, st);
}

static void
  sf_opaque_terminate_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S =
      ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
       chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_light_sensor_calibration_algorithm_atomic_sub_chart_library_optimization_info
        ();
    }

    finalize_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
       chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_light_sensor_calibration_algorithm_atomic_sub_chart_library
    ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void
  mdlProcessParameters_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *S)
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
    initialize_params_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      ((SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
       (chartInfo->chartInstance));
  }
}

static void
  mdlSetWorkWidths_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *S)
{
  ssSetModelReferenceSampleTimeDisallowInheritance(S);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct =
      load_light_sensor_calibration_algorithm_atomic_sub_chart_library_optimization_info
      ();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(856312758U));
  ssSetChecksum1(S,(3812187359U));
  ssSetChecksum2(S,(4119834533U));
  ssSetChecksum3(S,(3079828481U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,0);
}

static void
  mdlRTW_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void
  mdlStart_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *S)
{
  SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance =
    (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
     *)utMalloc(sizeof
                (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc4_light_sensor_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW =
    mdlRTW_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn =
    sf_exported_auto_userFcnGatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn =
    sf_exported_auto_autoFcnGatewayc4_light_sensor_calibration_algorithm_atomic_sub_chart_library;
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

void
  c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_method_dispatcher
  (SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_light_sensor_calibration_algorithm_atomic_sub_chart_library
      (S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_light_sensor_calibration_algorithm_atomic_sub_chart_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
