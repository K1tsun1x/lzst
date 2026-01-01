#include <virt-timer/virt-timer.h>

extern volatile size_t VIRT_TIMER_TICKS;
extern volatile uint16_t VIRT_TIMER_TICK_MS;

void virt_timer_delay(size_t ms) {
	const size_t start = VIRT_TIMER_TICKS;
	const size_t interval = (ms + VIRT_TIMER_TICK_MS - 1) / VIRT_TIMER_TICK_MS;
	while ((size_t)(VIRT_TIMER_TICKS - start) < interval) {
		hlt();
		memory_barrier();
	}
}