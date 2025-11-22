#include <tty.h>

void tty_print_string(const char* s, uint8_t r, uint8_t g, uint8_t b) {
	for (; *s;) tty_putchar((char32_t)*s++, r, g, b);
}