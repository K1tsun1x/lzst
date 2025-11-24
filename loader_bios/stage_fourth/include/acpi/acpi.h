#pragma once
#ifndef __ACPI_H
#define __ACPI_H

#include <string.h>
#include "acpi_rsdp.h"
#include "acpi_xsdp.h"
#include "acpi_sdt_header.h"

bool acpi_validate_ptr(const void* acpi_rsdp_xsdp);

#endif