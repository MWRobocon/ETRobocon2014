/* Include files */

#include <stddef.h>
#include "blas.h"
#include "gyro_calibration_algorithm_atomic_sub_chart_library_sfun.h"
#include "c2_gyro_calibration_algorithm_atomic_sub_chart_library.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "gyro_calibration_algorithm_atomic_sub_chart_library_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c2_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c2_IN_gyro_calibration_mode    ((uint8_T)1U)
#define c2_IN_GyroCalibration          ((uint8_T)1U)
#define c2_IN_StartCalibration         ((uint8_T)2U)
#define c2_IN_CalibComplete            ((uint8_T)1U)
#define c2_IN_MakeNoise                ((uint8_T)2U)
#define c2_IN_MoveTailDown             ((uint8_T)3U)
#define c2_b_IN_StartCalibration       ((uint8_T)4U)
#define c2_IN_StartCalibration1        ((uint8_T)5U)
#define c2_IN_Wait                     ((uint8_T)6U)
#define c2_IN_Waiting                  ((uint8_T)7U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_b_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_d_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_e_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_f_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_g_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_h_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_i_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_j_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_k_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_l_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_m_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_n_debug_family_names[2] = { "nargin", "nargout" };

static const char * c2_o_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_p_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_q_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_r_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_s_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_t_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_u_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_v_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

static const char * c2_w_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

/* Function Declarations */
static void initialize_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  initialize_params_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void enable_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void disable_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void c2_update_debugger_state_c2_gyro_calibration_algorithm_atomic_su
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static const mxArray
  *get_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void set_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_st);
static void c2_set_sim_state_side_effects_c2_gyro_calibration_algorithm_atom
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void finalize_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void sf_gateway_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void mdl_start_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void c2_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static boolean_T isStablec2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void duringc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void enterc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void exitc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void gatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void enablec2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void disablec2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void initBuffersc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void stepBuffersc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void initc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void activate_callc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  deactivate_callc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  increment_call_counterc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  reset_call_counterc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void
  check_state_inconsistency_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void initSimStructsc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void c2_GyroCalibration
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static boolean_T c2_b_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real32_T c2_c_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_sf_internal_predicateOutput, const char_T
   *c2_identifier);
static real32_T c2_d_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_e_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_f_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_tp_gyro_calibration_mode, const char_T
   *c2_identifier);
static uint8_T c2_g_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static c2_OperationModeStatusEnum c2_h_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_sensors_bus_io(void *chartInstanceVoid, void *c2_pData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_initFlags_bus_io(void *chartInstanceVoid, void
  *c2_pData);
static const mxArray *c2_c_emlrt_marshallOut
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const c2_Init_Bus c2_u);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static c2_Init_Bus c2_i_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_initFlags, const char_T *c2_identifier);
static c2_Init_Bus c2_j_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_PWM_bus_io(void *chartInstanceVoid, void *c2_pData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static c2_PWM_bus c2_k_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_PWM, const char_T *c2_identifier);
static c2_PWM_bus c2_l_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint16_T c2_m_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_temporalCounter_i1, const char_T
   *c2_identifier);
static uint16_T c2_n_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_o_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_dataWrittenToVector, const char_T
   *c2_identifier, boolean_T c2_y[3]);
static void c2_p_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
   boolean_T c2_y[3]);
static const mxArray *c2_q_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_setSimStateSideEffectsInfo, const char_T *
   c2_identifier);
static const mxArray *c2_r_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_updateDataWrittenToVector
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_vectorIndex);
static void c2_errorIfDataNotWrittenToFcn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_vectorIndex, uint32_T c2_dataNumber, uint32_T
   c2_ssIdOfSourceObject, int32_T c2_offsetInSourceObject, int32_T
   c2_lengthInSourceObject);
static c2_OperationModeStatusEnum c2_get_current_task_operation_status
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_elementIndex);
static void c2_set_current_task_operation_status
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_elementIndex, c2_OperationModeStatusEnum
   c2_elementValue);
static c2_OperationModeStatusEnum *c2_access_current_task_operation_status
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_rdOnly);
static void init_dsm_address_info
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);
static void init_simulink_io_address
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance);

