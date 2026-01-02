#pragma once
#ifndef __IDT_H
#define __IDT_H

#include <segment-selector/segment-selector.h>
#include "idtr.h"

#define IDT32_STATIC(offset, segment_selector, type, flags)			{\
	(uint16_t)((offset) & 0xffff), \
	(segment_selector), \
	0, \
	(((flags) & 0x0f) << 4) | ((type) & 0x0f), \
	(uint16_t)((offset) >> 16) \
}

#define IDT64_STATIC(offset, segment_selector, ist, type, flags)	{\
	(uint16_t)((offset) & 0xffff), \
	(segment_selector), \
	((ist) & 7), \
	(((flags) & 0x0f) << 4) | ((type) & 0x0f), \
	(uint16_t)(((offset) >> 16) & 0xffff), \
	(uint32_t)((offset) >> 32) \
}

#define IDT_TYPE_TASK				5
#define IDT_TYPE_INT16				6
#define IDT_TYPE_TRAP16				7

/**
 * @warning Only for 32-bit IDT!
 */
#define IDT_TYPE_INT32				14

/**
 * @warning Only for 32-bit IDT!
 */
#define IDT_TYPE_TRAP32				15

/**
 * @warning Only for 64-bit IDT!
 */
#define IDT_TYPE_INT64				14

/**
 * @warning Only for 64-bit IDT!
 */
#define IDT_TYPE_TRAP64				15

#define IDT_FLAG_DPL0				2
#define IDT_FLAG_DPL1				4
#define IDT_FLAG_PRESENT			8

#define IDT_NUM_ENTRIES				256

#define IDT_VECTOR_SCHEDULER_YIELD_HANDLER			0x40

#pragma pack(push, 1)
typedef struct _idt32_t {
	uint16_t			offset_low;

	// Code segment selector
	segment_selector_t	selector;
	uint8_t				reserved;
	uint8_t				type_flags;
	uint16_t			offset_high;
} idt32_t;

typedef struct _idt64_t {
	uint16_t			offset_low;

	// Code segment selector
	segment_selector_t	selector;
	uint8_t				ist;
	uint8_t				type_flags;
	uint16_t			offset_middle;
	uint32_t			offset_high;
	uint32_t			reserved;
} idt64_t;
#pragma pack(pop)

bool idt32_set_entry(
	size_t index,
	uint32_t offset, uint16_t segment_selector,
	uint8_t type, uint8_t flags
);

bool idt32_get_entry(size_t index, idt32_t* entry);

void idt32_init(void);

#endif