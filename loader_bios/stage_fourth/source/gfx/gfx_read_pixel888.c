#include <gfx/gfx.h>

extern gfx_video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;

void gfx_read_pixel888(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b) {
	const gfx_video_mode_t* vm = &GFX_VIDEO_MODE;
	uint8_t cr;
	uint8_t cg;
	uint8_t cb;
	if (x < 0 || y < 0 || x >= (int)vm->width || y >= (int)vm->height) cr = cg = cb = 0;
	else {
		const size_t offset = y * vm->pitch + (x << 1) + x;
		cb = GFX_BUFFER[offset];
		cg = GFX_BUFFER[offset + 1];
		cr = GFX_BUFFER[offset + 2];
	}

	if (r) *r = cr;
	if (g) *g = cg;
	if (b) *b = cb;
}