#ifndef __light_sensor_calibration_algorithm_atomic_sub_chart_library_sfun_h__
#define __light_sensor_calibration_algorithm_atomic_sub_chart_library_sfun_h__

/* Include files */
#define S_FUNCTION_NAME                sf_sfun
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "sf_runtime/sf_runtime_errors.h"
#include "rtwtypes.h"
#include "simtarget/slClientServerAPIBridge.h"
#include "multiword_types.h"
#include "sf_runtime/sfcdebug.h"
#define rtInf                          (mxGetInf())
#define rtMinusInf                     (-(mxGetInf()))
#define rtNaN                          (mxGetNaN())
#define rtIsNaN(X)                     ((int)mxIsNaN(X))
#define rtIsInf(X)                     ((int)mxIsInf(X))

struct SfDebugInstanceStruct;
extern struct SfDebugInstanceStruct* sfGlobalDebugInstanceStruct;

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */
extern uint32_T
  _light_sensor_calibration_algorithm_atomic_sub_chart_libraryMachineNumber_;

/* Variable Definitions */

/* Function Declarations */
extern void
  light_sensor_calibration_algorithm_atomic_sub_chart_library_initializer(void);
extern void
  light_sensor_calibration_algorithm_atomic_sub_chart_library_terminator(void);

/* Function Definitions */

/* We load infoStruct for rtw_optimation_info on demand in mdlSetWorkWidths and
   free it immediately in mdlStart. Given that this is machine-wide as
   opposed to chart specific, we use NULL check to make sure it gets loaded
   and unloaded once per machine even though the  methods mdlSetWorkWidths/mdlStart
   are chart/instance specific. The following methods abstract this out. */
extern mxArray*
  load_light_sensor_calibration_algorithm_atomic_sub_chart_library_optimization_info
  (void);
extern void
  unload_light_sensor_calibration_algorithm_atomic_sub_chart_library_optimization_info
  (void);

#endif
