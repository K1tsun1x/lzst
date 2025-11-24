#pragma once
#ifndef __BOOT_MEM_REG_TYPE_H
#define __BOOT_MEM_REG_TYPE_H

#include "typedefs.h"

typedef enum _boot_mem_reg_type_t ENUM_TYPE(size_t) {
	BOOT_MEM_REG_TYPE_NORMAL = 1,					// usable
	BOOT_MEM_REG_TYPE_RESERVED = 2,				// unusable
	BOOT_MEM_REG_TYPE_ACPI = 3,					// can be used after reading ACPI tables
	BOOT_MEM_REG_TYPE_NVS = 4,						// unusable
	BOOT_MEM_REG_TYPE_UNUSABLE = 5,				// unusable
	BOOT_MEM_REG_TYPE_DISABLED = 6,				// unusable
	BOOT_MEM_REG_TYPE_PERSISTENT = 7,				// maybe usable(?)
	BOOT_MEM_REG_TYPE_UNACCEPTED = 8,				// ?
	BOOT_MEM_REG_TYPE_UNKNOWN = ((size_t)-1)
} boot_mem_reg_type_t;

#endif