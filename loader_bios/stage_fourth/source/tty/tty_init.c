#include <tty/tty.h>

extern gfx_video_mode_t GFX_VIDEO_MODE;

size_t TTY_NUM_CHARS_PER_LINE;
size_t TTY_NUM_LINES;
size_t TTY_TARGET_GLYPH_WIDTH;
size_t TTY_TARGET_GLYPH_HEIGHT;
size_t TTY_SPACING_X;
size_t TTY_SPACING_Y;
size_t TTY_CELL_X;
size_t TTY_CELL_Y;

size_t TTY_POSITION;
size_t TTY_MAX_POSITION;

uint8_t TTY_FRG_RED;
uint8_t TTY_FRG_GREEN;
uint8_t TTY_FRG_BLUE;
uint8_t TTY_BKG_RED;
uint8_t TTY_BKG_GREEN;
uint8_t TTY_BKG_BLUE;

void tty_init(
	size_t num_chars_per_line, size_t num_lines,
	size_t spacing_x, size_t spacing_y,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
) {
	TTY_NUM_CHARS_PER_LINE = num_chars_per_line;
	TTY_NUM_LINES = num_lines;
	TTY_CELL_X = GFX_VIDEO_MODE.width / TTY_NUM_CHARS_PER_LINE;
	TTY_CELL_Y = GFX_VIDEO_MODE.height / TTY_NUM_LINES;
	TTY_SPACING_X = spacing_x;
	TTY_SPACING_Y = spacing_y;
	TTY_TARGET_GLYPH_WIDTH = TTY_CELL_X - TTY_SPACING_X;
	TTY_TARGET_GLYPH_HEIGHT = TTY_CELL_Y - TTY_SPACING_Y;

	TTY_POSITION = 0;
	TTY_MAX_POSITION = TTY_NUM_CHARS_PER_LINE * TTY_NUM_LINES - 1;

	TTY_FRG_RED = frg_r;
	TTY_FRG_GREEN = frg_g;
	TTY_FRG_BLUE = frg_b;
	TTY_BKG_RED = bkg_r;
	TTY_BKG_GREEN = bkg_g;
	TTY_BKG_BLUE = bkg_b;

	gfx_fill_rectangle(0, 0, GFX_VIDEO_MODE.width, GFX_VIDEO_MODE.height, 0x10, 0x10, 0x10);
}