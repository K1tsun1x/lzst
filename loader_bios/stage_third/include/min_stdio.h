#pragma once
#ifndef __MIN_STDIO_H
#define __MIN_STDIO_H

#include <stdarg.h>
#include "color.h"
#include "min_stdlib.h"
#include "min_string.h"

#define TTY_WIDTH						80
#define TTY_HEIGHT						25
#define TTY_LINE_SIZE					(TTY_WIDTH << 1)
#define TTY_LEN							(TTY_WIDTH * TTY_HEIGHT)
#define TTY_SIZE						(TTY_LEN << 1)
#define TTY_TAB_WIDTH					4

void min_stdio_init(void);

/**
 * @return On success, returns the written character.
 */
int put_colored_char(int c, uint8_t color);

/**
 * @return On success, returns the written character.
 */
static inline int putchar(int c) {
	return put_colored_char(c, COLOR_LIGHT_GRAY);
}

int puts(const char* s);

/**
 * Minimal printf implementation
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
int __cdecl printf(const char* s, ...);

/**
 * Minimal vprintf implementation
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
 * - 40: black, 41: red, 42: green, 43: brown,
 * - 44: blue, 45: magenta, 46: cyan, 47: dark gray,
 * - 100: light gray, 101: light red, 102: light green, 103: yellow,
 * - 104: light blue, 105: light magenta, 106: light cyan, 107: white
 */
int __cdecl vprintf(const char* s, va_list a);

#endif