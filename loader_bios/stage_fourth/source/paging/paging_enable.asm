bits 32

; void LOADERCALL paging_enable(void);
global paging_enable
paging_enable:
	push eax
	mov eax, cr0
	or eax, 0x80000001
	mov cr0, eax
	pop eax
	ret