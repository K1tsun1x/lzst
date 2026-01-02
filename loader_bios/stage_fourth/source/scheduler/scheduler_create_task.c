#include <scheduler/scheduler.h>

status_t scheduler_create_task(
	scheduler_task_def_regs_t* def_regs,
	scheduler_task_state_t state,
	uint32_t flags,
	scheduler_task_t* task
) {
	if (!def_regs) return STATUS_INVALID_PARAMETER_1;
	if (!task) return STATUS_INVALID_PARAMETER_4;

	if (sys_osxsave_present() || sys_fpu_present()) {
		task->fp_regs = pmm_allocate_memory(SCHEDULER_TASK_SIZE_FP_REGS, 0);
		if (!task->fp_regs) return STATUS_NO_MEMORY;
	}

	task->default_regs = *def_regs;
	scheduler_generate_task_id(&task->id);
	task->state = state;
	task->flags = flags;
	task->ticks_remaining = 0;
	return STATUS_OK;
}