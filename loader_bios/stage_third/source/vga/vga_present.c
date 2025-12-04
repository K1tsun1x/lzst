#include <vga.h>

bool vga_present(void) {
	const uint8_t saved = vga_crtc_read(VGA_CRTC_CURSOR_POSITION_LOW);
	vga_crtc_write(VGA_CRTC_CURSOR_POSITION_LOW, saved ^ 0xa5);
	bool res = vga_crtc_read(VGA_CRTC_CURSOR_POSITION_LOW) != saved;
	vga_crtc_write(VGA_CRTC_CURSOR_POSITION_LOW, saved);
	return res;
}