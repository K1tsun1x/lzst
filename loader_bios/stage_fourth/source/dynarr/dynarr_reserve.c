#include <dynarr/dynarr.h>

void* dynarr_reserve(void* dynarr_mem, size_t capacity) {
	if (!dynarr_mem) return NULL;

	capacity = ALIGN_UP_P2(capacity, DYNARR_START_CAPACITY);

	dynarr_header_t* header = DYNARR_HEADER_FROM_MEM(dynarr_mem);
	if (header->elem_size > SIZE_MAX / capacity) return NULL;

	const size_t data_size = header->elem_size * capacity;
	if (data_size > SIZE_MAX - sizeof(dynarr_header_t)) return NULL;

	const size_t total_size = sizeof(dynarr_header_t) + data_size;
	dynarr_header_t* tmp = (dynarr_header_t*)pmm_reallocate_memory(header, total_size, 0);
	if (!tmp) return NULL;

	header = tmp;
	header->capacity = capacity;

	return (void*)DYNARR_MEM_FROM_HEADER(header);
}