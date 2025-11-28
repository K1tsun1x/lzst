#include <dynarr/dynarr.h>

void* dynarr_append(void* dynarr_mem, const void* elem) {
	if (!dynarr_mem) return NULL;

	dynarr_t* dynarr = ((dynarr_t*)dynarr_mem) - 1;
	if (dynarr->num_elems >= dynarr->capacity) {
		const size_t capacity = dynarr->capacity + DYNARR_START_CAPACITY;
		dynarr_t* tmp = (dynarr_t*)pmm_reallocate_memory(dynarr, sizeof(dynarr_t) + dynarr->elem_size * capacity, 0);
		if (!tmp) return NULL;

		dynarr = tmp;
		dynarr->capacity = capacity;
	}

	uint8_t* tmp8 = (uint8_t*)(dynarr + 1);
	memcpy(&tmp8[dynarr->elem_size * dynarr->num_elems], elem, dynarr->elem_size);	
	dynarr->num_elems += 1;
	return (void*)(dynarr + 1);
}