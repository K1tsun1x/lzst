#include <scheduler/scheduler.h>

XTRN_C scheduler_task_t* SCHEDULER_QUEUE_READY;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_BLOCKED;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_TERMINATED;
XTRN_C scheduler_task_t* SCHEDULER_CURRENT_TASK;

status_t scheduler_remove_task(scheduler_task_id_t* id) {
	if (!id) return STATUS_INVALID_PARAMETER;

	scheduler_task_t* task;
	status_t status = scheduler_find_task(id, &task, NULL);
	if (status != STATUS_OK) return STATUS_NOT_FOUND;

	const uint8_t* fp_regs = task->fp_regs;
	scheduler_task_t* next = task->next;
	const bool other_tasks_in_queue = next != task;
	const bool is_running = SCHEDULER_CURRENT_TASK ? SCHEDULER_TASK_ID_EQUAL(*id, SCHEDULER_CURRENT_TASK->id) : false;

	scheduler_task_t** queue = NULL;
	if (task->state == SCHEDULER_TASK_STATE_READY) queue = &SCHEDULER_QUEUE_READY;
	if (task->state == SCHEDULER_TASK_STATE_BLOCKED) queue = &SCHEDULER_QUEUE_BLOCKED;
	if (task->state == SCHEDULER_TASK_STATE_TERMINATED) queue = &SCHEDULER_QUEUE_TERMINATED;
	else return STATUS_NOT_FOUND;

	const size_t index = ((uintptr_t)task - (uintptr_t)(*queue)) / sizeof(scheduler_task_t);
	scheduler_task_t* tmp = (scheduler_task_t*)dynarr_remove(*queue, index);
	if (!tmp) return STATUS_NO_MEMORY;

	*queue = tmp;

	if (other_tasks_in_queue) {
		if (index) (*queue)[index - 1].next = next;
		else {
			const size_t last_index = dynarr_get_length(*queue) - 1;
			(*queue)[last_index].next = next;
		}
	}

	if (fp_regs) pmm_free_memory(fp_regs);
	if (is_running) {
		// FIXME: must be next task, not first
		if (
			SCHEDULER_QUEUE_READY && dynarr_get_length(SCHEDULER_QUEUE_READY)
		) SCHEDULER_CURRENT_TASK = &SCHEDULER_QUEUE_READY[0];
		else SCHEDULER_CURRENT_TASK = NULL;
	}

	return STATUS_OK;
}