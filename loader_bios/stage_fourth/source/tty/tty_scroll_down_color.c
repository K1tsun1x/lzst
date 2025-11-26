#include <tty/tty.h>

extern gfx_video_mode_t GFX_VIDEO_MODE;

extern size_t TTY_NUM_CHARS_PER_LINE;
extern size_t TTY_NUM_LINES;
extern size_t TTY_CELL_Y;

void tty_scroll_down_color(
	size_t num_lines,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
) {
	for (size_t i = 0; i < num_lines; i++) {
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

		gfx_fill_rectangle(0, dst_y, GFX_VIDEO_MODE.width, TTY_CELL_Y, bkg_r, bkg_g, bkg_b);
	}
}