#include <ioapic/ioapic.h>

extern size_t IOAPIC_NUM_PINS;

void ioapic_unmask_irq(uint8_t irq) {
	if (irq >= IOAPIC_NUM_PINS) return;

	uint32_t low_index = 0x10 + (irq << 1);
	uint32_t low = ioapic_read(low_index);
	low &= ~(1 << 16);
    ioapic_write(low_index, low);
}