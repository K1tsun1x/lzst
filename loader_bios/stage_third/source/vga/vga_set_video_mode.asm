bits 16

extern switch_stack_to_bios
extern switch_stack_to_normal

; bool LOADERCALL vga_set_video_mode(uint8_t mode);
global vga_set_video_mode
vga_set_video_mode:
	push bp
	mov bp, sp
	push ax

	mov byte [.tmp_result], 0

	mov ah, 0
	mov al, [bp + 6]
	call switch_stack_to_bios
	int 0x10
	call switch_stack_to_normal

	mov ah, 0x0f
	call switch_stack_to_bios
	int 0x10
	call switch_stack_to_normal

	cmp al, [bp + 6]
	jne .fin

	mov byte [.tmp_result], 1
.fin:
	pop ax
	pop bp
	mov al, [.tmp_result]
	retd
.tmp_result:		db 0