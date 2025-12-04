#include <lapic/lapic.h>

void lapic_write(uint32_t index, uint32_t value) {
	__volatile__ uint32_t* regs = (__volatile__ uint32_t*)lapic_get_base();

	mfence();
	memory_barrier();
	regs[index >> 2] = value;
	memory_barrier();
	UNREFERENCED_PARAMETER(regs[LAPIC_REG_ID >> 2]);
}