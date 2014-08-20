/*
 * File: OperationModeEnum.h
 *
 * Code generated for Simulink model 'et_robocon'.
 *
 * Model version                  : 1.762
 * Simulink Coder version         : 8.7 (R2014b Prerelease) 21-May-2014
 * TLC version                    : 8.7 (May 23 2014)
 * C/C++ source code generated on : Wed Aug 13 16:26:36 2014
 */

#ifndef RTW_HEADER_OperationModeEnum_h_
#define RTW_HEADER_OperationModeEnum_h_

typedef enum {
  SKIP = 0,
  GYRO_CALIBRATION,
  LIGHT_CALIBRATION_ON_TAIL,
  LIGHT_CALIBRATION_UP,
  LINE_TRACKING,                       /* Default value */
  SEE_SAW,
  LIMBO,
  SEE_SAW_MARIO,
  SEE_SAW_PRINCESS,
  YOSHI,
  PARKING,
  LIGHT_CALIBRATION_LIMBO,
  LINE_TRACKING_LIMBO,
  LINE_TRACKING_ON_MAP,
  LIGHT_CALIBRATION_UP_FLASHING,
  LIGHT_CALIBRATION_UP_FLASHING_ON_MAP
} OperationModeEnum;

#endif                                 /* RTW_HEADER_OperationModeEnum_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
