#include <vga.h>

extern spinlock_t __VGA_SPINLOCK;

void vga_set_cursor_state(bool visible) {
	spinlock_acquire(&__VGA_SPINLOCK);

	uint8_t value = vga_crtc_read(VGA_CRTC_CURSOR_START);
	if (visible) value &= ~VGA_CRTC_CURSOR_START_FLAG_DISABLE;
	else value |= VGA_CRTC_CURSOR_START_FLAG_DISABLE;
	vga_crtc_write(VGA_CRTC_CURSOR_START, value);

	spinlock_release(&__VGA_SPINLOCK);
}