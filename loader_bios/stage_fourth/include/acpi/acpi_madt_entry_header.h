#pragma once
#ifndef __ACPI_MADT_ENTRY_HEADER_H
#define __ACPI_MADT_ENTRY_HEADER_H

#include <typedefs.h>

#define ACPI_MADT_ENTRY_TYPE_LAPIC				0x00
#define ACPI_MADT_ENTRY_TYPE_IOAPIC				0x01
#define ACPI_MADT_ENTRY_TYPE_IOAPIC_INT_SRC_OVERRIDE	0x02

#pragma pack(push, 1)
typedef struct _acpi_madt_entry_header_t {
	uint8_t			type;
	uint8_t			length;
} acpi_madt_entry_header_t;
#pragma pack(pop)

#endif