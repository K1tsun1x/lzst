#include <string.h>

#include <tty/tty.h>
void* __cdecl memcpy(void* dest, const void* src, size_t count) {
	if (!count || dest == src) return dest;

	for (size_t i = 0; i < count; i++) ((uint8_t*)dest)[i] = ((uint8_t*)src)[i];
	return dest;
}