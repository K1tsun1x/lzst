#include <cpuid486/cpuid486.h>

EXTERN_C void LOADERCALL __cpuid486_call(
	uint32_t leaf,
	uint32_t sub_leaf,
	uint32_t* eax,
	uint32_t* ecx,
	uint32_t* edx,
	uint32_t* ebx
);

void cpuid486(
	uint32_t leaf,
	uint32_t sub_leaf,
	uint32_t* eax,
	uint32_t* ecx,
	uint32_t* edx,
	uint32_t* ebx
) {
	return __cpuid486_call(leaf, sub_leaf, eax, ecx, edx, ebx);
}