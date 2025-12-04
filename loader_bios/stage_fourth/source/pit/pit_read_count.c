#include <pit/pit.h>

uint16_t pit_read_count(void) {
	ENTER_CRITICAL_SECTION();

	outb(PIT_PORT_COMMAND, 0);
	io_wait();
	
	uint16_t res = inb(PIT_PORT_CHNL0_DATA);
	io_wait();
	res |= inb(PIT_PORT_CHNL0_DATA);
	io_wait();

	EXIT_CRITICAL_SECTION();
	return res;
}