#include <virt-timer/virt-timer.h>

extern __volatile__ size_t VIRT_TIMER_TICKS;
extern __volatile__ uint16_t VIRT_TIMER_TICK_MS;

void virt_timer_sleep(size_t ms) {
	const uint32_t start = VIRT_TIMER_TICKS;
	const uint32_t interval = (ms + VIRT_TIMER_TICK_MS - 1) / VIRT_TIMER_TICK_MS;
	while ((uint32_t)(VIRT_TIMER_TICKS - start) < interval) {
		hlt();
		memory_barrier();
	}
}