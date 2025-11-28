#include <pic/pic.h>

void pic_init(void) {
	pic_remap(0x20, 0x28);
	pic_mask_all_irqs();
}