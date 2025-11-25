bits 32

; void LOADERCALL paging_load_directory(const paging_pde_t* directory);
global paging_load_directory
paging_load_directory:
	push ebp
	mov ebp, esp
	push eax
	
	mov eax, [ebp + 8]
	mov cr3, eax

	pop eax
	pop ebp
	ret