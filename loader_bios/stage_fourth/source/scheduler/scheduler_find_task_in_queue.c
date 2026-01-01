#include <scheduler/scheduler.h>

XTRN_C scheduler_task_t* SCHEDULER_QUEUE_READY;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_BLOCKED;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_TERMINATED;

status_t scheduler_find_task_in_queue(
	scheduler_task_state_t state,
	scheduler_task_id_t* id,
	scheduler_task_t** task,
	scheduler_task_t** queue
) {
	if (!id) return STATUS_INVALID_PARAMETER_2;
	if (!task) return STATUS_INVALID_PARAMETER_3;

	scheduler_task_t* cur_queue = NULL;
	if (state == SCHEDULER_TASK_STATE_READY) cur_queue = SCHEDULER_QUEUE_READY;
	else if (state == SCHEDULER_TASK_STATE_BLOCKED) cur_queue = SCHEDULER_QUEUE_BLOCKED;
	else if (state == SCHEDULER_TASK_STATE_TERMINATED) cur_queue = SCHEDULER_QUEUE_TERMINATED;
	else return STATUS_NOT_FOUND;

	const size_t len = dynarr_get_length(cur_queue);
	for (size_t i = 0; i < len; i++) if (SCHEDULER_TASK_ID_EQUAL(cur_queue[i].id, *id)) {
		*task = &cur_queue[i];
		if (queue) *queue = cur_queue;
		return STATUS_OK;
	}

	return STATUS_NOT_FOUND;
}