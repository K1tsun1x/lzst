#pragma once
#ifndef __ACPI_MADT_LAPIC_ADDRESS_OVERRIDE_H
#define __ACPI_MADT_LAPIC_ADDRESS_OVERRIDE_H

#include "acpi_sdt_header.h"

#define ACPI_MADT_RECORD_TYPE_LAPIC_ADDRESS_OVERRIDE		5

#pragma pack(push, 1)
typedef struct _acpi_madt_lapic_address_override_t {
	uint8_t			entry_type;
	uint8_t			record_length;

	uint8_t			reserved[2];
	uint64_t		lapic_address;
} acpi_madt_lapic_address_override_t;
#pragma pack(pop)

#endif