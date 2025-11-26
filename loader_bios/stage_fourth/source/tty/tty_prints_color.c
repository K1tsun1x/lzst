#include <tty/tty.h>

int tty_prints_color(
	const char* s,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
) {
	int printed_chars = 0;
	for (; *s;) {
		tty_putchar_color((int)(*s++), frg_r, frg_g, frg_b, bkg_r, bkg_g, bkg_b);
		++printed_chars;
	}

	return printed_chars;
}