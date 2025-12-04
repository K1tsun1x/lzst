#include <paging/paging.h>

typedef struct _paging_allocated_entry_t {
	size_t		index;
	uintptr_t	address;
} paging_allocated_entry_t;

extern spinlock_t __PAGING_LOCK;

// FIXME: no VMM_VIRT_TO_PHYS
bool paging_ensure_tables_present(paging_pde_t* directory, size_t start_index, size_t count, uint32_t flags) {
	const size_t end_index = start_index + count;
	if (end_index > PAGING_NUM_DIRECTORY_ENTRIES) return false;

	flags &= PAGING_MASK_PDE_FLAGS;
	flags |= PAGING_PDE_FLAG_PRESENT;

	size_t tmp_count = count;
	size_t num_allocated = 0;
	paging_allocated_entry_t* allocated_entries = (paging_allocated_entry_t*)pmm_allocate_memory(
		count * sizeof(paging_allocated_entry_t),
		0
	);

	if (!allocated_entries) return false;

	ENTER_CRITICAL_SECTION();

	for (size_t i = start_index; tmp_count && i < PAGING_NUM_DIRECTORY_ENTRIES; i++) {
		if (directory[i] & PAGING_PDE_FLAG_PRESENT) {
			tmp_count -= 1;
			continue;
		}

		uintptr_t tmp_address = (uintptr_t)pmm_allocate_memory(PAGING_TABLE_SIZE, 0);
		if (!tmp_address) break;

		directory[i] = tmp_address | flags;
		memset((void*)tmp_address, 0, PAGING_TABLE_SIZE);

		allocated_entries[num_allocated].index = i;
		allocated_entries[num_allocated++].address = tmp_address;
		tmp_count -= 1;
	}

	if (tmp_count) {
		/*
			If it was not possible to allocate the required amount of memory for the tables,
			clear the old ones and remove them from the directory
		*/
		for (size_t i = 0; i < num_allocated; i++) {
			pmm_free_memory((void*)allocated_entries[i].address);
			directory[allocated_entries[i].index] = 0;
		}

		if (allocated_entries) pmm_free_memory(allocated_entries);

		EXIT_CRITICAL_SECTION();
		return false;
	}

	if (allocated_entries) pmm_free_memory(allocated_entries);

	EXIT_CRITICAL_SECTION();
	return true;
}