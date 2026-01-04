#include <scheduler/scheduler.h>

status_t scheduler_create_task(
	scheduler_task_def_regs_t* def_regs,
	scheduler_task_state_t state,
	uint32_t flags,
	scheduler_task_t* task
) {
	if (!def_regs) return STATUS_INVALID_PARAMETER_1;
	if (!task) return STATUS_INVALID_PARAMETER_4;

	bool osxsave_present = sys_osxsave_present();
	bool fpu_present = sys_fpu_present();
	if (osxsave_present || fpu_present) {
		task->fp_regs = pmm_allocate_memory(SCHEDULER_TASK_SIZE_FP_REGS, 0);
		if (!task->fp_regs) return STATUS_NO_MEMORY;

		if (osxsave_present) xsave(task->fp_regs);
		else if (fpu_present) fxsave(task->fp_regs);
	}

	task->default_regs = *def_regs;
	scheduler_generate_task_id(&task->id);
	task->state = state;
	task->flags = flags;
	task->ticks_remaining = 0;
	return STATUS_OK;
}