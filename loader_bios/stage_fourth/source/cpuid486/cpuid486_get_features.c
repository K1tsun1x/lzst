#include <cpuid486.h>

uint32_t cpuid486_get_features(void) {
	uint32_t edx;
	cpuid486(1, 0, NULL, NULL, &edx, NULL);
	return edx;
}