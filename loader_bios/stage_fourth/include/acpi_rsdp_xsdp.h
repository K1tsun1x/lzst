#pragma once
#ifndef __ACPI_RSDP_XSDP_H
#define __ACPI_RSDP_XSDP_H

#include "typedefs.h"
#include "min_string.h"

#define ACPI_RSDP_SIGNATURE				"RSD PTR "
#define ACPI_XSDP_SIGNATURE				ACPI_RSDP_SIGNATURE

#pragma pack(push, 1)
typedef struct _acpi_rsdp_t {
	char		signature[8];
	uint8_t		checksum;
	char		oem_id[6];
	uint8_t		revision;
	uint32_t	rsdt_address;			// deprecated since version 2.0
} acpi_rsdp_t;

typedef struct _acpi_xsdp_t {
	char		signature[8];
	uint8_t		checksum;
	char		oem_id[6];
	uint8_t		revision;
	uint32_t	rsdt_address;			// deprecated since version 2.0

	uint32_t	length;
	uint64_t	xsdt_address;
	uint8_t		extended_checksum;
	uint8_t		reserved[3];
} acpi_xsdp_t;
#pragma pack(pop)

bool acpi_rsdp_xsdp_validate(const void* acpi_rsdp_xsdp);

#endif