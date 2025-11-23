#include <color.h>

size_t color_find_nearset_index(
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