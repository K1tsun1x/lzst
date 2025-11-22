bits 16

extern switch_stack_to_bios
extern switch_stack_to_normal

; void LOADERCALL __min_stdio_write_word(uint16_t offset, uint16_t value)
global __min_stdio_write_word
__min_stdio_write_word:
	push bp
	mov bp, sp
	push ax
	push bx
	push es

	mov ax, 0xb800
	mov es, ax
	mov bx, [bp + 6]
	mov ax, [bp + 10]
	mov [es:bx], ax

	pop es
	pop bx
	pop ax
	pop bp
	retd