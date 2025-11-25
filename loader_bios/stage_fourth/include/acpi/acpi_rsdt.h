#pragma once
#ifndef __ACPI_RSDT_H
#define __ACPI_RSDT_H

#include "acpi_sdt_header.h"

// RSDT
#define ACPI_RSDT_SIGNATURE				0x54445352

#pragma pack(push, 1)
typedef struct _acpi_rsdt_t {
	acpi_sdt_header_t	header;
	uint32_t			tables[ARRAY_LENGTH_VARIABLE];
} acpi_rsdt_t;
#pragma pack(pop)

#endif