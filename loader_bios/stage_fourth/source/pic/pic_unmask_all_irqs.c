#include <pic/pic.h>

void pic_unmask_all_irqs(void) {
	outb(PIC_PORT_MASTER_DATA, 0);
	outb(PIC_PORT_SLAVE_DATA, 0);
}