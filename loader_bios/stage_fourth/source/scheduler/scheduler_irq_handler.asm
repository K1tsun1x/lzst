bits 32

%define SCHEDULER_QUANTUM_TICKS			10

%define TASK_OFFSET_FP_REGS				0x00
%define TASK_OFFSET_DEF_REGS			0x04
%define TASK_OFFSET_STATE				0x40
%define TASK_OFFSET_NEXT				0x4c
%define TASK_OFFSET_CR3					0x50

%define TASK_DEF_REGS_OFFSET_DS			0x00
%define TASK_DEF_REGS_OFFSET_SS			0x04
%define TASK_DEF_REGS_OFFSET_DI			0x08
%define TASK_DEF_REGS_OFFSET_SI			0x0c
%define TASK_DEF_REGS_OFFSET_BP			0x10
%define TASK_DEF_REGS_OFFSET_SP			0x14
%define TASK_DEF_REGS_OFFSET_BX			0x18
%define TASK_DEF_REGS_OFFSET_DX			0x1c
%define TASK_DEF_REGS_OFFSET_CX			0x20
%define TASK_DEF_REGS_OFFSET_AX			0x24
%define TASK_DEF_REGS_OFFSET_IP			0x28
%define TASK_DEF_REGS_OFFSET_CS			0x2c
%define TASK_DEF_REGS_OFFSET_FLAGS		0x30

%define TASK_STATE_READY				0x02
%define TASK_STATE_RUNNING				0x03

%define DYNARR_HEADER_SIZE				0x0c
%define DYNARR_HEADER_OFFSET_NUM_ELEMS	0x04

extern SCHEDULER_ENABLE_TASK_SWITCHING
extern SCHEDULER_CURRENT_TASK
extern SCHEDULER_QUEUE_READY
extern SCHEDULER_IRQ

extern sys_osxsave_present
extern sys_fpu_present
extern virt_timer_irq_handler
extern virt_int_ctrl_eoi

global SCHEDULER_TICKS
SCHEDULER_TICKS:			dd 0

global scheduler_irq_handler
scheduler_irq_handler:
	pusha
	push ss
	push ds

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	cmp byte [SCHEDULER_ENABLE_TASK_SWITCHING], 0
	je .after_load_next

	inc dword [SCHEDULER_TICKS]
	
	; Has the required number of ticks passed to switch the task?
	cmp dword [SCHEDULER_TICKS], SCHEDULER_QUANTUM_TICKS
	jb .after_load_next

	mov dword [SCHEDULER_TICKS], 0
	
	cmp dword [SCHEDULER_CURRENT_TASK], 0
	je .after_save_cur

	mov esi, [SCHEDULER_CURRENT_TASK]
	cmp dword [esi + TASK_OFFSET_FP_REGS], 0
	je .after_save_cur_fp_regs

	mov edi, [esi + TASK_OFFSET_FP_REGS]
	call sys_osxsave_present
	test al, al
	jz .save_cur_fp_regs_fpu

	xor ecx, ecx
	xor edx, edx
	xgetbv
	xsave [edi]
	jmp .after_save_cur_fp_regs
.save_cur_fp_regs_fpu:
	call sys_fpu_present
	jz .after_save_cur_fp_regs

	fxsave [edi]
.after_save_cur_fp_regs:
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DS]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SS]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DI]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SI]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_BP]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SP]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_BX]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DX]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_CX]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_AX]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_IP]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_CS]
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_FLAGS]

	mov dword [esi + TASK_OFFSET_STATE], TASK_STATE_READY

	mov eax, cr3
	mov [esi + TASK_OFFSET_CR3], eax

	push dword [esi + TASK_OFFSET_NEXT]
	pop dword [SCHEDULER_CURRENT_TASK]
.after_save_cur_def_regs:
	mov eax, [SCHEDULER_CURRENT_TASK]
	mov dword [eax + TASK_OFFSET_STATE], TASK_STATE_RUNNING

	mov ecx, [eax + TASK_OFFSET_CR3]
	mov cr3, ecx

	mov ds, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DS]
	mov es, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DS]
	mov fs, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DS]
	mov gs, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DS]
	mov ss, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SS]
	mov edi, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DI]
	mov esi, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SI]
	mov ebp, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_BP]
	mov esp, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SP]

	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_IP]			; overwrite IP
	mov [esp + 0], ecx
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_CS]			; overwrite CS
	mov [esp + 4], ecx
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_FLAGS]		; overwrite FLAGS
	mov [esp + 8], ecx

	mov ebx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_BX]
	mov edx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DX]
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_CX]
	mov eax, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_AX]

	; We write the same thing to the stack to restore it before IRET.
	; Needed for setting up kernel segments, so that if the switch does not happen,
	; the registers remain the same
	pusha
	push ss
	push ds
	jmp .after_load_next
.after_save_cur:
	push esi
	mov esi, [SCHEDULER_QUEUE_READY]
	cmp dword [esi - DYNARR_HEADER_SIZE + DYNARR_HEADER_OFFSET_NUM_ELEMS], 0
	pop esi
	je .after_load_next

	push dword [SCHEDULER_QUEUE_READY]
	pop dword [SCHEDULER_CURRENT_TASK]
	jmp .after_save_cur_def_regs
.after_load_next:
	pop eax
	mov ds, eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	pop eax
	mov ss, eax
	popa

	call virt_timer_irq_handler
	push dword [SCHEDULER_IRQ]
	call [virt_int_ctrl_eoi]
	add esp, 4
	iret