/* Function Definitions */
static void initialize_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  initialize_params_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void disable_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void c2_update_debugger_state_c2_gyro_calibration_algorithm_atomic_su
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c2_prevAniVal;
  c2_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c2_is_active_c2_gyro_calibration_algorithm_atomic_sub_chart_libr
      == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_c2_gyro_calibration_algorithm_atomic_sub_chart_library
      == c2_IN_gyro_calibration_mode) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_gyro_calibration_mode == c2_IN_GyroCalibration) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_GyroCalibration == c2_IN_Waiting) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_GyroCalibration == c2_IN_MoveTailDown) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_GyroCalibration == c2_b_IN_StartCalibration) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_GyroCalibration == c2_IN_Wait) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_GyroCalibration == c2_IN_MakeNoise) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_GyroCalibration == c2_IN_StartCalibration1) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_GyroCalibration == c2_IN_CalibComplete) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_gyro_calibration_mode == c2_IN_StartCalibration) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
  }

  _SFD_SET_ANIMATION(c2_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray
  *get_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  const mxArray *c2_b_y = NULL;
  real32_T c2_u;
  const mxArray *c2_c_y = NULL;
  real32_T c2_b_u;
  const mxArray *c2_d_y = NULL;
  real32_T c2_c_u;
  const mxArray *c2_e_y = NULL;
  c2_Init_Bus c2_r0;
  real32_T c2_hoistedGlobal;
  real32_T c2_d_u;
  const mxArray *c2_f_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_e_u;
  const mxArray *c2_g_y = NULL;
  uint8_T c2_c_hoistedGlobal;
  uint8_T c2_f_u;
  const mxArray *c2_h_y = NULL;
  uint8_T c2_d_hoistedGlobal;
  uint8_T c2_g_u;
  const mxArray *c2_i_y = NULL;
  uint8_T c2_e_hoistedGlobal;
  uint8_T c2_h_u;
  const mxArray *c2_j_y = NULL;
  uint16_T c2_f_hoistedGlobal;
  uint16_T c2_i_u;
  const mxArray *c2_k_y = NULL;
  int32_T c2_i0;
  boolean_T c2_j_u[3];
  const mxArray *c2_l_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(9, 1), false);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_u = *(real32_T *)&((char_T *)chartInstance->c2_PWM)[0];
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_b_y, c2_c_y, "left", "left", 0);
  c2_b_u = *(real32_T *)&((char_T *)chartInstance->c2_PWM)[4];
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_b_y, c2_d_y, "right", "right", 0);
  c2_c_u = *(real32_T *)&((char_T *)chartInstance->c2_PWM)[8];
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_b_y, c2_e_y, "tail", "tail", 0);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_r0.fall = *(boolean_T *)&((char_T *)chartInstance->c2_initFlags)[0];
  c2_r0.gyroInit = *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[4];
  c2_r0.gyroReset = *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[8];
  c2_r0.theta = *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[12];
  c2_r0.tail = *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[16];
  sf_mex_setcell(c2_y, 1, c2_c_emlrt_marshallOut(chartInstance, c2_r0));
  c2_hoistedGlobal = chartInstance->c2_desired_tail;
  c2_d_u = c2_hoistedGlobal;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 2, c2_f_y);
  c2_b_hoistedGlobal =
    chartInstance->c2_is_active_c2_gyro_calibration_algorithm_atomic_sub_chart_libr;
  c2_e_u = c2_b_hoistedGlobal;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 3, c2_g_y);
  c2_c_hoistedGlobal =
    chartInstance->c2_is_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  c2_f_u = c2_c_hoistedGlobal;
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 4, c2_h_y);
  c2_d_hoistedGlobal = chartInstance->c2_is_gyro_calibration_mode;
  c2_g_u = c2_d_hoistedGlobal;
  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", &c2_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 5, c2_i_y);
  c2_e_hoistedGlobal = chartInstance->c2_is_GyroCalibration;
  c2_h_u = c2_e_hoistedGlobal;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_h_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 6, c2_j_y);
  c2_f_hoistedGlobal = chartInstance->c2_temporalCounter_i1;
  c2_i_u = c2_f_hoistedGlobal;
  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", &c2_i_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 7, c2_k_y);
  for (c2_i0 = 0; c2_i0 < 3; c2_i0++) {
    c2_j_u[c2_i0] = chartInstance->c2_dataWrittenToVector[c2_i0];
  }

  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", c2_j_u, 11, 0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c2_y, 8, c2_l_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  c2_PWM_bus c2_r1;
  c2_Init_Bus c2_r2;
  boolean_T c2_bv0[3];
  int32_T c2_i1;
  c2_u = sf_mex_dup(c2_st);
  c2_r1 = c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
    "PWM");
  *(real32_T *)&((char_T *)chartInstance->c2_PWM)[0] = c2_r1.left;
  *(real32_T *)&((char_T *)chartInstance->c2_PWM)[4] = c2_r1.right;
  *(real32_T *)&((char_T *)chartInstance->c2_PWM)[8] = c2_r1.tail;
  c2_r2 = c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
    "initFlags");
  *(boolean_T *)&((char_T *)chartInstance->c2_initFlags)[0] = c2_r2.fall;
  *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[4] = c2_r2.gyroInit;
  *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[8] = c2_r2.gyroReset;
  *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[12] = c2_r2.theta;
  *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[16] = c2_r2.tail;
  chartInstance->c2_desired_tail = c2_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 2)), "desired_tail");
  chartInstance->c2_is_active_c2_gyro_calibration_algorithm_atomic_sub_chart_libr
    = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 3)),
    "is_active_c2_gyro_calibration_algorithm_atomic_sub_chart_library");
  chartInstance->c2_is_c2_gyro_calibration_algorithm_atomic_sub_chart_library =
    c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 4)),
    "is_c2_gyro_calibration_algorithm_atomic_sub_chart_library");
  chartInstance->c2_is_gyro_calibration_mode = c2_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 5)),
     "is_gyro_calibration_mode");
  chartInstance->c2_is_GyroCalibration = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 6)), "is_GyroCalibration");
  chartInstance->c2_temporalCounter_i1 = c2_m_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 7)), "temporalCounter_i1");
  c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 8)),
                        "dataWrittenToVector", c2_bv0);
  for (c2_i1 = 0; c2_i1 < 3; c2_i1++) {
    chartInstance->c2_dataWrittenToVector[c2_i1] = c2_bv0[c2_i1];
  }

  sf_mex_assign(&chartInstance->c2_setSimStateSideEffectsInfo,
                c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 9)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c2_u);
  chartInstance->c2_doSetSimStateSideEffects = 1U;
  c2_update_debugger_state_c2_gyro_calibration_algorithm_atomic_su(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void c2_set_sim_state_side_effects_c2_gyro_calibration_algorithm_atom
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  if (chartInstance->c2_doSetSimStateSideEffects != 0) {
    if (chartInstance->c2_is_c2_gyro_calibration_algorithm_atomic_sub_chart_library
        == c2_IN_gyro_calibration_mode) {
      chartInstance->c2_tp_gyro_calibration_mode = 1U;
    } else {
      chartInstance->c2_tp_gyro_calibration_mode = 0U;
    }

    if (chartInstance->c2_is_gyro_calibration_mode == c2_IN_GyroCalibration) {
      chartInstance->c2_tp_GyroCalibration = 1U;
    } else {
      chartInstance->c2_tp_GyroCalibration = 0U;
    }

    if (chartInstance->c2_is_GyroCalibration == c2_IN_CalibComplete) {
      chartInstance->c2_tp_CalibComplete = 1U;
    } else {
      chartInstance->c2_tp_CalibComplete = 0U;
    }

    if (chartInstance->c2_is_GyroCalibration == c2_IN_MakeNoise) {
      chartInstance->c2_tp_MakeNoise = 1U;
      if (sf_mex_sub(chartInstance->c2_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 5) == 0.0) {
        chartInstance->c2_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c2_tp_MakeNoise = 0U;
    }

    if (chartInstance->c2_is_GyroCalibration == c2_IN_MoveTailDown) {
      chartInstance->c2_tp_MoveTailDown = 1U;
    } else {
      chartInstance->c2_tp_MoveTailDown = 0U;
    }

    if (chartInstance->c2_is_GyroCalibration == c2_b_IN_StartCalibration) {
      chartInstance->c2_tp_StartCalibration = 1U;
    } else {
      chartInstance->c2_tp_StartCalibration = 0U;
    }

    if (chartInstance->c2_is_GyroCalibration == c2_IN_StartCalibration1) {
      chartInstance->c2_tp_StartCalibration1 = 1U;
    } else {
      chartInstance->c2_tp_StartCalibration1 = 0U;
    }

    if (chartInstance->c2_is_GyroCalibration == c2_IN_Wait) {
      chartInstance->c2_tp_Wait = 1U;
      if (sf_mex_sub(chartInstance->c2_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 9) == 0.0) {
        chartInstance->c2_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c2_tp_Wait = 0U;
    }

    if (chartInstance->c2_is_GyroCalibration == c2_IN_Waiting) {
      chartInstance->c2_tp_Waiting = 1U;
      if (sf_mex_sub(chartInstance->c2_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 10) == 0.0) {
        chartInstance->c2_temporalCounter_i1 = 0U;
      }
    } else {
      chartInstance->c2_tp_Waiting = 0U;
    }

    if (chartInstance->c2_is_gyro_calibration_mode == c2_IN_StartCalibration) {
      chartInstance->c2_b_tp_StartCalibration = 1U;
    } else {
      chartInstance->c2_b_tp_StartCalibration = 0U;
    }

    chartInstance->c2_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  sf_mex_destroy(&chartInstance->c2_setSimStateSideEffectsInfo);
}

static void sf_gateway_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  c2_set_sim_state_side_effects_c2_gyro_calibration_algorithm_atom(chartInstance);
}

static void mdl_start_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void c2_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c2_debug_family_var_map[3];
  real_T c2_nargin = 0.0;
  real_T c2_nargout = 1.0;
  boolean_T c2_out;
  uint32_T c2_b_debug_family_var_map[2];
  real_T c2_b_nargin = 0.0;
  real_T c2_b_nargout = 0.0;
  real_T c2_c_nargin = 0.0;
  real_T c2_c_nargout = 0.0;
  uint16_T c2_u0;
  void *c2_inputVarPtrs[1];
  int32_T c2_inputVarSizes[1];
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_isStable = true;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  switch (chartInstance->c2_is_gyro_calibration_mode) {
   case c2_IN_GyroCalibration:
    CV_STATE_EVAL(0, 0, 1);
    c2_GyroCalibration(chartInstance);
    break;

   case c2_IN_StartCalibration:
    CV_STATE_EVAL(0, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c2_q_debug_family_names,
      c2_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 0U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 1U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_out, 2U, c2_b_sf_marshallOut,
      c2_b_sf_marshallIn);
    c2_out = CV_EML_IF(6, 0, 0, *(real32_T *)&((char_T *)
      chartInstance->c2_sensors)[28] != 0.0F);
    _SFD_SYMBOL_SCOPE_POP();
    if (c2_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
      chartInstance->c2_b_tp_StartCalibration = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
      chartInstance->c2_isStable = false;
      chartInstance->c2_is_gyro_calibration_mode = c2_IN_GyroCalibration;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_GyroCalibration = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_debug_family_names,
        c2_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      chartInstance->c2_desired_tail = 0.0F;
      c2_updateDataWrittenToVector(chartInstance, 2U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c2_desired_tail, 4U);
      _SFD_SYMBOL_SCOPE_POP();
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
      chartInstance->c2_isStable = false;
      chartInstance->c2_is_GyroCalibration = c2_IN_MoveTailDown;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_MoveTailDown = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_d_debug_family_names,
        c2_b_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      c2_u0 = 100U;
      c2_inputVarPtrs[0U] = (void *)&c2_u0;
      c2_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c2_inputVarPtrs, (void *)c2_inputVarSizes, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U,
                   chartInstance->c2_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c2_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 0, 0);
    chartInstance->c2_is_gyro_calibration_mode = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static boolean_T isStablec2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  return chartInstance->c2_isStable;
}

static void duringc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  c2_c2_gyro_calibration_algorithm_atomic_sub_chart_library(chartInstance);
}

static void enterc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  chartInstance->c2_is_active_c2_gyro_calibration_algorithm_atomic_sub_chart_libr
    = 1U;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  chartInstance->c2_isStable = false;
  chartInstance->c2_is_c2_gyro_calibration_algorithm_atomic_sub_chart_library =
    c2_IN_gyro_calibration_mode;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
  chartInstance->c2_tp_gyro_calibration_mode = 1U;
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
  chartInstance->c2_isStable = false;
  chartInstance->c2_is_gyro_calibration_mode = c2_IN_StartCalibration;
  _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
  chartInstance->c2_b_tp_StartCalibration = 1U;
}

