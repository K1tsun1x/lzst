#include <scheduler/scheduler.h>

XTRN_C scheduler_task_t* SCHEDULER_QUEUE_READY;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_BLOCKED;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_TERMINATED;

status_t scheduler_find_task(scheduler_task_id_t* id, scheduler_task_t** task, scheduler_task_t** queue) {
	if (!id) return STATUS_INVALID_PARAMETER_1;
	if (!task) return STATUS_INVALID_PARAMETER_2;

	scheduler_task_t* queues[] = {
		SCHEDULER_QUEUE_READY,
		SCHEDULER_QUEUE_BLOCKED,
		SCHEDULER_QUEUE_TERMINATED
	};

	const size_t num_queues = sizeof(queues) / sizeof(queues[0]);
	for (size_t i = 0; i < num_queues; i++) {
		scheduler_task_t* cur_queue = queues[i];
		const size_t len = dynarr_get_length(cur_queue);
		for (size_t j = 0; j < len; j++) {
			if (!SCHEDULER_TASK_ID_EQUAL(cur_queue[j].id, *id)) continue;

			status_t res = scheduler_find_task_in_queue(
				cur_queue[j].state,
				id,
				task,
				&cur_queue
			);

			if (res == STATUS_OK) {
				if (queue) *queue = cur_queue;
				return STATUS_OK;
			}
		}
	}

	return STATUS_NOT_FOUND;
}