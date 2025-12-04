#include <vmm/vmm.h>

size_t vmm_find_free_pages(const paging_pde_t* directory, size_t num_pages) {
	size_t free_run = 0;
	size_t run_start = 0;
	for (size_t i = 0; i < PAGING_NUM_DIRECTORY_ENTRIES; i++) {
		if (!(directory[i] & PAGING_PDE_FLAG_PRESENT)) {
			if (free_run == 0) run_start = i * PAGING_NUM_TABLE_ENTRIES;
			free_run += PAGING_NUM_TABLE_ENTRIES;
			if (free_run >= num_pages) return run_start;
			continue;
		}

		const uintptr_t dir_phys = directory[i] & PAGING_MASK_PDE_ADDRESS;
		paging_pte_t* pt = (paging_pte_t*)VMM_PHYS_TO_VIRT(dir_phys);
		if (!pt) for (size_t j = 0; j < PAGING_NUM_TABLE_ENTRIES; j++) {
			paging_pte_t pte = pt[j];
			if (!(pte & PAGING_PTE_FLAG_PRESENT)) {
				if (free_run == 0) run_start = i * PAGING_NUM_TABLE_ENTRIES + j;

				free_run++;
				if (free_run >= num_pages)  return run_start;
			}
			else free_run = 0;
		}
	}

	return SIZE_MAX;
}