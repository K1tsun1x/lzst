#pragma once
#ifndef __ACPI_MADT_LAPIC_NMI_SRC_H
#define __ACPI_MADT_LAPIC_NMI_SRC_H

#include "acpi_sdt_header.h"

#define ACPI_MADT_RECORD_TYPE_LAPIC_NMI_SRC					4

#pragma pack(push, 1)
typedef struct _acpi_madt_lapic_nmi_t {
	uint8_t			entry_type;
	uint8_t			record_length;

	uint8_t			acpi_processor_id;
	uint16_t		flags;
	uint8_t			lint_number;
} acpi_madt_lapic_nmi_t;
#pragma pack(pop)

#endif