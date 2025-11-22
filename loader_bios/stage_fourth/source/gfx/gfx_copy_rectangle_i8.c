#include <gfx.h>

extern video_mode_t GFX_VIDEO_MODE;
extern uint8_t* GFX_BUFFER;

void gfx_copy_rectangle_i8(int src_x, int src_y, int dst_x, int dst_y, size_t width, size_t height) {
	const video_mode_t* vm = &GFX_VIDEO_MODE;
	if (src_x < 0) {
		width += src_x;
		src_x = 0;
	}

	if (src_y < 0) {
		height += src_y;
		src_y = 0;
	}

	if (dst_x < 0) {
		width += dst_x;
		src_x -= dst_x;
		dst_x = 0;
	}

	if (dst_y < 0) {
		height += dst_y;
		src_y -= dst_y;
		dst_y = 0;
	}

	if (src_x + width > vm->width) width = vm->width - src_x;
	if (dst_x + width > vm->width) width = vm->width - dst_x;
	if (src_y + height > vm->height) height = vm->height - src_y;
	if (dst_y + height > vm->height) height = vm->height - dst_y;

	if (!width || !height) return;

	int row_start, row_end, row_step;
	if (dst_y > src_y) {
		row_start = height - 1;
		row_end = -1;
		row_step = -1;
	} else {
		row_start = 0;
		row_end = height;
		row_step = 1;
	}

	for (int row = row_start; row != row_end; row += row_step) {
		uint8_t* src_line = (uint8_t*)(GFX_BUFFER + (src_y + row) * vm->pitch) + src_x;
		uint8_t* dst_line = (uint8_t*)(GFX_BUFFER + (dst_y + row) * vm->pitch) + dst_x;
		for (size_t col = 0; col < width; ++col) dst_line[col] = src_line[col];
	}
}