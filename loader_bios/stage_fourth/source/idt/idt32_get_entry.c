#include <idt/idt.h>

extern idt32_t ALIGNED(16) IDT32[IDT_NUM_ENTRIES];

bool idt32_get_entry(size_t index, idt32_t* entry) {
	if (!entry || index >= IDT_NUM_ENTRIES) return false;
	
	*entry = IDT32[index];
	return true;
}