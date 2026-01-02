bits 32

%define IDT_VECTOR_SCHEDULER_YIELD_HANDLER	0x40

; void LOADERCALL scheduler_yield(void)
global scheduler_yield
scheduler_yield:
	int IDT_VECTOR_SCHEDULER_YIELD_HANDLER
	ret