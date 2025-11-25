#pragma once
#ifndef __ACPI_GAS_H
#define __ACPI_GAS_H

#include "acpi_gas_address_space.h"
#include "acpi_gas_access_size.h"

#pragma pack(push, 1)
// ACPI Generic Access Structure
typedef struct _acpi_gas_t {
	// ACPI_GAS_ADDRESS_SPACE_*
	uint8_t		address_space;
	uint8_t		bit_width;
	uint8_t		bit_offset;

	// ACPI_GAS_ADDRESS_SIZE_*
	uint8_t		access_size;
	uint64_t	address;
} acpi_gas_t;
#pragma pack(pop)

#endif