#include <tty.h>

int tty_print_string(const char* s, uint8_t r, uint8_t g, uint8_t b) {
	int printed_chars = 0;
	for (; *s;) {
		tty_putchar((char32_t)*s++, r, g, b);
		++printed_chars;
	}

	return printed_chars;
}