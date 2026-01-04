bits 32

%define SW_INT_SCHEDULER_YIELD	0
%define SW_INT_TTY				1

%macro SW_INT					1
global sw_int_stub%+%1
sw_int_stub%+%1:
	mov dword [int_index], %1+0x40
	jmp sw_int_global_handler_stub
%endmacro

extern KERNEL_CR3

extern sw_int_global_handler

SW_INT			SW_INT_SCHEDULER_YIELD
SW_INT			SW_INT_TTY

sw_int_global_handler_stub:
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
.push_scheduler_tick_args:
	; push flags, cs, ip
	push dword [.reg_flags]
	push dword [.seg_cs]
	push dword [.reg_ip]

	; pusha
	push eax
	push ecx
	push edx
	push ebx
	push dword [.reg_sp]
	push dword [.reg_bp]
	push esi
	push edi

	; push ss, ds, cr3
	push dword [.seg_ss]
	push dword [.seg_ds]
	push dword [.reg_cr3]

	; push int index
	push dword [int_index]

	; push address of structure
	push esp

	; push [bool ring_switch]
	push dword [.ring_switch]
	
	cld
	call sw_int_global_handler
.pop_scheduler_tick_args:
	; remove ring_switch, address of structure, int index
	add esp, 12

	; pop cr3, ds, ss
	pop dword [.reg_cr3]
	pop dword [.seg_ds]
	pop dword [.seg_ss]

	; popa
	pop edi
	pop esi
	pop dword [.reg_bp]
	pop dword [.reg_sp]
	pop ebx
	pop edx
	pop ecx
	pop eax

	; pop ip, cs, flags
	pop dword [.reg_ip]
	pop dword [.seg_cs]
	pop dword [.reg_flags]
.return_back:
	mov [.tmp], eax
	; load cr3
	mov eax, [.reg_cr3]
	mov cr3, eax
	mov eax, [.tmp]

	; load stack
	mov ss, [.seg_ss]
	mov esp, [.reg_sp]
	mov ebp, [.reg_bp]

	; load segment registers
	mov ds, [.seg_ds]
	mov es, [.seg_ds]
	mov fs, [.seg_ds]
	mov gs, [.seg_ds]

	; push IRET-frame
	push dword [.reg_flags]
	push dword [.seg_cs]
	push dword [.reg_ip]

	cmp byte [.ring_switch], 0
	je .fin

	; although SS:ESP have already been changed,
	; they must be in the IRET frame after changing PL
	push dword [.reg_sp]
	push dword [.seg_ss]
.fin:
	iret
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
int_index:					dd 0