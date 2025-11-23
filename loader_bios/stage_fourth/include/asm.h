#pragma once
#ifndef __ASM_H
#define __ASM_H

#include "typedefs.h"

#ifdef _MSC_VER
#include <immintrin.h>
#endif

static inline void xgetbv(uint32_t index, uint32_t* eax, uint32_t* edx) {
	uint32_t ceax;
	uint32_t cedx;
#ifdef _MSC_VER
	uint64_t tmp = _xgetbv(index);
	ceax = (uint32_t)tmp & 0xffffffff;
	cedx = (uint32_t)(tmp >> 32);
#elif defined(__GNUC__) || defined(__clang__)
	__asm__ __volatile__("xgetbv":"=a"(ceax), "=d"(cedx):"c"(index));
#endif
	if (eax) *eax = ceax;
	if (edx) *edx = cedx;
}

static inline void xsetbv(uint32_t index, uint32_t eax, uint32_t edx) {
#ifdef _MSC_VER
	uint64_t tmp = ((uint64_t)edx << 32) | (uint64_t)eax;
	_xsetbv(index, tmp);
#elif defined(__GNUC__) || defined(__clang__)
	__asm__ __volatile__("xsetbv"::"a"(eax), "c"(index), "d"(edx));
#endif
}

#endif