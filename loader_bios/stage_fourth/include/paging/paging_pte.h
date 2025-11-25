#pragma once
#ifndef __PAGING_PTE_H
#define __PAGING_PTE_H

#include <typedefs.h>
#include "paging_pte_flag.h"

#define PAGING_NUM_TABLE_ENTRIES				1024
#define PAGING_TABLE_SIZE						(sizeof(paging_pte_t) * PAGING_NUM_TABLE_ENTRIES)
#define PAGING_MASK_PTE_FLAGS					0xfff

// PAGING_PTE_FLAG_* | ...
typedef uint32_t	paging_pte_t;

#endif