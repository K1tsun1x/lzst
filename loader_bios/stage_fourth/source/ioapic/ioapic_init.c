#include <ioapic/ioapic.h>

uintptr_t IOAPIC_BASE = 0;
size_t IOAPIC_NUM_PINS = 0;

void ioapic_init(uintptr_t base) {
	IOAPIC_BASE = base;
	IOAPIC_NUM_PINS = ((ioapic_read(0x01) >> 16) & 0xff) + 1;

	for (size_t i = 0; i < IOAPIC_NUM_PINS; i++) {
		if (i < NUM_IRQS) ioapic_remap_irq(i, i + 32, IRQ_INFOS[i].trigger_mode, IRQ_INFOS[i].polarity);
		else ioapic_remap_irq(i, i + 32, true, true);
	}
}