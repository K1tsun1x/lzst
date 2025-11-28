#include <ioapic/ioapic.h>

extern uintptr_t IOAPIC_BASE;

void ioapic_write(uint8_t reg, uint32_t value) {
	uint32_t* regs = (uint32_t*)IOAPIC_BASE;
	regs[IOAPIC_REG_SEL >> 2] = reg;
	regs[IOAPIC_REG_WIN >> 2] = value;
}