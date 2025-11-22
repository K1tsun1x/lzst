#include <tty.h>

extern video_mode_t GFX_VIDEO_MODE;

extern size_t TTY_NUM_CHARS_PER_LINE;
extern size_t TTY_NUM_LINES;
extern size_t TTY_TARGET_GLYPH_WIDTH;
extern size_t TTY_TARGET_GLYPH_HEIGHT;
extern size_t TTY_SPACING_X;
extern size_t TTY_SPACING_Y;
extern size_t TTY_CELL_X;
extern size_t TTY_CELL_Y;

extern size_t TTY_POSITION;
extern size_t TTY_MAX_POSITION;

extern uint8_t TTY_BKG_RED;
extern uint8_t TTY_BKG_GREEN;
extern uint8_t TTY_BKG_BLUE;

void tty_putchar(char32_t c, uint8_t r, uint8_t g, uint8_t b) {
	if (TTY_POSITION > TTY_MAX_POSITION) {
		tty_scroll_down_once();
		TTY_POSITION = (TTY_NUM_LINES - 1) * TTY_NUM_CHARS_PER_LINE;
	}

	if (c == U'\r') {
		const size_t pos_in_line = TTY_POSITION % TTY_NUM_CHARS_PER_LINE;
		TTY_POSITION -= pos_in_line;
	}
	else if (c == U'\n') {
		const size_t line = TTY_POSITION / TTY_NUM_CHARS_PER_LINE + 1;
		TTY_POSITION = line * TTY_NUM_CHARS_PER_LINE;
	}
	else if (c == U'\t') {
		const size_t pos_in_line = TTY_POSITION % TTY_NUM_CHARS_PER_LINE;
		const size_t spaces = TTY_TAB_WIDTH - (pos_in_line % TTY_TAB_WIDTH);
		for (size_t i = 0; i < spaces; i++) tty_putchar(U' ', r, g, b);
	}
	else if (c == U'\v') for (size_t i = 0; i < TTY_TAB_WIDTH; i++) tty_putchar(U'\n', r, g, b);
	else if (c == U'\b') {
		if (TTY_POSITION) --TTY_POSITION;
	}
	else {
		const size_t y = TTY_POSITION / TTY_NUM_CHARS_PER_LINE * TTY_CELL_Y;
		const size_t x = (TTY_POSITION % TTY_NUM_CHARS_PER_LINE) * TTY_CELL_X;

		gfx_draw_glyph8x8(
			c,
			x, y,
			r, g, b,
			TTY_TARGET_GLYPH_WIDTH, TTY_TARGET_GLYPH_HEIGHT,
			TTY_BKG_RED, TTY_BKG_GREEN, TTY_BKG_BLUE,
			true
		);

		++TTY_POSITION;
	}
}