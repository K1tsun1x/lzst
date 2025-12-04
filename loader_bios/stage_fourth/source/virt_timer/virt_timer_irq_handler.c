#include <virt-timer/virt-timer.h>

extern __volatile__ uint32_t VIRT_TIMER_TICKS;
extern __volatile__ bool __VIRT_TIMER_TICK;

void virt_timer_irq_handler(isr_data_t* data) {
	UNREFERENCED_PARAMETER(data);

	VIRT_TIMER_TICKS += 1;
	__VIRT_TIMER_TICK = true;
}