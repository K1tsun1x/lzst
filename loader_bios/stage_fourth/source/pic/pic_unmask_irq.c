#include <pic/pic.h>

void pic_unmask_irq(uint8_t index) {
	uint16_t port;
	if (index < 8) port = PIC_PORT_MASTER_DATA;
	else {
		index -= 8;
		port = PIC_PORT_SLAVE_DATA;
	}

	uint8_t data = inb(port) & ~(1 << index);
	outb(port, data);
}