static void exitc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c2_debug_family_var_map[2];
  real_T c2_nargin = 0.0;
  real_T c2_nargout = 0.0;
  real32_T c2_hoistedGlobal;
  real32_T c2_b_hoistedGlobal;
  real32_T c2_c_hoistedGlobal;
  void *c2_inputVarPtrs[2];
  int32_T c2_inputVarSizes[2];
  real32_T c2_f0;
  void *c2_outputVarPtrs[1];
  int32_T c2_outputVarSizes[1];
  _sfTime_ = sf_get_time(chartInstance->S);
  switch (chartInstance->c2_is_gyro_calibration_mode) {
   case c2_IN_GyroCalibration:
    CV_STATE_EVAL(0, 1, 1);
    switch (chartInstance->c2_is_GyroCalibration) {
     case c2_IN_CalibComplete:
      CV_STATE_EVAL(1, 1, 1);
      chartInstance->c2_tp_CalibComplete = 0U;
      chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
      break;

     case c2_IN_MakeNoise:
      CV_STATE_EVAL(1, 1, 2);
      chartInstance->c2_tp_MakeNoise = 0U;
      chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
      break;

     case c2_IN_MoveTailDown:
      CV_STATE_EVAL(1, 1, 3);
      chartInstance->c2_tp_MoveTailDown = 0U;
      chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
      break;

     case c2_b_IN_StartCalibration:
      CV_STATE_EVAL(1, 1, 4);
      chartInstance->c2_tp_StartCalibration = 0U;
      chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
      break;

     case c2_IN_StartCalibration1:
      CV_STATE_EVAL(1, 1, 5);
      chartInstance->c2_tp_StartCalibration1 = 0U;
      chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
      break;

     case c2_IN_Wait:
      CV_STATE_EVAL(1, 1, 6);
      chartInstance->c2_tp_Wait = 0U;
      chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
      break;

     case c2_IN_Waiting:
      CV_STATE_EVAL(1, 1, 7);
      chartInstance->c2_tp_Waiting = 0U;
      chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
      break;

     default:
      CV_STATE_EVAL(1, 1, 0);
      chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
      break;
    }

    chartInstance->c2_tp_GyroCalibration = 0U;
    _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_c_debug_family_names,
      c2_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 0U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 1U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    c2_errorIfDataNotWrittenToFcn(chartInstance, 2U, 4U, 21U, 106, 12);
    c2_hoistedGlobal = chartInstance->c2_desired_tail;
    c2_b_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c2_sensors)[8];
    c2_c_hoistedGlobal = c2_hoistedGlobal;
    c2_inputVarPtrs[0U] = (void *)&c2_b_hoistedGlobal;
    c2_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
    c2_inputVarPtrs[1U] = (void *)&c2_c_hoistedGlobal;
    c2_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
    c2_outputVarPtrs[0U] = (void *)&c2_f0;
    c2_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
    sfcs_request_service(chartInstance->S, "tail_controller", 2, (void *)
                         c2_inputVarPtrs, (void *)c2_inputVarSizes, 1, (void *)
                         c2_outputVarPtrs, (void *)c2_outputVarSizes);
    *(real32_T *)&((char_T *)chartInstance->c2_PWM)[8] = c2_f0;
    c2_updateDataWrittenToVector(chartInstance, 1U);
    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    chartInstance->c2_is_gyro_calibration_mode = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
    break;

   case c2_IN_StartCalibration:
    CV_STATE_EVAL(0, 1, 2);
    chartInstance->c2_b_tp_StartCalibration = 0U;
    chartInstance->c2_is_gyro_calibration_mode = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 1, 0);
    chartInstance->c2_is_gyro_calibration_mode = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
    break;
  }

  chartInstance->c2_tp_gyro_calibration_mode = 0U;
  chartInstance->c2_is_c2_gyro_calibration_algorithm_atomic_sub_chart_library =
    c2_IN_NO_ACTIVE_CHILD;
  _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
}

static void gatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c2_temporalCounter_i1 < 2047U) {
    chartInstance->c2_temporalCounter_i1++;
  }
}

static void enablec2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disablec2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
  if (chartInstance->c2_temporalCounter_i1 < 2047U) {
    chartInstance->c2_temporalCounter_i1++;
  }
}

static void initBuffersc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void stepBuffersc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void initc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_doSetSimStateSideEffects = 0U;
  chartInstance->c2_setSimStateSideEffectsInfo = NULL;
  chartInstance->c2_is_gyro_calibration_mode = c2_IN_NO_ACTIVE_CHILD;
  chartInstance->c2_tp_gyro_calibration_mode = 0U;
  chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
  chartInstance->c2_tp_GyroCalibration = 0U;
  chartInstance->c2_tp_CalibComplete = 0U;
  chartInstance->c2_tp_MakeNoise = 0U;
  chartInstance->c2_temporalCounter_i1 = 0U;
  chartInstance->c2_tp_MoveTailDown = 0U;
  chartInstance->c2_tp_StartCalibration = 0U;
  chartInstance->c2_tp_StartCalibration1 = 0U;
  chartInstance->c2_tp_Wait = 0U;
  chartInstance->c2_temporalCounter_i1 = 0U;
  chartInstance->c2_tp_Waiting = 0U;
  chartInstance->c2_temporalCounter_i1 = 0U;
  chartInstance->c2_b_tp_StartCalibration = 0U;
  chartInstance->c2_is_active_c2_gyro_calibration_algorithm_atomic_sub_chart_libr
    = 0U;
  chartInstance->c2_is_c2_gyro_calibration_algorithm_atomic_sub_chart_library =
    c2_IN_NO_ACTIVE_CHILD;
}

static void activate_callc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
}

