#pragma once
#ifndef __ACPI_MADT_IOAPIC_H
#define __ACPI_MADT_IOAPIC_H

#include "acpi_sdt_header.h"
#include "acpi_madt_entry_header.h"

#define ACPI_MADT_RECORD_TYPE_IOAPIC						1

#pragma pack(push, 1)
typedef struct _acpi_madt_ioapic_t {
	acpi_madt_entry_header_t	header;

	uint8_t						ioapic_id;
	uint8_t						reserved;
	uint32_t					ioapic_base;
	uint32_t					global_system_interrupt_base;
} acpi_madt_ioapic_t;
#pragma pack(pop)

#endif