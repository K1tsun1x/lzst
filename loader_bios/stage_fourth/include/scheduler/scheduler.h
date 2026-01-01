#pragma once
#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include <idt/idt.h>

#include <pmm/pmm.h>
#include <vmm/vmm.h>
#include <sys/sys.h>
#include <dynarr/dynarr.h>
#include <status/status.h>
#include <virt-int-ctrl/virt-int-ctrl.h>
#include "scheduler_task.h"

#define SCHEDULER_QUANTUM_TICKS									1000
#define SCHEDULER_MAX_TASKS_REMOVED_PER_CLEANUP					10
#define SCHEDULER_MAX_TASKS										32

/**
 * @return `STATUS_NO_MEMORY`: not enough memory for queues,
 * @return `STATUS_OK`: ok
 */
status_t scheduler_init(uint8_t timer_vector);
void scheduler_remap(uint8_t timer_vector);

void scheduler_generate_task_id(scheduler_task_id_t* id);

/**
 * @return `STATUS_INVALID_PARAMETER_1`: def_regs = NULL,
 * @return `STATUS_INVALID_PARAMETER_4`: task = NULL,
 * @return `STATUS_NO_MEMORY`: not enough memory for fp_regs,
 * @return `STATUS_OK`: ok
 */
status_t scheduler_create_task(
	scheduler_task_def_regs_t* def_regs,
	scheduler_task_state_t state,
	uint32_t flags,
	scheduler_task_t* task
);

/**
 * @return `STATUS_INVALID_PARAMETER`: task = NULL,
 * @return `STATUS_NOT_FOUND`: could not determine the queue to which to add the task,
 * @return `STATUS_NO_MEMORY`: not enough memory to add the task to the queue,
 * @return `STATUS_OK`: ok
 */
status_t scheduler_add_task(scheduler_task_t* task);

/**
 * @return `STATUS_INVALID_PARAMETER_2`: id = NULL,
 * @return `STATUS_INVALID_PARAMETER_3`: task = NULL,
 * @return `STATUS_NOT_FOUND`: task not found,
 * @return `STATUS_OK`:
 */
status_t scheduler_find_task_in_queue(
	scheduler_task_state_t state,
	scheduler_task_id_t* id,
	scheduler_task_t** task,
	scheduler_task_t** queue
);

/**
 * @return `STATUS_INVALID_PARAMETER_1`: id = NULL,
 * @return `STATUS_INVALID_PARAMETER_2`: task = NULL,
 * @return `STATUS_NOT_FOUND`: task not found,
 * @return `STATUS_OK`:
 */
status_t scheduler_find_task(scheduler_task_id_t* id, scheduler_task_t** task, scheduler_task_t** queue);

/**
 * @return `STATUS_INVALID_PARAMETER`: id = NULL,
 * @return `STATUS_NOT_FOUND`: task not found,
 * @return `STATUS_NO_MEMORY`: not enough memory to remove the task from the queue,
 * @return `STATUS_OK`:
 */
status_t scheduler_remove_task(scheduler_task_id_t* id);

XTRN_C void LOADERCALL scheduler_yield(void);

#endif