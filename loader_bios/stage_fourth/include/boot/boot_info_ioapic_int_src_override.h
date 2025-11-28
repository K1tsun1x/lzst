#pragma once
#ifndef __BOOT_INFO_IOAPIC_INT_SRC_OVERRIDE_H
#define __BOOT_INFO_IOAPIC_INT_SRC_OVERRIDE_H

#include <typedefs.h>

typedef struct _boot_info_ioapic_int_src_override_t {
	uint8_t				bus;
	uint8_t				irq;
	uint32_t			gsi;
	uint16_t			flags;
} boot_info_ioapic_int_src_override_t;

#endif