#include <tty/tty.h>

int tty_printf(
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg,
	const char* s, ...
) {
	va_list args;
	va_start(args, s);
	int res = tty_vprintf(
		frg_r, frg_g, frg_b,
		bkg_r, bkg_g, bkg_b,
		fill_bkg,
		s, args
	);
	
	va_end(args);
	return res;
}