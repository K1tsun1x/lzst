#include <pit/pit.h>

uint16_t pit_calc_divisor(uint32_t ms) {
	uint32_t ticks = (PIT_HW_FREQ * ms) / 1000;
	if (!ticks) ticks = 1;
	else if (ticks > 65535) ticks = 65535;
    return (uint16_t)ticks;
}