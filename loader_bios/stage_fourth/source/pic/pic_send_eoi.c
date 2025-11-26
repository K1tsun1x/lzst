#include <pic/pic.h>

void pic_send_eoi(uint8_t index) {
	outb(PIC_PORT_MASTER_COMMAND, PIC_COMMAND_EOI);
	if (index >= 8) outb(PIC_PORT_SLAVE_COMMAND, PIC_COMMAND_EOI);
}