#include <string.h>

void* __cdecl memset(void* dest, int c, size_t n) {
	if (!n) return dest;

	uint8_t* cur = (uint8_t*)dest;
	/*
	ULONG_PTR pattern = 0;
	for (SIZE_T i = 0; i < sizeof(ULONG_PTR); i++) pattern = (pattern << 8) | Value;

	while (((ULONG_PTR)cur & (sizeof(ULONG_PTR) - 1)) && Length) {
		*cur++ = Value;
		--Length;
	}

	PULONG_PTR curWord = (PULONG_PTR)cur;
	while (Length >= sizeof(ULONG_PTR)) {
		*curWord++ = pattern;
		Length -= sizeof(ULONG_PTR);
	}

	cur = (PUCHAR)curWord;
	*/
	while (n--) *cur++ = (uint8_t)c;
	return dest;
}