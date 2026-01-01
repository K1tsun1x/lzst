#include <lapic/lapic.h>

extern volatile uint32_t* LAPIC_REGS;

uint32_t lapic_read(uint32_t index) {
	// lfence();
	// memory_barrier();
	return LAPIC_REGS[index >> 2];
}