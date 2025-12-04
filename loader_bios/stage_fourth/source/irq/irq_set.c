#include <irq/irq.h>

extern isr_t IRQ_HANDLERS[NUM_IRQS];
extern irq_info_t IRQ_INFOS[NUM_IRQS];

bool irq_set(size_t irq, isr_t handler) {
	if (!handler || irq >= NUM_IRQS) return false;

	for (size_t i = 0; i < NUM_IRQS; i++) {
		if (IRQ_INFOS[i].irq_original == irq) {
			if (IRQ_INFOS[i].irq_remapped < NUM_IRQS) IRQ_HANDLERS[IRQ_INFOS[i].irq_remapped] = handler;
			return true;
		}
	}

	IRQ_HANDLERS[irq] = handler;
	return true;
}