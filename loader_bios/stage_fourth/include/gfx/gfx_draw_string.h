#pragma once
#ifndef __GFX_DRAW_STRING_H
#define __GFX_DRAW_STRING_H

#include "gfx_draw_pixel.h"
#include "gfx_draw_glyph.h"
#include "gfx_fill_rectangle.h"

void gfx_draw_string8x8(
	const char* s,
	int x, int y,
	size_t spacing_x,
	size_t spacing_y,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	size_t glyph_width, size_t glyph_height,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
);

#endif