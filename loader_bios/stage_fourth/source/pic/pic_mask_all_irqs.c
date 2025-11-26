#include <pic/pic.h>

void pic_mask_all_irqs(void) {
	outb(PIC_PORT_MASTER_DATA, 0xff);
	outb(PIC_PORT_SLAVE_DATA, 0xff);
}