bits 16

; bool LOADERCALL a20_enabled(void)
global a20_enabled
a20_enabled:
	pushf
	push si
	push di
	push ds
	push es
	push bx
	mov bh, ah
	cli

	xor ax, ax
	mov ds, ax
	not ax
	mov es, ax
	mov si, 0x0500
	mov di, 0x0510

	mov ah, [es:di]
	mov al, [ds:si]

	mov byte [es:di], 0xaa
	mov byte [ds:si], 0x55

	cmp byte [es:di], 0x55

	mov byte [es:di], ah
	mov byte [ds:si], al

	mov al, 0
	je .fin

	mov al, 1
.fin:
	mov ah, bh
	pop bx
	pop es
	pop ds
	pop di
	pop si
	popf
	retd