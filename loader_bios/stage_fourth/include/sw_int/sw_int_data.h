#pragma once
#ifndef __SW_INT_DATA_H
#define __SW_INT_DATA_H

#include <scheduler/scheduler_task_def_regs.h>

#pragma pack(push, 1)
typedef struct _sw_int_data_t {
	size_t							int_index;			// offset: 0x00
	scheduler_task_def_regs_t		def_regs;			// offset: 0x04
} sw_int_data_t;
#pragma pack(pop)

#endif