#pragma once
#ifndef __ACPI_XSDT_H
#define __ACPI_XSDT_H

#include "acpi_sdt_header.h"

// XSDT
#define ACPI_XSDT_SIGNATURE				0x54445358

#pragma pack(push, 1)
typedef struct _acpi_xsdt_t {
	uint32_t	signature;
	uint32_t	length;
	uint8_t		revision;
	uint8_t		checksum;
	char		oem_id[6];
	char		oem_table_id[8];
	uint32_t	oem_revision;
	uint32_t	creator_id;
	uint32_t	creator_revision;
	
	uint64_t	tables[ARRAY_LENGTH_VARIABLE];
} acpi_xsdt_t;
#pragma pack(pop)

#endif