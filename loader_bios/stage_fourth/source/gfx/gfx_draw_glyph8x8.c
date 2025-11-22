#include <gfx.h>

extern const glyph8x8_t GFX_GLYPHS8X8[];
extern const size_t GFX_NUM_GLYPHS8X8;

void gfx_draw_glyph8x8(
	char32_t c,
	int x, int y, 
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	size_t target_width, size_t target_height,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
) {
	const glyph8x8_t* glyph = 0;
	for (size_t i = 0; i < GFX_NUM_GLYPHS8X8; i++) {
		if (GFX_GLYPHS8X8[i].index == c) {
			glyph = (const glyph8x8_t*)&GFX_GLYPHS8X8[i];
			break;
		}
	}
	
	if (!glyph) glyph = &GLYPH_UNKNOWN8X8;
	gfx_draw_glyph(x, y, &glyph->data, 8, 8, frg_r, frg_g, frg_b, target_width, target_height, bkg_r, bkg_g, bkg_b, fill_bkg);
}