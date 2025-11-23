#pragma once
#ifndef __ACPI_SDT_HEADER_H
#define __ACPI_SDT_HEADER_H

#include "typedefs.h"

typedef enum _acpi_sdt_header_signature_t ENUM_TYPE(uint32_t) {
	ACPI_SDT_HEADER_SIGNATURE_RSDT = 0x54445352,
	ACPI_SDT_HEADER_SIGNATURE_XSDT = 0x54445358,
	ACPI_SDT_HEADER_SIGNATURE_FADT = 0x50434146,
	ACPI_SDT_HEADER_SIGNATURE_DSDT = 0x54445344
} acpi_sdt_header_signature_t;

#pragma pack(push, 1)
typedef struct _acpi_sdt_header_t {
	uint32_t	signature;
	uint32_t	length;
	uint8_t		revision;
	uint8_t		checksum;
	char		oem_id[6];
	char		oem_table_id[8];
	uint32_t	oem_revision;
	uint32_t	creator_id;
	uint32_t	creator_revision;
} acpi_sdt_header_t;
#pragma pack(pop)

bool acpi_sdt_header_validate(const acpi_sdt_header_t* acpi_sdt_header, uint32_t signature);

#endif