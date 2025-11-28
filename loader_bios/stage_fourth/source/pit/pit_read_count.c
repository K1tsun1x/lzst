#include <pit/pit.h>

uint16_t pit_read_count(void) {
	irq_flags_t irq_flags = irq_disable();

	outb(PIT_PORT_COMMAND, 0);
	io_wait();
	
	uint16_t res = inb(PIT_PORT_CHNL0_DATA);
	io_wait();
	res |= inb(PIT_PORT_CHNL0_DATA);
	io_wait();

	irq_restore(irq_flags);
	return res;
}