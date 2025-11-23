bits 16

; uint16_t LOADERCALL __vbe_read_far_word(uint16_t offset, uint16_t segment);
global __vbe_read_far_word
__vbe_read_far_word:
	push bp
	mov bp, sp
	push si
	push ds

	mov si, [bp + 10]
	mov ds, si
	mov si, [bp + 6]
	mov ax, [ds:si]

	pop ds
	pop si
	pop bp
	retd