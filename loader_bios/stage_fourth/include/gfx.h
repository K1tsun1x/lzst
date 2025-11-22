#pragma once
#ifndef __GFX_H
#define __GFX_H

#include "video_mode.h"
#include "color.h"
#include "glyph.h"
#include "min_string.h"

typedef void (*pgfx_draw_pixel)(int x, int y, uint8_t r, uint8_t g, uint8_t b);
typedef void (*pgfx_read_pixel)(int x, int y, uint8_t* r, uint8_t* g, uint8_t* b);
typedef void (*pgfx_copy_rectangle)(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height);

void gfx_init(video_mode_t* video_mode);
extern pgfx_draw_pixel gfx_draw_pixel;
extern pgfx_read_pixel gfx_read_pixel;
extern pgfx_copy_rectangle gfx_copy_rectangle;
void gfx_fill_rectangle(int x, int y, size_t width, size_t height, uint8_t r, uint8_t g, uint8_t b);

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

void gfx_draw_ustring8x8(
	const char32_t* s,
	int x, int y,
	size_t spacing_x,
	size_t spacing_y,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	size_t glyph_width, size_t glyph_height,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
);

#endif