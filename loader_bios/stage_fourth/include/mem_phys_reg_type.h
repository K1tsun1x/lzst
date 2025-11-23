#pragma once
#ifndef __MEM_PHYS_REG_TYPE_H
#define __MEM_PHYS_REG_TYPE_H

#include "typedefs.h"

typedef enum _mem_phys_reg_type_t ENUM_TYPE(size_t) {
	MEM_PHYS_REG_TYPE_NORMAL = 1,					// usable
	MEM_PHYS_REG_TYPE_RESERVED = 2,				// unusable
	MEM_PHYS_REG_TYPE_ACPI = 3,					// can be used after reading ACPI tables
	MEM_PHYS_REG_TYPE_NVS = 4,						// unusable
	MEM_PHYS_REG_TYPE_UNUSABLE = 5,				// unusable
	MEM_PHYS_REG_TYPE_DISABLED = 6,				// unusable
	MEM_PHYS_REG_TYPE_PERSISTENT = 7,				// maybe usable(?)
	MEM_PHYS_REG_TYPE_UNACCEPTED = 8,				// ?
	MEM_PHYS_REG_TYPE_UNKNOWN = ((size_t)-1)
} mem_phys_reg_type_t;

#endif