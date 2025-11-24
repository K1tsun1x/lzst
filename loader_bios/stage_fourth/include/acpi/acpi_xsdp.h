#pragma once
#ifndef __ACPI_XSDP_H
#define __ACPI_XSDP_H

#include <typedefs.h>

#define ACPI_XSDP_SIGNATURE				"RSD PTR "

#pragma pack(push, 1)
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

#endif