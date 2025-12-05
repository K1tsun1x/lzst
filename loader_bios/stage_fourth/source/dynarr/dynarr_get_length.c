#include <dynarr/dynarr.h>

size_t dynarr_get_length(void* dynarr_mem) {
	if (!dynarr_mem) return 0;
	return DYNARR_HEADER_FROM_MEM(dynarr_mem)->num_elems;
}