#include <gfx.h>

extern video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;
extern const color_t GFX_PALETTE_I8[256];

/**
 * Only for indexed video mode with 8 bits per pixel
 */
void gfx_read_pixel_i8(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b) {
	const video_mode_t* vm = &GFX_VIDEO_MODE;
	if (x < 0 || y < 0 || x >= (int)vm->width || y >= (int)vm->height) return;

	const size_t offset = y * vm->pitch + x;
	const size_t index = GFX_BUFFER[offset];

	uint8_t cr = GFX_PALETTE_I8[index].r;
	uint8_t cg = GFX_PALETTE_I8[index].g;
	uint8_t cb = GFX_PALETTE_I8[index].b;
	if (r) *r = cr;
	if (g) *g = cg;
	if (b) *b = cb;
}