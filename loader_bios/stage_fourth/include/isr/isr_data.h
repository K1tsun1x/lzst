#pragma once
#ifndef __ISR_DATA_H
#define __ISR_DATA_H

#include <typedefs.h>

#pragma pack(push, 1)
typedef struct _isr_data_t {
	size_t	gs;
	size_t	fs;
	size_t	es;
	size_t	ds;
	size_t	di;
	size_t	si;
	size_t	bp;
	size_t	sp;
	size_t	bx;
	size_t	dx;
	size_t	cx;
	size_t	ax;
	size_t	int_index;
	size_t	error_code;
	size_t	ip;
	size_t	cs;
	size_t	flags;
} isr_data_t;
#pragma pack(pop)

#endif