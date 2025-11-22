bits 32

; bool LOADERCALL cpuid486_present(void);
global cpuid486_present
cpuid486_present:
	push ecx
	push eax

	pushfd
	pushfd
	xor dword [esp], 0x00200000
	popfd
	pushfd
	pop eax
	xor eax, [esp] 
	popfd
	and eax, 0x00200000

	test eax, eax
	jz .no

	mov cl, 1
	jmp .fin
.no:
	mov cl, 0
.fin:
	pop eax
	mov al, cl
	pop ecx
	ret