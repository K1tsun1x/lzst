bits 32

; void LOADERCALL gdt_reload(const void* gdt_descriptor);
global gdt_reload
gdt_reload:
	pushf
	push ebx
	mov ebx, [esp + 12]
	lgdt [ebx]
	jmp 0x08:.l_jmp
.l_jmp:
	pop ebx
	popf
	ret