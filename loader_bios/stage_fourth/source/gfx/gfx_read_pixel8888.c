#include <gfx.h>

extern video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;

/**
 * Only for non-index video mode with 32 bits per pixel (ARGB, A - reserved)
 */
void gfx_read_pixel8888(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b) {
	const video_mode_t* vm = &GFX_VIDEO_MODE;
	uint8_t cr;
	uint8_t cg;
	uint8_t cb;
	if (x < 0 || y < 0 || x >= (int)vm->width || y >= (int)vm->height) cr = cg = cb = 0;
	else {
		const size_t offset = y * vm->pitch + (x << 2);
		cb = GFX_BUFFER[offset];
		cg = GFX_BUFFER[offset + 1];
		cr = GFX_BUFFER[offset + 2];
	}

	if (r) *r = cr;
	if (g) *g = cg;
	if (b) *b = cb;
}