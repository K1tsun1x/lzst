#pragma once
#ifndef __ACPI_MADT_IOAPIC_NMI_SRC_H
#define __ACPI_MADT_IOAPIC_NMI_SRC_H

#include "acpi_sdt_header.h"

#define ACPI_MADT_RECORD_TYPE_IOAPIC_NSO				3

#pragma pack(push, 1)
// I/O APIC NMI Source Override
typedef struct _acpi_madt_ioapic_nso_t {
	uint8_t			entry_type;
	uint8_t			record_length;

	uint8_t			nmi_src;
	uint8_t			reserved;
	uint16_t		flags;
	uint32_t		global_system_interrupt;
} acpi_madt_ioapic_nso_t;
#pragma pack(pop)

#endif