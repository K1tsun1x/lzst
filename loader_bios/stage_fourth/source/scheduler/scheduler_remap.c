#include <scheduler/scheduler.h>

XTRN_C void scheduler_irq_handler(void);

XTRN_ONLY_CPP uint32_t SCHEDULER_IRQ = 0;

void scheduler_remap(uint8_t timer_vector) {
	SCHEDULER_IRQ = timer_vector - 32;
	idt32_set_entry(timer_vector, (uint32_t)scheduler_irq_handler, 0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
}