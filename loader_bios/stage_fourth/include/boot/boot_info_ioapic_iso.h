#pragma once
#ifndef __BOOT_INFO_IOAPIC_ISO_H
#define __BOOT_INFO_IOAPIC_ISO_H

#include <typedefs.h>

// I/O APIC Interrupt Source Override
typedef struct _boot_info_ioapic_iso_t {
	uint8_t				bus;
	uint8_t				irq;
	uint32_t			gsi;
	uint16_t			flags;
} boot_info_ioapic_iso_t;

#endif