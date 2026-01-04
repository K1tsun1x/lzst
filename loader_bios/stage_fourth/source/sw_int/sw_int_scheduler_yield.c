#include <sw_int/sw_int.h>

XTRN_C scheduler_task_t* SCHEDULER_QUEUE_READY;
XTRN_C scheduler_task_t* SCHEDULER_CURRENT_TASK;

XTRN_C void sw_int_scheduler_yield(bool ring_switch, sw_int_data_t* data) {
	UNREFERENCED_PARAMETER(ring_switch);
	
	scheduler_task_t* next = NULL;
	if (SCHEDULER_CURRENT_TASK) {
		if (SCHEDULER_CURRENT_TASK->fp_regs) {
			if (sys_osxsave_present()) xsave(SCHEDULER_CURRENT_TASK->fp_regs);
			else if (sys_fpu_present()) fxsave(SCHEDULER_CURRENT_TASK->fp_regs);
		}

		SCHEDULER_CURRENT_TASK->default_regs = data->def_regs;
		SCHEDULER_CURRENT_TASK->state = SCHEDULER_TASK_STATE_READY;
		next = SCHEDULER_CURRENT_TASK->next;
	}
	else if (
		SCHEDULER_QUEUE_READY &&
		DYNARR_HEADER_FROM_MEM(SCHEDULER_QUEUE_READY)->num_elems
	) next = &SCHEDULER_QUEUE_READY[0];

	if (!next) return;

	SCHEDULER_CURRENT_TASK = next;
	if (SCHEDULER_CURRENT_TASK->fp_regs) {
		if (sys_osxsave_present()) xrstor(SCHEDULER_CURRENT_TASK->fp_regs);
		else if (sys_fpu_present()) fxrstor(SCHEDULER_CURRENT_TASK->fp_regs);
	}

	data->def_regs = SCHEDULER_CURRENT_TASK->default_regs;
}