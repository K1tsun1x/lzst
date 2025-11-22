bits 16

extern switch_stack_to_bios
extern switch_stack_to_normal

; bool LOADERCALL __e820_get_next_entry(uint32_t ebx, uint16_t di, uint32_t* size, uint32_t* next);
global __e820_get_next_entry
__e820_get_next_entry:
	push bp
	mov bp, sp
	push eax
	push ecx
	push edx
	push ebx
	push esi
	push edi
	push es

	mov byte [.tmp_result], 0

	push word ds
	pop es
	mov ebx, [bp + 6]
	mov di, [bp + 10]
	mov eax, 0x0000e820
	mov ecx, 0x00000018
	mov edx, 0x534d4150
	
	; In Bochs, int 15h breaks the stack, so before calling it
	; you have to save the old registers SS, DS, ES, ESP, EBP,
	; load a new stack intended only for BIOS,
	; and after int 0x15 restore the old stack
	call switch_stack_to_bios
	int 0x15
	call switch_stack_to_normal
	jc .fin

	cmp eax, 0x534d4150
	jne .fin

	mov di, [bp + 14]
	mov [di], ecx
	mov di, [bp + 18]
	mov [di], ebx

	mov byte [.tmp_result], 1
.fin:
	pop es
	pop edi
	pop esi
	pop ebx
	pop edx
	pop ecx
	pop eax
	pop bp
	mov al, [.tmp_result]
	retd
.tmp_result:			db 0