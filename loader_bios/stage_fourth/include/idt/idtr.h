#pragma once
#ifndef __IDTR_H
#define __IDTR_H

#include <typedefs.h>

#define IDTR_STATIC(size, offset)		{\
	(uint16_t)((size) - 1), \
	(offset) \
}

#pragma pack(push, 1)
typedef struct _idtr32_t {
	uint16_t			size;
	uint32_t			offset;
} idtr32_t;

typedef struct _idtr64_t {
	uint16_t			size;
	uint64_t			offset;
} idtr64_t;
#pragma pack(pop)

EXTERN_C void LOADERCALL idtr_load(const void* idtr);

#endif