#include <scheduler/scheduler.h>

XTRN_ONLY_CPP scheduler_task_t* SCHEDULER_QUEUE_READY = NULL;
XTRN_ONLY_CPP scheduler_task_t* SCHEDULER_QUEUE_BLOCKED = NULL;
XTRN_ONLY_CPP scheduler_task_t* SCHEDULER_QUEUE_TERMINATED = NULL;
XTRN_ONLY_CPP scheduler_task_t* SCHEDULER_CURRENT_TASK = NULL;

status_t scheduler_init(uint8_t timer_vector) {
	if (SCHEDULER_QUEUE_READY) {
		dynarr_free(SCHEDULER_QUEUE_READY);
		SCHEDULER_QUEUE_READY = NULL;
	}
	
	if (SCHEDULER_QUEUE_BLOCKED) {
		dynarr_free(SCHEDULER_QUEUE_BLOCKED);
		SCHEDULER_QUEUE_BLOCKED = NULL;
	}
	
	if (SCHEDULER_QUEUE_TERMINATED) {
		dynarr_free(SCHEDULER_QUEUE_TERMINATED);
		SCHEDULER_QUEUE_TERMINATED = NULL;
	}

	SCHEDULER_QUEUE_READY = (scheduler_task_t*)dynarr_create(sizeof(scheduler_task_t), DYNARR_START_CAPACITY);
	if (!SCHEDULER_QUEUE_READY) return STATUS_NO_MEMORY;

	SCHEDULER_QUEUE_BLOCKED = (scheduler_task_t*)dynarr_create(sizeof(scheduler_task_t), DYNARR_START_CAPACITY);
	if (!SCHEDULER_QUEUE_BLOCKED) {
		dynarr_free(SCHEDULER_QUEUE_READY);
		return STATUS_NO_MEMORY;
	}

	SCHEDULER_QUEUE_TERMINATED = (scheduler_task_t*)dynarr_create(sizeof(scheduler_task_t), DYNARR_START_CAPACITY);
	if (!SCHEDULER_QUEUE_TERMINATED) {
		dynarr_free(SCHEDULER_QUEUE_BLOCKED);
		dynarr_free(SCHEDULER_QUEUE_READY);
		return STATUS_NO_MEMORY;
	}

	scheduler_remap(timer_vector);
	return STATUS_OK;
}