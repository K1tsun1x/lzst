#pragma once
#ifndef __PMM_H
#define __PMM_H

#include <e820/e820.h>
#include "pmm_reg.h"
#include "pmm_page.h"

#define PMM_PAGE_SIZE				0x1000

size_t pmm_init(
	e820_reg_t* regs,
	size_t num_regs,
	const e820_reg_t* extra_regs,
	size_t num_extra_regs
);

#endif