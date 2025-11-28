#pragma once
#ifndef __ACPI_RSDT_H
#define __ACPI_RSDT_H

#include "acpi_sdt_header.h"

// RSDT
#define ACPI_RSDT_SIGNATURE				0x54445352

#pragma pack(push, 1)
typedef struct _acpi_rsdt_t {
	uint32_t	signature;
	uint32_t	length;
	uint8_t		revision;
	uint8_t		checksum;
	char		oem_id[6];
	char		oem_table_id[8];
	uint32_t	oem_revision;
	uint32_t	creator_id;
	uint32_t	creator_revision;
	
	uint32_t	tables[ARRAY_LENGTH_VARIABLE];
} acpi_rsdt_t;
#pragma pack(pop)

#endif