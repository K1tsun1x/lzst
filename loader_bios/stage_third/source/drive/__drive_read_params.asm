bits 16

extern switch_stack_to_bios
extern switch_stack_to_normal

; bool LOADERCALL __drive_read_params(uint8_t drive, uint8_t* dh, uint16_t* cx);
global __drive_read_params
__drive_read_params:
	push bp
	mov bp, sp
	push ax
	push cx
	push dx
	push bx
	push si
	push di
	push es

	mov byte [.tmp_result], 0

	push word 0
	pop es
	mov ah, 0x08
	mov dl, [bp + 6]
	xor di, di
	call switch_stack_to_bios
	int 0x13
	call switch_stack_to_normal
	jc .fin

	mov di, [bp + 10]
	mov [di], dh
	mov di, [bp + 14]
	mov [di], cx

	mov byte [.tmp_result], 1
.fin:
	pop es
	pop di
	pop si
	pop bx
	pop dx
	pop cx
	pop ax
	pop bp
	mov al, [.tmp_result]
	retd
.tmp_result:			db 0