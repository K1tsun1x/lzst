#include <paging/paging.h>

extern spinlock_t __PAGING_LOCK;

bool paging_map_pages(paging_pde_t* directory, uintptr_t src_phys, uintptr_t dst_virt, size_t count, uint32_t flags) {
	if ((src_phys & 0x3ff) || (dst_virt & 0x3ff)) return false;
	
	size_t i_phys = (src_phys & 0xfffff000) >> 12;
	size_t i_virt = (dst_virt & 0xfffff000) >> 12;

	flags |= PAGING_PTE_FLAG_PRESENT;

	size_t i = (i_virt >> 10) & 0x3ff;
	size_t i_page_in_table = i_virt & 0x3ff;

	const size_t num_tables_present = ALIGN_UP_P2(count, PAGING_NUM_TABLE_ENTRIES) / PAGING_NUM_TABLE_ENTRIES;
	if (!paging_ensure_tables_present(directory, i, num_tables_present, flags)) return false;

	irq_flags_t irq_flags = irq_disable();
	spinlock_acquire(&__PAGING_LOCK);
	
	for (; i < PAGING_NUM_DIRECTORY_ENTRIES && count; i++) {
		paging_pte_t* pte = (paging_pte_t*)(directory[i] & PAGING_MASK_PDE_ADDRESS);
		for (; i_page_in_table < PAGING_NUM_TABLE_ENTRIES && count; i_page_in_table++) {
			pte[i_page_in_table] = (i_phys << 12) | flags;
			i_phys += 1;
			count -= 1;

			invlpg(dst_virt);
			dst_virt += 0x1000;
		}

		i_page_in_table = 0;
	}

	spinlock_release(&__PAGING_LOCK);
	irq_restore(irq_flags);
	return count == 0;
}