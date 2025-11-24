#include <gfx/gfx.h>

void gfx_draw_string8x8(
	const char* s,
	int x, int y,
	size_t spacing_x,
	size_t spacing_y,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	size_t glyph_width, size_t glyph_height,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
) {
	for (; *s;) {
		if(fill_bkg) gfx_fill_rectangle(x, y, glyph_width + spacing_x, glyph_height + spacing_y, bkg_r, bkg_g, bkg_b);
		gfx_draw_glyph8x8((char32_t)*s++, x, y, frg_r, frg_g, frg_b, glyph_width, glyph_height, 0, 0, 0, false);
		x += glyph_width + spacing_x;
	}
}