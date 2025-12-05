#include <dynarr/dynarr.h>

void* dynarr_create(size_t elem_size, size_t num_elems) {
	if (!elem_size) elem_size = 1;

	// FIXME: ALIGN_UP_P2 must be replaced
	size_t capacity = ALIGN_UP_P2(num_elems, DYNARR_START_CAPACITY);
	if (capacity < DYNARR_START_CAPACITY) capacity = DYNARR_START_CAPACITY;
	if (elem_size > SIZE_MAX / capacity) return NULL;

	const size_t data_size = elem_size * capacity;
	if (data_size > SIZE_MAX - sizeof(dynarr_header_t)) return NULL;

	const size_t total_size = sizeof(dynarr_header_t) + data_size;
	dynarr_header_t* header = (dynarr_header_t*)pmm_allocate_memory(total_size, 0);
	if (!header) return NULL;

	header->elem_size = elem_size;
	header->num_elems = num_elems;
	header->capacity = capacity;
	return (void*)DYNARR_MEM_FROM_HEADER(header);
}