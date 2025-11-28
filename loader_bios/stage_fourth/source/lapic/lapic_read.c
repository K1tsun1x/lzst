#include <lapic/lapic.h>

uint32_t lapic_read(uint32_t index) {
	__volatile__ uint32_t* regs = (__volatile__ uint32_t*)lapic_get_base();
	__asm__ __volatile__("lfence":::"memory");
	return regs[index >> 2];
}