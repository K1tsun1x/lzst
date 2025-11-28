#include <lapic/lapic.h>

uint32_t lapic_timer_calibrate(void) {
	lapic_write(LAPIC_REG_DCR, 0x03);
	lapic_write(LAPIC_REG_INITIAL_COUNT, 0xffffffff);

	pit_oneshot(10);
	virt_timer_wait_irq();
	uint32_t elapsed = 0xffffffff - lapic_read(LAPIC_REG_CCR);
	return elapsed / 10;
}