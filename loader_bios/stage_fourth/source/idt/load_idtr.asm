bits 32

; void LOADERCALL idtr_load(const void* idtr);
global idtr_load
idtr_load:
	pushf
	push ebx
	
	mov ebx, [esp + 12]
	lidt [ebx]

	pop ebx
	popf
	ret