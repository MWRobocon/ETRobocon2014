/*****************************************************************************
 * FILE: ecrobot.c
 *
 * 09/03/2011 - MathWorks modified this file to remove Button control
 *
 * COPYRIGHT 2008 Takashi Chikamasa <takashic@cybernet.co.jp>
 *
 * <About leJOS NXJ>
 *  leJOS NXJ is a full firmware replacement of LEGO Mindstorms NXT and
 *  designed for Java programming environment for the NXT
 *  ( For more detailed information, please see: http://lejos.sourceforge.net/ )
 *  In the leJOS NXJ distribution, C source files for NXT platform layer is also
 *  included besides with the Java VM. The platform C source code is well
 *  structured, comprehensive, and achieved higher performance than the LEGO's
 *  one. Therefore, leJOS NXJ (platform) is also the best GCC based C/C++
 *  development platform for NXT.
 *
 *  The contents of this file are subject to the Mozilla Public License
 *  Version 1.0 (the "License"); you may not use this file except in
 *  compliance with the License. You may obtain a copy of the License at
 *  http://www.mozilla.org/MPL/
 *
 *  Software distributed under the License is distributed on an "AS IS"
 *  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See the
 *  License for the specific language governing rights and limitations
 *  under the License.
 *
 *  The Original Code is TinyVM code, first released March 6, 2000,
 *  later released as leJOS on September 23, 2000.
 *
 *  The Initial Developer of the Original Code is Jose H. Solorzano.
 *
 *  Contributor(s): see leJOS NXJ ACKNOWLEDGEMENTS .
 *
 *
 * <About TOPPERS OSEK>
 *  TOPPERS OSEK is an open source OSEK kernel and developed by TOPPERS project.
 *  TOPPERS(Toyohashi OPen Platform for Embedded Real-time Systems) has been managed
 *  by a Non Profit Organization founded in Sep. 2003 and has been led by Professor
 *  Hiroaki Takada of Nagoya University in Japan.
 *
 *  TOPPERS OSEK program is covered by the TOPPERS License as published
 *  by the TOPPERS PROJECT (http://www.toppers.jp/en/index.html).
 *
 *****************************************************************************/

#include <string.h>

#include "ecrobot_base.h"
#include "ecrobot_private.h"
#include "ecrobot_interface.h"

/* TOPPERS OSEK */
#include "kernel.h"
#include "cpu_insn.h"


SINT main(void)
{
    
    init_OS_flag(); /* this should be called before device init */
    nxt_device_init();
    ecrobot_initDeviceStatus(); // added 10/28/2010 to fix a bug by tchikama
    ecrobot_init_nxtstate();
    
    ecrobot_device_initialize();
    ecrobot_setDeviceInitialized();
    
    nxt_motor_set_count(NXT_PORT_A, 0);
    nxt_motor_set_count(NXT_PORT_B, 0);
    nxt_motor_set_count(NXT_PORT_C, 0);
    cpp_constructor();
    display_clear(1);
    systick_wait_ms(10);
    
    disable_int(); /* set_OS_flag and Start OS have to be atomic */
    set_OS_flag(); /* this shoud be called before starting OS */
    StartOS(1);    /* start TOPPERS OSEK */
    
    /* never reached here */
    return 0;
}

