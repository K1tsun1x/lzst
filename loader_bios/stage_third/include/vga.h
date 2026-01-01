#pragma once
#ifndef __VGA_H
#define __VGA_H

#include "spinlock.h"

#define VGA_PORT_CRTC_INDEX					0x3d4
#define VGA_PORT_CRTC_DATA					0x3d5

#define VGA_CRTC_CURSOR_START				0x0a
#define VGA_CRTC_CURSOR_END					0x0b
#define VGA_CRTC_CURSOR_POSITION_LOW		0x0f

#define VGA_CRTC_CURSOR_START_FLAG_DISABLE	0x20

XTRN_C bool LOADERCALL vga_set_video_mode(uint8_t mode);

bool vga_present(void);
void vga_set_cursor_state(bool visible);

static inline uint8_t vga_crtc_read(uint8_t reg) {
	outb(VGA_PORT_CRTC_INDEX, reg);
	return inb(VGA_PORT_CRTC_DATA);
}

static inline void vga_crtc_write(uint8_t reg, uint8_t value) {
	outb(VGA_PORT_CRTC_INDEX, reg);
	io_wait();
	outb(VGA_PORT_CRTC_DATA, value);
	io_wait();
}

#endif