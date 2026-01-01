#pragma once
#ifndef __SYS_INFO_IOAPIC_H
#define __SYS_INFO_IOAPIC_H

#include <typedefs.h>

typedef struct _sys_info_ioapic_t {
	uint8_t			ioapic_id;
	uint32_t		ioapic_base;
	uint32_t		ioapic_gsib;
} sys_info_ioapic_t;

#endif