#include <gfx/gfx.h>

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
) {
	uint32_t scaled_r = gfx_color_scale_component(r, bits_red) << shift_red;
	uint32_t scaled_g = gfx_color_scale_component(g, bits_green) << shift_green;
	uint32_t scaled_b = gfx_color_scale_component(b, bits_blue) << shift_blue;
	return scaled_r | scaled_g | scaled_b;
}