static void
  deactivate_callc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  increment_call_counterc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  reset_call_counterc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void
  check_state_inconsistency_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  _SFD_CHECK_FOR_STATE_INCONSISTENCY
    (_gyro_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
     chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  (void)chartInstance;
}

static void c2_GyroCalibration
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  uint32_T c2_debug_family_var_map[2];
  real_T c2_nargin = 0.0;
  real_T c2_nargout = 0.0;
  real32_T c2_hoistedGlobal;
  real32_T c2_b_hoistedGlobal;
  real32_T c2_c_hoistedGlobal;
  void *c2_inputVarPtrs[2];
  int32_T c2_inputVarSizes[2];
  real32_T c2_f1;
  void *c2_outputVarPtrs[1];
  int32_T c2_outputVarSizes[1];
  uint32_T c2_b_debug_family_var_map[3];
  real_T c2_b_nargin = 0.0;
  real_T c2_b_nargout = 1.0;
  boolean_T c2_out;
  real_T c2_c_nargin = 0.0;
  real_T c2_c_nargout = 0.0;
  uint16_T c2_u1;
  void *c2_b_inputVarPtrs[1];
  int32_T c2_b_inputVarSizes[1];
  real_T c2_d_nargin = 0.0;
  real_T c2_d_nargout = 0.0;
  real_T c2_e_nargin = 0.0;
  real_T c2_e_nargout = 1.0;
  boolean_T c2_b_out;
  real_T c2_f_nargin = 0.0;
  real_T c2_f_nargout = 0.0;
  uint16_T c2_u2;
  real_T c2_g_nargin = 0.0;
  real_T c2_g_nargout = 0.0;
  real_T c2_h_nargin = 0.0;
  real_T c2_h_nargout = 1.0;
  boolean_T c2_c_out;
  real_T c2_i_nargin = 0.0;
  real_T c2_i_nargout = 0.0;
  real_T c2_j_nargin = 0.0;
  real_T c2_j_nargout = 0.0;
  real_T c2_k_nargin = 0.0;
  real_T c2_k_nargout = 0.0;
  uint16_T c2_u3;
  real_T c2_l_nargin = 0.0;
  real_T c2_l_nargout = 1.0;
  boolean_T c2_d_out;
  real_T c2_m_nargin = 0.0;
  real_T c2_m_nargout = 1.0;
  boolean_T c2_e_out;
  real_T c2_n_nargin = 0.0;
  real_T c2_n_nargout = 0.0;
  uint16_T c2_u4;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  c2_errorIfDataNotWrittenToFcn(chartInstance, 2U, 4U, 21U, 106, 12);
  c2_hoistedGlobal = chartInstance->c2_desired_tail;
  c2_b_hoistedGlobal = *(real32_T *)&((char_T *)chartInstance->c2_sensors)[8];
  c2_c_hoistedGlobal = c2_hoistedGlobal;
  c2_inputVarPtrs[0U] = (void *)&c2_b_hoistedGlobal;
  c2_inputVarSizes[0U] = (int32_T)sizeof(real32_T);
  c2_inputVarPtrs[1U] = (void *)&c2_c_hoistedGlobal;
  c2_inputVarSizes[1U] = (int32_T)sizeof(real32_T);
  c2_outputVarPtrs[0U] = (void *)&c2_f1;
  c2_outputVarSizes[0U] = (int32_T)sizeof(real32_T);
  sfcs_request_service(chartInstance->S, "tail_controller", 2, (void *)
                       c2_inputVarPtrs, (void *)c2_inputVarSizes, 1, (void *)
                       c2_outputVarPtrs, (void *)c2_outputVarSizes);
  *(real32_T *)&((char_T *)chartInstance->c2_PWM)[8] = c2_f1;
  c2_updateDataWrittenToVector(chartInstance, 1U);
  _SFD_SYMBOL_SCOPE_POP();
  switch (chartInstance->c2_is_GyroCalibration) {
   case c2_IN_CalibComplete:
    CV_STATE_EVAL(1, 0, 1);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U, chartInstance->c2_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c2_sfEvent);
    break;

   case c2_IN_MakeNoise:
    CV_STATE_EVAL(1, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c2_p_debug_family_names,
      c2_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 0U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 1U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_out, 2U, c2_b_sf_marshallOut,
      c2_b_sf_marshallIn);
    c2_out = CV_EML_IF(3, 0, 0, chartInstance->c2_temporalCounter_i1 >= 125);
    _SFD_SYMBOL_SCOPE_POP();
    if (c2_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_MakeNoise = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
      chartInstance->c2_isStable = false;
      chartInstance->c2_is_GyroCalibration = c2_IN_StartCalibration1;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_StartCalibration1 = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_i_debug_family_names,
        c2_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      c2_u1 = 102U;
      c2_b_inputVarPtrs[0U] = (void *)&c2_u1;
      c2_b_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c2_b_inputVarPtrs, (void *)c2_b_inputVarSizes, 0,
                           NULL, NULL);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[4] = 0.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[8] = 0.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[12] = 0.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                   chartInstance->c2_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_h_debug_family_names,
        c2_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c2_sfEvent);
    break;

   case c2_IN_MoveTailDown:
    CV_STATE_EVAL(1, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c2_l_debug_family_names,
      c2_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_e_nargin, 0U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_e_nargout, 1U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_out, 2U, c2_b_sf_marshallOut,
      c2_b_sf_marshallIn);
    c2_errorIfDataNotWrittenToFcn(chartInstance, 2U, 4U, 20U, 1, 12);
    c2_b_out = CV_EML_IF(0, 0, 0, CV_RELATIONAL_EVAL(5U, 0U, 0, (real_T)
      chartInstance->c2_desired_tail, 1.75, -3, 5U,
      chartInstance->c2_desired_tail >= 1.75F));
    _SFD_SYMBOL_SCOPE_POP();
    if (c2_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_MoveTailDown = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
      chartInstance->c2_isStable = false;
      chartInstance->c2_is_GyroCalibration = c2_b_IN_StartCalibration;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_StartCalibration = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_f_debug_family_names,
        c2_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_f_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_f_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      c2_u2 = 101U;
      c2_b_inputVarPtrs[0U] = (void *)&c2_u2;
      c2_b_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c2_b_inputVarPtrs, (void *)c2_b_inputVarSizes, 0,
                           NULL, NULL);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[4] = 1.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[8] = 1.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[12] = 1.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                   chartInstance->c2_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_e_debug_family_names,
        c2_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_g_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_g_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      c2_errorIfDataNotWrittenToFcn(chartInstance, 2U, 4U, 18U, 67, 12);
      chartInstance->c2_desired_tail += 0.008F;
      c2_updateDataWrittenToVector(chartInstance, 2U);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c2_desired_tail, 4U);
      _SFD_SYMBOL_SCOPE_POP();
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c2_sfEvent);
    break;

   case c2_b_IN_StartCalibration:
    CV_STATE_EVAL(1, 0, 4);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c2_m_debug_family_names,
      c2_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_h_nargin, 0U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_h_nargout, 1U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_out, 2U, c2_b_sf_marshallOut,
      c2_b_sf_marshallIn);
    c2_c_out = CV_EML_IF(2, 0, 0, *(real32_T *)&((char_T *)
      chartInstance->c2_sensors)[28] != 0.0F);
    _SFD_SYMBOL_SCOPE_POP();
    if (c2_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_n_debug_family_names,
        c2_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
      chartInstance->c2_tp_StartCalibration = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
      chartInstance->c2_isStable = false;
      chartInstance->c2_is_GyroCalibration = c2_IN_Wait;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
      chartInstance->c2_temporalCounter_i1 = 0U;
      chartInstance->c2_tp_Wait = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_g_debug_family_names,
        c2_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_j_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_j_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      sfcs_request_service(chartInstance->S, "Speak", 0, NULL, NULL, 0, NULL,
                           NULL);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U,
                   chartInstance->c2_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c2_sfEvent);
    break;

   case c2_IN_StartCalibration1:
    CV_STATE_EVAL(1, 0, 5);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
    chartInstance->c2_tp_StartCalibration1 = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
    chartInstance->c2_isStable = false;
    chartInstance->c2_is_GyroCalibration = c2_IN_CalibComplete;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
    chartInstance->c2_tp_CalibComplete = 1U;
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_j_debug_family_names,
      c2_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_k_nargin, 0U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_k_nargout, 1U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    c2_u3 = 103U;
    c2_b_inputVarPtrs[0U] = (void *)&c2_u3;
    c2_b_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
    sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                         c2_b_inputVarPtrs, (void *)c2_b_inputVarSizes, 0, NULL,
                         NULL);
    c2_set_current_task_operation_status(chartInstance, 0,
      OperationModeStatusEnum_SUCCESSFULLY_COMPLETED);
    ssUpdateDataStoreLog(chartInstance->S, 0);
    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c2_sfEvent);
    break;

   case c2_IN_Wait:
    CV_STATE_EVAL(1, 0, 6);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c2_o_debug_family_names,
      c2_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_l_nargin, 0U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_l_nargout, 1U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_out, 2U, c2_b_sf_marshallOut,
      c2_b_sf_marshallIn);
    c2_d_out = CV_EML_IF(1, 0, 0, chartInstance->c2_temporalCounter_i1 >= 1250);
    _SFD_SYMBOL_SCOPE_POP();
    if (c2_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_Wait = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
      chartInstance->c2_isStable = false;
      chartInstance->c2_is_GyroCalibration = c2_IN_MakeNoise;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
      chartInstance->c2_temporalCounter_i1 = 0U;
      chartInstance->c2_tp_MakeNoise = 1U;
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                   chartInstance->c2_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c2_sfEvent);
    break;

   case c2_IN_Waiting:
    CV_STATE_EVAL(1, 0, 7);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c2_k_debug_family_names,
      c2_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_m_nargin, 0U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_m_nargout, 1U, c2_sf_marshallOut,
      c2_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_e_out, 2U, c2_b_sf_marshallOut,
      c2_b_sf_marshallIn);
    c2_e_out = CV_EML_IF(5, 0, 0, chartInstance->c2_temporalCounter_i1 >= 250);
    _SFD_SYMBOL_SCOPE_POP();
    if (c2_e_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_Waiting = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
      chartInstance->c2_isStable = false;
      chartInstance->c2_is_GyroCalibration = c2_b_IN_StartCalibration;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
      chartInstance->c2_tp_StartCalibration = 1U;
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c2_f_debug_family_names,
        c2_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_n_nargin, 0U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_n_nargout, 1U, c2_sf_marshallOut,
        c2_sf_marshallIn);
      c2_u4 = 101U;
      c2_b_inputVarPtrs[0U] = (void *)&c2_u4;
      c2_b_inputVarSizes[0U] = (int32_T)sizeof(uint16_T);
      sfcs_request_service(chartInstance->S, "StatusLCD", 1, (void *)
                           c2_b_inputVarPtrs, (void *)c2_b_inputVarSizes, 0,
                           NULL, NULL);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[4] = 1.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[8] = 1.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      *(real32_T *)&((char_T *)chartInstance->c2_initFlags)[12] = 1.0F;
      c2_updateDataWrittenToVector(chartInstance, 0U);
      _SFD_SYMBOL_SCOPE_POP();
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                   chartInstance->c2_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c2_sfEvent);
    break;

   default:
    CV_STATE_EVAL(1, 0, 0);
    chartInstance->c2_is_GyroCalibration = c2_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  boolean_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(boolean_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static boolean_T c2_b_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  boolean_T c2_y;
  boolean_T c2_b0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b0, 1, 11, 0U, 0, 0U, 0);
  c2_y = c2_b0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_sf_internal_predicateOutput;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  boolean_T c2_y;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_sf_internal_predicateOutput = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_sf_internal_predicateOutput), &c2_thisId);
  sf_mex_destroy(&c2_sf_internal_predicateOutput);
  *(boolean_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real32_T c2_c_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_sf_internal_predicateOutput, const char_T
   *c2_identifier)
{
  real32_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_sf_internal_predicateOutput), &c2_thisId);
  sf_mex_destroy(&c2_sf_internal_predicateOutput);
  return c2_y;
}

