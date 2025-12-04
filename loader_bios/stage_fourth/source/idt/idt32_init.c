#include <idt/idt.h>

extern idtr32_t ALIGNED(16) IDTR32;

void idt32_init(void) {
	idtr_load(&IDTR32);
}