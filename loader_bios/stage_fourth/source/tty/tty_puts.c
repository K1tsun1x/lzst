#include <tty/tty.h>

int tty_puts(
	const char* s,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
) {
	int printed_chars = tty_prints(s, frg_r, frg_g, frg_b, bkg_r, bkg_g, bkg_b, fill_bkg);
	tty_putchar('\n', frg_r, frg_g, frg_b, bkg_r, bkg_g, bkg_b, fill_bkg);
	return printed_chars + 1;
}