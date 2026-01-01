#include <vmm/vmm.h>

bool vmm_copy_memory(const paging_pde_t* dst_directory, uintptr_t dst_address, const void* src, size_t count) {
	if (!dst_directory) return false;

	uintptr_t cur_dst = dst_address;
	uintptr_t cur_src = (uintptr_t)src;
	while (count) {
		size_t i_dir = PAGING_DIR_INDEX_FROM_ADDRESS(cur_dst);
		size_t i_page = PAGING_PAGE_INDEX_FROM_ADDRESS(cur_dst);
		size_t offset = cur_dst % VMM_PAGE_SIZE;

		ENTER_CRITICAL_SECTION();
		if (!(dst_directory[i_dir] & PAGING_PDE_FLAG_PRESENT)) {
			EXIT_CRITICAL_SECTION();
			return false;
		}

		paging_pte_t* tbl = (paging_pte_t*)(dst_directory[i_dir] & PAGING_MASK_PDE_ADDRESS);
		if (!(tbl[i_page] & PAGING_PTE_FLAG_PRESENT)) {
			EXIT_CRITICAL_SECTION();
			return false;
		}

		uintptr_t dst_phys = tbl[i_page] & PAGING_MASK_PTE_ADDRESS;
		EXIT_CRITICAL_SECTION();

		size_t to_copy = VMM_PAGE_SIZE - offset;
		if (to_copy > count) to_copy = count;

		memcpy((void*)(dst_phys + offset), (void*)cur_src, to_copy);
		cur_dst += to_copy;
		cur_src += to_copy;
		count -= to_copy;
	}
	
	return true;
}