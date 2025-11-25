#pragma once
#ifndef __ACPI_FADT_H
#define __ACPI_FADT_H

#include "acpi_sdt_header.h"
#include "acpi_gas.h"

// FACP
#define ACPI_FADT_SIGNATURE				0x50434146

#pragma pack(push, 1)
typedef struct _acpi_fadt_t {
	acpi_sdt_header_t			sdt_header;
	uint32_t					firmware_ctrl;
    uint32_t					dsdt;

    // field used in ACPI 1.0; no longer in use, for compatibility only
    uint8_t						reserved;

    uint8_t						preferred_power_management_profile;
    uint16_t					sci_interrupt;
    uint32_t					smi_command_port;
    uint8_t						acpi_enable;
    uint8_t						acpi_disable;
    uint8_t						s4_bios_reg;
    uint8_t						pstate_control;
    uint32_t					pm1a_event_block;
    uint32_t					pm1b_event_block;
    uint32_t					pm1a_control_block;
    uint32_t					pm1b_control_block;
    uint32_t					pm2_control_block;
    uint32_t					pm_timer_block;
    uint32_t					gpe0_block;
    uint32_t					gpe1_block;
    uint8_t						pm1_event_length;
    uint8_t						pm1_control_length;
    uint8_t						pm2_control_length;
    uint8_t						pm_timer_length;
    uint8_t						gpe0_length;
    uint8_t						gpe1_length;
    uint8_t						gpe1_base;
    uint8_t						cstate_control;
    uint16_t					worst_c2_latency;
    uint16_t					worst_c3_latency;
    uint16_t					flush_size;
    uint16_t					flush_stride;
    uint8_t						duty_offset;
    uint8_t						duty_width;
    uint8_t						day_alarm;
    uint8_t						month_alarm;
    uint8_t						century;

    // reserved in ACPI 1.0; used since ACPI 2.0+

    uint16_t					boot_architecture_flag;

    uint8_t						reserved2;
    uint32_t					flags;

    acpi_gas_t					reset_reg;

    uint8_t						reset_value;
    uint8_t						reserved3[3];
  
    // 64-bit pointers - Available on ACPI 2.0+

    uint64_t					x_firmware_control;
    uint64_t					x_dsdt;

    acpi_gas_t					x_pm1a_event_block;
    acpi_gas_t					x_pm1b_event_block;
    acpi_gas_t					x_pm1a_control_block;
    acpi_gas_t					x_pm1b_control_block;
    acpi_gas_t					x_pm2_control_block;
    acpi_gas_t					x_pm_timer_block;
    acpi_gas_t					x_gpe0_block;
    acpi_gas_t					x_gpe1_block;
} acpi_fadt_t;
#pragma pack(pop)

#endif