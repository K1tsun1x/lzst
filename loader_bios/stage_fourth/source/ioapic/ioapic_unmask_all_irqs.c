#include <ioapic/ioapic.h>

extern size_t IOAPIC_NUM_PINS;

void ioapic_unmask_all_irqs(void) {
	for (size_t i = 0; i < IOAPIC_NUM_PINS; i++) ioapic_unmask_irq(i);
}