#include <e820/e820.h>

e820_reg_overlap_t e820_get_reg_overlap(const e820_reg_t* first, const e820_reg_t* second) {
	uint64_t end_second = second->base + second->length;
	uint64_t end_first = first->base + first->length;

	if (second->base <= first->base && end_second > first->base && end_second < end_first) return E820_REG_OVERLAP_START;
	else if (second->base < end_first && second->base > first->base && end_second >= end_first) return E820_REG_OVERLAP_END;
	else if (second->base >= first->base && end_second <= end_first) return E820_REG_OVERLAP_INSIDE;
	else if (second->base <= first->base && end_second >= end_first) return E820_REG_OVERLAP_OUTSIDE;
	return E820_REG_OVERLAP_NONE;
}