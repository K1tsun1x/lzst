#include <lapic/lapic.h>

void lapic_eoi(uint8_t index) {
	UNREFERENCED_PARAMETER(index);
	
	lapic_write(LAPIC_REG_EOI, 0);
}