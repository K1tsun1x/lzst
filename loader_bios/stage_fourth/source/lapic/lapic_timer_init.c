#include <lapic/lapic.h>

uint32_t lapic_timer_init(uint8_t vector, uint16_t tick_ms) {
	LAPIC_TICKS_PER_MS = lapic_timer_calibrate();

	lapic_write(LAPIC_REG_DCR, 0x03);
	uint32_t value = lapic_read(LAPIC_REG_LVT_TIMER);
	value &= ~0xff;
	value |= vector;
	value |= 1 << 17;
	value &= ~(1 << 16);
	lapic_write(LAPIC_REG_LVT_TIMER, value);
	virt_int_ctrl_unmask_irq(vector - 32);
	lapic_write(LAPIC_REG_INITIAL_COUNT, LAPIC_TICKS_PER_MS * tick_ms);

	return LAPIC_TICKS_PER_MS;
}