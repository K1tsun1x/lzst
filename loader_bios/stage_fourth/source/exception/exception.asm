bits 32

extern exception_global_handler

%macro ERROR_STUB				1
global exception_stub%+%1
exception_stub%+%1:
	; FIXME: use of global variables (problem for SMP)
	pop dword [error_code]
	mov dword [int_index], %1
	jmp exception_global_handler_stub
%endmacro

%macro NOT_ERROR_STUB			1
global exception_stub%+%1
exception_stub%+%1:
	; FIXME: use of global variables (problem for SMP)
	mov dword [error_code], 0
	mov dword [int_index], %1
	jmp exception_global_handler_stub
%endmacro

extern KERNEL_CR3

NOT_ERROR_STUB		0
NOT_ERROR_STUB		1
NOT_ERROR_STUB		2
NOT_ERROR_STUB		3
NOT_ERROR_STUB		4
NOT_ERROR_STUB		5
NOT_ERROR_STUB		6
NOT_ERROR_STUB		7
ERROR_STUB			8
NOT_ERROR_STUB		9
ERROR_STUB			10
ERROR_STUB			11
ERROR_STUB			12
ERROR_STUB			13
ERROR_STUB			14
NOT_ERROR_STUB		15
NOT_ERROR_STUB		16
ERROR_STUB			17
NOT_ERROR_STUB		18
NOT_ERROR_STUB		19
NOT_ERROR_STUB		20
NOT_ERROR_STUB		21
NOT_ERROR_STUB		22
NOT_ERROR_STUB		23
NOT_ERROR_STUB		24
NOT_ERROR_STUB		25
NOT_ERROR_STUB		26
NOT_ERROR_STUB		27
NOT_ERROR_STUB		28
NOT_ERROR_STUB		29
NOT_ERROR_STUB		30
NOT_ERROR_STUB		31

global exception_global_handler_stub
exception_global_handler_stub:
	; FIXME: use of global variables (problem for SMP)
	; check if there was a privilege level change
	mov [.tmp], eax
	mov eax, [esp + 4]
	and eax, 3
	cmp eax, 3
	sete al
	mov byte [.ring_switch], al
	and byte [.ring_switch], 0xff
	mov eax, [.tmp]

	; save ip, cs, flags
	pop dword [.reg_ip]
	pop dword [.seg_cs]
	pop dword [.reg_flags]

	; save ds, bp
	mov word [.seg_ds], ds
	mov dword [.reg_bp], ebp

	cmp byte [.ring_switch], 0
	jne .save_iret_frame_with_new_pl

	; save ss, sp
	mov word [.seg_ss], ss
	and dword [.seg_ss], 0xffff
	mov dword [.reg_sp], esp

	jmp .save_cr3
.save_iret_frame_with_new_pl:
	; save old sp, old ss
	pop dword [.reg_sp]
	pop dword [.seg_ss]
.save_cr3:
	mov [.tmp], eax
	; save cr3
	mov eax, cr3
	mov dword [.reg_cr3], eax
.enter_kernel:
	; load kernel cr3
	mov eax, [KERNEL_CR3]
	mov cr3, eax

	; load kernel segment registers
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; FIXME: must be REAL kernel stack (now it's real, but can be changed later)
	; load kernel sp & bp
	mov esp, 0x6000
	mov ebp, 0x6000
	mov eax, [.tmp]
.push_exception_global_handler_args:
	; push flags, cs, ip
	push dword [.reg_flags]
	push dword [.seg_cs]
	push dword [.reg_ip]
	
	; push error_code, int_index
	push dword [error_code]
	push dword [int_index]

	; pusha
	push eax
	push ecx
	push edx
	push ebx
	push dword [.reg_sp]
	push dword [.reg_bp]
	push esi
	push edi

	push dword [.seg_ds]
	push dword [.seg_ds]
	push dword [.seg_ds]
	push dword [.seg_ds]

	push esp
	cld
	call exception_global_handler
	add esp, 4
	jmp $

;	pusha
;	push ds
;	push es
;	push fs
;	push gs
;
;	mov ax, 0x10
;	mov ds, ax
;	mov es, ax
;	mov fs, ax
;	mov gs, ax
;	
;	mov eax, esp
;	push eax
;	cld
;	call exception_global_handler
;	jmp $
;	pop eax
;
;	pop gs
;	pop fs
;	pop es
;	pop ds
;	popa

;	add esp, 8
;	iret
.ring_switch:				dd 0
.reg_ip:					dd 0
.seg_cs:					dd 0
.reg_old_sp:				dd 0
.seg_old_ss:				dd 0
.reg_flags:					dd 0
.seg_ss:					dd 0
.reg_sp:					dd 0
.reg_bp:					dd 0
.seg_ds:					dd 0
.reg_cr3:					dd 0
.tmp:						dd 0
error_code:					dd 0
int_index:					dd 0