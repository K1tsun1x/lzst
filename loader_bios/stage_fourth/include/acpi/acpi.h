#pragma once
#ifndef __ACPI_H
#define __ACPI_H

#include <string.h>
#include <align.h>
#include "acpi_rsdp.h"
#include "acpi_xsdp.h"
#include "acpi_rsdt.h"
#include "acpi_xsdt.h"
#include "acpi_gas.h"
#include "acpi_fadt.h"
#include "acpi_madt.h"

bool acpi_validate_ptr(const void* acpi_rsdp_xsdp);
void* acpi_find_rsdp_xsdp(void);
void* acpi_find_sdt32(const acpi_rsdt_t* acpi_rsdt, uint32_t signature);
void* acpi_find_sdt64(const acpi_xsdt_t* acpi_xsdt, uint32_t signature);

#endif