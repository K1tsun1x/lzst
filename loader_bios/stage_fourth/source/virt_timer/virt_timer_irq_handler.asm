bits 32

extern VIRT_TIMER_TICKS
extern __VIRT_TIMER_TICK

extern tty_putchar

global virt_timer_irq_handler
virt_timer_irq_handler:
	inc dword [VIRT_TIMER_TICKS]
	mov byte [__VIRT_TIMER_TICK], 1
	ret