#pragma once
#ifndef __PAGING_PDE_H
#define __PAGING_PDE_H

#include <typedefs.h>
#include "paging_pde_flag.h"

#define PAGING_NUM_DIRECTORY_ENTRIES			1024
#define PAGING_DIRECTORY_SIZE					(sizeof(paging_pde_t) * PAGING_NUM_DIRECTORY_ENTRIES)
#define PAGING_MASK_PDE_FLAGS					0xfff
#define PAGING_MASK_PDE_ADDRESS					0xfffff000

// PAGING_PDE_FLAG_* | ...
typedef uint32_t	paging_pde_t;

#endif