#include <gfx/gfx.h>

extern gfx_video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;

void gfx_draw_pixel888(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	const gfx_video_mode_t* vm = &GFX_VIDEO_MODE;
	if (x < 0 || y < 0 || x >= (int)vm->width || y >= (int)vm->height) return;

	uint32_t pixel = gfx_color_scale_rgb(
		r, g, b,
		vm->bits_red, vm->shift_red,
		vm->bits_green, vm->shift_green,
		vm->bits_blue, vm->shift_blue
	);

	const size_t offset = y * vm->pitch + (x << 1) + x;
	GFX_BUFFER[offset] = pixel & 0xff;
	GFX_BUFFER[offset + 1] = (pixel >> 8) & 0xff;
	GFX_BUFFER[offset + 2] = (pixel >> 16) & 0xff;
}