#pragma once
#ifndef __CPUID486_H
#define __CPUID486_H

#include "cpuid486_ecx_feature.h"
#include "cpuid486_edx_feature.h"

EXTERN_C bool LOADERCALL cpuid486_present(void);

/**
 * @param leaf EAX
 * @param sub_leaf ECX
 */
void cpuid486(
	uint32_t leaf,
	uint32_t sub_leaf,
	uint32_t* eax,
	uint32_t* ecx,
	uint32_t* edx,
	uint32_t* ebx
);

void cpuid486_get_features(uint32_t* ecx, uint32_t* edx);

#endif