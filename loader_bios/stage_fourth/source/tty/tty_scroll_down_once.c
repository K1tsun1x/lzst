#include <tty.h>

extern video_mode_t GFX_VIDEO_MODE;

extern size_t TTY_NUM_CHARS_PER_LINE;
extern size_t TTY_NUM_LINES;
extern size_t TTY_SPACING_X;
extern size_t TTY_SPACING_Y;
extern size_t TTY_CELL_X;
extern size_t TTY_CELL_Y;

extern size_t TTY_POSITION;
extern size_t TTY_MAX_POSITION;

extern uint8_t TTY_BKG_RED;
extern uint8_t TTY_BKG_GREEN;
extern uint8_t TTY_BKG_BLUE;

void tty_scroll_down_once(void) {
	int src_y = TTY_CELL_Y;
	int dst_y = 0;
	const int end_src_y = (TTY_NUM_LINES - 1) * TTY_CELL_Y;
	for (; src_y < end_src_y;) {
		gfx_copy_rectangle(
			0, src_y,
			0, dst_y,
			GFX_VIDEO_MODE.width, TTY_CELL_Y
		);

		src_y += TTY_CELL_Y;
		dst_y += TTY_CELL_Y;
	}

	gfx_fill_rectangle(0, dst_y, GFX_VIDEO_MODE.width, TTY_CELL_Y, TTY_BKG_RED, TTY_BKG_GREEN, TTY_BKG_BLUE);
}