#include <min_string.h>

size_t strlen(const char* s) {
	const char* p = s;
	for (; *p != '\0';) ++p;
	return (size_t)(p - s);
}