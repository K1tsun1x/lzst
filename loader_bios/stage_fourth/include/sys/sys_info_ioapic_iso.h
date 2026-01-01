#pragma once
#ifndef __SYS_INFO_IOAPIC_ISO_H
#define __SYS_INFO_IOAPIC_ISO_H

#include <typedefs.h>

// I/O APIC Interrupt Source Override
typedef struct _sys_info_ioapic_iso_t {
	uint8_t				bus;
	uint8_t				irq;
	uint32_t			gsi;
	uint16_t			flags;
} sys_info_ioapic_iso_t;

#endif