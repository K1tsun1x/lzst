#include <tty/tty.h>

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

int tty_putchar(
	int c,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
) {
	if (TTY_POSITION > TTY_MAX_POSITION) {
		tty_scroll_down(1, bkg_r, bkg_g, bkg_b);
		TTY_POSITION = (TTY_NUM_LINES - 1) * TTY_NUM_CHARS_PER_LINE;
	}

	if (c == '\r') {
		const size_t pos_in_line = TTY_POSITION % TTY_NUM_CHARS_PER_LINE;
		TTY_POSITION -= pos_in_line;
	}
	else if (c == '\n') {
		const size_t line = TTY_POSITION / TTY_NUM_CHARS_PER_LINE + 1;
		TTY_POSITION = line * TTY_NUM_CHARS_PER_LINE;
	}
	else if (c == '\t') {
		const size_t pos_in_line = TTY_POSITION % TTY_NUM_CHARS_PER_LINE;
		const size_t spaces = TTY_TAB_WIDTH - (pos_in_line % TTY_TAB_WIDTH);
		for (size_t i = 0; i < spaces; i++) tty_putchar(' ', frg_r, frg_g, frg_b, bkg_r, bkg_g, bkg_b, fill_bkg);
	}
	else if (c == '\v') {
		for (size_t i = 0; i < TTY_TAB_WIDTH; i++) tty_putchar('\n', frg_r, frg_g, frg_b, bkg_r, bkg_g, bkg_b, fill_bkg);
	}
	else if (c == '\b') {
		if (TTY_POSITION) --TTY_POSITION;
	}
	else {
		const size_t y = TTY_POSITION / TTY_NUM_CHARS_PER_LINE * TTY_CELL_Y;
		const size_t x = (TTY_POSITION % TTY_NUM_CHARS_PER_LINE) * TTY_CELL_X;

		gfx_draw_glyph8x8(
			c,
			x, y,
			frg_r, frg_g, frg_b,
			TTY_TARGET_GLYPH_WIDTH, TTY_TARGET_GLYPH_HEIGHT,
			bkg_r, bkg_g, bkg_b,
			fill_bkg
		);

		if (fill_bkg) {
			gfx_fill_rectangle(
				x + TTY_TARGET_GLYPH_WIDTH, y,
				TTY_SPACING_X, TTY_CELL_Y,
				bkg_r, bkg_g, bkg_b
			);
			
			gfx_fill_rectangle(
				x, y + TTY_TARGET_GLYPH_HEIGHT,
				TTY_CELL_X, TTY_SPACING_Y,
				bkg_r, bkg_g, bkg_b
			);
		}

		++TTY_POSITION;
	}

	return c;
}