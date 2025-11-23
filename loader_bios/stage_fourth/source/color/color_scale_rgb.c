#include <color.h>

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
) {
	uint32_t scaled_r = color_scale_component(r, bits_red) << shift_red;
	uint32_t scaled_g = color_scale_component(g, bits_green) << shift_green;
	uint32_t scaled_b = color_scale_component(b, bits_blue) << shift_blue;
	return scaled_r | scaled_g | scaled_b;
}