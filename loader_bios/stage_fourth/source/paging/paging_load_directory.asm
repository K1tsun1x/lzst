bits 32

global KERNEL_CR3
KERNEL_CR3:				dd 0

; void LOADERCALL paging_load_directory(const paging_pde_t* directory);
global paging_load_directory
paging_load_directory:
	push ebp
	mov ebp, esp
	push eax
	
	mov eax, [ebp + 8]
	mov cr3, eax
	mov [KERNEL_CR3], eax

	pop eax
	pop ebp
	ret