#pragma once
#ifndef __SYS_INFO_LAPIC_H
#define __SYS_INFO_LAPIC_H

#include <typedefs.h>

typedef struct _sys_info_lapic_t {
	uint8_t			acpi_processor_id;
	uint8_t			apic_id;
	uint32_t		flags;
	bool			bsp;
} sys_info_lapic_t;

#endif