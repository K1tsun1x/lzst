bits 16
org 0x1000

%define BUFFER				END

BEGIN:
	; It’s not necessary now, but if the code in this file is changed,
	; it can save time searching for an error (if suddenly DL is used)
	mov [DRIVE], dl

	mov bp, BEGIN
	mov sp, BEGIN

	; Load the third stage header
	mov ah, 0x42
	mov dl, [DRIVE]
	mov si, DISK_ADDRESS_PACKET
	int 0x13
	jc .ERROR_FAILED_TO_READ_THIRD_STAGE

	; Check the third stage header signature
	cmp dword [BUFFER], 0x444c5a4c
	jne .ERROR_INVALID_THIRD_STAGE_HEADER_SIGNATURE

	; Check the size of the bootloader (in sectors)
	mov eax, [BUFFER + 4]
	cmp eax, 0x7f
	ja .ERROR_THIRD_STAGE_IS_TOO_LARGE_TO_LOAD

	test al, al
	jz .ERROR_FAILED_TO_READ_THIRD_STAGE

	dec al
	jz .JUMP_TO_THIRD_STAGE

	and ax, 0xffff
	add word [DISK_ADDRESS_PACKET.Offset], 512
	mov word [DISK_ADDRESS_PACKET.Count], ax
	inc dword [DISK_ADDRESS_PACKET.LBALow]
	mov byte [DISK_ADDRESS_PACKET.Size], 16

	; Load the third stage
	mov ah, 0x42
	mov dl, [DRIVE]
	mov si, DISK_ADDRESS_PACKET
	int 0x13
	jc .ERROR_FAILED_TO_READ_THIRD_STAGE
.JUMP_TO_THIRD_STAGE:
	; Push the BIOS drive number
	mov dl, [DRIVE]
	and edx, 0xff
	push dword edx

	; Jump to the third stage entry point
	push dword .HALT
	jmp word [BUFFER + 8]
.HALT:
	jmp $

.ERROR_FAILED_TO_READ_THIRD_STAGE:
	mov si, ErrorFailedToReadThirdStage
	call print
	jmp $

.ERROR_INVALID_THIRD_STAGE_HEADER_SIGNATURE:
	mov si, ErrorInvalidThirdStageHeaderSignature
	call print
	jmp $

.ERROR_THIRD_STAGE_IS_TOO_LARGE_TO_LOAD:
	mov si, ErrorThirdStageIsTooLargeToLoad
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

ErrorFailedToReadThirdStage:			db "Error: failed to read third stage", 0
ErrorInvalidThirdStageHeaderSignature:	db "Error: invalid third stage header signature", 0
ErrorThirdStageIsTooLargeToLoad:		db "Error: third stage is too large to load", 0
DRIVE:	db 0

DISK_ADDRESS_PACKET:
	.Size:				db 16
	.Reserved:			db 0
	.Count:				dw 1
	.Offset:			dw BUFFER
	.Segment:			dw 0
	.LBALow:			dd 2
	.LBAHigh:			dd 0

times 512 - $ + $$ db 0
END: