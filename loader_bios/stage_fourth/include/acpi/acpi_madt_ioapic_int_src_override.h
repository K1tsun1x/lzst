#pragma once
#ifndef __ACPI_MADT_IOAPIC_INT_SRC_OVERRIDE_H
#define __ACPI_MADT_IOAPIC_INT_SRC_OVERRIDE_H

#include "acpi_sdt_header.h"

#define ACPI_MADT_RECORD_TYPE_IOAPIC_INT_SRC_OVERRIDE		2

#pragma pack(push, 1)
typedef struct _acpi_madt_ioapic_int_src_override_t {
	uint8_t			entry_type;
	uint8_t			record_length;

	uint8_t			bus_src;
	uint8_t			irq_src;
	uint32_t		global_system_interrupt;
	uint16_t		flags;
} acpi_madt_ioapic_int_src_override_t;
#pragma pack(pop)

#endif