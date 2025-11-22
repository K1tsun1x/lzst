#pragma once
#ifndef __GDT_ACCESS_H
#define __GDT_ACCESS_H

#include "typedefs.h"

typedef enum _gdt_access_t ENUM_TYPE(uint8_t) {
	GDT_ACCESS_ACCESSED = 1,
	GDT_ACCESS_READABLE_WRITEABLE = 2,
	GDT_ACCESS_DIRECTION = 4,
	GDT_ACCESS_EXECUTABLE = 8,
	GDT_ACCESS_NOT_SYSTEM = 16,
	// GDT_ACCESS_DPL_LOW = 32,
	// GDT_ACCESS_DPL_HIGH = 64,
	GDT_ACCESS_PRESENT = 128
} gdt_access_t;

#endif