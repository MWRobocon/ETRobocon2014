#ifndef __c3_et_robocon_h__
#define __c3_et_robocon_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc3_et_roboconInstanceStruct
#define typedef_SFc3_et_roboconInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  uint8_T c3_tp_CheckForReset;
  boolean_T c3_isStable;
  uint8_T c3_is_active_c3_et_robocon;
  uint8_T c3_is_c3_et_robocon;
  uint8_T c3_doSetSimStateSideEffects;
  const mxArray *c3_setSimStateSideEffectsInfo;
  real32_T *c3_init_flag;
} SFc3_et_roboconInstanceStruct;

#endif                                 /*typedef_SFc3_et_roboconInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_et_robocon_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_et_robocon_get_check_sum(mxArray *plhs[]);
extern void c3_et_robocon_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
