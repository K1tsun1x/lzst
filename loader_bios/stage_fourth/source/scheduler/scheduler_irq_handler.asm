bits 32

extern SCHEDULER_IRQ
extern SCHEDULER_ENABLE_TASK_SWITCHING

extern virt_timer_irq_handler
extern __scheduler_tick
extern virt_int_ctrl_eoi

global scheduler_irq_handler
scheduler_irq_handler:
	call virt_timer_irq_handler

	push dword [SCHEDULER_IRQ]
	call [virt_int_ctrl_eoi]
	add esp, 4
	iret