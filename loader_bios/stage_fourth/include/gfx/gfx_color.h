#pragma once
#ifndef __GFX_COLOR_H
#define __GFX_COLOR_H

#include <typedefs.h>

#define GFX_PACK_COLOR(r, g, b)			((gfx_color_t){ r, g, b })
#define GFX_UNPACK_COLOR(c)				c.r, c.g, c.b

#define GFX_COLOR_BLACK					GFX_PACK_COLOR(0, 0, 0)
#define GFX_COLOR_BLUE					GFX_PACK_COLOR(0, 0, 171)
#define GFX_COLOR_GREEN					GFX_PACK_COLOR(0, 171, 0)
#define GFX_COLOR_CYAN					GFX_PACK_COLOR(0, 171, 171)
#define GFX_COLOR_RED					GFX_PACK_COLOR(171, 0, 0)
#define GFX_COLOR_MAGENTA				GFX_PACK_COLOR(171, 0, 171)
#define GFX_COLOR_BROWN					GFX_PACK_COLOR(171, 100, 0)
#define GFX_COLOR_LIGHT_GRAY			GFX_PACK_COLOR(171, 171, 171)
#define GFX_COLOR_DARK_GRAY				GFX_PACK_COLOR(100, 100, 100)
#define GFX_COLOR_LIGHT_BLUE			GFX_PACK_COLOR(100, 100, 241)
#define GFX_COLOR_LIGHT_GREEN			GFX_PACK_COLOR(100, 241, 100)
#define GFX_COLOR_LIGHT_CYAN			GFX_PACK_COLOR(100, 241, 241)
#define GFX_COLOR_LIGHT_RED				GFX_PACK_COLOR(241, 100, 100)
#define GFX_COLOR_LIGHT_MAGENTA			GFX_PACK_COLOR(241, 100, 241)
#define GFX_COLOR_YELLOW				GFX_PACK_COLOR(241, 241, 100)
#define GFX_COLOR_WHITE					GFX_PACK_COLOR(241, 241, 241)

typedef struct _gfx_color_t {
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
} gfx_color_t;

static inline uint32_t gfx_color_scale_component(uint8_t color_component, uint8_t bits) {
	if (bits == 8) return color_component;
	return (color_component * 255 + ((1 << bits) - 1) / 2) / ((1 << bits) - 1);
}

uint32_t gfx_color_scale_rgb(
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t bits_red,
	uint8_t shift_red,
	uint8_t bits_green,
	uint8_t shift_green,
	uint8_t bits_blue,
	uint8_t shift_blue
);

size_t gfx_color_find_nearset_index(
	uint8_t r, uint8_t g, uint8_t b,
	const gfx_color_t* palette,
	size_t num_colors_in_palette
);

#endif