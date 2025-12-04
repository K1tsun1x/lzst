#include <virt-timer/virt-timer.h>

extern __volatile__ uint16_t VIRT_TIMER_TICK_MS;

void virt_timer_set_tick_ms(uint16_t tick_ms) {
	VIRT_TIMER_TICK_MS = tick_ms;
}