#include <irq/irq.h>

extern irq_info_t IRQ_INFOS[NUM_IRQS];

bool irq_get_info(size_t irq, irq_info_t* info) {
	if (!info || irq >= NUM_IRQS) return false;

	*info = IRQ_INFOS[irq];
	return true;
}