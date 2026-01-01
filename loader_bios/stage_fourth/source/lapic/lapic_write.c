#include <lapic/lapic.h>

extern volatile uint32_t* LAPIC_REGS;

void lapic_write(uint32_t index, uint32_t value) {
	// FIXME: not checked
	mfence();
	memory_barrier();
	LAPIC_REGS[index >> 2] = value;
	memory_barrier();
	UNREFERENCED_PARAMETER(LAPIC_REGS[LAPIC_REG_ID >> 2]);
}