#include <irq/irq.h>

extern isr_t IRQ_HANDLERS[NUM_IRQS];

XTRN_C void irq_global_handler(isr_data_t* data) {
	size_t irq_index = data->int_index - 32;

	if (irq_index >= NUM_IRQS) return;
	if (IRQ_HANDLERS[irq_index]) IRQ_HANDLERS[irq_index](data);
}