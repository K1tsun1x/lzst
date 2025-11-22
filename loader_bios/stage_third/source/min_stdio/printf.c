#include <min_stdio.h>

int __cdecl printf(const char* s, ...) {
	va_list ap;
	va_start(ap, s);
	int res = vprintf(s, ap);
	va_end(ap);
	return res;
}