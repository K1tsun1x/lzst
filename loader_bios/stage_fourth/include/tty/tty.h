#pragma once
#ifndef __TTY_H
#define __TTY_H

#include <gfx/gfx.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define TTY_TAB_WIDTH			4

void tty_scroll_down(
	size_t num_lines,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

void tty_scroll_up(
	size_t num_lines,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

int tty_putchar(
	int c,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
);

int tty_prints(
	const char* s,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
);

int tty_puts(
	const char* s,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
);

int tty_printf(
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg,
	const char* s, ...
);

int tty_vprintf(
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg,
	const char* s, va_list args
);

void tty_init(
	size_t num_chars_per_line, size_t num_lines,
	size_t spacing_x, size_t spacing_y
	// uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

static inline int tty_prints_negative(const char* s) {
	return tty_printf(
		GFX_UNPACK_COLOR(GFX_COLOR_LIGHT_RED),
		GFX_UNPACK_COLOR(GFX_COLOR_BLACK),
		false,
		"\x1b[91m%s\x1b[0m", s
	);
}

static inline int tty_prints_positive(const char* s) {
	return tty_printf(
		GFX_UNPACK_COLOR(GFX_COLOR_LIGHT_GREEN),
		GFX_UNPACK_COLOR(GFX_COLOR_BLACK),
		false,
		"\x1b[92m%s\x1b[0m", s
	);
}

static inline int tty_prints_neutral(const char* s) {
	return tty_printf(
		GFX_UNPACK_COLOR(GFX_COLOR_LIGHT_RED),
		GFX_UNPACK_COLOR(GFX_COLOR_BLACK),
		false,
		"\x1b[93m%s\x1b[0m", s
	);
}

// extern uint8_t TTY_BKG_RED;
// extern uint8_t TTY_BKG_GREEN;
// extern uint8_t TTY_BKG_BLUE;

#endif