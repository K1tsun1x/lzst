#pragma once
#ifndef __ISR_DATA_H
#define __ISR_DATA_H

#include <typedefs.h>

#pragma pack(push, 1)
typedef struct _isr_data_t {
	size_t	gs;					// Offset: 0x00
	size_t	fs;					// Offset: 0x04
	size_t	es;					// Offset: 0x08
	size_t	ds;					// Offset: 0x0c
	size_t	di;					// Offset: 0x10
	size_t	si;					// Offset: 0x14
	size_t	bp;					// Offset: 0x18
	size_t	sp;					// Offset: 0x1c
	size_t	bx;					// Offset: 0x20
	size_t	dx;					// Offset: 0x24
	size_t	cx;					// Offset: 0x28
	size_t	ax;					// Offset: 0x2c
	size_t	int_index;			// Offset: 0x30
	size_t	error_code;			// Offset: 0x34
	size_t	ip;					// Offset: 0x38
	size_t	cs;					// Offset: 0x3c
	size_t	flags;				// Offset: 0x40
} isr_data_t;
#pragma pack(pop)

#endif