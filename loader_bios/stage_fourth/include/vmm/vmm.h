#pragma once
#ifndef __VMM_H
#define __VMM_H

#include <pmm/pmm.h>
#include <paging/paging.h>

#define VMM_PAGE_SIZE				PMM_PAGE_SIZE

#define VMM_PHYS_TO_VIRT(...)		(__VA_ARGS__)

#define VMM_BLOCK_INFO_MAGIC		0xD34DB33F

typedef struct _vmm_allocation_t {
	size_t		virt_addr;
	uintptr_t	phys_addr;
} vmm_allocation_t;

typedef struct _vmm_block_info_t {
	uint32_t	magic;
	size_t		num_pages;
} vmm_block_info_t;

/**
 * @return Returns the index of the first page of the first free area of ​​the required size,
 * and if it could not be found, then SIZE_MAX
 */
size_t vmm_find_free_pages(const paging_pde_t* directory, size_t num_pages);

/**
 * @return Returns the virtual address to which pages will be mapped.
 * If it was not possible to find/allocate pages, then UINTPTR_MAX
 */
uintptr_t vmm_allocate_memory(paging_pde_t* directory, size_t num_bytes, uint32_t vmm_page_flags, uint32_t pmm_page_flags);

bool vmm_free_memory(paging_pde_t* directory, uintptr_t virt_address);

bool vmm_copy_memory(const paging_pde_t* dst_directory, uintptr_t dst_address, const void* src, size_t count);

#endif