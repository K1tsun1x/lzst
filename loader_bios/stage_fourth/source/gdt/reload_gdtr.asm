bits 32

; void LOADERCALL reload_gdtr(const void* gdtr);
global reload_gdtr
reload_gdtr:
	pushf
	push ebx
	mov ebx, [esp + 12]
	lgdt [ebx]
	jmp 0x08:.l_jmp
.l_jmp:
	pop ebx
	popf
	ret