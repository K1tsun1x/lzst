#include <min_stdio.h>

int puts(const char* s) {
	for (; *s != '\0';) putchar(*s++);
	return putchar('\n');
}