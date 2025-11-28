#include <lapic/lapic.h>

uint32_t LAPIC_TICKS_PER_MS = 0;

void lapic_init(void) {
	uint32_t apic_base = lapic_get_base();
	lapic_set_base(apic_base);

	lapic_enable_svr(0xff);

	// mask LVT LINT0, LINT1, ERROR
	lapic_write(LAPIC_REG_LVT_LINT0, 1 << 16);
	lapic_write(LAPIC_REG_LVT_LINT1, 1 << 16);
	lapic_write(LAPIC_REG_LVT_ERROR, 1 << 16);

	lapic_set_tpr(0);
}