static real32_T c2_d_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real32_T c2_y;
  real32_T c2_f2;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_f2, 1, 1, 0U, 0, 0U, 0);
  c2_y = c2_f2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_sf_internal_predicateOutput;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real32_T c2_y;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_sf_internal_predicateOutput = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_sf_internal_predicateOutput), &c2_thisId);
  sf_mex_destroy(&c2_sf_internal_predicateOutput);
  *(real32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray
  *sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_eml_resolved_functions_info
  (void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 1, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("OperationModeStatusEnum"),
                  "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[N]C:/ETRobocon2014/Repository/data_types/enumerations/OperationModeStatusEnum.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1409161942U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_u)), false);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 7, 0U, 0U, 0U, 0), false);
  return c2_y;
}

void
  sf_exported_auto_userFcnGatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *c2_S, int32_T c2_ssidNumber, void *c2_ioVarPtrs)
{
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  (void)c2_ssidNumber;
  (void)c2_ioVarPtrs;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    ((ChartInfoStruct *)((ChartRunTimeInfo *)ssGetUserData(c2_S))->instanceInfo
    )->chartInstance;
}

void
  sf_exported_auto_autoFcnGatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *c2_S, int32_T c2_fcnNumber, void *c2_ioVarPtrs)
{
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    ((ChartInfoStruct *)((ChartRunTimeInfo *)ssGetUserData(c2_S))->instanceInfo
    )->chartInstance;
  if (c2_fcnNumber == -1) {
  } else if (c2_fcnNumber == 61) {
    *(boolean_T *)(*(void *(*)[1])c2_ioVarPtrs)[0] =
      isStablec2_gyro_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c2_fcnNumber == 62) {
    duringc2_gyro_calibration_algorithm_atomic_sub_chart_library(chartInstance);
  } else if (c2_fcnNumber == 63) {
    enterc2_gyro_calibration_algorithm_atomic_sub_chart_library(chartInstance);
  } else if (c2_fcnNumber == 64) {
    exitc2_gyro_calibration_algorithm_atomic_sub_chart_library(chartInstance);
  } else if (c2_fcnNumber == 65) {
    gatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library(chartInstance);
  } else if (c2_fcnNumber == 66) {
    enablec2_gyro_calibration_algorithm_atomic_sub_chart_library(chartInstance);
  } else if (c2_fcnNumber == 67) {
    disablec2_gyro_calibration_algorithm_atomic_sub_chart_library(chartInstance);
  } else if (c2_fcnNumber == 68) {
    initBuffersc2_gyro_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c2_fcnNumber == 69) {
    stepBuffersc2_gyro_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c2_fcnNumber == 70) {
    initSimStructsc2_gyro_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c2_fcnNumber == 71) {
    initc2_gyro_calibration_algorithm_atomic_sub_chart_library(chartInstance);
  } else if (c2_fcnNumber == 72) {
    activate_callc2_gyro_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c2_fcnNumber == 73) {
    deactivate_callc2_gyro_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c2_fcnNumber == 74) {
    increment_call_counterc2_gyro_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else if (c2_fcnNumber == 75) {
    reset_call_counterc2_gyro_calibration_algorithm_atomic_sub_chart_library
      (chartInstance);
  } else {
    if (c2_fcnNumber == 76) {
      check_state_inconsistency_c2_gyro_calibration_algorithm_atomic_sub_chart_library
        (chartInstance);
    }
  }
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_e_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i2;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i2, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static uint8_T c2_f_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_tp_gyro_calibration_mode, const char_T
   *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_tp_gyro_calibration_mode), &c2_thisId);
  sf_mex_destroy(&c2_b_tp_gyro_calibration_mode);
  return c2_y;
}

