#pragma once
#ifndef __GDT_H
#define __GDT_H

#include "gdtr.h"

#define GDT32_STATIC(limit, base, access, flags)		{ \
	(limit) & 0xffff, \
	(base) & 0xffff, \
	((base) >> 16) & 0xff, \
	(access), \
	(((flags) & 0x0f) << 4) | (((limit) >> 16) & 0x0f), \
	(base) >> 24 \
}

#define GDT64_STATIC(limit, base, access, flags)		{ \
	(limit) & 0xffff, \
	(base) & 0xffff, \
	((base) >> 16) & 0xff, \
	(access), \
	(((flags) & 0x0f) << 4) | (((limit) >> 16) & 0x0f), \
	((base) >> 24) & 0xff, \
	(base) >> 32, \
	0 \
}

#define GDT_ACCESS_ACCESSED								1
#define GDT_ACCESS_READABLE_WRITEABLE					2
#define GDT_ACCESS_DIRECTION							4
#define GDT_ACCESS_EXECUTABLE							8
#define GDT_ACCESS_NOT_SYSTEM							16
#define GDT_ACCESS_DPL0									32
#define GDT_ACCESS_DPL1									64
#define GDT_ACCESS_PRESENT								128

#define GDT_FLAG_LONG_MODE_CODE							2
#define GDT_FLAG_SIZE									4
#define GDT_FLAG_GRANULARITY							8

#pragma pack(push, 1)
typedef struct _gdt32_t {
	uint16_t			limit_low;
	uint16_t			base_low;
	uint8_t				base_middle;
	uint8_t				access;				// GDT_ACCESS_* | ...
	uint8_t				limit_high_flags;	// flags = GDT_FLAG_* | ...
	uint8_t				base_high;
} gdt32_t;

typedef struct _gdt64_t {
	uint16_t			limit_low;
	uint16_t			base_low;
	uint8_t				base_middle;
	uint8_t				access;				// GDT_ACCESS_* | ...
	uint8_t				limit_high_flags;	// flags = GDT_FLAG_* | ...
	uint8_t				base_high_low;
	uint32_t			base_high_high;
	uint32_t			reserved;
} gdt64_t;
#pragma pack(pop)

static inline void gdt_init32(
	gdt32_t* dst,
	uint32_t limit,
	uint32_t base,
	uint8_t access,
	uint8_t flags
) {
	if (!dst) return;

	dst->limit_low = limit & 0xffff;
	dst->base_low = base & 0xffff;
	dst->base_middle = (base >> 16) & 0xff;
	dst->access = access;
	dst->limit_high_flags = ((flags & 0x0f) << 4) | (((limit) >> 16) & 0x0f);
	dst->base_high = base >> 24;
}

static inline void gdt_init64(
	gdt64_t* dst,
	uint32_t limit,
	uint64_t base,
	uint8_t access,
	uint8_t flags
) {
	dst->limit_low = limit & 0xffff;
	dst->base_low = base & 0xffff;
	dst->base_middle = (base >> 16) & 0xff;
	dst->access = access;
	dst->limit_high_flags = ((flags & 0x0f) << 4) | (((limit) >> 16) & 0x0f);
	dst->base_high_low = (base >> 24) & 0xff;
	dst->base_high_high = base >> 32;
	dst->reserved = 0;
}

#endif