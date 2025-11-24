#pragma once
#ifndef __GDT_FLAG_H
#define __GDT_FLAG_H

#include <typedefs.h>

typedef enum _gdt_flag_t ENUM_TYPE(uint8_t) {
	// GDT_FLAG_RESERVED = 1,		// must be cleared(!)
	GDT_FLAG_LONG_MODE_CODE = 2,
	GDT_FLAG_SIZE = 4,
	GDT_FLAG_GRANULARITY = 8
} gdt_flag_t;

#endif