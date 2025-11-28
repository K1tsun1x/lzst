#include <ioapic/ioapic.h>

extern uintptr_t IOAPIC_BASE;

uint32_t ioapic_read(uint8_t reg) {
	uint32_t* regs = (uint32_t*)IOAPIC_BASE;
	regs[IOAPIC_REG_SEL >> 2] = reg;
	return regs[IOAPIC_REG_WIN >> 2];
}