#include <string.h>

void* __cdecl memmove(void* dest, const void* src, size_t count) {
	if (dest == src || !count) return dest;

	uint8_t* d = (uint8_t*)dest;
	uint8_t* s = CONST_CAST(uint8_t*, (const uint8_t*)src);
	if (d > s && d < s + count) {
		d += count;
		s += count;
		while (count--) *(--d) = *(--s);
	}
	else while (count--) *d++ = *s++;
	return dest;
}