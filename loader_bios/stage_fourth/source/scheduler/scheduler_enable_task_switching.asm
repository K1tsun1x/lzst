bits 32

global SCHEDULER_ENABLE_TASK_SWITCHING
SCHEDULER_ENABLE_TASK_SWITCHING:			db 0

extern scheduler_yield

; void LOADERCALL scheduler_enable_task_switching(void)
global scheduler_enable_task_switching
scheduler_enable_task_switching:
	mov byte [SCHEDULER_ENABLE_TASK_SWITCHING], 1
	call scheduler_yield
	ret