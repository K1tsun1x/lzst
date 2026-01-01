#include <scheduler/scheduler.h>

static scheduler_task_id_t PREV_TASK_ID = { 0, 0 };

void scheduler_generate_task_id(scheduler_task_id_t* id) {
	if (PREV_TASK_ID.value == UINT32_MAX) PREV_TASK_ID.generation += 1;
	PREV_TASK_ID.value += 1;

	if (id) *id = PREV_TASK_ID;
}