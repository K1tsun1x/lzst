bits 32

; void LOADERCALL load_idtr(const void* idtr);
global load_idtr
load_idtr:
	pushf
	push ebx
	
	mov ebx, [esp + 12]
	lidt [ebx]

	pop ebx
	popf
	ret