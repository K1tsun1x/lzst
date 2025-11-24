#include <stdlib.h>

char* __cdecl ltoa(long value, char* str, int radix) {
	if (radix < 2 || radix > 36 || !str) return NULL;

	char* p = str;
	unsigned long uvalue;
	if (value < 0) {
		*p++ = '-';
		uvalue = (unsigned long)(-(unsigned long)value);
	}
	else uvalue = (unsigned long)value;

	if (!ultoa(uvalue, p, radix)) return NULL;
	return str;
}