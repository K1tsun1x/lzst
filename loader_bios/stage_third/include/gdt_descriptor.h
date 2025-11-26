#pragma once
#ifndef __GDT_DESCRIPTOR_H
#define __GDT_DESCRIPTOR_H

#include "typedefs.h"

#define GDT_DESCRIPTOR_STATIC(size, offset)	{\
	(uint16_t)((size) - 1), \
	(uintptr_t)(offset) \
}

#pragma pack(push, 1)
typedef struct _gdt_descriptor32_t {
	uint16_t			size;
	uint32_t			offset;
} gdt_descriptor32_t, *pgdt_descriptor32_t;

typedef struct _gdt_descriptor64_t {
	uint16_t			size;
	uint64_t			offset;
} gdt_descriptor64_t, *pgdt_descriptor64_t;
#pragma pack(pop)

#endif