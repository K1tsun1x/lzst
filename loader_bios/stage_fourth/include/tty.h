#pragma once
#ifndef __TTY_H
#define __TTY_H

#include "gfx.h"
#include "min_string.h"

#define TTY_TAB_WIDTH			4

void tty_init(
	size_t num_chars_per_line, size_t num_lines,
	size_t spacing_x, size_t spacing_y,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
);

void tty_putchar(char32_t c, uint8_t r, uint8_t g, uint8_t b);
void tty_print_string(const char* s, uint8_t r, uint8_t g, uint8_t b);
void tty_print_ustring(const char32_t* s, uint8_t r, uint8_t g, uint8_t b);

void tty_scroll_down_once(void);
void tty_scroll_up_once(void);

static inline void tty_scroll_down(size_t num_lines) {
	for (size_t i = 0; i < num_lines; i++) tty_scroll_down_once();
}

static inline void tty_scroll_up(size_t num_lines) {
	for (size_t i = 0; i < num_lines; i++) tty_scroll_up_once();
}

#endif