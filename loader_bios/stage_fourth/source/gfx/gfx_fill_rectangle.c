#include <gfx.h>

extern video_mode_t GFX_VIDEO_MODE;

void gfx_fill_rectangle(int x, int y, size_t width, size_t height, uint8_t r, uint8_t g, uint8_t b) {
	const video_mode_t* vm = &GFX_VIDEO_MODE;
	if (x >= (int)vm->width || y >= (int)vm->height) return;

	int ex = x + (int)width;
	int ey = y + (int)height;
	if (ex <= 0) return;
	if (ey <= 0) return;

	if (x < 0) {
		x = 0;
		width = (size_t)ex;
	}
	
	if (y < 0) {
		y = 0;
		height = (size_t)ey;
	}

	if (ex > (int)vm->width) ex = vm->width;
	if (ey > (int)vm->width) ey = vm->height;
	for (; y < ey; ++y) for (size_t cx = x; cx < (size_t)ex; ++cx) gfx_draw_pixel(cx, y, r, g, b);
}