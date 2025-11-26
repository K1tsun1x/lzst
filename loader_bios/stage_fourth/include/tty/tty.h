#pragma once
#ifndef __TTY_H
#define __TTY_H

#include <gfx/gfx.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define TTY_TAB_WIDTH			4

void tty_scroll_down_color(
	size_t num_lines,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

void tty_scroll_up_color(
	size_t num_lines,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

int tty_putchar_color(
	int c,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

int tty_prints_color(
	const char* s,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

int tty_puts_color(
	const char* s,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

void tty_scroll_down(size_t num_lines);
void tty_scroll_up(size_t num_lines);
int tty_putchar(int c);
int tty_prints(const char* s);
int tty_puts(const char* s);

/**
 * Template: %(#)[%duxobcs]
 * - %% = %
 * - %d = ptrdiff_t (radix = 10)
 * - %u = size_t (radix = 10)
 * - %x = size_t (radix = 16)
 * - %o = size_t (radix = 8)
 * - %b = size_t (radix = 2)
 * - %s = char*
 * - %c = char
 * 
 * \x1b[attribute1;attribute2...m = set attribute
 * 0 - default color
 * Foreground colors:
 * - 30: black, 31: red, 32: green, 33: brown,
 * - 34: blue, 35: magenta, 36: cyan, 37: dark gray,
 * - 90: light gray, 91: light red, 92: light green, 93: yellow,
 * - 94: light blue, 95: light magenta, 96: light cyan, 97: white
 * 
 * Background colors:
 * - 90: black, 91: red, 92: green, 93: brown,
 * - 94: blue, 95: magenta, 96: cyan, 97: dark gray,
 * - 100: light gray, 101: light red, 102: light green, 103: yellow,
 * - 104: light blue, 105: light magenta, 106: light cyan, 107: white
 */
int tty_printf(const char* s, ...);

/**
 * Template: %(#)[%duxobcs]
 * - %% = %
 * - %d = ptrdiff_t (radix = 10)
 * - %u = size_t (radix = 10)
 * - %x = size_t (radix = 16)
 * - %o = size_t (radix = 8)
 * - %b = size_t (radix = 2)
 * - %s = char*
 * - %c = char
 * 
 * \x1b[attribute1;attribute2...m = set attribute
 * 0 - default color
 * Foreground colors:
 * - 30: black, 31: red, 32: green, 33: brown,
 * - 34: blue, 35: magenta, 36: cyan, 37: dark gray,
 * - 90: light gray, 91: light red, 92: light green, 93: yellow,
 * - 94: light blue, 95: light magenta, 96: light cyan, 97: white
 * 
 * Background colors:
 * - 90: black, 91: red, 92: green, 93: brown,
 * - 94: blue, 95: magenta, 96: cyan, 97: dark gray,
 * - 100: light gray, 101: light red, 102: light green, 103: yellow,
 * - 104: light blue, 105: light magenta, 106: light cyan, 107: white
 */
int tty_vprintf(const char* s, va_list args);

void tty_init(
	size_t num_chars_per_line, size_t num_lines,
	size_t spacing_x, size_t spacing_y,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

static inline int tty_prints_negative(const char* s) {
	return tty_printf("\x1b[91m%s\x1b[0m", s);
}

static inline int tty_prints_positive(const char* s) {
	return tty_printf("\x1b[92m%s\x1b[0m", s);
}

static inline int tty_prints_neutral(const char* s) {
	return tty_printf("\x1b[93m%s\x1b[0m", s);
}

#endif