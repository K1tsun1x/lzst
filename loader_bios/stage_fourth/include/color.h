#pragma once
#ifndef __COLOR_H
#define __COLOR_H

#include "typedefs.h"

#define COLOR_BLACK					((color_t){0, 0, 0})
#define COLOR_BLUE					((color_t){0, 0, 171})
#define COLOR_GREEN					((color_t){0, 171, 0})
#define COLOR_CYAN					((color_t){0, 171, 171})
#define COLOR_RED					((color_t){171, 0, 0})
#define COLOR_MAGENTA				((color_t){171, 0, 171})
#define COLOR_BROWN					((color_t){171, 100, 0})
#define COLOR_LIGHT_GRAY			((color_t){171, 171, 171})
#define COLOR_DARK_GRAY				((color_t){100, 100, 100})
#define COLOR_LIGHT_BLUE			((color_t){100, 100, 241})
#define COLOR_LIGHT_GREEN			((color_t){100, 241, 100})
#define COLOR_LIGHT_CYAN			((color_t){100, 241, 241})
#define COLOR_LIGHT_RED				((color_t){241, 100, 100})
#define COLOR_LIGHT_MAGENTA			((color_t){241, 100, 241})
#define COLOR_YELLOW				((color_t){241, 241, 100})
#define COLOR_WHITE					((color_t){241, 241, 241})

typedef struct _color_t {
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
} color_t;

static inline uint32_t color_scale_component(uint8_t color_component, uint8_t bits) {
	if (bits == 8) return color_component;
	return (color_component * 255 + ((1 << bits) - 1) / 2) / ((1 << bits) - 1);
}

uint32_t color_scale_rgb(
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

size_t color_find_nearset_index(
	uint8_t r, uint8_t g, uint8_t b,
	const color_t* palette,
	size_t num_colors_in_palette
);

#endif