#include <virt-timer/virt-timer.h>

extern __volatile__ bool __VIRT_TIMER_TICK;

void virt_timer_wait_irq(void) {
	while (!__VIRT_TIMER_TICK) cpu_relax();
	__VIRT_TIMER_TICK = false;
}