static uint8_T c2_g_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u5;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u5, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u5;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_tp_gyro_calibration_mode;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_b_tp_gyro_calibration_mode = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_tp_gyro_calibration_mode), &c2_thisId);
  sf_mex_destroy(&c2_b_tp_gyro_calibration_mode);
  *(uint8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  c2_OperationModeStatusEnum c2_u;
  const mxArray *c2_y = NULL;
  static const int32_T c2_enumValues[4] = { 0, 1, 2, 3 };

  static const char * c2_enumNames[4] = { "NOT_STARTED", "IN_PROGRESS",
    "SUCCESSFULLY_COMPLETED", "ABORTED" };

  int32_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  const mxArray *c2_m0 = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(c2_OperationModeStatusEnum *)c2_inData;
  c2_y = NULL;
  sf_mex_check_enum("OperationModeStatusEnum", 4, c2_enumNames, c2_enumValues);
  c2_b_u = (int32_T)c2_u;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_m0, c2_b_y, false);
  sf_mex_assign(&c2_y, sf_mex_create_enum("OperationModeStatusEnum", c2_m0),
                false);
  sf_mex_destroy(&c2_m0);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static c2_OperationModeStatusEnum c2_h_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  c2_OperationModeStatusEnum c2_y;
  static const int32_T c2_enumValues[4] = { 0, 1, 2, 3 };

  static const char * c2_enumNames[4] = { "NOT_STARTED", "IN_PROGRESS",
    "SUCCESSFULLY_COMPLETED", "ABORTED" };

  (void)chartInstance;
  sf_mex_check_enum("OperationModeStatusEnum", 4, c2_enumNames, c2_enumValues);
  sf_mex_check_builtin(c2_parentId, c2_u, "OperationModeStatusEnum", 0, 0U, NULL);
  c2_y = (c2_OperationModeStatusEnum)sf_mex_get_enum_element(c2_u, 0);
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_current_task_operation_status;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_OperationModeStatusEnum c2_y;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_current_task_operation_status = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_current_task_operation_status), &c2_thisId);
  sf_mex_destroy(&c2_current_task_operation_status);
  *(c2_OperationModeStatusEnum *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_sensors_bus_io(void *chartInstanceVoid, void *c2_pData)
{
  const mxArray *c2_mxVal = NULL;
  c2_Sensors_Bus c2_tmp;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxVal = NULL;
  c2_tmp.theta_L = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[0];
  c2_tmp.theta_R = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[4];
  c2_tmp.theta_T = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[8];
  c2_tmp.light = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[12];
  c2_tmp.gyro = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[16];
  c2_tmp.sonar = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[20];
  c2_tmp.battery = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[24];
  c2_tmp.touch = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[28];
  c2_tmp.time = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[32];
  c2_tmp.ok_button = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[36];
  c2_tmp.BT_status_in = *(real32_T *)&((char_T *)(c2_Sensors_Bus *)c2_pData)[40];
  sf_mex_assign(&c2_mxVal, c2_g_sf_marshallOut(chartInstance, &c2_tmp), false);
  return c2_mxVal;
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  c2_Sensors_Bus c2_u;
  const mxArray *c2_y = NULL;
  real32_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  real32_T c2_c_u;
  const mxArray *c2_c_y = NULL;
  real32_T c2_d_u;
  const mxArray *c2_d_y = NULL;
  real32_T c2_e_u;
  const mxArray *c2_e_y = NULL;
  real32_T c2_f_u;
  const mxArray *c2_f_y = NULL;
  real32_T c2_g_u;
  const mxArray *c2_g_y = NULL;
  real32_T c2_h_u;
  const mxArray *c2_h_y = NULL;
  real32_T c2_i_u;
  const mxArray *c2_i_y = NULL;
  real32_T c2_j_u;
  const mxArray *c2_j_y = NULL;
  real32_T c2_k_u;
  const mxArray *c2_k_y = NULL;
  real32_T c2_l_u;
  const mxArray *c2_l_y = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(c2_Sensors_Bus *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_b_u = c2_u.theta_L;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_b_y, "theta_L", "theta_L", 0);
  c2_c_u = c2_u.theta_R;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_c_y, "theta_R", "theta_R", 0);
  c2_d_u = c2_u.theta_T;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_d_y, "theta_T", "theta_T", 0);
  c2_e_u = c2_u.light;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_e_y, "light", "light", 0);
  c2_f_u = c2_u.gyro;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_f_y, "gyro", "gyro", 0);
  c2_g_u = c2_u.sonar;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_g_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_g_y, "sonar", "sonar", 0);
  c2_h_u = c2_u.battery;
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_h_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_h_y, "battery", "battery", 0);
  c2_i_u = c2_u.touch;
  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", &c2_i_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_i_y, "touch", "touch", 0);
  c2_j_u = c2_u.time;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_j_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_j_y, "time", "time", 0);
  c2_k_u = c2_u.ok_button;
  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", &c2_k_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_k_y, "ok_button", "ok_button", 0);
  c2_l_u = c2_u.BT_status_in;
  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", &c2_l_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_l_y, "BT_status_in", "BT_status_in", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static const mxArray *c2_initFlags_bus_io(void *chartInstanceVoid, void
  *c2_pData)
{
  const mxArray *c2_mxVal = NULL;
  c2_Init_Bus c2_tmp;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxVal = NULL;
  c2_tmp.fall = *(boolean_T *)&((char_T *)(c2_Init_Bus *)c2_pData)[0];
  c2_tmp.gyroInit = *(real32_T *)&((char_T *)(c2_Init_Bus *)c2_pData)[4];
  c2_tmp.gyroReset = *(real32_T *)&((char_T *)(c2_Init_Bus *)c2_pData)[8];
  c2_tmp.theta = *(real32_T *)&((char_T *)(c2_Init_Bus *)c2_pData)[12];
  c2_tmp.tail = *(real32_T *)&((char_T *)(c2_Init_Bus *)c2_pData)[16];
  sf_mex_assign(&c2_mxVal, c2_h_sf_marshallOut(chartInstance, &c2_tmp), false);
  return c2_mxVal;
}

static const mxArray *c2_c_emlrt_marshallOut
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const c2_Init_Bus c2_u)
{
  const mxArray *c2_y = NULL;
  boolean_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  real32_T c2_c_u;
  const mxArray *c2_c_y = NULL;
  real32_T c2_d_u;
  const mxArray *c2_d_y = NULL;
  real32_T c2_e_u;
  const mxArray *c2_e_y = NULL;
  real32_T c2_f_u;
  const mxArray *c2_f_y = NULL;
  (void)chartInstance;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_b_u = c2_u.fall;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_b_y, "fall", "fall", 0);
  c2_c_u = c2_u.gyroInit;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_c_y, "gyroInit", "gyroInit", 0);
  c2_d_u = c2_u.gyroReset;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_d_y, "gyroReset", "gyroReset", 0);
  c2_e_u = c2_u.theta;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_e_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_e_y, "theta", "theta", 0);
  c2_f_u = c2_u.tail;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_f_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_f_y, "tail", "tail", 0);
  return c2_y;
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  sf_mex_assign(&c2_mxArrayOutData, c2_c_emlrt_marshallOut(chartInstance,
    *(c2_Init_Bus *)c2_inData), false);
  return c2_mxArrayOutData;
}

