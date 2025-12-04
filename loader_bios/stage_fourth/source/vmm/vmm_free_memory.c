#include <vmm/vmm.h>

bool vmm_free_memory(paging_pde_t* directory, uintptr_t virt_address) {
	if (virt_address & 0xfff) return false;

	const uintptr_t header_virt = virt_address - VMM_PAGE_SIZE;
	const size_t pde_index = (header_virt >> 22) & 0x3ff;
	const size_t pte_index = (header_virt >> 12) & 0x3ff;

	ENTER_CRITICAL_SECTION();
	if (!(directory[pde_index] & PAGING_PDE_FLAG_PRESENT)) {
		EXIT_CRITICAL_SECTION();
		return false;
	}

	const uintptr_t pt_phys = (uintptr_t)(directory[pde_index] & PAGING_MASK_PDE_ADDRESS);
	paging_pte_t* pt = (paging_pte_t*)pt_phys;
	if (!(pt[pte_index] & PAGING_PTE_FLAG_PRESENT)) {
		EXIT_CRITICAL_SECTION();
		return false;
	}

	const uintptr_t block_info_phys = (uintptr_t)(pt[pte_index] & PAGING_MASK_PTE_ADDRESS);
	vmm_block_info_t* block_info = (vmm_block_info_t*)VMM_PHYS_TO_VIRT(block_info_phys);
	if (block_info->magic != VMM_BLOCK_INFO_MAGIC) {
		EXIT_CRITICAL_SECTION();
		return false;
	}

	const size_t num_pages = block_info->num_pages + 1;
	bool res = paging_unmap_pages(directory, header_virt, num_pages);

	EXIT_CRITICAL_SECTION();
	return res;
}