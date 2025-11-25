#include <paging/paging.h>

extern spinlock_t __PAGING_LOCK;

bool paging_unmap_pages(const paging_pde_t* directory, uintptr_t virt, size_t count) {
	if (virt & 0x3ff) return false;

	irq_flags_t irq_flags = irq_disable();
	spinlock_acquire(&__PAGING_LOCK);
	
	size_t i_virt = (virt & 0xfffff000) >> 12;

	size_t i = (i_virt >> 10) & 0x3ff;
	size_t i_page_in_table = i_virt & 0x3ff;
	for (; i < PAGING_NUM_DIRECTORY_ENTRIES && count; i++) {
		uintptr_t tmp_address = directory[i] & PAGING_MASK_PDE_ADDRESS;
		if (
			!(directory[i] & PAGING_PDE_FLAG_PRESENT) ||
			!tmp_address
		) {
			if (count > PAGING_NUM_TABLE_ENTRIES) {
				count -= PAGING_NUM_TABLE_ENTRIES;
				i_page_in_table = 0;
				continue;
			}
			else {
				count = 0;
				break;
			}
		}

		paging_pte_t* pte = (paging_pte_t*)tmp_address;
		for (; i_page_in_table < PAGING_NUM_TABLE_ENTRIES && count; i_page_in_table++) {
			pte[i_page_in_table] = 0;
			count -= 1;

			invlpg(virt);
			virt += 0x1000;
		}

		i_page_in_table = 0;
	}

	spinlock_release(&__PAGING_LOCK);
	irq_restore(irq_flags);
	return count == 0;
}