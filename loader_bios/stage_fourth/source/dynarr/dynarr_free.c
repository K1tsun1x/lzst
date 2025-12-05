#include <dynarr/dynarr.h>

void dynarr_free(void* dynarr_mem) {
	if (!dynarr_mem) return;
	
	dynarr_header_t* header = DYNARR_HEADER_FROM_MEM(dynarr_mem);
	pmm_free_memory(header);
}