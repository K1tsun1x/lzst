#include <gfx/gfx.h>

extern gfx_video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;

void gfx_draw_pixel555_565(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	const gfx_video_mode_t* vm = &GFX_VIDEO_MODE;
	if (x < 0 || y < 0 || x >= (int)vm->width || y >= (int)vm->height) return;

	uint32_t pixel = gfx_color_scale_rgb(
		r, g, b,
		vm->bits_red, vm->shift_red,
		vm->bits_green, vm->shift_green,
		vm->bits_blue, vm->shift_blue
	);

	const size_t offset = y * (vm->pitch >> 1) + x;
	((uint16_t*)GFX_BUFFER)[offset] = (uint16_t)pixel;
}