#include <dynarr/dynarr.h>

void* dynarr_alloc(size_t size) {
	dynarr_t* dynarr = (dynarr_t*)pmm_allocate_memory(size, 0);
	if (!dynarr) return NULL;

	return (void*)(dynarr + 1);
}