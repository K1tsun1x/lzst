#include <tty.h>

void tty_print_ustring(const char32_t* s, uint8_t r, uint8_t g, uint8_t b) {
	for (; *s;) tty_putchar(*s++, r, g, b);
}