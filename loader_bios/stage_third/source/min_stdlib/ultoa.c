#include <min_stdlib.h>

extern const char __DIGIT_CHARS[NUM_DIGIT_CHARS];

char* ultoa(unsigned long n, char* buffer, int radix) {
	if (!buffer || radix < 2 || radix > NUM_DIGIT_CHARS) return NULL;

	size_t len = 1;
	unsigned long tmp = n;
	for (; tmp /= radix;) ++len;

	char* cur = &buffer[len];
	*cur-- = '\0';
	for (; cur >= buffer; ) {
		*cur-- = __DIGIT_CHARS[n % radix];
		n /= radix;
	}

	return buffer;
}