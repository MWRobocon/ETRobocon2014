/*
 * File: ert_main.c
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
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "ecrobot_private.h"

int tick = 0;
double period = 0.004;
int sampleTime = 0;
int or_ext = 0;
int or_mdl = 0;
int timesup = 0;
DeclareEvent(TIMESUP);
DeclareTask(OSEK_Task_main);
DeclareTask(OSEK_Task_background);
void user_1ms_isr_type2(void)
{
  tick++;
  if (tick >= sampleTime) {
    tick = 0;
    or_ext++;
    or_mdl++;
    SetEvent(OSEK_Task_main, TIMESUP);
    timesup = 0;
  }
}

void ecrobot_device_initialize(void)
{
  et_robocon_initialize();
}

TASK(OSEK_Task_main)
{
  sampleTime = (int)(period/0.001);
  while (1) {
    WaitEvent(TIMESUP);
    ClearEvent(TIMESUP);
    et_robocon_output();

    /* Get model outputs here */
    et_robocon_update();
    or_mdl = 0;
  }

  TerminateTask();
}

TASK(OSEK_Task_background)
{
  TerminateTask();
}

void ecrobot_device_terminate(void)
{
  et_robocon_terminate();
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