static c2_Init_Bus c2_i_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_initFlags, const char_T *c2_identifier)
{
  c2_Init_Bus c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_initFlags),
    &c2_thisId);
  sf_mex_destroy(&c2_b_initFlags);
  return c2_y;
}

static c2_Init_Bus c2_j_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  c2_Init_Bus c2_y;
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[5] = { "fall", "gyroInit", "gyroReset",
    "theta", "tail" };

  c2_thisId.fParent = c2_parentId;
  sf_mex_check_struct(c2_parentId, c2_u, 5, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "fall";
  c2_y.fall = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "fall", "fall", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "gyroInit";
  c2_y.gyroInit = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_u, "gyroInit", "gyroInit", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "gyroReset";
  c2_y.gyroReset = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c2_u, "gyroReset", "gyroReset", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "theta";
  c2_y.theta = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "theta", "theta", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "tail";
  c2_y.tail = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "tail", "tail", 0)), &c2_thisId);
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_initFlags;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_Init_Bus c2_y;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_b_initFlags = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_initFlags),
    &c2_thisId);
  sf_mex_destroy(&c2_b_initFlags);
  *(c2_Init_Bus *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_PWM_bus_io(void *chartInstanceVoid, void *c2_pData)
{
  const mxArray *c2_mxVal = NULL;
  c2_PWM_bus c2_tmp;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxVal = NULL;
  c2_tmp.left = *(real32_T *)&((char_T *)(c2_PWM_bus *)c2_pData)[0];
  c2_tmp.right = *(real32_T *)&((char_T *)(c2_PWM_bus *)c2_pData)[4];
  c2_tmp.tail = *(real32_T *)&((char_T *)(c2_PWM_bus *)c2_pData)[8];
  sf_mex_assign(&c2_mxVal, c2_i_sf_marshallOut(chartInstance, &c2_tmp), false);
  return c2_mxVal;
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  c2_PWM_bus c2_u;
  const mxArray *c2_y = NULL;
  real32_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  real32_T c2_c_u;
  const mxArray *c2_c_y = NULL;
  real32_T c2_d_u;
  const mxArray *c2_d_y = NULL;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(c2_PWM_bus *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  c2_b_u = c2_u.left;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_b_y, "left", "left", 0);
  c2_c_u = c2_u.right;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_c_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_c_y, "right", "right", 0);
  c2_d_u = c2_u.tail;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_d_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c2_y, c2_d_y, "tail", "tail", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static c2_PWM_bus c2_k_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_PWM, const char_T *c2_identifier)
{
  c2_PWM_bus c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_PWM), &c2_thisId);
  sf_mex_destroy(&c2_b_PWM);
  return c2_y;
}

static c2_PWM_bus c2_l_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  c2_PWM_bus c2_y;
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[3] = { "left", "right", "tail" };

  c2_thisId.fParent = c2_parentId;
  sf_mex_check_struct(c2_parentId, c2_u, 3, c2_fieldNames, 0U, NULL);
  c2_thisId.fIdentifier = "left";
  c2_y.left = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "left", "left", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "right";
  c2_y.right = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "right", "right", 0)), &c2_thisId);
  c2_thisId.fIdentifier = "tail";
  c2_y.tail = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c2_u, "tail", "tail", 0)), &c2_thisId);
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_PWM;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_PWM_bus c2_y;
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    chartInstanceVoid;
  c2_b_PWM = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_PWM), &c2_thisId);
  sf_mex_destroy(&c2_b_PWM);
  *(c2_PWM_bus *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint16_T c2_m_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_temporalCounter_i1, const char_T
   *c2_identifier)
{
  uint16_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_temporalCounter_i1),
    &c2_thisId);
  sf_mex_destroy(&c2_b_temporalCounter_i1);
  return c2_y;
}

static uint16_T c2_n_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint16_T c2_y;
  uint16_T c2_u6;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u6, 1, 5, 0U, 0, 0U, 0);
  c2_y = c2_u6;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_o_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_dataWrittenToVector, const char_T
   *c2_identifier, boolean_T c2_y[3])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_dataWrittenToVector),
                        &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_dataWrittenToVector);
}

static void c2_p_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
   boolean_T c2_y[3])
{
  boolean_T c2_bv1[3];
  int32_T c2_i3;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_bv1, 1, 11, 0U, 1, 0U, 1, 3);
  for (c2_i3 = 0; c2_i3 < 3; c2_i3++) {
    c2_y[c2_i3] = c2_bv1[c2_i3];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_q_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_b_setSimStateSideEffectsInfo, const char_T *
   c2_identifier)
{
  const mxArray *c2_y = NULL;
  emlrtMsgIdentifier c2_thisId;
  c2_y = NULL;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  sf_mex_assign(&c2_y, c2_r_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_setSimStateSideEffectsInfo), &c2_thisId), false);
  sf_mex_destroy(&c2_b_setSimStateSideEffectsInfo);
  return c2_y;
}

static const mxArray *c2_r_emlrt_marshallIn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  (void)c2_parentId;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u), false);
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_updateDataWrittenToVector
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_vectorIndex)
{
  chartInstance->c2_dataWrittenToVector[(uint32_T)_SFD_EML_ARRAY_BOUNDS_CHECK(0U,
    (int32_T)c2_vectorIndex, 0, 2, 1, 0)] = true;
}

static void c2_errorIfDataNotWrittenToFcn
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_vectorIndex, uint32_T c2_dataNumber, uint32_T
   c2_ssIdOfSourceObject, int32_T c2_offsetInSourceObject, int32_T
   c2_lengthInSourceObject)
{
  (void)c2_ssIdOfSourceObject;
  (void)c2_offsetInSourceObject;
  (void)c2_lengthInSourceObject;
  if (!chartInstance->c2_dataWrittenToVector[(uint32_T)
      _SFD_EML_ARRAY_BOUNDS_CHECK(0U, (int32_T)c2_vectorIndex, 0, 2, 1, 0)]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(c2_dataNumber);
  }
}

static c2_OperationModeStatusEnum c2_get_current_task_operation_status
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_elementIndex)
{
  ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, NULL, c2_elementIndex);
  return *chartInstance->c2_current_task_operation_status_address;
}

static void c2_set_current_task_operation_status
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_elementIndex, c2_OperationModeStatusEnum
   c2_elementValue)
{
  ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, NULL, c2_elementIndex);
  *chartInstance->c2_current_task_operation_status_address = c2_elementValue;
}

static c2_OperationModeStatusEnum *c2_access_current_task_operation_status
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance, uint32_T c2_rdOnly)
{
  c2_OperationModeStatusEnum *c2_dsmAddr;
  ssReadFromDataStore_wrapper(chartInstance->S, 0, NULL);
  c2_dsmAddr = chartInstance->c2_current_task_operation_status_address;
  if (c2_rdOnly == 0U) {
    ssWriteToDataStore_wrapper(chartInstance->S, 0, NULL);
  }

  return c2_dsmAddr;
}

static void init_dsm_address_info
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S,
    "current_task_operation_status", (void **)
    &chartInstance->c2_current_task_operation_status_address,
    &chartInstance->c2_current_task_operation_status_index);
}

