#include <scheduler/scheduler.h>

XTRN_C void virt_timer_irq_handler(isr_data_t* data);

XTRN_C bool SCHEDULER_ENABLE_TASK_SWITCHING;
XTRN_C scheduler_task_t* SCHEDULER_QUEUE_READY;
XTRN_C scheduler_task_t* SCHEDULER_CURRENT_TASK;

static size_t SCHEDULER_TICKS = 0;

// #include <tty/tty.h>
XTRN_C void scheduler_tick(bool ring_switch, scheduler_task_def_regs_t* def_regs) {
	UNREFERENCED_PARAMETER(ring_switch);

	virt_timer_irq_handler(NULL);
	if (!SCHEDULER_ENABLE_TASK_SWITCHING) return;

	SCHEDULER_TICKS += 1;
	if (SCHEDULER_TICKS % SCHEDULER_QUANTUM_TICKS != 0) return;


	scheduler_task_t* next = NULL;
	if (SCHEDULER_CURRENT_TASK) {
		// tty_puts("CUR:\n");
		// tty_print_scheduler_task_def_regs(def_regs);

		if (SCHEDULER_CURRENT_TASK->fp_regs) {
			if (sys_osxsave_present()) xsave(SCHEDULER_CURRENT_TASK->fp_regs);
			else if (sys_fpu_present()) fxsave(SCHEDULER_CURRENT_TASK->fp_regs);
		}

		SCHEDULER_CURRENT_TASK->default_regs = *def_regs;
		SCHEDULER_CURRENT_TASK->state = SCHEDULER_TASK_STATE_READY;
		next = SCHEDULER_CURRENT_TASK->next;
	}
	else if (
		SCHEDULER_QUEUE_READY &&
		DYNARR_HEADER_FROM_MEM(SCHEDULER_QUEUE_READY)->num_elems
	) next = &SCHEDULER_QUEUE_READY[0];

	if (!next) return;

	SCHEDULER_CURRENT_TASK = next;
	// tty_puts("NXT:\n");
	// tty_print_scheduler_task_def_regs(&SCHEDULER_CURRENT_TASK->default_regs);
	if (SCHEDULER_CURRENT_TASK->fp_regs) {
		if (sys_osxsave_present()) xrstor(SCHEDULER_CURRENT_TASK->fp_regs);
		else if (sys_fpu_present()) fxrstor(SCHEDULER_CURRENT_TASK->fp_regs);
	}

	*def_regs = SCHEDULER_CURRENT_TASK->default_regs;
}