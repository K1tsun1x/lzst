#include <lapic/lapic.h>

uint32_t LAPIC_TICKS_PER_MS = 0;

#include <tty/tty.h>
void lapic_init(void) {
	volatile uint64_t lapic_base = lapic_get_base();
	if (lapic_base > 0xffffffffULL) {
		tty_prints_negative("Error: LAPIC registers unreachable!\n");
		panic_halt();
	}

	lapic_set_base((uintptr_t)(lapic_base & 0xffffffff));

	lapic_enable_svr(0xff);

	// mask LVT LINT0, LINT1, ERROR
	lapic_write(LAPIC_REG_LVT_LINT0, 1 << 16);
	lapic_write(LAPIC_REG_LVT_LINT1, 1 << 16);
	lapic_write(LAPIC_REG_LVT_ERROR, 1 << 16);

	lapic_set_tpr(0);
}