#pragma once
#ifndef __TTY_H
#define __TTY_H

#include <stdarg.h>
#include "gfx.h"
#include "min_string.h"
#include "typedefs.h"
#include "min_stdlib.h"

#define TTY_TAB_WIDTH			4

void tty_init(
	size_t num_chars_per_line, size_t num_lines,
	size_t spacing_x, size_t spacing_y,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

int tty_putchar(int c, uint8_t r, uint8_t g, uint8_t b);
int tty_print_string(const char* s, uint8_t r, uint8_t g, uint8_t b);
int tty_printf(const char* s, ...);
int tty_vprintf(const char* s, va_list a);

static inline int tty_puts(const char* s, uint8_t r, uint8_t g, uint8_t b) {
	int res = tty_print_string(s, r, g, b) + 1;
	tty_putchar('\n', r, g, b);
	return res;
}

void tty_scroll_down_once(void);
void tty_scroll_up_once(void);

static inline void tty_scroll_down(size_t num_lines) {
	for (size_t i = 0; i < num_lines; i++) tty_scroll_down_once();
}

static inline void tty_scroll_up(size_t num_lines) {
	for (size_t i = 0; i < num_lines; i++) tty_scroll_up_once();
}

#endif