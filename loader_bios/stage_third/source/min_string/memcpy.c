#include <min_string.h>

void* memcpy(void* d, const void* s, size_t n) {
	if (!n) return d;

	uint8_t* d1 = (uint8_t*)d;
	uint8_t* s1 = CONST_CAST(uint8_t*, s);
	
	const size_t size = sizeof(size_t);
	const size_t mask = size - 1;
	for (; n > 0 && (((size_t)d1) | ((size_t)s1)) & mask; --n) *d1++ = *s1++;

	for (; n >= size; n -= size) {
		size_t tmp = *(const size_t*)s1;
		*(size_t*)d1 = tmp;
		d1 += size;
		s1 += size;
	}

	for (; n > 0; --n) *d1++ = *s1++;
	return d;
}