bits 32

%define SW_INT_SCHEDULER_YIELD				0x40

; void LOADERCALL scheduler_yield(void)
global scheduler_yield
scheduler_yield:
	int SW_INT_SCHEDULER_YIELD
	ret