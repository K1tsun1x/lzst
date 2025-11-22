#pragma once
#ifndef __E820_ARD_TYPE_H
#define __E820_ARD_TYPE_H

#include "typedefs.h"

typedef enum _e820_ard_type_t ENUM_TYPE(uint32_t) {
	E820_ARD_TYPE_MEM = 1,			// usable
	E820_ARD_TYPE_RESERVED = 2,		// unusable
	E820_ARD_TYPE_ACPI = 3,			// can be used after reading ACPI tables
	E820_ARD_TYPE_NVS = 4,			// unusable
	E820_ARD_TYPE_UNUSABLE = 5,		// unusable
	E820_ARD_TYPE_DISABLED = 6,		// unusable
	E820_ARD_TYPE_PERSISTENT = 7,	// maybe usable(?)
	E820_ARD_TYPE_UNACCEPTED = 8,	// ?
} e820_ard_type_t;

#endif