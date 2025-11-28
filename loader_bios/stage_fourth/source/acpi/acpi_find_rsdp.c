#include <acpi/acpi.h>

void* acpi_find_rsdp(void) {
	const uint32_t ebda_base = (uint32_t)(((uint32_t)*((uint16_t*)0x040e)) << 4);
	const uint32_t ebda_end = ebda_base + 0x20000;
	uint32_t address = ALIGN_UP_P2(ebda_base, 16);
	while (address < ebda_end) {
		acpi_xsdp_t* xsdp = (acpi_xsdp_t*)address;
		if (!acpi_validate_ptr(xsdp)) {
			address += 16;
			continue;
		}

		return xsdp;
	}

	const uint32_t reg_base = 0xe0000;
	const uint32_t reg_end = reg_base + 0x20000;
	address = ALIGN_UP_P2(reg_base, 16);
	while (address < reg_end) {
		acpi_xsdp_t* xsdp = (acpi_xsdp_t*)address;
		if (!acpi_validate_ptr(xsdp)) {
			address += 16;
			continue;
		}

		return xsdp;
	}

	return NULL;
}