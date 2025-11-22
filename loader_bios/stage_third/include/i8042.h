#pragma once
#ifndef __I8042_H
#define __I8042_H

#include "spinlock.h"

#define I8042_REG_DATA									0x60
#define I8042_REG_STATUS								0x64
#define I8042_REG_COMMAND								0x64

#define I8042_STATUS_OUTPUT_BUFFER_FULL					1		// 1 - data can be read (must be 1 before reading from port 0x60)
#define I8042_STATUS_INPUT_BUFFER_FULL					2		// 0 - data can be written (must be 0 before writing to port 0x60 or 0x64)
#define I8042_STATUS_SYSTEM_FLAG						4		// cleared on reset, set by firmware
#define I8042_STATUS_DATA_FOR_CONTROLLER				8		// 0 - data->input for: 0 - PS/2 dev, 1 - PS/2 controller
#define I8042_STATUS_TIMEOUT_ERROR						64		// 1 - time-out error
#define I8042_STATUS_PARITY_ERROR						128		// 1 - parity error

#define I8042_CONTROLLER_OUTPUT_SYSTEM_RESET			1
#define I8042_CONTROLLER_OUTPUT_A20_GATE				2
#define I8042_CONTROLLER_OUTPUT_SECOND_CLOCK			4		// only if 2 PS/2 ports supported
#define I8042_CONTROLLER_OUTPUT_SECOND_DATA				8		// only if 2 PS/2 ports supported
#define I8042_CONTROLLER_OUTPUT_FIRST_FULL				16
#define I8042_CONTROLLER_OUTPUT_SECOND_FULL				32
#define I8042_CONTROLLER_OUTPUT_FIRST_CLOCK				64
#define I8042_CONTROLLER_OUTPUT_FIRST_DATA				128

#define I8042_DISABLE_MOUSE								0xA7	// disable second PS/2 port
#define I8042_ENABLE_MOUSE								0xA8	// enable second PS/2 port
#define I8042_DISABLE_KBD								0xAD	// disable first PS/2 port
#define I8042_ENABLE_KBD								0xAE	// enable first PS/2 port
#define I8042_COMMAND_READ_CONTROLLER_OUTPUT			0xD0	// read from controller output port
#define I8042_COMMAND_WRITE_CONTROLLER_OUTPUT			0xD1	// write to controller output port

bool i8042_present(void);

void i8042_set_a20_state(bool enabled);

static inline uint8_t i8042_read_status(void) {
	uint8_t res = inb(I8042_REG_STATUS);
	return res;
}

static inline bool i8042_is_ready_to_read(void) {
	return i8042_read_status() & I8042_STATUS_OUTPUT_BUFFER_FULL;
}

static inline bool i8042_is_ready_to_write(void) {
	return !(i8042_read_status() & I8042_STATUS_INPUT_BUFFER_FULL);
}

static inline void i8042_wait_until_ready_to_read(void) {
	while (!i8042_is_ready_to_read()) cpu_relax();
}

static inline void i8042_wait_until_ready_to_write(void) {
	while (!i8042_is_ready_to_write()) cpu_relax();
}

static inline uint8_t i8042_read_data(void) {
	i8042_wait_until_ready_to_read();
	uint8_t res = inb(I8042_REG_DATA);
	return res;
}

static inline void i8042_write_data(uint8_t data) {
	i8042_wait_until_ready_to_write();
	outb(I8042_REG_DATA, data);
	io_wait();
}

static inline void i8042_write_cmd(uint8_t command) {
	i8042_wait_until_ready_to_write();
	outb(I8042_REG_COMMAND, command);
	io_wait();
}

static inline void i8042_flush_buf(void) {
	while (i8042_is_ready_to_read()) { (void)(inb(I8042_REG_DATA)); }
}

static inline void i8042_disable_kbd(void) {
	i8042_write_cmd(I8042_DISABLE_KBD);
}

static inline void i8042_disable_mouse(void) {
	i8042_write_cmd(I8042_DISABLE_MOUSE);
}

static inline void i8042_enable_kbd(void) {
	i8042_write_cmd(I8042_ENABLE_KBD);
}

static inline void i8042_enable_mouse(void) {
	i8042_write_cmd(I8042_ENABLE_MOUSE);
}

static inline uint8_t i8042_read_cntrl_out(void) {
	i8042_write_cmd(I8042_COMMAND_READ_CONTROLLER_OUTPUT);
	return i8042_read_data();
}

static inline void i8042_write_cntrl_out(uint8_t data) {
	i8042_write_cmd(I8042_COMMAND_WRITE_CONTROLLER_OUTPUT);
	i8042_write_data(data);
}

#endif