#include <boot/boot_info.h>

status_t boot_info_parse_acpi_tables(boot_info_t* boot_info) {
	boot_info->acpi_rsdp_address = 0;
	boot_info->acpi_rsdp_version = 0;
	boot_info->acpi_rsdt_address = 0;
	boot_info->acpi_fadt_address = 0;
	boot_info->acpi_madt_address = 0;
	
	uint64_t acpi_rsdp_address = (uint64_t)(uintptr_t)acpi_find_rsdp();
	if (!acpi_rsdp_address) return STATUS_NOT_FOUND;

	boot_info->acpi_rsdp_address = (uint32_t)(acpi_rsdp_address & 0xffffffff);
	boot_info->acpi_rsdp_version = ((acpi_rsdp_t*)((uintptr_t)acpi_rsdp_address))->revision;
	acpi_rsdp_t* rsdp = (acpi_rsdp_t*)(uintptr_t)boot_info->acpi_rsdp_address;
	acpi_xsdp_t* xsdp = (acpi_xsdp_t*)(uintptr_t)boot_info->acpi_rsdp_address;

	if (rsdp->revision >= 2) {
		acpi_xsdt_t* xsdt = (acpi_xsdt_t*)(uintptr_t)xsdp->xsdt_address;
		if (
			!acpi_validate_sdt_header((acpi_sdt_header_t*)xsdt, ACPI_XSDT_SIGNATURE)
		) return STATUS_INVALID_HEADER;
#ifndef X64

		if (xsdp->xsdt_address > 0xffffffff) return STATUS_UNREACHABLE;

#endif
		boot_info->acpi_rsdt_address = (uint32_t)(xsdp->xsdt_address & 0xffffffff);
		boot_info->acpi_fadt_address = (uint32_t)(uintptr_t)acpi_find_sdt64(xsdt, ACPI_FADT_SIGNATURE);
		boot_info->acpi_madt_address = (uint32_t)(uintptr_t)acpi_find_sdt64(xsdt, ACPI_MADT_SIGNATURE);
	}
	else {
		acpi_rsdt_t* rsdt = (acpi_rsdt_t*)rsdp->rsdt_address;
		if (
			!acpi_validate_sdt_header((acpi_sdt_header_t*)rsdt, ACPI_RSDT_SIGNATURE)
		) return STATUS_INVALID_HEADER;

		boot_info->acpi_rsdt_address = rsdp->rsdt_address;
		boot_info->acpi_fadt_address = (uint32_t)(uintptr_t)acpi_find_sdt32(rsdt, ACPI_FADT_SIGNATURE);
		boot_info->acpi_madt_address = (uint32_t)(uintptr_t)acpi_find_sdt32(rsdt, ACPI_MADT_SIGNATURE);
	}

	if (!boot_info->acpi_madt_address) return STATUS_OK;

	acpi_madt_t* madt = (acpi_madt_t*)boot_info->acpi_madt_address;
	boot_info->lapics = (boot_info_lapic_t*)dynarr_create(sizeof(boot_info_lapic_t), 0);
	boot_info->ioapics = (boot_info_ioapic_t*)dynarr_create(sizeof(boot_info_ioapic_t), 0);
	boot_info->ioapic_int_src_overrides = (boot_info_ioapic_int_src_override_t*)dynarr_create(sizeof(boot_info_ioapic_int_src_override_t), 0);
	if (
		!boot_info->lapics ||
		!boot_info->ioapics ||
		!boot_info->ioapic_int_src_overrides
	) return STATUS_NO_MEMORY;

	boot_info->num_lapics = 0;
	boot_info->num_ioapics = 0;
	boot_info->num_ioapic_int_src_overrides = 0;

	acpi_madt_entry_header_t* entry = madt->entries;
	const uint32_t bsp_lapic_id = lapic_read(LAPIC_REG_ID) << 24;
	const uintptr_t madt_end = (uintptr_t)madt + madt->header.length;
	while ((uintptr_t)entry < madt_end) {
		switch (entry->type) {
			case ACPI_MADT_ENTRY_TYPE_LAPIC: {
				acpi_madt_lapic_t* lapic = (acpi_madt_lapic_t*)entry;

				boot_info_lapic_t el;
				el.acpi_processor_id = lapic->acpi_processor_id;
				el.apic_id = lapic->apic_id;
				el.flags = lapic->flags;
				el.bsp = el.apic_id == bsp_lapic_id;

				boot_info_lapic_t* da = (boot_info_lapic_t*)dynarr_append(boot_info->lapics, &el);
				if (!da) return STATUS_NO_MEMORY;

				boot_info->lapics = da;
				boot_info->num_lapics += 1;
				break;
			}
			case ACPI_MADT_ENTRY_TYPE_IOAPIC: {
				acpi_madt_ioapic_t* ioapic = (acpi_madt_ioapic_t*)entry;

				boot_info_ioapic_t el;
				el.ioapic_id = ioapic->ioapic_id;
				el.ioapic_base = ioapic->ioapic_base;
				el.ioapic_gsib = ioapic->global_system_interrupt_base;
				
				boot_info_ioapic_t* da = (boot_info_ioapic_t*)dynarr_append(boot_info->ioapics, &el);
				if (!da) return STATUS_NO_MEMORY;

				boot_info->ioapics = da;
				boot_info->num_ioapics += 1;
				break;
			}
			case ACPI_MADT_ENTRY_TYPE_IOAPIC_INT_SRC_OVERRIDE: {
				acpi_madt_ioapic_int_src_override_t* int_src_ovrd = (acpi_madt_ioapic_int_src_override_t*)entry;

				boot_info_ioapic_int_src_override_t el;
				el.bus = int_src_ovrd->bus_src;
				el.irq = int_src_ovrd->irq_src;
				el.gsi = int_src_ovrd->global_system_interrupt;
				el.flags = int_src_ovrd->flags;

				boot_info_ioapic_int_src_override_t* da = (boot_info_ioapic_int_src_override_t*)dynarr_append(boot_info->ioapic_int_src_overrides, &el);
				if (!da) return STATUS_NO_MEMORY;

				boot_info->ioapic_int_src_overrides = da;
				boot_info->num_ioapic_int_src_overrides += 1;
				break;
			}
			default: break;
		}

		entry = (acpi_madt_entry_header_t*)((uintptr_t)entry + entry->length);
	}

	return STATUS_OK;
}