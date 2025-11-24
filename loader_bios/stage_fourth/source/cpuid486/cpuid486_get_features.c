#include <cpuid486/cpuid486.h>

void cpuid486_get_features(uint32_t* ecx, uint32_t* edx) {
	uint32_t cecx;
	uint32_t cedx;
	cpuid486(1, 0, NULL, &cecx, &cedx, NULL);
	
	if (ecx) *ecx = cecx;
	if (edx) *edx = cedx;
}