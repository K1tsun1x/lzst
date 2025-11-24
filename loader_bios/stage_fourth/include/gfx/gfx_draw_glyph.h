#pragma once
#ifndef __GFX_DRAW_GLYPH_H
#define __GFX_DRAW_GLYPH_H

#include "gfx_draw_pixel.h"
#include "gfx_glyph.h"

/**
 * @warning Bits in glyphs must be in the MSB format!
 * @param x X of the point on the screen where we will display the symbol
 * @param y Y of the point on the screen where we will display the symbol
 * @param glyph_data Glyph (array of bytes/words/...)
 * @param width_bits Glyph width in bits
 * @param height_bits Glyph height in bits
 * @param frg_r Red glyph color component
 * @param frg_g Green glyph color component
 * @param frg_b Blue glyph color component
 * @param target_width Target width of the glyph on the screen (the glyph can be stretched/compressed)
 * @param target_height Target height of the glyph on the screen
 * @param bkg_r Red background color component
 * @param bkg_g Green background color component
 * @param bkg_b Blue background color component
 * @param fill_bkg Determines whether the background under the glyph will be painted over
 */
void gfx_draw_glyph(
	int x, int y,
	const void* glyph_data,
	size_t width_bits, size_t height_bits,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	size_t target_width, size_t target_height,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
);

void gfx_draw_glyph8x8(
	char32_t c,
	int x, int y,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	size_t target_width, size_t target_height,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
);

#endif