bits 16
org 0x7c00
%define BUFFER						0x1000
%define SECTOR_SIZE					512

BEGIN:
	; Reset the CS register
	jmp 0:INIT
INIT:
	; Reset the other segment registers
	cli
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; Reset the stack registers
	mov bp, BEGIN
	mov sp, BEGIN
	sti
	cld

	; Switch to BIOS video mode 3 (80x25 text)
	mov ax, 3
	int 0x10

	mov dl, 0x80
FIND_DRIVE:
	mov ah, 0x41
	mov bx, 0x55aa
	int 0x13
	jc .NEXT

	test cx, 1
	jz .NEXT

	mov byte [DISK_ADDRESS_PACKET.Size], 16
	mov byte [DISK_ADDRESS_PACKET.Reserved], 0
	mov word [DISK_ADDRESS_PACKET.Count], 1
	mov word [DISK_ADDRESS_PACKET.Offset], BUFFER
	mov word [DISK_ADDRESS_PACKET.Segment], 0
	mov dword [DISK_ADDRESS_PACKET.LBALow], 0
	mov dword [DISK_ADDRESS_PACKET.LBAHigh], 0
	mov ah, 0x42
	mov si, DISK_ADDRESS_PACKET
	int 0x13
	jc .NEXT

	cmp word [BUFFER + 510], 0xaa55
	jne .NEXT

	mov byte [DISK_ADDRESS_PACKET.Size], 16
	mov byte [DISK_ADDRESS_PACKET.Reserved], 0
	mov word [DISK_ADDRESS_PACKET.Count], 1
	mov word [DISK_ADDRESS_PACKET.Offset], BUFFER
	mov word [DISK_ADDRESS_PACKET.Segment], 0
	mov dword [DISK_ADDRESS_PACKET.LBALow], 2
	mov dword [DISK_ADDRESS_PACKET.LBAHigh], 0
	mov ah, 0x42
	mov si, DISK_ADDRESS_PACKET
	int 0x13
	jc .NEXT

	cmp dword [BUFFER], 0x444c5a4c
	jne .NEXT

	jmp .DRIVE_FOUND
.NEXT:
	inc dl
	cmp dl, 0
	je .COULD_NOT_BOOT_FROM_THIS_DRIVE
	jmp FIND_DRIVE

.DRIVE_FOUND:
	mov [DRIVE], dl

	; Load the second stage
	mov byte [DISK_ADDRESS_PACKET.Size], 16
	mov byte [DISK_ADDRESS_PACKET.Reserved], 0
	mov word [DISK_ADDRESS_PACKET.Count], 1
	mov word [DISK_ADDRESS_PACKET.Offset], BUFFER
	mov word [DISK_ADDRESS_PACKET.Segment], 0
	mov dword [DISK_ADDRESS_PACKET.LBALow], 1
	mov dword [DISK_ADDRESS_PACKET.LBAHigh], 0

	mov ah, 0x42
	mov dl, [DRIVE]
	mov si, DISK_ADDRESS_PACKET
	int 0x13
	jc .ERROR_FAILED_TO_READ_SECOND_STAGE

	mov dl, [DRIVE]
	jmp BUFFER

.COULD_NOT_BOOT_FROM_THIS_DRIVE:
	mov si, ErrorCouldNotBootFromThisDrive
	call print
	jmp $
.ERROR_FAILED_TO_READ_SECOND_STAGE:
	mov si, ErrorFailedToReadSecondStage
	call print
	jmp $

;	In:
;		si - string
print:
	push ax
	push si
	mov ah, 0x0e
.put_char:
	lodsb
	test al, al
	jz .finish
	int 0x10
	jmp .put_char
.finish:
	pop si
	pop ax
	ret

ErrorCouldNotBootFromThisDrive:			db "Error: could not boot from this drive", 0
ErrorFailedToReadSecondStage:			db "Error: failed to read second stage", 0
DRIVE:									db 0

DISK_ADDRESS_PACKET:
	.Size:				db 16
	.Reserved:			db 0
	.Count:				dw 1
	.Offset:			dw BUFFER
	.Segment:			dw 0
	.LBALow:			dd 1
	.LBAHigh:			dd 0

PARTITION_TABLE:
	times 446 - $ + $$ db 0
.FIRST_ENTRY:					; LZST bootloader partition (will be initialized after loading)
	db			0x80			; Flags (bootable)
	db			0				; Starting head
	dw			0				; Starting sector & cylinder
	db			0x7f			; System ID
	db			0				; Ending head
	dw			0				; Ending sector & cylinder
	dd			0				; Relative sector
	dd			0				; Total sectors in partition
.SECOND_ENTRY:	times 16 db 0	; Empty partition (here will be information about the file system)
.THIRD_ENTRY:	times 16 db 0	; Empty partition
.FOURTH_ENTRY:	times 16 db 0	; Empty partition

times 510 - $ + $$ db 0
dw 0xaa55
END: