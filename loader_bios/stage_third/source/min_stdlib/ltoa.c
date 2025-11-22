#include <min_stdlib.h>

extern const char __DIGIT_CHARS[NUM_DIGIT_CHARS];

char* ltoa(long n, char* buffer, int radix) {
	if (!buffer || radix < 2 || radix > NUM_DIGIT_CHARS) return NULL;

	char* res = buffer;
	unsigned long u;
	if (n < 0) {
		u = (unsigned long)(-(n + 1)) + 1;
		*buffer++ = '-';
	}
	else u = (unsigned long)n;

	size_t len = 1;
	unsigned long tmp = u;
	for (; tmp /= radix;) ++len;

	char* cur = &buffer[len];
	*cur-- = '\0';
	for (; cur >= buffer; ) {
		*cur-- = __DIGIT_CHARS[u % radix];
		u /= radix;
	}

	return res;
}