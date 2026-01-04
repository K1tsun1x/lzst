#pragma once
#ifndef __SW_INT_TTY_H
#define __SW_INT_TTY_H

#include <tty/tty.h>
#include <vmm/vmm.h>

#define IDT_SW_INT_TTY_VECTOR						0x41
#define SW_INT_TTY									1

/*
	In:
	`eax`: 0
	`cl`: char
*/
#define SW_INT_TTY_FUNCTION_PUTCHAR					0

#define SW_INT_TTY_FUNCTION_PUTS					1

#endif