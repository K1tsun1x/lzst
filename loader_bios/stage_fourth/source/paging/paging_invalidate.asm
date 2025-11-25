bits 32

; void LOADERCALL paging_invalidate(void);
global paging_invalidate
paging_invalidate:
	push eax
	mov eax, cr3
	mov cr3, eax
	pop eax
	ret