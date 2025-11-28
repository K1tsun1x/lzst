#include <virt-timer/virt-timer.h>

uint32_t VIRT_TIMER_TICKS = 0;
__volatile__ bool __VIRT_TIMER_TICK = false;

void virt_timer_irq_handler(isr_data_t* data) {
	UNREFERENCED_PARAMETER(data);

	VIRT_TIMER_TICKS += 1;
	__VIRT_TIMER_TICK = true;
	virt_int_ctrl_eoi(IRQ_INFOS[0].vector);
}