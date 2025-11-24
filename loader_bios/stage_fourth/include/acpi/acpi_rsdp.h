#pragma once
#ifndef __ACPI_RSDP_H
#define __ACPI_RSDP_H

#include <typedefs.h>

#define ACPI_RSDP_SIGNATURE				"RSD PTR "

#pragma pack(push, 1)
typedef struct _acpi_rsdp_t {
	char		signature[8];
	uint8_t		checksum;
	char		oem_id[6];
	uint8_t		revision;
	uint32_t	rsdt_address;			// deprecated since version 2.0
} acpi_rsdp_t;
#pragma pack(pop)

#endif