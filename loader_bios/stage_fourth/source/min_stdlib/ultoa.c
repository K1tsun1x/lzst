#include <min_stdlib.h>

char* __cdecl ultoa(unsigned long value, char* str, int radix) {
	if (radix < 2 || radix > 36 || !str) return NULL;

	char* p = str;
	if (!value) {
		*p++ = '0';
		*p = '\0';
		return str;
	}

	while (value > 0) {
		unsigned long remainder = value % radix;
		if (remainder < 10) *p++ = '0' + (char)remainder;
		else *p++ = 'A' + (char)(remainder - 10);
		value /= radix;
	}

	*p = '\0';
	char* start = str;
	char* end = p - 1;
	while (start < end) {
		char tmp = *start;
		*start++ = *end;
		*end-- = tmp;
	}

	return str;
}