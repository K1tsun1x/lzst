#include <min_string.h>

size_t __cdecl strlen(const char* s) {
	if (!s) return 0;

	size_t length = 0;
	while (s[length] != '\0') ++length;
	return length;
}