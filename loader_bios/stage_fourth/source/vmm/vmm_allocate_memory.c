#include <vmm/vmm.h>

uintptr_t vmm_allocate_memory(paging_pde_t* directory, size_t num_bytes, uint32_t vmm_page_flags, uint32_t pmm_page_flags) {
	ENTER_CRITICAL_SECTION();

	const size_t num_pages = ALIGN_UP_P2(num_bytes, VMM_PAGE_SIZE) / VMM_PAGE_SIZE;
	const size_t virt_index = vmm_find_free_pages(directory, num_pages + 1);
	if (virt_index == SIZE_MAX) {
		EXIT_CRITICAL_SECTION();
		return UINTPTR_MAX;
	}
	
	const uintptr_t block_info_virt_address = virt_index << 12;
	const uintptr_t block_info_phys_address = (uintptr_t)pmm_allocate_memory(VMM_PAGE_SIZE, 0);
	vmm_block_info_t* block_info = (vmm_block_info_t*)VMM_PHYS_TO_VIRT(block_info_phys_address);
	if (!block_info) {
		EXIT_CRITICAL_SECTION();
		return UINTPTR_MAX;
	}

	block_info->magic = VMM_BLOCK_INFO_MAGIC;
	block_info->num_pages = num_pages;
	if (!paging_map_pages(directory, (uintptr_t)block_info, block_info_virt_address, 1, PAGING_PTE_FLAG_READ_WRITE)) {
		pmm_free_memory(block_info);
		EXIT_CRITICAL_SECTION();
		return UINTPTR_MAX;
	}

	uintptr_t base_virt_address = block_info_virt_address + VMM_PAGE_SIZE;
	size_t num_allocations = 0;
	size_t cur_num_pages = num_pages;
	uintptr_t virt_address = base_virt_address;
	const uintptr_t allocations_phys_address = (uintptr_t)pmm_allocate_memory(sizeof(vmm_allocation_t) * num_pages, 0);
	vmm_allocation_t* allocations = (vmm_allocation_t*)VMM_PHYS_TO_VIRT(allocations_phys_address);
	for (size_t i = 0; i < num_pages; i++) {
		uintptr_t phys_page = (uintptr_t)pmm_allocate_memory(VMM_PAGE_SIZE, pmm_page_flags);
		if (!phys_page) break;

		allocations[num_allocations].virt_addr = virt_address;
		allocations[num_allocations++].phys_addr = phys_page;

		if (!paging_map_pages(directory, phys_page, virt_address, 1, vmm_page_flags)) break;
		virt_address += VMM_PAGE_SIZE;
		cur_num_pages -= 1;
	}

	if (cur_num_pages) {
		for (size_t i = 0; i < num_allocations; i++) {
			paging_unmap_pages(directory, allocations[i].virt_addr, 1);
			pmm_free_memory((void*)(allocations[i].phys_addr));
		}

		paging_unmap_pages(directory, block_info_virt_address, 1);
		pmm_free_memory(block_info);

		base_virt_address = UINTPTR_MAX;
	}

	if (allocations) pmm_free_memory(allocations);
	
	EXIT_CRITICAL_SECTION();
	return base_virt_address;
}