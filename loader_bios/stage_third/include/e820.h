#pragma once
#ifndef __E820_H
#define __E820_H

#include "e820_ard.h"
#include "mem_phys_reg.h"

#define E820_SMAP_SIGNATURE				0x534d4150

bool e820_get_map(boot_mem_reg_t* buffer, size_t max_len, size_t* out_len);

#endif