#include <vmm/vmm.h>

bool vmm_copy_memory_from(const paging_pde_t* src_directory, void* dst, uintptr_t src_address, size_t count) {
	if (!src_directory || !dst) return false;
	if (!count) return true;

	uintptr_t cur_src = src_address;
	uintptr_t cur_dst = (uintptr_t)dst;
	while (count) {
		size_t i_dir = PAGING_DIR_INDEX_FROM_ADDRESS(cur_src);
		size_t i_page = PAGING_PAGE_INDEX_FROM_ADDRESS(cur_src);
		size_t offset = cur_src % VMM_PAGE_SIZE;

		ENTER_CRITICAL_SECTION();
		if (!(src_directory[i_dir] & PAGING_PDE_FLAG_PRESENT)) {
			EXIT_CRITICAL_SECTION();
			return false;
		}

		paging_pte_t* tbl = (paging_pte_t*)(src_directory[i_dir] & PAGING_MASK_PDE_ADDRESS);
		if (!(tbl[i_page] & PAGING_PTE_FLAG_PRESENT)) {
			EXIT_CRITICAL_SECTION();
			return false;
		}

		uintptr_t src_phys = tbl[i_page] & PAGING_MASK_PTE_ADDRESS;
		EXIT_CRITICAL_SECTION();

		size_t to_copy = VMM_PAGE_SIZE - offset;
		if (to_copy > count) to_copy = count;

		// all user physical memory is identity-mapped in kernel
		memcpy((void*)cur_dst, (void*)(src_phys + offset), to_copy);
		cur_dst += to_copy;
		cur_src += to_copy;
		count -= to_copy;
	}
	
	return true;
}