bits 16

extern switch_stack_to_bios
extern switch_stack_to_normal

; bool LOADERCALL __drive_read_sector(uint8_t al, uint16_t cx, uint16_t dx, uint16_t es, uint16_t bx);
global __drive_read_sector
__drive_read_sector:
	push bp
	mov bp, sp
	push ax
	push cx
	push dx
	push bx
	push es

	mov byte [.tmp_result], 0

	mov ax, [bp + 18]
	mov es, ax
	mov ah, 0x02
	mov al, [bp + 6]
	mov cx, [bp + 10]
	mov dx, [bp + 14]
	mov bx, [bp + 22]
	call switch_stack_to_bios
	int 0x13
	call switch_stack_to_normal
	jc .fin

	mov byte [.tmp_result], 1
.fin:
	pop es
	pop bx
	pop dx
	pop cx
	pop ax
	pop bp
	mov al, [.tmp_result]
	retd
.tmp_result:			db 0