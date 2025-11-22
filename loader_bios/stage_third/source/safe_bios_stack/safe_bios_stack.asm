bits 16

ALIGN(2)
global __SAVED_PRE_SP
global __SAVED_PRE_BP
global __SAVED_PRE_SS
__SAVED_PRE_DS:			dw 0
__SAVED_PRE_ES:			dw 0
__SAVED_PRE_SS:			dw 0
__SAVED_PRE_SP:			dw 0
__SAVED_PRE_BP:			dw 0

ALIGN(16)
global BIOS_STACK_BOTTOM
BIOS_STACK_BOTTOM:
	times 0x1000 db 0
global BIOS_STACK_TOP
BIOS_STACK_TOP:

; This function should only be called from 16-bit assembly
global switch_stack_to_bios
switch_stack_to_bios:
	pop word [.tmp_ret_address]

	cli
	mov [__SAVED_PRE_DS], ds
	mov [__SAVED_PRE_ES], es
	mov [__SAVED_PRE_SS], ss
	mov [__SAVED_PRE_SP], sp
	mov [__SAVED_PRE_BP], bp
	mov bp, BIOS_STACK_TOP
	mov sp, BIOS_STACK_TOP
	sti

	jmp word [.tmp_ret_address]
.tmp_ret_address:		dw 0

; This function should only be called from 16-bit assembly
global switch_stack_to_normal
switch_stack_to_normal:
	pop word [.tmp_ret_address]

	cli
	mov [.tmp_ax], ax
	mov ax, [__SAVED_PRE_SS]
	mov ss, ax
	mov ax, [__SAVED_PRE_DS]
	mov ds, ax
	mov ax, [__SAVED_PRE_ES]
	mov es, ax
	mov ax, [.tmp_ax]
	mov bp, [__SAVED_PRE_BP]
	mov sp, [__SAVED_PRE_SP]
	sti

	jmp word [.tmp_ret_address]
.tmp_ret_address:		dw 0
.tmp_ax:				dw 0