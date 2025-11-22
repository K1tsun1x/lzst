#include <min_stdio.h>

extern uint16_t __min_stdio_offset;

EXTERN_C void LOADERCALL __min_stdio_write_word(uint16_t offset, uint16_t value);
EXTERN_C uint16_t LOADERCALL __min_stdio_read_word(uint16_t offset);

int putchar(int c) {
	if (__min_stdio_offset >= TTY_SIZE) {
		__min_stdio_offset = TTY_SIZE - TTY_LINE_SIZE;

		size_t tmp = TTY_LINE_SIZE;
		const size_t lastLineOffset = TTY_SIZE - TTY_LINE_SIZE;
		for (; tmp < lastLineOffset; tmp += 2) __min_stdio_write_word(
			tmp - TTY_LINE_SIZE,
			__min_stdio_read_word(tmp)
		);

		const uint16_t attribute = COLOR_LIGHT_GRAY << 8;
		for (; tmp < TTY_SIZE; tmp += 2) __min_stdio_write_word(
			tmp,
			attribute | ' '
		);
	}

	if (c == '\r') __min_stdio_offset -= __min_stdio_offset % TTY_LINE_SIZE;
	else if (
		c == '\n'
	) __min_stdio_offset = __min_stdio_offset - (__min_stdio_offset % TTY_LINE_SIZE) + TTY_LINE_SIZE;
	else if (
		c == '\b' && __min_stdio_offset > 1
	) {
		__min_stdio_offset -= 2;
		// __min_stdio_write_word(__min_stdio_offset, (uint16_t)((COLOR_LIGHT_GRAY  << 8) | ' '));
	}
	else if (c == '\t') {
		size_t cur_pos_in_line = (__min_stdio_offset % TTY_LINE_SIZE) >> 1;
		const size_t spaces = TTY_TAB_WIDTH - (cur_pos_in_line % TTY_TAB_WIDTH);
		for (size_t i = 0; i < spaces; i++) putchar(' ');
	}
	else if (
		c == '\v'
	) __min_stdio_offset = __min_stdio_offset - (__min_stdio_offset % TTY_LINE_SIZE) + TTY_TAB_WIDTH * TTY_LINE_SIZE;
	else if (c == '\a') __min_stdio_write_word(__min_stdio_offset, __min_stdio_read_word(__min_stdio_offset) ^ 0xff00);
	else {
		uint16_t w = __min_stdio_read_word(__min_stdio_offset);
		uint16_t attribute = w & 0xff00;
		__min_stdio_write_word(__min_stdio_offset, attribute | (uint16_t)(c));
		__min_stdio_offset += 2;
	}

	return c;
}