#include <pit/pit.h>

uint16_t pit_calc_divisor(uint32_t tick_ms) {
	uint32_t ticks = (PIT_HW_FREQ * tick_ms) / 1000;
	if (!ticks) ticks = 1;
	else if (ticks > 65535) ticks = 65535;
    return (uint16_t)ticks;
}