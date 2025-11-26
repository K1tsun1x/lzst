#include <irq/irq.h>

isr_t IRQ_HANDLERS[NUM_IRQS] = { 0 };

#include <tty/tty.h>
EXTERN_C void irq_global_handler(isr_data_t* data) {
	size_t int_index = data->int_index - 32;
	if (int_index >= NUM_IRQS) return;

	if (IRQ_HANDLERS[int_index]) IRQ_HANDLERS[int_index](data);

	tty_printf("IRQ %#x\n", int_index);

	// FIXME: PIC driver needed
	outb(0x20, 0x20);
	if (int_index >= 8) outb(0xa0, 0x20);
}