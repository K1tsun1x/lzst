#include <dynarr/dynarr.h>

void dynarr_free(void* dynarr_mem) {
	dynarr_t* dynarr = ((dynarr_t*)dynarr_mem) - 1;
	pmm_free_memory(dynarr);
}