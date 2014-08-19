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
 *	�^�X�N�Ǘ����W���[��
 */

#include "osek_kernel.h"
#include "check.h"
#include "task.h"
#include "resource.h"
#include "cpu_context.h"

/*
 *  �X�^�e�B�b�N�֐��̃v���g�^�C�v�錾
 */
Inline void	ready_insert_first(Priority pri, TaskType tskid);
Inline void	ready_insert_last(Priority pri, TaskType tskid);
Inline TaskType	ready_delete_first(Priority pri);
Inline Priority	bitmap_search(UINT16 bitmap);

/*
 *  ���f�B�L���[
 *
 *  ���f�B�L���[�ɂ͎��s�\��Ԃ̃^�X�N�݂̂��Ȃ����ƂƂ��C���s���
 *  �̃^�X�N�̓��f�B�L���[����͊O���D�����ɂ́Cschedtsk �����f�B�L���[
 *  ����O���i�����ݏ������ɂ́Cruntsk �����f�B�L���[����O��Ă���Ƃ�
 *  ����Ȃ��j�D
 *  ���f�B�L���[�́C�D��x���̒P���������N�L���[�ō\������D���f�B�L���[
 *  �̐擪�̃^�X�NID�� ready_queue_first �ɁC�����̃^�X�NID ��
 *  ready_queue_last �ɕێ�����D���f�B�L���[����̎��́Cready_queue_first 
 *  �� TSKID_NULL �Ƃ��Cready_queue_last �͕s��Ƃ���D
 */
static TaskType ready_queue_first[TNUM_PRIORITY];
static TaskType ready_queue_last[TNUM_PRIORITY];

/*
 *  ���f�B�L���[�̐擪�ւ̑}��
 */
Inline void
ready_insert_first(Priority pri, TaskType tskid)
{
	TaskType	first;

	assert(pri <= TPRI_MAXTASK);
	first = ready_queue_first[pri];
	ready_queue_first[pri] = tskid;
	tcb_next[tskid] = first;
	if (first == TSKID_NULL) {
		ready_queue_last[pri] = tskid;
	}
}

/*
 *  ���f�B�L���[�̖����ւ̑}��
 */
Inline void
ready_insert_last(Priority pri, TaskType tskid)
{
	assert(pri <= TPRI_MAXTASK);
	if (ready_queue_first[pri] == TSKID_NULL) {
		ready_queue_first[pri] = tskid;
	}
	else {
		tcb_next[ready_queue_last[pri]] = tskid;
	}
	ready_queue_last[pri] = tskid;
	tcb_next[tskid] = TSKID_NULL;
}

/*
 *  ���f�B�L���[�̐擪�^�X�N�̍폜
 */
Inline TaskType
ready_delete_first(Priority pri)
{
	TaskType	first;

	first = ready_queue_first[pri];
	assert(first != TSKID_NULL);
	ready_queue_first[pri] = tcb_next[first];
	return(first);
}

/*
 *  �r�b�g�}�b�v�T�[�`�֐�
 *
 *  bitmap ���� 1 �̃r�b�g�̓��C�ł���L�i���j�̂��̂��T�[�`���C���̃r
 *  �b�g�ԍ���Ԃ��D�r�b�g�ԍ��́C�ŉ��ʃr�b�g�� 0 �Ƃ���Dbitmap �� 0
 *  ���w�肵�Ă͂Ȃ�Ȃ��D���̊֐��ł́C�D��x��16�i�K�ȉ��ł��邱�Ƃ�
 *  ���肵�Cbitmap �̉���16�r�b�g�݂̂��T�[�`����D
 *  �r�b�g�T�[�`���߂����v���Z�b�T�ł́C�r�b�g�T�[�`���߂��g���悤��
 *  ���������������������ǂ����낤�D���̂悤�ȏꍇ�ɂ́Ccpu_insn.h ��
 *  �r�b�g�T�[�`���߂��g���� bitmap_search ���`���CCPU_BITMAP_SEARCH 
 *  ���}�N����`����΂悢�D�܂��C�r�b�g�T�[�`���߂̃T�[�`�������t�Ȃ�
 *  �̗��R�ŗD��x�ƃr�b�g�Ƃ̑Ή���ύX�������ꍇ�ɂ́CPRIMAP_BIT ��
 *  �}�N����`����΂悢�D
 *  �܂��C�W�����C�u������ ffs ������Ȃ�C���̂悤�ɒ�`���ĕW�����C
 *  �u�������g���������������ǂ��\��������D
 *	#define PRIMAP_BIT(pri)	(0x8000u >> (pri))
 *	#define	bitmap_search(bitmap) (16 - ffs(bitmap))
 *  ��ITRON�d�l�Ƃ͗D��x�̈Ӗ����t�̂��߁C�T�[�`����������t�ɂȂ���
 *  ����Dbitmap_search ��u��������ꍇ�ɂ́C���ӂ��K�v�ł���D
 */
#ifndef PRIMAP_BIT
#define	PRIMAP_BIT(pri)		(1u << (pri))
#endif /* PRIMAP_BIT */

#ifndef CPU_BITMAP_SEARCH

Inline Priority
bitmap_search(UINT16 bitmap)
{
	static const UINT8 search_table[] = { 0, 1, 1, 2, 2, 2, 2,
						3, 3, 3, 3, 3, 3, 3, 3 };
	Priority	pri = 0;

	assert((bitmap & ((UINT16) 0xffffu)) != 0);
	if ((bitmap & ((UINT16) 0xff00u)) != 0) {
		bitmap >>= 8;
		pri += 8;
	}
	if ((bitmap & ((UINT16) 0xf0)) != 0) {
		bitmap >>= 4;
		pri += 4;
	}
	return(pri + (search_table[(bitmap & ((UINT16) 0x0f)) - 1]));
}

#endif /* CPU_BITMAP_SEARCH */

/*
 *  ���s��Ԃ̃^�X�N
 */
TaskType	runtsk;

/*
 *  �ō��D�揇�ʃ^�X�N
 */
TaskType	schedtsk;

/*
 *  ���f�B�L���[���̍ō��D��x
 */
Priority	nextpri;

/*
 *  ���f�B�L���[�ɓ����Ă���^�X�N�̗D��x�̃r�b�g�}�b�v
 *
 *  ���f�B�L���[����̎��i���s�\��Ԃ̃^�X�N���������j�� 0 �ɂ���D
 */
static UINT16	ready_primap;

/*
 *  �^�X�N�Ǘ����W���[���̏�����
 */
void
task_initialize(void)
{
	Priority	pri;
	TaskType	tskid;

	runtsk = TSKID_NULL;
	schedtsk = TSKID_NULL;
	for (pri = 0; pri < TNUM_PRIORITY; pri++) {
		ready_queue_first[pri] = TSKID_NULL;
	}
	nextpri = TPRI_MINTASK;
	ready_primap = 0u;

	for (tskid = 0; tskid < tnum_task; tskid++) {
		tcb_actcnt[tskid] = 0;
		if ((tinib_autoact[tskid] & appmode) != APPMODE_NONE) {
			(void)make_active(tskid);
			tcb_tstat[tskid] = TS_RUNNABLE;
		}
		else {
			tcb_tstat[tskid] = TS_DORMANT;
		}
	}
}

/*
 *  �^�X�N�̋N��
 *
 *  TerminateTask �� ChainTask �̒��ŁC���^�X�N�ɑ΂��� make_active ��
 *  �Ăԏꍇ������̂Œ��ӂ���D
 */
BOOL
make_active(TaskType tskid)
{
	tcb_curpri[tskid] = tinib_inipri[tskid];
	if (tskid < tnum_exttask) {
		tcb_curevt[tskid] = EVTMASK_NONE;
		tcb_waievt[tskid] = EVTMASK_NONE;
	}
	tcb_lastres[tskid] = RESID_NULL;
	activate_context(tskid);
	return(make_runnable(tskid));
}

/*
 *  ���s�ł����Ԃւ̈ڍs
 */
BOOL
make_runnable(TaskType tskid)
{
	Priority	pri, schedpri;

	tcb_tstat[tskid] = TS_RUNNABLE;
	if (schedtsk != TSKID_NULL) {
		pri = tcb_curpri[tskid];
		schedpri = tcb_curpri[schedtsk];
		if (pri <= schedpri) {
			/*
			 *  schedtsk �̕����D��x�������ꍇ�Ctskid ����
			 *  �f�B�L���[�̍Ō�ɓ����D
			 */
			ready_insert_last(pri, tskid);
			ready_primap |= PRIMAP_BIT(pri);
			if (pri > nextpri) {
				nextpri = pri;
			}
			return(FALSE);
		}
		/*
		 *  tskid �̕����D��x�������ꍇ�Cschedtsk �����f�B�L���[
		 *  �̐擪�ɓ���Ctskid ��V���� schedtsk �Ƃ���D
		 */
		ready_insert_first(schedpri, schedtsk);
		ready_primap |= PRIMAP_BIT(schedpri);
		nextpri = schedpri;
	}
	schedtsk = tskid;
	return(TRUE);
}

/*
 *  �ō��D�揇�ʃ^�X�N�̃T�[�`
 */
void
search_schedtsk(void)
{
	if (ready_primap == ((UINT16) 0)) {
		schedtsk = TSKID_NULL;
	}
	else {
		schedtsk = ready_delete_first(nextpri);
		if (ready_queue_first[nextpri] == TSKID_NULL) {
			ready_primap &= ~PRIMAP_BIT(nextpri);
			nextpri = (ready_primap == ((UINT16) 0)) ?
						TPRI_MINTASK : bitmap_search(ready_primap);
		}
	}
}

/*
 *  �^�X�N�̃v���G���v�g
 */
void
preempt(void)
{
	assert(runtsk == schedtsk);
	ready_insert_first(tcb_curpri[schedtsk], schedtsk);
	ready_primap |= PRIMAP_BIT(tcb_curpri[schedtsk]);
	search_schedtsk();
}
