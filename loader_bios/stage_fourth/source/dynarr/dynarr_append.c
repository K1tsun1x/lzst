#include <dynarr/dynarr.h>

void* dynarr_append(void* dynarr_mem, const void* elem) {
	if (!dynarr_mem) return NULL;

	dynarr_header_t* header = DYNARR_HEADER_FROM_MEM(dynarr_mem);
	if (header->num_elems >= header->capacity) {
		dynarr_mem = dynarr_reserve(dynarr_mem, header->capacity * 2);
		if (!dynarr_mem) return NULL;
		
		header = DYNARR_HEADER_FROM_MEM(dynarr_mem);
	}

	void* res = (void*)DYNARR_MEM_FROM_HEADER(header);
	memcpy(
		&((uint8_t*)res)[header->elem_size * header->num_elems],
		elem,
		header->elem_size
	);

	header->num_elems += 1;
	return (void*)res;
}