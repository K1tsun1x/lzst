#include <paging/paging.h>

// FIXME: no VMM_VIRT_TO_PHYS
bool paging_unmap_pages(paging_pde_t* directory, uintptr_t virt, size_t count) {
	if (virt & 0xfff) return false;

	ENTER_CRITICAL_SECTION();
	
	size_t i_virt = (virt & 0xfffff000) >> 12;

	size_t i = (i_virt >> 10) & 0x3ff;
	size_t i_page_in_table = i_virt & 0x3ff;
	for (; i < PAGING_NUM_DIRECTORY_ENTRIES && count; i++) {
		uintptr_t tmp_address = directory[i] & PAGING_MASK_PDE_ADDRESS;
		const size_t remaining = PAGING_NUM_TABLE_ENTRIES - i_page_in_table;
		if (!(directory[i] & PAGING_PDE_FLAG_PRESENT)) {
			size_t skip = count < remaining ? count : remaining;
			count -= skip;
			virt += skip * 0x1000;
			i_page_in_table = 0;
			continue;
		}

		paging_pte_t* pte = (paging_pte_t*)tmp_address;
		for (; i_page_in_table < PAGING_NUM_TABLE_ENTRIES && count; i_page_in_table++) {
			const uintptr_t phys_addr = pte[i_page_in_table] & PAGING_MASK_PTE_ADDRESS;
			const bool present = pte[i_page_in_table] & PAGING_PTE_FLAG_PRESENT;

			pte[i_page_in_table] = 0;
			count -= 1;

			invlpg(virt);
			virt += 0x1000;

			if (present && phys_addr) pmm_free_memory((void*)phys_addr);
		}

		i_page_in_table = 0;

		bool pt_empty = true;
		for (size_t k = 0; k < PAGING_NUM_TABLE_ENTRIES; k++) {
			if (pte[k] & PAGING_PTE_FLAG_PRESENT) {
				pt_empty = false;
				break;
			}
		}

		if (pt_empty) {
			uintptr_t pt_phys = directory[i] & PAGING_MASK_PTE_ADDRESS;
			directory[i] = 0;
			if (pt_phys) pmm_free_memory((void*)pt_phys);
		}
	}

	EXIT_CRITICAL_SECTION();
	return count == 0;
}