#include <paging/paging.h>

extern spinlock_t __PAGING_LOCK;

bool paging_free_tables(paging_pde_t* directory, size_t start_index, size_t count) {
	const size_t end_index = start_index + count;
	if (end_index > PAGING_NUM_DIRECTORY_ENTRIES) return false;

	irq_flags_t irq_flags = irq_disable();
	spinlock_acquire(&__PAGING_LOCK);

	for (size_t i = start_index; count && i < end_index; i++) {
		if (!(directory[i] & PAGING_PDE_FLAG_PRESENT)) {
			count -= 1;
			continue;
		}

		pmm_free_memory((void*)(directory[i] & PAGING_MASK_PDE_ADDRESS));
		directory[i] = 0;
		count -= 1;
	}

	spinlock_release(&__PAGING_LOCK);
	irq_restore(irq_flags);
	return true;
}