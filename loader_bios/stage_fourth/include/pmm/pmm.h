#pragma once
#ifndef __PMM_H
#define __PMM_H

#include <e820/e820.h>
#include "pmm_reg.h"
#include "pmm_page.h"

size_t pmm_init(
	e820_reg_t* mem_regs,
	const size_t num_mem_regs,
	const e820_reg_t* extra_regs,
	const size_t num_extra_regs
);

#endif