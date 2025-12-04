#include <irq/irq.h>

extern irq_info_t IRQ_INFOS[NUM_IRQS];

bool irq_set_info(size_t irq, const irq_info_t* info) {
	if (!info || irq >= NUM_IRQS) return false;

	IRQ_INFOS[irq] = *info;
	return true;
}