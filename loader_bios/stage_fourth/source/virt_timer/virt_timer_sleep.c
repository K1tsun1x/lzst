#include <virt-timer/virt-timer.h>

extern uint32_t VIRT_TIMER_TICKS;

void virt_timer_sleep(size_t ms) {
	const uint32_t start = VIRT_TIMER_TICKS;
	const uint32_t interval = ms / 10;
	while ((uint32_t)(VIRT_TIMER_TICKS - start) < interval) __asm__ __volatile__("hlt");
}