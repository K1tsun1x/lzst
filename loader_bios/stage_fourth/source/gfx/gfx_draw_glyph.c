#include <gfx/gfx.h>

extern gfx_video_mode_t GFX_VIDEO_MODE;

void gfx_draw_glyph(
	int x, int y,
	const void* glyph_data,
	size_t width_bits, size_t height_bits,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	size_t target_width, size_t target_height,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
) {
	const gfx_video_mode_t* vm = &GFX_VIDEO_MODE;
	if (target_width == 0 || target_height == 0) return;

	// src_x = floor(dst_x * src_w / target_width)
	// src_y = floor(dst_y * src_h / target_height)

	size_t stride = (width_bits + 7) / 8;
	if (fill_bkg) {
		for (size_t dy = 0; dy < target_height; ++dy) {
			size_t src_y = (dy * height_bits) / target_height;
			const uint8_t* row = glyph_data + src_y * stride;
			for (size_t dx = 0; dx < target_width; ++dx) {
				size_t src_x = (dx * width_bits) / target_width;
				size_t byte_index = src_x >> 3;
				uint8_t mask = 0x80 >> (src_x & 7);				// MSB(!)
				if (row[byte_index] & mask) {
					int px = x + dx;
					int py = y + dy;
					if ((size_t)px < vm->width && (size_t)py < vm->height) gfx_draw_pixel(px, py, frg_r, frg_g, frg_b);
				}
				else {
					int px = x + dx;
					int py = y + dy;
					if ((size_t)px < vm->width && (size_t)py < vm->height) gfx_draw_pixel(px, py, bkg_r, bkg_g, bkg_b);
				}
			}
		}
	}
	else {
		for (size_t dy = 0; dy < target_height; ++dy) {
			size_t src_y = (dy * height_bits) / target_height;
			const uint8_t* row = glyph_data + src_y * stride;
			for (size_t dx = 0; dx < target_width; ++dx) {
				size_t src_x = (dx * width_bits) / target_width;
				size_t byte_index = src_x >> 3;
				uint8_t mask = 0x80 >> (src_x & 7);				// MSB(!)
				if (row[byte_index] & mask) {
					int px = x + dx;
					int py = y + dy;
					if ((size_t)px < vm->width && (size_t)py < vm->height) gfx_draw_pixel(px, py, frg_r, frg_g, frg_b);
				}
			}
		}
	}
}