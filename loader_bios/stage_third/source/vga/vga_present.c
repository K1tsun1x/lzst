#include <vga.h>

extern spinlock_t __VGA_SPINLOCK;

bool vga_present(void) {
	spinlock_acquire(&__VGA_SPINLOCK);			// FIXME: makes no sense in single threaded mode
	irq_flags_t irq_flags = irq_disable();

	const uint8_t saved = vga_crtc_read(VGA_CRTC_CURSOR_POSITION_LOW);
	vga_crtc_write(VGA_CRTC_CURSOR_POSITION_LOW, saved ^ 0xa5);
	bool res = vga_crtc_read(VGA_CRTC_CURSOR_POSITION_LOW) != saved;
	vga_crtc_write(VGA_CRTC_CURSOR_POSITION_LOW, saved);

	irq_restore(irq_flags);
	spinlock_release(&__VGA_SPINLOCK);			// FIXME: makes no sense in single threaded mode
	return res;
}