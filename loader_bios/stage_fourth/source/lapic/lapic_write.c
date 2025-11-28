#include <lapic/lapic.h>

void lapic_write(uint32_t index, uint32_t value) {
	__volatile__ uint32_t* regs = (__volatile__ uint32_t*)lapic_get_base();

	__asm__ __volatile__("mfence":::"memory");
	regs[index >> 2] = value;
	__asm__ __volatile__("":::"memory");
	UNREFERENCED_PARAMETER(regs[LAPIC_REG_ID >> 2]);
}