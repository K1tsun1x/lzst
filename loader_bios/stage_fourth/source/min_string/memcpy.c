#include <min_string.h>

void* __cdecl memcpy(void* dest, const void* src, size_t count) {
	if (!count || dest == src) return dest;

	uint8_t* d = (uint8_t*)dest;
	uint8_t* s = CONST_CAST(uint8_t*, ((const uint8_t*)src));
	while (count--) *d++ = *s++;
	return dest;
}