#pragma once
#ifndef __PIT_H
#define __PIT_H

#include <asm.h>
#include <irq/irq.h>
#include <isr/isr_data.h>
#include <virt-int-ctrl/virt-int-ctrl.h>
#include <critical-section/critical-section.h>

#define PIT_PORT_CHNL0_DATA				0x40
#define PIT_PORT_CHNL1_DATA				0x41
#define PIT_PORT_CHNL2_DATA				0x42
#define PIT_PORT_COMMAND				0x43

/*
	BCD/Binary mode
*/

#define PIT_COMMAND_BINARY				0x00
#define PIT_COMMAND_BCD					0x01

/*
	Operating mode
*/

#define PIT_COMMAND_INT_ON_TERMINAL_CNT	(0b000 << 1)
#define PIT_COMMAND_RETRIG_ONE_SHOT		(0b001 << 1)
#define PIT_COMMAND_RATE				(0b010 << 1)
#define PIT_COMMAND_SQUARE_WAVE			(0b011 << 1)
#define PIT_COMMAND_SW_STROBE			(0b100 << 1)
#define PIT_COMMAND_HW_STROBE			(0b101 << 1)

/*
	Access mode
*/

#define PIT_COMMAND_ACCESS_LATCH_CNT	(0b00 << 4)
#define PIT_COMMAND_ACCESS_LOBYTE		(0b01 << 4)
#define PIT_COMMAND_ACCESS_HIBYTE		(0b10 << 4)
#define PIT_COMMAND_ACCESS_BOTH			(PIT_COMMAND_ACCESS_LOBYTE | PIT_COMMAND_ACCESS_HIBYTE)

/*
	Channel
*/

#define PIT_COMMAND_CHNL0				(0b00 << 6)
#define PIT_COMMAND_CHNL1				(0b01 << 6)
#define PIT_COMMAND_CHNL2				(0b10 << 6)
#define PIT_COMMAND_READ_BACK			(0b11 << 6)

#define PIT_HW_FREQ						(3579545 / 3)
#define PIT_SW_FREQ						1000

uint16_t pit_calc_divisor(uint32_t tick_ms);
uint16_t pit_read_count(void);

void pit_init(
	uint8_t operating_mode,
	uint8_t channel,
	uint16_t tick_ms
);

static inline void pit_oneshot(uint16_t ms) {
	pit_init(PIT_COMMAND_INT_ON_TERMINAL_CNT, PIT_COMMAND_CHNL0, ms);
}

#endif