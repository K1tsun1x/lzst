#pragma once
#ifndef __GDR_DESCRIPTOR_H
#define __GDR_DESCRIPTOR_H

#include <typedefs.h>

#define GDTR_STATIC(size, offset)	{\
	(uint16_t)((size) - 1), \
	(offset) \
}

#pragma pack(push, 1)
typedef struct _gdtr32_t {
	uint16_t			size;
	uint32_t			offset;
} gdtr32_t;

typedef struct _gdtr64_t {
	uint16_t			size;
	uint64_t			offset;
} gdtr64_t;
#pragma pack(pop)

/**
 * @warning gdt[0] = empty, gdt[1] = code, gdt[2] = data(!)
 */
EXTERN_C void LOADERCALL gdtr_load(const void* gdtr);

#endif