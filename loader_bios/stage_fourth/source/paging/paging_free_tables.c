#include <paging/paging.h>

// FIXME: no VMM_VIRT_TO_PHYS
bool paging_free_tables(paging_pde_t* directory, size_t start_index, size_t count) {
	const size_t end_index = start_index + count;
	if (end_index > PAGING_NUM_DIRECTORY_ENTRIES) return false;

	ENTER_CRITICAL_SECTION();

	for (size_t i = start_index; count && i < end_index; i++) {
		if (!(directory[i] & PAGING_PDE_FLAG_PRESENT)) {
			count -= 1;
			continue;
		}

		pmm_free_memory((void*)(directory[i] & PAGING_MASK_PDE_ADDRESS));
		directory[i] = 0;
		count -= 1;
	}

	EXIT_CRITICAL_SECTION();
	return true;
}