#include <acpi/acpi.h>

void* acpi_find_sdt64(const acpi_xsdt_t* acpi_xsdt, uint32_t signature) {
	const size_t num_entries = (acpi_xsdt->header.length - sizeof(acpi_xsdt->header)) / 8;

	for (size_t i = 0; i < num_entries; i++) {
		acpi_sdt_header_t* acpi_sdt_header = (acpi_sdt_header_t*)(uintptr_t)acpi_xsdt->tables[i];
		if (!acpi_validate_sdt_header(acpi_sdt_header, signature)) continue;

		return (void*)acpi_sdt_header;
	}

	return NULL;
}