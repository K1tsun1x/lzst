#pragma once
#ifndef __PAGING_H
#define __PAGING_H

#include <asm.h>
#include <pmm/pmm.h>
#include <critical-section/critical-section.h>
#include <spinlock/spinlock.h>
#include "paging_pde.h"
#include "paging_pte.h"

EXTERN_C void LOADERCALL paging_load_directory(const paging_pde_t* directory);
EXTERN_C paging_pde_t* LOADERCALL paging_get_directory(void);
EXTERN_C void LOADERCALL paging_enable(void);
EXTERN_C void LOADERCALL paging_invalidate(void);

/**
 * @warning Only for identity paging!
 */
bool paging_ensure_tables_present(paging_pde_t* directory, size_t start_index, size_t count, uint32_t flags);

/**
 * @warning Only for identity paging!
 */
bool paging_free_tables(paging_pde_t* directory, size_t start_index, size_t count);

/**
 * @warning Only for identity paging!
 */
bool paging_map_pages(paging_pde_t* directory, uintptr_t src_phys, uintptr_t dst_virt, size_t count, uint32_t flags);

/**
 * @warning Only for identity paging!
 */
bool paging_unmap_pages(paging_pde_t* directory, uintptr_t virt, size_t count);

#endif