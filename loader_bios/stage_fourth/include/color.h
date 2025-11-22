#pragma once
#ifndef __COLOR_H
#define __COLOR_H

#include "typedefs.h"

typedef struct _color_t {
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
} color_t;

static inline uint32_t color_scale_component(uint8_t color_component, uint8_t bits) {
	if (bits == 8) return color_component;
	return (color_component * 255 + ((1 << bits) - 1) / 2) / ((1 << bits) - 1);
}

static inline uint32_t color_scale_rgb(
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t bits_red,
	uint8_t shift_red,
	uint8_t bits_green,
	uint8_t shift_green,
	uint8_t bits_blue,
	uint8_t shift_blue
) {
	uint32_t scaled_r = color_scale_component(r, bits_red) << shift_red;
	uint32_t scaled_g = color_scale_component(g, bits_green) << shift_green;
	uint32_t scaled_b = color_scale_component(b, bits_blue) << shift_blue;
	return scaled_r | scaled_g | scaled_b;
}

static inline size_t color_find_nearset_indexed(
	uint8_t r, uint8_t g, uint8_t b,
	const color_t* palette,
	size_t num_colors_in_palette
) {
	size_t best_distance2 = (size_t)-1;
	size_t best_color_index = 0;
	for (size_t i = 0; i < num_colors_in_palette; i++) {
		int r_distance = r - palette[i].r;
		int g_distance = g - palette[i].g;
		int b_distance = b - palette[i].b;
		size_t distance2 = r_distance * r_distance + g_distance * g_distance + b_distance * b_distance;

		if (distance2 <= best_distance2) {
			best_distance2 = distance2;
			best_color_index = i;
		}
	}

	return best_color_index;
}

#endif