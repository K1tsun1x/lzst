#pragma once
#ifndef __ACPI_MADT_H
#define __ACPI_MADT_H

#include "acpi_sdt_header.h"

#define ACPI_MADT_SIGNATURE							0x43495041

#define ACPI_MADT_FLAG_DUAL_8259					1

#pragma pack(push, 1)
typedef struct _acpi_madt_t {
	acpi_sdt_header_t			sdt_header;
	uint32_t					local_apic_address;
	uint32_t					flags;
	
	void*						records;
} acpi_madt_t;
#pragma pack(pop)

#endif