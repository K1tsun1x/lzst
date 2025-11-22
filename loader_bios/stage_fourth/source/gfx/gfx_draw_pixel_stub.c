#include <gfx.h>

/**
 * Needed if there is no suitable gfx_draw_pixel*
 */
void gfx_draw_pixel_stub(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b) {
	(void)(x);
	(void)(y);
	(void)(r);
	(void)(g);
	(void)(b);
	return;
}