#include <dynarr/dynarr.h>

void* dynarr_realloc(void* dynarr_old, size_t size) {
	dynarr_t* dynarr = ((dynarr_t*)dynarr_old) - 1;
	return pmm_reallocate_memory(dynarr, size, 0);
}