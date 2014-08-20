/*
 *  TOPPERS/OSEK Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      OSEK Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2004 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *	�����݊Ǘ��@�\
 */

#include "osek_kernel.h"
#include "interrupt.h"

/*
 *  ���s����ISR�i�J�e�S��2�j
 */
IsrType		runisr;

/*
 *  �����݊Ǘ��@�\�����Ŏg�p����ϐ��̒�`
 */

/*
 *  SuspendAllInterrupts �̃l�X�g��
 *
 *  ���̕ϐ��́Cdisable_int() ������Ԃł̂ݕύX���Ă悢�D
 */
UINT8		sus_all_cnt;

/*
 *  SuspendOSInterrupts �̃l�X�g��
 *
 *  ���̕ϐ��́Cset_ipl(ipl_maxisr2) ������Ԃł̂ݕύX���Ă悢�D
 *  set_ipl(ipl_maxisr2) ���Ă��C�J�e�S��1 �� ISR �͓����Ă��邪�C����
 *  �l�ɖ߂��Ă��烊�^�[������Ζ��͂Ȃ��D
 */
static UINT8	sus_os_cnt;

/*
 *  SuspendOSInterrupts ����O�̊����ݗD�惌�x��
 *
 *  ���̕ϐ��́Cset_ipl(ipl_maxisr2) ������Ԃł̂ݕύX���Ă悢�D�܂��C
 *  ���̕ϐ����g�p���Ă���Ԃ́Csus_os_cnt ���[���ɂ��Ă����D
 *  set_ipl(ipl_maxisr2) ���Ă��J�e�S��1 �� ISR �͓����Ă��邪�C
 *  sus_os_cnt ���[���ɂ��Ă������ƂŁC�J�e�S��1 �� ISR �ł��̕ϐ���
 *  �ύX����邱�Ƃ͂Ȃ��D
 */
static IPL	saved_ipl;

/*
 *  SuspendAllInterrupts/SuspendOSInterrupts ����O�̎��s�R���e�L�X�g
 *
 *  ���̕ϐ��́Cdisable_int �܂��� set_ipl(ipl_maxisr2) ������Ԃł̂�
 *  �ύX���Ă悢�D�܂��C���̕ϐ����g�p���Ă���Ԃ́Csus_all_cnt �� 
 *  sus_os_cnt ���[���ɂ��Ă����Dset_ipl(ipl_maxisr2) ���Ă��J�e�S��1
 *  �� ISR �͓����Ă��邪�Csus_os_cnt ���[���ɂ��Ă������ƂŁC�J�e�S
 *  ��1 �� ISR �ł��̕ϐ����ύX����邱�Ƃ͂Ȃ��D
 */
static UINT8	saved_callevel;

/*
 *  �����݊Ǘ��@�\�̏�����
 */
void
interrupt_initialize(void)
{
	IsrType		isrid;

	isrid = ISRID_NULL;
	sus_all_cnt = 0u;
	sus_os_cnt = 0u;
	for (isrid = 0; isrid < tnum_isr2; isrid++) {
		isrcb_lastres[isrid] = 0u;
	}
}

/*
 *  ���ׂĂ̊����݂̋֎~�i�����ȈՔŁj
 */
void
DisableAllInterrupts(void)
{
	LOG_DISINT_ENTER();
	disable_int();
	LOG_DISINT_LEAVE();
}

/*
 *  ���ׂĂ̊����݂̋��i�����ȈՔŁj
 */
void
EnableAllInterrupts(void)
{
	LOG_ENAINT_ENTER();
	enable_int();
	LOG_ENAINT_LEAVE();
}

/*
 *  ���ׂĂ̊����݂̋֎~
 */
void
SuspendAllInterrupts(void)
{
	LOG_SUSALL_ENTER();
	if (sus_all_cnt == UINT8_INVALID) {
		/*
		 *  SuspendAllInterrupts ���J��Ԃ��Ă񂾏ꍇ�̑΍�
		 *  �i���������ɔ�����j
		 */
	}
	else if (sus_all_cnt == 0) {
		disable_int();
		sus_all_cnt++;
		if (sus_os_cnt == 0) {
			saved_callevel = callevel;
			callevel = TCL_NULL;
		}
	}
	else {
		sus_all_cnt++;
	}
	LOG_SUSALL_LEAVE();
}

/*
 *  ���ׂĂ̊����݂̋���
 */
void
ResumeAllInterrupts(void)
{
	LOG_RSMALL_ENTER();
	if (sus_all_cnt == 0) {
		/*
		 *  SuspendAllInterrupts ���Ă΂��ɁCResumeAllInterrupts
		 *  ���Ă񂾏ꍇ�̑΍�i���������ɔ�����j
		 */
	}
	else if (sus_all_cnt == 1) {
		if (sus_os_cnt == 0) {
			callevel = saved_callevel;
		}
		sus_all_cnt--;
		enable_int();
	}
	else {
		sus_all_cnt--;
	}
	LOG_RSMALL_LEAVE();
}

/*
 *  �J�e�S��2�̊����݂̋֎~
 */
void
SuspendOSInterrupts(void)
{
	IPL	ipl;

	LOG_SUSOSI_ENTER();
	if (sus_os_cnt == UINT8_INVALID) {
		/*
		 *  SuspendOSInterrupts ���J��Ԃ��Ă񂾏ꍇ�̑΍�
		 *  �i���������ɔ�����j
		 */
	}
	else if (sus_os_cnt == 0) {
		ipl = current_ipl();

		/*
		 *  ���ł� ISR2 ���֎~����Ă��鎞�͉������Ȃ��D
		 */
		if (ipl < ipl_maxisr2) {
			set_ipl(ipl_maxisr2);
		}
		sus_os_cnt++;
		saved_ipl = ipl;
		if (sus_all_cnt == 0) {
			saved_callevel = callevel;
			callevel = TCL_NULL;
		}
	}
	else {
		sus_os_cnt++;
	}
	LOG_SUSOSI_LEAVE();
}

/*
 *  �J�e�S��2�̊����݂̋���
 */
void
ResumeOSInterrupts(void)
{
	LOG_RSMOSI_ENTER();
	if (sus_os_cnt == 0) {
		/*
		 *  SuspendOSInterrupts ���Ă΂��ɁCResumeOSInterrupts
		 *  ���Ă񂾏ꍇ�̑΍�i���������ɔ�����j
		 */
	}
	else if (sus_os_cnt == 1) {
		if (sus_all_cnt == 0) {
			callevel = saved_callevel;
		}
		sus_os_cnt--;

		/*
		 *  ���Ƃ��� ISR2 ���֎~����Ă������͉������Ȃ��D
		 */
		if (saved_ipl < ipl_maxisr2) {
			set_ipl(saved_ipl);
		}
	}
	else {
		sus_os_cnt--;
	}
	LOG_RSMOSI_LEAVE();
}
