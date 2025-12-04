#include <idt/idt.h>

extern idt32_t ALIGNED(16) IDT32[IDT_NUM_ENTRIES];

bool idt32_set_entry(
	size_t index,
	uint32_t offset, uint16_t segment_selector,
	uint8_t type, uint8_t flags
) {
	if (index >= IDT_NUM_ENTRIES) return false;

	IDT32[index].offset_low = (uint16_t)(offset & 0xffff);
	IDT32[index].selector = segment_selector;
	IDT32[index].reserved = 0;
	IDT32[index].type_flags = ((flags & 0x0f) << 4) | (type & 0x0f);
	IDT32[index].offset_high = (uint16_t)((offset) >> 16);
	return true;
}