#pragma once
#ifndef __ALIGN_H
#define __ALIGN_H

#include "typedefs.h"

#define ALIGN_UP_P2(v, a)			(((v) + (a) - 1) & ~((a) - 1))
#define ALIGN_DOWN_P2(v, a)			((v) & ~((a) - 1))

static inline uint32_t align_down_u32(uint32_t value, uint32_t alignment) {
	uint32_t remainder = value % alignment;
	if (!remainder) return value;
	return value - remainder;
}

static inline uint32_t align_up_u32(uint32_t value, uint32_t alignment) {
	uint32_t remainder = value % alignment;
	if (!remainder) return value;
	return value + (alignment - remainder);
}

static inline uint64_t align_down_u64(uint64_t value, uint64_t alignment) {
	uint64_t remainder = value % alignment;
	if (!remainder) return value;
	return value - remainder;
}

static inline uint64_t align_up_u64(uint64_t value, uint64_t alignment) {
	uint64_t remainder = value % alignment;
	if (!remainder) return value;
	return value + (alignment - remainder);
}

#endif