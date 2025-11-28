#pragma once
#ifndef __BOOT_INFO_IOAPIC_H
#define __BOOT_INFO_IOAPIC_H

#include <typedefs.h>

typedef struct _boot_info_ioapic_t {
	uint8_t			ioapic_id;
	uint32_t		ioapic_base;
	uint32_t		ioapic_gsib;
} boot_info_ioapic_t;

#endif