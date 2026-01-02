#include <scheduler/scheduler.h>

XTRN_C scheduler_task_t* SCHEDULER_QUEUE_READY;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_BLOCKED;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_TERMINATED;

status_t scheduler_add_task(scheduler_task_t* task) {
	if (!task) return STATUS_INVALID_PARAMETER;

	scheduler_task_t** queue = NULL;
	if (task->state == SCHEDULER_TASK_STATE_READY) queue = &SCHEDULER_QUEUE_READY;
	else if (task->state == SCHEDULER_TASK_STATE_BLOCKED) queue = &SCHEDULER_QUEUE_BLOCKED;
	else if (task->state == SCHEDULER_TASK_STATE_TERMINATED) queue = &SCHEDULER_QUEUE_TERMINATED;
	else return STATUS_NOT_FOUND;

	const size_t index = dynarr_get_length(*queue);
	scheduler_task_t* tmp = (scheduler_task_t*)dynarr_append(*queue, task);
	if (!tmp) return STATUS_NO_MEMORY;

	*queue = tmp;

	task = &(*queue)[index];

	paging_pde_t* task_dir = (paging_pde_t*)(task->default_regs.cr3 & PAGING_MASK_PDE_ADDRESS);
	task->default_regs.sp -= sizeof(uintptr_t);
	vmm_copy_memory(
		task_dir,
		task->default_regs.sp,
		&task->default_regs.flags,
		sizeof(uintptr_t)
	);
	
	task->default_regs.sp -= sizeof(uintptr_t);
	vmm_copy_memory(
		task_dir,
		task->default_regs.sp,
		&task->default_regs.cs,
		sizeof(uintptr_t)
	);
	
	task->default_regs.sp -= sizeof(uintptr_t);
	vmm_copy_memory(
		task_dir,
		task->default_regs.sp,
		&task->default_regs.ip,
		sizeof(uintptr_t)
	);
	
	task->next = &(*queue)[0];
	if (index) (*queue)[index - 1].next = task;
	return STATUS_OK;
}