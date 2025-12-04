#include <idt/idt.h>

idt32_t ALIGNED(16) IDT32[IDT_NUM_ENTRIES] = { 0 };
idtr32_t ALIGNED(16) IDTR32 = IDTR_STATIC(
	sizeof(IDT32), (uint32_t)(&IDT32[0])
);