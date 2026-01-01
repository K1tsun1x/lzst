#include <virt-timer/virt-timer.h>

extern volatile bool __VIRT_TIMER_TICK;

void virt_timer_wait_irq(void) {
	while (!__VIRT_TIMER_TICK) cpu_relax();
	__VIRT_TIMER_TICK = false;
}