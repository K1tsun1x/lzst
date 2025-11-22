#include <gfx.h>

// Video mode information (width, height, etc...)
extern video_mode_t GFX_VIDEO_MODE;

/**
 * @note gfx_draw_pixel(x, y, r, g, b) - Procedure for drawing one pixel
 * @warning Bits in glyphs must be in the MSB format!
 * @param x X of the point on the screen where we will display the symbol
 * @param y Y of the point on the screen where we will display the symbol
 * @param glyph_data Glyph (array of bytes/words/...)
 * @param width_bits Glyph width in bits
 * @param height_bits Glyph height in bits
 * @param frg_r Red glyph color component
 * @param frg_g Green glyph color component
 * @param frg_b Blue glyph color component
 * @param target_width Target width of the glyph on the screen (the glyph can be stretched/compressed)
 * @param target_height Target height of the glyph on the screen
 * @param bkg_r Red background color component
 * @param bkg_g Green background color component
 * @param bkg_b Blue background color component
 * @param fill_bkg Determines whether the background under the glyph will be painted over
 */
void gfx_draw_glyph(
	int x, int y,
	const void* glyph_data,
	size_t width_bits, size_t height_bits,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	size_t target_width, size_t target_height,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg
) {
	const video_mode_t* vm = &GFX_VIDEO_MODE;
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