#pragma once
#ifndef __GDT_ACCESS_TYPE_H
#define __GDT_ACCESS_TYPE_H

#include "typedefs.h"

/**
 * @warning Only for system segment descriptor(!)
 */
typedef enum _gdt_access_type_t ENUM_TYPE(uint8_t) {
	GDT_ACCESS_TYPE_TSS16 = 1,
	GDT_ACCESS_TYPE_LDT = 2,
	GDT_ACCESS_TYPE_BUSY_TSS16 = 3,
	GDT_ACCESS_TYPE_TSS32_64 = 9,
	GDT_ACCESS_TYPE_BUSY_TSS32_64 = 11
} gdt_access_type_t;

#endif