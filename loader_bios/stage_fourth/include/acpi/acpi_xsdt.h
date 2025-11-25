#pragma once
#ifndef __ACPI_XSDT_H
#define __ACPI_XSDT_H

#include "acpi_sdt_header.h"

// XSDT
#define ACPI_XSDT_SIGNATURE				0x54445358

#pragma pack(push, 1)
typedef struct _acpi_xsdt_t {
	acpi_sdt_header_t	header;
	uint64_t			tables[ARRAY_LENGTH_VARIABLE];
} acpi_xsdt_t;
#pragma pack(pop)

#endif