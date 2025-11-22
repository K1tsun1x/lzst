bits 16

; void LOADERCALL gdt_load(const void* gdt_descriptor, uintptr_t return_address, uintptr_t stack_top);
global gdt_load
gdt_load:
	cli
	pop ebx
	pop ebx
	pop dword [.tmp_return_address]
	pop dword [.tmp_stack_top]
	pop dword [.tmp_bootloader_info_ptr]

	lgdt [ebx]
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
	mov ebp, [.tmp_stack_top]
	mov esp, ebp

	push dword [.tmp_bootloader_info_ptr]
	call dword [.tmp_return_address]
	cli
	hlt
.tmp_return_address:		dd 0
.tmp_stack_top:				dd 0
.tmp_bootloader_info_ptr:	dd 0
bits 16