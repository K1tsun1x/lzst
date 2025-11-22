#include <vbe.h>

static vbe_mode_info_t __VBE_MODE_INFO;

static inline int __idiff(int a, int b) {
	a -= b;
	if (a < 0) a = -a;
	return a;
}

void vbe_find_best_video_mode(
	const vbe_info_t* vbe_info,
	size_t width,
	size_t height,
	size_t depth,
	video_mode_t* best_video_mode
) {
	const size_t size = width * height;

	int best_depth_diff = 8 >= depth ? 8 - depth : (depth - 8) * 2;
	int best_pix_diff = __idiff(320 * 200, (int)size);
	uint16_t *modes;
	int depth_diff;
	int pix_diff;

	uint16_t best_number = 0x13;
	uint8_t	best_type = VIDEO_MODE_TYPE_DIRECT_COLOR;
	uint16_t best_width = 320;
	uint16_t best_height = 200;
	uint8_t best_depth = 8;
	uint16_t best_pitch = 320;
	uint8_t best_bits_red = 0;
	uint8_t best_shift_red = 0;
	uint8_t best_bits_green = 0;
	uint8_t best_shift_green = 0;
	uint8_t best_bits_blue = 0;
	uint8_t best_shift_blue = 0;
	uint8_t best_bits_reserved = 0;
	uint8_t best_shift_reserved = 0;
	uint32_t best_physical_buffer_address = 0xb8000;

	modes = (uint16_t*)((uintptr_t)vbe_info->video_mode_ptr[0]);
	for (size_t i = 0; modes[i] != 0xFFFF; ++i) {
		if (!vbe_get_mode_info(modes[i], &__VBE_MODE_INFO)) break;

		if (
			!(__VBE_MODE_INFO.attributes & VBE_MODE_ATTRIBUTE_LFB) ||
			(
				__VBE_MODE_INFO.memory_model != VIDEO_MODE_TYPE_DIRECT_COLOR &&
				__VBE_MODE_INFO.memory_model != VIDEO_MODE_TYPE_PACKED
			)
		) continue;

		if (
			__VBE_MODE_INFO.width == width &&
			__VBE_MODE_INFO.height == height &&
			__VBE_MODE_INFO.depth == depth
		) {
			best_number = modes[i];
			best_type = __VBE_MODE_INFO.memory_model;
			best_width = __VBE_MODE_INFO.width;
			best_height = __VBE_MODE_INFO.height;
			best_depth = __VBE_MODE_INFO.depth;
			best_pitch = __VBE_MODE_INFO.pitch;
			best_bits_red = __VBE_MODE_INFO.red_mask;
			best_shift_red = __VBE_MODE_INFO.red_position;
			best_bits_green = __VBE_MODE_INFO.green_mask;
			best_shift_green = __VBE_MODE_INFO.green_position;
			best_bits_blue = __VBE_MODE_INFO.blue_mask;
			best_shift_blue = __VBE_MODE_INFO.blue_position;
			best_bits_reserved = __VBE_MODE_INFO.reserved_mask;
			best_shift_reserved = __VBE_MODE_INFO.reserved_position;
			best_physical_buffer_address = __VBE_MODE_INFO.framebuffer;
			break;
		}

		pix_diff = __idiff(__VBE_MODE_INFO.width * __VBE_MODE_INFO.height, size);
		if (__VBE_MODE_INFO.depth >= depth) depth_diff = __VBE_MODE_INFO.depth - depth;
		else depth_diff = (depth - __VBE_MODE_INFO.depth) * 2;

		if (best_pix_diff > pix_diff ||
			(
				best_pix_diff == pix_diff &&
				best_depth_diff > depth_diff
			)
		) {
			best_pix_diff = pix_diff;
			best_depth_diff = depth_diff;
			
			best_number = modes[i];
			best_type = __VBE_MODE_INFO.memory_model;
			best_width = __VBE_MODE_INFO.width;
			best_height = __VBE_MODE_INFO.height;
			best_depth = __VBE_MODE_INFO.depth;
			best_pitch = __VBE_MODE_INFO.pitch;
			best_bits_red = __VBE_MODE_INFO.red_mask;
			best_shift_red = __VBE_MODE_INFO.red_position;
			best_bits_green = __VBE_MODE_INFO.green_mask;
			best_shift_green = __VBE_MODE_INFO.green_position;
			best_bits_blue = __VBE_MODE_INFO.blue_mask;
			best_shift_blue = __VBE_MODE_INFO.blue_position;
			best_bits_reserved = __VBE_MODE_INFO.reserved_mask;
			best_shift_reserved = __VBE_MODE_INFO.reserved_position;
			best_physical_buffer_address = __VBE_MODE_INFO.framebuffer;
		}
	}

	if (width == 640 && height == 480 && depth == 1) {
		best_number = 0x11;
		best_type = VIDEO_MODE_TYPE_HERCULES;
		best_width = 640;
		best_height = 480;
		best_depth = 1;
		best_pitch = 80;
		best_bits_red = 0;
		best_shift_red = 0;
		best_bits_green = 0;
		best_shift_green = 0;
		best_bits_blue = 0;
		best_shift_blue = 0;
		best_bits_reserved = 0;
		best_shift_reserved = 0;
		best_physical_buffer_address = 0xb0000;
	}

	if (best_video_mode) {
		best_video_mode->number = best_number;
		best_video_mode->width = best_width;
		best_video_mode->height = best_height;
		best_video_mode->depth = best_depth;
		best_video_mode->pitch = best_pitch;
		best_video_mode->type = best_type;
		best_video_mode->bits_red = best_bits_red;
		best_video_mode->shift_red = best_shift_red;
		best_video_mode->bits_green = best_bits_green;
		best_video_mode->shift_green = best_shift_green;
		best_video_mode->bits_blue = best_bits_blue;
		best_video_mode->shift_blue = best_shift_blue;
		best_video_mode->bits_reserved = best_bits_reserved;
		best_video_mode->shift_reserved = best_shift_reserved;
		best_video_mode->framebuffer = best_physical_buffer_address;
	}
}