static void init_simulink_io_address
  (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
   *chartInstance)
{
  chartInstance->c2_sensors = (c2_Sensors_Bus *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_initFlags = (c2_Init_Bus *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_PWM = (c2_PWM_bus *)ssGetOutputPortSignal_wrapper
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

void sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_check_sum
  (mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4235845936U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3832930159U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3076960834U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3396071605U);
}

mxArray*
  sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_post_codegen_info
  (void);
mxArray
  *sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_autoinheritance_info
  (void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("82X6xD5NvJhfslkp2DkzGG");
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
      sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_post_codegen_info
      ();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray
  *sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_third_party_uses_info
  (void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray
  *sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_jit_fallback_info
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
  *sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_updateBuildInfo_args_info
  (void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray*
  sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_post_codegen_info
  (void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString(
      "lSGNVT3cA4W1threRTXalC");
    mwSize exp_dims[2] = { 3, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);

    {
      mxArray* mxFcnName = mxCreateString("Speak");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 0, mxFcnName);
    }

    {
      mxArray* mxFcnName = mxCreateString("StatusLCD");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 1, mxFcnName);
    }

    {
      mxArray* mxFcnName = mxCreateString("tail_controller");
      mxSetCell(mxExportedFunctionsUsedByThisChart, 2, mxFcnName);
    }

    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray
  *sf_get_sim_state_info_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x9'type','srcId','name','auxInfo'{{M[1],M[36],T\"PWM\",},{M[1],M[35],T\"initFlags\",},{M[3],M[37],T\"desired_tail\",},{M[8],M[0],T\"is_active_c2_gyro_calibration_algorithm_atomic_sub_chart_library\",},{M[9],M[0],T\"is_c2_gyro_calibration_algorithm_atomic_sub_chart_library\",},{M[9],M[1],T\"is_gyro_calibration_mode\",},{M[9],M[21],T\"is_GyroCalibration\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"at\",M1x3[38 23 26],M[1]}}},{M[15],M[0],T\"dataWrittenToVector\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 9, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_gyro_calibration_algorithm_atomic_sub_chart_library_get_check_sum
    (&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
      *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance =
      (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _gyro_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
           2,
           10,
           9,
           0,
           5,
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
          (_gyro_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
           chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,
             _gyro_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _gyro_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,11,0,0,"current_task_operation_status");
          _SFD_SET_DATA_PROPS(1,1,1,0,"sensors");
          _SFD_SET_DATA_PROPS(2,2,0,1,"initFlags");
          _SFD_SET_DATA_PROPS(3,2,0,1,"PWM");
          _SFD_SET_DATA_PROPS(4,0,0,0,"desired_tail");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,0);
          _SFD_CH_SUBSTATE_COUNT(1);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_ST_SUBSTATE_COUNT(0,2);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,9);
          _SFD_ST_SUBSTATE_COUNT(1,7);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,3);
          _SFD_ST_SUBSTATE_INDEX(1,2,4);
          _SFD_ST_SUBSTATE_INDEX(1,3,5);
          _SFD_ST_SUBSTATE_INDEX(1,4,6);
          _SFD_ST_SUBSTATE_INDEX(1,5,7);
          _SFD_ST_SUBSTATE_INDEX(1,6,8);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(9,0);
        }

        _SFD_CV_INIT_CHART(1,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,2,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,7,1,1,0,0,NULL,NULL);
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
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(2,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(4,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(5,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(7,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(3,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(6,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(2,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML(5,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(5,0,0,0,12,0,12);
        _SFD_CV_INIT_EML(0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(0,0,0,1,29,1,29);
        _SFD_CV_INIT_EML_RELATIONAL(0,0,0,1,29,-3,5);
        _SFD_CV_INIT_EML(2,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(2,0,0,1,14,1,14);
        _SFD_CV_INIT_EML(1,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(1,0,0,0,12,0,12);
        _SFD_CV_INIT_EML(3,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(3,0,0,0,14,0,14);
        _SFD_CV_INIT_EML(6,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(6,0,0,1,14,1,14);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_INT32,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_f_sf_marshallOut,(MexInFcnForType)c2_f_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sensors_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_initFlags_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_PWM_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)c2_c_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U,
          chartInstance->c2_current_task_operation_status_address);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c2_sensors);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_initFlags);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c2_PWM);
        _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c2_desired_tail);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _gyro_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "FC7IeRrUWBxVRTDVJi2xfE";
}

static void
  sf_opaque_initialize_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (void *chartInstanceVar)
{
  chart_debug_initialization
    (((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
      chartInstanceVar)->S,0);
  initialize_params_c2_gyro_calibration_algorithm_atomic_sub_chart_library
    ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
  initialize_c2_gyro_calibration_algorithm_atomic_sub_chart_library
    ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

static void
  sf_opaque_enable_c2_gyro_calibration_algorithm_atomic_sub_chart_library(void
  *chartInstanceVar)
{
  enable_c2_gyro_calibration_algorithm_atomic_sub_chart_library
    ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

static void
  sf_opaque_disable_c2_gyro_calibration_algorithm_atomic_sub_chart_library(void *
  chartInstanceVar)
{
  disable_c2_gyro_calibration_algorithm_atomic_sub_chart_library
    ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

static void
  sf_opaque_gateway_c2_gyro_calibration_algorithm_atomic_sub_chart_library(void *
  chartInstanceVar)
{
  sf_gateway_c2_gyro_calibration_algorithm_atomic_sub_chart_library
    ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

static const mxArray*
  sf_opaque_get_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library
    ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInfo->chartInstance);        /* raw sim ctx */
}

static void
  sf_opaque_set_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library
    ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInfo->chartInstance, st);
}

static void
  sf_opaque_terminate_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S =
      ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
       chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_gyro_calibration_algorithm_atomic_sub_chart_library_optimization_info
        ();
    }

    finalize_c2_gyro_calibration_algorithm_atomic_sub_chart_library
      ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
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
  initSimStructsc2_gyro_calibration_algorithm_atomic_sub_chart_library
    ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
     chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void
  mdlProcessParameters_c2_gyro_calibration_algorithm_atomic_sub_chart_library
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
    initialize_params_c2_gyro_calibration_algorithm_atomic_sub_chart_library
      ((SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct*)
       (chartInfo->chartInstance));
  }
}

static void
  mdlSetWorkWidths_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *S)
{
  ssSetModelReferenceSampleTimeDisallowInheritance(S);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct =
      load_gyro_calibration_algorithm_atomic_sub_chart_library_optimization_info
      ();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4234616315U));
  ssSetChecksum1(S,(4036705158U));
  ssSetChecksum2(S,(820742801U));
  ssSetChecksum3(S,(3009862445U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c2_gyro_calibration_algorithm_atomic_sub_chart_library
  (SimStruct *S)
{
  SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct
    *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance =
    (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct *)
    utMalloc(sizeof
             (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct));
  memset(chartInstance, 0, sizeof
         (SFc2_gyro_calibration_algorithm_atomic_sub_chart_libraryInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW =
    mdlRTW_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.mdlStart =
    mdlStart_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn =
    sf_exported_auto_userFcnGatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn =
    sf_exported_auto_autoFcnGatewayc2_gyro_calibration_algorithm_atomic_sub_chart_library;
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

void c2_gyro_calibration_algorithm_atomic_sub_chart_library_method_dispatcher
  (SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_gyro_calibration_algorithm_atomic_sub_chart_library(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_gyro_calibration_algorithm_atomic_sub_chart_library(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_gyro_calibration_algorithm_atomic_sub_chart_library
      (S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_gyro_calibration_algorithm_atomic_sub_chart_library_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
