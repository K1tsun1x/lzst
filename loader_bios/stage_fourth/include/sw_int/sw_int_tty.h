#pragma once
#ifndef __SW_INT_TTY_H
#define __SW_INT_TTY_H

#include <tty/tty.h>
#include <vmm/vmm.h>

#define IDT_SW_INT_TTY_VECTOR						0x41
#define SW_INT_TTY									1

#define SW_INT_TTY_MAX_STR_LEN						VMM_PAGE_SIZE * 8

/*
	In:
	`eax`: 0
	`cl`: char
	Out:
	`eax`: status
*/
#define SW_INT_TTY_FUNCTION_PUTCHAR					0

/*
	In:
	`eax`: 1
	`ecx`: str address
	Out:
	`eax`: status
*/
#define SW_INT_TTY_FUNCTION_PUTS					1

#endif