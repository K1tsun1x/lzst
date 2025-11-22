#include <gfx.h>

extern video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;

/**
 * Only for non-index video mode with 15 or 16 bits per pixel (RGB)
 */
void gfx_read_pixel555_565(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b) {
	const video_mode_t* vm = &GFX_VIDEO_MODE;
	uint8_t cr;
	uint8_t cg;
	uint8_t cb;
	if (x < 0 || y < 0 || x >= (int)vm->width || y >= (int)vm->height) cr = cg = cb = 0;
	else {
		const size_t offset = y * (vm->pitch >> 1) + x;
		uint32_t pixel = (uint32_t)((uint16_t*)GFX_BUFFER)[offset];

		const uint32_t mask_red = (1 << GFX_VIDEO_MODE.bits_red) - 1;
		const uint32_t mask_green = (1 << GFX_VIDEO_MODE.bits_green) - 1;
		const uint32_t mask_blue = (1 << GFX_VIDEO_MODE.bits_blue) - 1;
		cr = color_scale_component((pixel >> GFX_VIDEO_MODE.shift_red) & mask_red, 8);
		cg = color_scale_component((pixel >> GFX_VIDEO_MODE.shift_green) & mask_green, 8);
		cb = color_scale_component((pixel >> GFX_VIDEO_MODE.shift_blue) & mask_blue, 8);
	}

	if (r) *r = cr;
	if (g) *g = cg;
	if (b) *b = cb;
}