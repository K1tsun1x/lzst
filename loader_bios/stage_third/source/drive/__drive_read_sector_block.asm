bits 16

extern switch_stack_to_bios
extern switch_stack_to_normal

; bool LOADERCALL __drive_read_sector_block(
; 	uint8_t drive,
; 	uint16_t count,
; 	uint16_t buffer_off,
; 	uint16_t buffer_seg,
; 	uint32_t lba_low,
; 	uint32_t lba_high
; );
global __drive_read_sector_block
__drive_read_sector_block:
	push bp
	mov bp, sp
	push eax
	push cx
	push dx
	push bx
	push si
	push ds

	mov byte [.return_value], 0

	mov byte [DISK_ADDRESS_PACKET.Size], 16
	mov ax, [bp + 10]
	mov [DISK_ADDRESS_PACKET.Count], ax
	mov ax, [bp + 14]
	mov [DISK_ADDRESS_PACKET.Offset], ax
	mov ax, [bp + 18]
	mov [DISK_ADDRESS_PACKET.Segment], ax
	mov eax, [bp + 22]
	mov [DISK_ADDRESS_PACKET.LBALow], eax
	mov eax, [bp + 26]
	mov [DISK_ADDRESS_PACKET.LBAHigh], eax

	mov ax, 0
	mov ds, ax

	mov ah, 0x42
	mov dl, [bp + 6]
	mov si, DISK_ADDRESS_PACKET
	call switch_stack_to_bios
	int 0x13
	pushf
	pop ax
	call switch_stack_to_normal
	
	test ax, 1
	jnz .fin

	mov byte [.return_value], 1
.fin:
	pop ds
	pop si
	pop bx
	pop dx
	pop cx
	pop eax
	pop bp
	mov al, [.return_value]
	retd
.return_value:		db 0
align(16)
DISK_ADDRESS_PACKET:
	.Size:			db 16
	.Reserved:		db 0
	.Count:			dw 0
	.Offset:		dw 0
	.Segment:		dw 0
	.LBALow:		dd 0
	.LBAHigh:		dd 0