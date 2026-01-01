#pragma once
#ifndef __SCHEDULER_TASK_ID_H
#define __SCHEDULER_TASK_ID_H

#include <typedefs.h>

#define SCHEDULER_TASK_ID_EQUAL(_a_id, _b_id)		((_a_id).value == (_b_id).value && (_a_id).generation == (_b_id).generation)

typedef struct _scheduler_task_id_t {
	uint32_t			value;
	uint32_t			generation;
} scheduler_task_id_t;

#endif