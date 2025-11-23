#include <acpi_sdt_header.h>

bool acpi_sdt_header_validate(const acpi_sdt_header_t* acpi_sdt_header, uint32_t signature) {
	if (acpi_sdt_header->signature != signature) return false;

	uint8_t sum = 0;
	for (uint32_t i = 0; i < acpi_sdt_header->length; i++) sum += ((uint8_t*)acpi_sdt_header)[i];
	return sum == 0;
}