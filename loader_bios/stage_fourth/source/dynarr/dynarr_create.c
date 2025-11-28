#include <dynarr/dynarr.h>

void* dynarr_create(size_t elem_size, size_t num_elems) {
	size_t capacity = ALIGN_UP_P2(num_elems, DYNARR_START_CAPACITY);
	dynarr_t* dynarr = (dynarr_t*)pmm_allocate_memory(sizeof(dynarr_t) + elem_size * capacity, 0);
	if (!dynarr) return dynarr;

	dynarr->elem_size = elem_size;
	dynarr->num_elems = num_elems;
	dynarr->capacity = capacity;
	return (void*)(dynarr + 1);
}