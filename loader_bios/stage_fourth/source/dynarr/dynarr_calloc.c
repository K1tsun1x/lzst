#include <dynarr/dynarr.h>

void* dynarr_calloc(size_t size, size_t count) {
	return dynarr_alloc(size * count);
}