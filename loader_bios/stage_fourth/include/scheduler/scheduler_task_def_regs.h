#pragma once
#ifndef __SCHEDULER_TASK_DEF_REGS_H
#define __SCHEDULER_TASK_DEF_REGS_H

#include <typedefs.h>

#define SCHEDULER_STATIC_TASK_DEF_REGS($cr3, $ds, $ss, $stack_top, $ip, $cs, $flags){\
	.cr3 = ($cr3), \
	.ds = ($ds), .ss = ($ss), \
	.bp = ($stack_top), .sp = ($stack_top), \
	.ip = ($ip), .cs = ($cs), .flags = ($flags) \
}

#define SCHEDULER_STATIC_DEFAULT_TASK_DEF_REGS(cr3, stack_top, ip)			SCHEDULER_STATIC_TASK_DEF_REGS(cr3, 0x10, 0x10, stack_top, ip, 0x08, read_flags())

#pragma pack(push, 1)
typedef struct _scheduler_task_def_regs_t {
	size_t			cr3;				// offset: 0x00
	size_t			ds;					// Offset: 0x04
	size_t			ss;					// Offset: 0x08

	size_t			di;					// Offset: 0x0c
	size_t			si;					// Offset: 0x10
	size_t			bp;					// Offset: 0x14
	size_t			sp;					// Offset: 0x18
	size_t			bx;					// Offset: 0x1c
	size_t			dx;					// Offset: 0x20
	size_t			cx;					// Offset: 0x24
	size_t			ax;					// Offset: 0x28

	size_t			ip;					// Offset: 0x2c
	size_t			cs;					// Offset: 0x30
	size_t			flags;				// Offset: 0x34
} scheduler_task_def_regs_t;
#pragma pack(pop)

#endif