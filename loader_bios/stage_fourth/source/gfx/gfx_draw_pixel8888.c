#include <gfx/gfx.h>

extern gfx_video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;

void gfx_draw_pixel8888(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	const gfx_video_mode_t* vm = &GFX_VIDEO_MODE;
	if (x < 0 || y < 0 || x >= (int)vm->width || y >= (int)vm->height) return;

	const size_t offset = y * vm->pitch + (x << 2);
	GFX_BUFFER[offset] = b;
	GFX_BUFFER[offset + 1] = g;
	GFX_BUFFER[offset + 2] = r;
	GFX_BUFFER[offset + 3] = 0;
}