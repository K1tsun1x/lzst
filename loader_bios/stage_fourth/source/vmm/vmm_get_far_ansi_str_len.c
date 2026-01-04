#include <vmm/vmm.h>

size_t vmm_get_far_ansi_str_len(const paging_pde_t* src_directory, uintptr_t str_address, size_t max) {
	if (!src_directory) return SIZE_MAX;
	if (!max) max = SIZE_MAX;

	uintptr_t cur_str = str_address;
	size_t res = 0;
	while (true) {
		size_t i_dir = PAGING_DIR_INDEX_FROM_ADDRESS(cur_str);
		size_t i_page = PAGING_PAGE_INDEX_FROM_ADDRESS(cur_str);
		size_t offset = cur_str % VMM_PAGE_SIZE;

		ENTER_CRITICAL_SECTION();
		if (!(src_directory[i_dir] & PAGING_PDE_FLAG_PRESENT)) {
			EXIT_CRITICAL_SECTION();
			return SIZE_MAX;
		}

		paging_pte_t* tbl = (paging_pte_t*)(src_directory[i_dir] & PAGING_MASK_PDE_ADDRESS);
		if (!(tbl[i_page] & PAGING_PTE_FLAG_PRESENT)) {
			EXIT_CRITICAL_SECTION();
			return SIZE_MAX;
		}

		uintptr_t src_phys = tbl[i_page] & PAGING_MASK_PTE_ADDRESS;
		EXIT_CRITICAL_SECTION();

		char* cur = (char*)(src_phys + offset);
		while (offset < VMM_PAGE_SIZE) {
			if (*cur == '\0') return res;
			if (res >= max) return SIZE_MAX;

			++cur;
			++offset;
			++cur_str;
			++res;
		}
	}
}