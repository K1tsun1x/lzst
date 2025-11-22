bits 16

extern switch_stack_to_bios
extern switch_stack_to_normal

; bool LOADERCALL vbe_get_info(vbe_info_t* buffer);
global vbe_get_info
vbe_get_info:
	push bp
	mov bp, sp
	push ax
	push si
	push di
	push es

	mov byte [.tmp_result], 0

	push word ds
	pop es
	mov ax, 0x4f00
	mov di, [bp + 6]
	call switch_stack_to_bios
	int 0x10
	call switch_stack_to_normal
	jc .fin

	cmp ax, 0x004f
	jne .fin

	mov byte [.tmp_result], 1
.fin:
	pop es
	pop di
	pop si
	pop ax
	pop bp
	mov al, [.tmp_result]
	retd
.tmp_result:			db 0