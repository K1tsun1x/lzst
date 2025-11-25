bits 32

; paging_pde_t* LOADERCALL paging_get_directory(void)
global paging_get_directory
paging_get_directory:
	mov eax, cr3
	ret