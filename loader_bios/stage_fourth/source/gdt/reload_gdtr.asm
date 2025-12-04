bits 32

; void LOADERCALL gdtr_load(const void* gdtr);
global gdtr_load
gdtr_load:
	pushf
	push ebx
	mov ebx, [esp + 12]
	lgdt [ebx]
	jmp 0x08:.l_jmp
.l_jmp:
	pop ebx
	popf
	ret