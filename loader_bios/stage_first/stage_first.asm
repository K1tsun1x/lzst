bits 16
org 0x7c00
%define BUFFER						0x1000
%define SECTOR_SIZE					512

BEGIN:
	; It’s not necessary now, but if the code in this file is changed,
	; it can save time searching for an error (if suddenly DL is used)
	mov [DRIVE], dl

	; Reset the CS register
	jmp 0:INIT
INIT:
	; Reset the other segment registers
	mov ax, 0
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; Reset the stack registers
	mov bp, BEGIN
	mov sp, BEGIN

	; Switch to BIOS video mode 3 (80x25 text)
	mov ax, 3
	int 0x10

	; Load the second stage
	mov ax, 0x0201
	mov cx, 2
	mov dh, 0
	mov bx, BUFFER
	int 0x13
	jc .ERROR_FAILED_TO_READ_SECOND_STAGE

	mov dl, [DRIVE]
	jmp BUFFER

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

ErrorFailedToReadSecondStage:			db "Error: failed to read second stage", 0
DRIVE:									db 0

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