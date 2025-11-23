#include <acpi_rsdp_xsdp.h>

bool acpi_rsdp_xsdp_validate(const void* acpi_rsdp) {
	acpi_rsdp_t* rsdp = (acpi_rsdp_t*)acpi_rsdp;
	if (memcmp(rsdp->signature, ACPI_RSDP_SIGNATURE, sizeof(rsdp->signature))) return false;

	uint8_t sum = 0;
	for (uint32_t i = 0; i < sizeof(acpi_rsdp_t); i++) sum += ((uint8_t*)rsdp)[i];
	if (sum != 0) return false;

	if (rsdp->revision >= 2) {
		acpi_xsdp_t* xsdp = (acpi_xsdp_t*)acpi_rsdp;
		for (uint32_t i = 0; i < xsdp->length; i++) sum += ((uint8_t*)xsdp)[i];
		if (sum != 0) return false;

		if (xsdp->xsdt_address == 0) return false;
	}
	else {
		if (rsdp->rsdt_address == 0) return false;
	}

	return true;
}