#include <acpi/acpi.h>

void* acpi_find_sdt32(const acpi_rsdt_t* acpi_rsdt, uint32_t signature) {
	const size_t num_entries = (acpi_rsdt->header.length - sizeof(acpi_rsdt->header)) / 4;

	for (size_t i = 0; i < num_entries; i++) {
		acpi_sdt_header_t* acpi_sdt_header = (acpi_sdt_header_t*)acpi_rsdt->tables[i];
		if (!acpi_validate_sdt_header(acpi_sdt_header, signature)) continue;

		return (void*)acpi_sdt_header;
	}

	return NULL;
}