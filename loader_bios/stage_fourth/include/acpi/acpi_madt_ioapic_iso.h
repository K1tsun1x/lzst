#pragma once
#ifndef __ACPI_MADT_IOAPIC_ISO_H
#define __ACPI_MADT_IOAPIC_ISO_H

#include "acpi_sdt_header.h"
#include "acpi_madt_entry_header.h"

#define ACPI_MADT_RECORD_TYPE_IOAPIC_ISO		2

#pragma pack(push, 1)
// I/O APIC Interrupt Source Override
typedef struct _acpi_madt_ioapic_iso_t {
	acpi_madt_entry_header_t	header;

	uint8_t						bus_src;
	uint8_t						irq_src;
	uint32_t					global_system_interrupt;
	uint16_t					flags;
} acpi_madt_ioapic_iso_t;
#pragma pack(pop)

#endif