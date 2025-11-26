#include <pic/pic.h>

void pic_remap(uint8_t master_base, uint8_t slave_base) {

	uint8_t master_data = inb(PIC_PORT_MASTER_DATA);
	uint8_t slave_data = inb(PIC_PORT_SLAVE_DATA);
	outb(PIC_PORT_MASTER_COMMAND, PIC_COMMAND_ICW1_INIT | PIC_COMMAND_ICW1_ICW4);
	outb(PIC_PORT_SLAVE_COMMAND, PIC_COMMAND_ICW1_INIT | PIC_COMMAND_ICW1_ICW4);

	outb(PIC_PORT_MASTER_DATA, master_base);
	outb(PIC_PORT_SLAVE_DATA, slave_base);

	outb(PIC_PORT_MASTER_DATA, 4);
	outb(PIC_PORT_SLAVE_DATA, 2);

	outb(PIC_PORT_MASTER_DATA, PIC_COMMAND_ICW4_UP_MODE);
	outb(PIC_PORT_SLAVE_DATA, PIC_COMMAND_ICW4_UP_MODE);

	outb(PIC_PORT_MASTER_DATA, master_data);
	outb(PIC_PORT_SLAVE_DATA, slave_data);
}