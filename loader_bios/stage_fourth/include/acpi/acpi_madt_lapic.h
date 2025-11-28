#pragma once
#ifndef __ACPI_MADT_LAPIC_H
#define __ACPI_MADT_LAPIC_H

#include "acpi_sdt_header.h"
#include "acpi_madt_entry_header.h"

#define ACPI_MADT_RECORD_TYPE_LAPIC							0

#define ACPI_MADT_LAPIC_FLAG_PROCESSOR_ENABLED				1
#define ACPI_MADT_LAPIC_FLAG_ONLINE_CAPABLE					2

#pragma pack(push, 1)
typedef struct _acpi_madt_lapic_t {
	acpi_madt_entry_header_t	header;

	uint8_t						acpi_processor_id;
	uint8_t						apic_id;
	// ACPI_MADT_LAPIC_FLAG_* | ...
	uint32_t					flags;
} acpi_madt_lapic_t;
#pragma pack(pop)

#endif