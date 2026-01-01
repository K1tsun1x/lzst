#pragma once
#ifndef __SCHEDULER_TASK_H
#define __SCHEDULER_TASK_H

#include <isr/isr_data.h>
#include "scheduler_task_id.h"
#include "scheduler_task_def_regs.h"

#define SCHEDULER_TASK_SIZE_FP_REGS							2048

#define SCHEDULER_TASK_FLAG_NO_AUTOREMOVE					(1 << 0)

typedef enum _scheduler_task_state_t ENUM_TYPE(size_t) {
	SCHEDULER_TASK_STATE_TERMINATED,
	SCHEDULER_TASK_STATE_BLOCKED,
	SCHEDULER_TASK_STATE_READY,
	SCHEDULER_TASK_STATE_RUNNING
} scheduler_task_state_t;

#pragma pack(push, 1)
typedef struct _scheduler_task_t {
	uint8_t*					fp_regs;
	scheduler_task_def_regs_t	default_regs;

	scheduler_task_id_t			id;
	scheduler_task_state_t		state;

	// SCHEDULER_TASK_FLAG_* | ...
	uint32_t					flags;
	size_t						ticks_remaining;
	
	// For task switching
	struct _scheduler_task_t*	next;
	size_t						cr3;
} scheduler_task_t;
#pragma pack(pop)

#endif