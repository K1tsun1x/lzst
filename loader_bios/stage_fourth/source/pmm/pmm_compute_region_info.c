#include <pmm/pmm.h>

size_t pmm_compute_region_info(
	uint64_t base,
	uint64_t length,
	uint64_t* first_page_info,
	uint64_t* first_page
) {
	size_t res = length / (PMM_PAGE_SIZE + sizeof(pmm_page_t));
	while (res > 0) {
		uint64_t page_info = ALIGN_UP_P2(base + sizeof(pmm_reg_t), 8);
		uint64_t page = ALIGN_UP_P2(page_info + res * sizeof(pmm_page_t), PMM_PAGE_SIZE);
		uint64_t total_used = page - base + res * PMM_PAGE_SIZE;

		if (total_used <= length) {
			if (first_page_info) *first_page_info = page_info;
			if (first_page) *first_page = page;
			break;
		}

		res -= 1;
	}

	return res;
}