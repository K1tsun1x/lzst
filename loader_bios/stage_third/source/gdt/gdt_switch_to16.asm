bits 32

extern __GDT_DESCRIPTOR16

; @warnign SS will be 0(!)
; void LOADERCALL gdt_switch_to16(uint16_t return_address);
global gdt_switch_to16
gdt_switch_to16:
	cli
	mov dword [.tmp_eax], eax
	mov dword [.tmp_ebx], ebx
	pop ebx
	pop dword [.tmp_return_address]

	lgdt [__GDT_DESCRIPTOR16]
	jmp 0x08:.set_segment_registers_pm16
.set_segment_registers_pm16:
bits 16
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov eax, cr0
	and eax, 0xfffffffe
	mov cr0, eax
	jmp 0:.set_segment_registers_rm
.set_segment_registers_rm:
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov eax, [.tmp_eax]
	mov ebx, [.tmp_ebx]
	mov esi, [.tmp_return_address]
	sti

	jmp word [.tmp_return_address]
.tmp_eax:					dd 0
.tmp_ebx:					dd 0
.tmp_return_address:		dd 0
bits 32