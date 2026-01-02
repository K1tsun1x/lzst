bits 32

%define TASK_OFFSET_FP_REGS				0x00
%define TASK_OFFSET_DEF_REGS			0x04
%define TASK_OFFSET_STATE				0x44
%define TASK_OFFSET_NEXT				0x50

%define TASK_DEF_REGS_OFFSET_CR3		0x00
%define TASK_DEF_REGS_OFFSET_DS			0x04
%define TASK_DEF_REGS_OFFSET_SS			0x08
%define TASK_DEF_REGS_OFFSET_DI			0x0c
%define TASK_DEF_REGS_OFFSET_SI			0x10
%define TASK_DEF_REGS_OFFSET_BP			0x14
%define TASK_DEF_REGS_OFFSET_SP			0x18
%define TASK_DEF_REGS_OFFSET_BX			0x1c
%define TASK_DEF_REGS_OFFSET_DX			0x20
%define TASK_DEF_REGS_OFFSET_CX			0x24
%define TASK_DEF_REGS_OFFSET_AX			0x28
%define TASK_DEF_REGS_OFFSET_IP			0x2c
%define TASK_DEF_REGS_OFFSET_CS			0x30
%define TASK_DEF_REGS_OFFSET_FLAGS		0x34

%define TASK_STATE_READY				0x02
%define TASK_STATE_RUNNING				0x03

%define DYNARR_HEADER_SIZE				0x0c
%define DYNARR_HEADER_OFFSET_NUM_ELEMS	0x04

extern KERNEL_CR3
extern SCHEDULER_CURRENT_TASK
extern SCHEDULER_QUEUE_READY

extern sys_osxsave_present
extern sys_fpu_present

global scheduler_yield_handler
scheduler_yield_handler:
	; FIXME: use of global variables (problem for SMP)
	mov word [.nxt_ss], ss
	mov dword [.nxt_sp], esp
	mov word [.nxt_ds], ds

	pusha
	push ss
	push ds
	mov eax, cr3
	push eax

	; pusha:	+32	= 32
	; push ss:	+4	= 36
	; push ds:	+4	= 40
	; push cr3:	+4	= 44
	mov eax, [esp + 44]
	mov [.nxt_ip], eax
	mov eax, [esp + 48]
	mov [.nxt_cs], eax
	mov eax, [esp + 52]
	mov [.nxt_flags], eax

	mov eax, [KERNEL_CR3]
	mov cr3, eax
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	cmp dword [SCHEDULER_CURRENT_TASK], 0
	je .no_cur_save

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
	pop dword [esi + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_CR3]
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

	push dword [esi + TASK_OFFSET_NEXT]
	pop dword [SCHEDULER_CURRENT_TASK]
.after_save_cur_def_regs:
	mov eax, [SCHEDULER_CURRENT_TASK]
	mov dword [eax + TASK_OFFSET_STATE], TASK_STATE_RUNNING

	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_CR3]
	mov dword [.nxt_cr3], ecx
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SS]
	mov dword [.nxt_ss], ecx
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SP]
	mov dword [.nxt_sp], ecx
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DS]
	mov dword [.nxt_ds], ecx

	mov edi, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DI]
	mov esi, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_SI]
	mov ebp, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_BP]

	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_IP]
	mov [.nxt_ip], ecx
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_CS]
	mov [.nxt_cs], ecx
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_FLAGS]
	mov [.nxt_flags], ecx

	mov ebx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_BX]
	mov edx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_DX]
	mov ecx, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_CX]
	mov eax, [eax + TASK_OFFSET_DEF_REGS + TASK_DEF_REGS_OFFSET_AX]

	; We write the same thing to the stack to restore it before IRET.
	; Needed for setting up kernel cr3 & segments, so that if the switch does not happen,
	; the registers remain the same
	pusha
	push dword [.nxt_ss]
	push dword [.nxt_ds]
	push dword [.nxt_cr3]
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
	mov dword [.nxt_cr3], eax
	pop eax
	mov dword [.nxt_ds], eax
	mov es, eax
	mov fs, eax
	mov gs, eax
	pop eax
	mov [.nxt_ss], eax
	popa

	mov [.tmp], eax
	mov eax, [.nxt_cr3]
	mov cr3, eax

	mov ss, [.nxt_ss]
	mov esp, [.nxt_sp]

	mov ds, [.nxt_ds]
	mov es, [.nxt_ds]
	mov fs, [.nxt_ds]
	mov gs, [.nxt_ds]

	mov eax, [.nxt_ip]
	mov [esp + 0], eax
	mov eax, [.nxt_cs]
	mov [esp + 4], eax
	mov eax, [.nxt_flags]
	mov [esp + 8], eax
	mov eax, [.tmp]
	iret
.no_cur_save:
	; pusha:	+32	= 32
	; push ss:	+4	= 36
	; push ds:	+4	= 40
	; push cr3:	+4	= 44
	; we are NOT REMOVING IRET-frame FROM STACK (-flags,cs,ip)!!!
	pop eax				; remove CR3
	pop eax				; remove DS
	pop eax				; remove SS
	popa				; remove GPR

	push esi
	mov esi, [SCHEDULER_QUEUE_READY]
	cmp dword [esi - DYNARR_HEADER_SIZE + DYNARR_HEADER_OFFSET_NUM_ELEMS], 0
	pop esi
	je .after_load_next

	push dword [SCHEDULER_QUEUE_READY]
	pop dword [SCHEDULER_CURRENT_TASK]
	jmp .after_save_cur_def_regs
.nxt_cr3:					dd 0
.nxt_ss:					dd 0
.nxt_sp:					dd 0
.nxt_ds:					dd 0
.tmp:						dd 0
.nxt_ip:					dd 0
.nxt_cs:					dd 0
.nxt_flags:					dd 0