#pragma once
#ifndef __ACPI_MADT_LX2APIC_H
#define __ACPI_MADT_LX2APIC_H

#include "acpi_sdt_header.h"

#define ACPI_MADT_RECORD_TYPE_LX2APIC						9

#define ACPI_MADT_LX2APIC_FLAG_PROCESSOR_ENABLED			1
#define ACPI_MADT_LX2APIC_FLAG_ONLINE_CAPABLE				2

#pragma pack(push, 1)
typedef struct _acpi_madt_lapic_address_override_t {
	uint8_t			entry_type;
	uint8_t			record_length;

	uint8_t			reserved[2];
	uint32_t		lx2apic_id;

	// ACPI_MADT_LX2APIC_FLAG_* | ...
	uint32_t		flags;
	uint32_t		acpi_id;
} acpi_madt_lapic_address_override_t;
#pragma pack(pop)

#endif