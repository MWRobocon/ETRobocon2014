/*
 *  TOPPERS/OSEK Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      OSEK Kernel
 * 
 *  Copyright (C) 2004-2006 by Witz Corporation, JAPAN
 * 
 *  上記著作権者は，以下の (1)～(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 */

/*
 *	サンプル向けターゲット依存システムタイマモジュール（LEGO MINDSTORMS NXT用）
 */


#include "kernel.h"

/* LEJOS NXJ */
#include "AT91SAM7.h"
#include "systick.h"

#include "ecrobot_base.h"
#include "ecrobot_interface.h"

/* Originally, systick_low_priority_C is a LEJOS ISR. 
 * LEJOS-OSEK uses systick_isr_C1 category 2 ISR instead of systick_low_priority_C 
 * to implement a system timer module for OSEK alarm and 
 * check the buttons status to shutdown the system
 */
extern void systick_low_priority_C(void);

void systick_isr_C1()
{
	/* clear the interrupt status register (2007/12/27) */
	*AT91C_AIC_ICCR = (1 << 10); /* 10 = LOW_PRIORITY_IRQ */

	/* check OSEK was started */ 
	if (get_OS_flag())
	{
		user_1ms_isr_type2();
		check_NXT_buttons();
	}

	/* this function should be here to stop the NXT immediately 
	 * after EXIT button was pressed
	 */
	systick_low_priority_C();

}

