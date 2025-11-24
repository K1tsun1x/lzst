#pragma once
#ifndef __CPUID486_ECX_FEATURE_H
#define __CPUID486_ECX_FEATURE_H

#include <typedefs.h>

typedef enum _cpuid486_ecx_feature_t ENUM_TYPE(uint32_t) {
	CPUID486_ECX_FEATURE_SSE3 =		1 << 0,
	// ...
	CPUID486_ECX_FEATURE_SSSE =		1 << 9,
	// ...
	CPUID486_ECX_FEATURE_SSE4_1 =	1 << 19,
	CPUID486_ECX_FEATURE_SSE4_2 =	1 << 20,
	// ...
	CPUID486_ECX_FEATURE_OSXSAVE =	1 << 27,
	CPUID486_ECX_FEATURE_AVX =		1 << 28
	// ...
} cpuid486_ecx_feature_t;

#endif