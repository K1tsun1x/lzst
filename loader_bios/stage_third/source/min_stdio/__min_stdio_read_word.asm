bits 16

extern switch_stack_to_bios
extern switch_stack_to_normal

; uint16_t LOADERCALL __min_stdio_read_word(uint16_t offset)
global __min_stdio_read_word
__min_stdio_read_word:
	push bp
	mov bp, sp
	push bx
	push es

	mov ax, 0xb800
	mov es, ax
	mov bx, [bp + 6]
	mov ax, [es:bx]

	pop es
	pop bx
	pop bp
	retd