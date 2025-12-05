#include <dynarr/dynarr.h>

void* dynarr_insert(void* dynarr_mem, size_t index, const void* mem) {
	if (!dynarr_mem) return NULL;

	dynarr_header_t* header = DYNARR_HEADER_FROM_MEM(dynarr_mem);
	if (index > header->num_elems) return NULL;

	dynarr_mem = dynarr_reserve(dynarr_mem, header->num_elems + 1);
	if (!dynarr_mem) return NULL;

	header = DYNARR_HEADER_FROM_MEM(dynarr_mem);
	uint8_t* src = ((uint8_t*)dynarr_mem) + index * header->elem_size;
	uint8_t* dst = src + header->elem_size;
	memmove(dst, src, (header->num_elems - index - 1) * header->elem_size);
	memcpy(
		((uint8_t*)dynarr_mem) + index * header->elem_size,
		mem,
		header->elem_size
	);

	return dynarr_mem;
}