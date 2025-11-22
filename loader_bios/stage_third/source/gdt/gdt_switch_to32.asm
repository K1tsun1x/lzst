bits 32

extern __GDT_DESCRIPTOR32

; void LOADERCALL gdt_switch_to32(uint32_t return_address);
global gdt_switch_to32
gdt_switch_to32:
bits 16
	cli
	mov dword [.tmp_eax], eax
	mov dword [.tmp_ebx], ebx
	pop ebx
	pop dword [.tmp_return_address]

	lgdt [__GDT_DESCRIPTOR32]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp 0x08:.set_segment_registers
.set_segment_registers:
bits 32
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	mov eax, [.tmp_eax]
	mov ebx, [.tmp_ebx]
	jmp dword [.tmp_return_address]
.tmp_eax:					dd 0
.tmp_ebx:					dd 0
.tmp_return_address:		dd 0