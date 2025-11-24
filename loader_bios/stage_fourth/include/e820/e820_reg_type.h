#pragma once
#ifndef __E820_REG_TYPE_H
#define __E820_REG_TYPE_H

#include <typedefs.h>

typedef enum _e820_reg_type_t ENUM_TYPE(size_t) {
	E820_REG_TYPE_NORMAL = 1,					// usable
	E820_REG_TYPE_RESERVED = 2,					// unusable
	E820_REG_TYPE_ACPI = 3,						// can be used after reading ACPI tables
	E820_REG_TYPE_NVS = 4,						// unusable
	E820_REG_TYPE_UNUSABLE = 5,					// unusable
	E820_REG_TYPE_DISABLED = 6,					// unusable
	E820_REG_TYPE_PERSISTENT = 7,				// maybe usable(?)
	E820_REG_TYPE_UNACCEPTED = 8,				// ?
	E820_REG_TYPE_UNKNOWN = ((size_t)-1)
} e820_reg_type_t;

#endif