#include <gfx.h>

extern video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;
extern const color_t GFX_PALETTE_I8[256];

/**
 * Only for indexed video mode with 8 bits per pixel
 */
void gfx_draw_pixel_i8(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	const video_mode_t* vm = &GFX_VIDEO_MODE;
	if (x < 0 || y < 0 || x >= (int)vm->width || y >= (int)vm->height) return;

	const size_t offset = y * vm->pitch + x;
	GFX_BUFFER[offset] = (uint8_t)color_find_nearset_indexed(
		r, g, b,
		GFX_PALETTE_I8,
		256
	);
}