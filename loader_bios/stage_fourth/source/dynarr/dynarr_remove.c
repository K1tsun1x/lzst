#include <dynarr/dynarr.h>

void* dynarr_remove(void* dynarr_mem, size_t index) {
	if (!dynarr_mem) return dynarr_mem;

	dynarr_header_t* header = DYNARR_HEADER_FROM_MEM(dynarr_mem);
	if (index >= header->num_elems) return dynarr_mem;

	uint8_t* data = (uint8_t*)dynarr_mem;
	memmove(
		data + index * header->elem_size,
		data + (index + 1) * header->elem_size,
		(header->num_elems - index - 1) * header->elem_size
	);

	header->num_elems -= 1;
	size_t new_num_elems = header->num_elems;
	if (header->capacity > DYNARR_START_CAPACITY && !((new_num_elems + 1) % DYNARR_START_CAPACITY)) {
		size_t new_capacity = header->capacity - DYNARR_START_CAPACITY;
		if (header->elem_size > SIZE_MAX / new_capacity) return dynarr_mem;

		const size_t data_size = header->elem_size * new_capacity;
		if (data_size > SIZE_MAX - sizeof(dynarr_header_t)) return dynarr_mem;

		const size_t total_size = data_size + sizeof(dynarr_header_t);
		dynarr_header_t* new_header = (dynarr_header_t*)pmm_reallocate_memory(header, total_size, 0);
		if (new_header) {
			new_header->capacity = new_capacity;
			dynarr_mem = (void*)DYNARR_MEM_FROM_HEADER(new_header);
		}
	}

	return dynarr_mem;
}