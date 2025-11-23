#include <tty.h>

int tty_printf(const char* s, ...) {
	va_list args;
	va_start(args, s);
	int res = tty_vprintf(s, args);
	va_end(args);

	return res;
}