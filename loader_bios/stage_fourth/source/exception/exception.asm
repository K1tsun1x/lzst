bits 32

extern exception_global_handler

%macro ERROR_STUB				1
global exception_stub%+%1
exception_stub%+%1:
	push dword %1
	jmp exception_global_handler_stub
%endmacro

%macro NOT_ERROR_STUB			1
global exception_stub%+%1
exception_stub%+%1:
	push dword 0
	push dword %1
	jmp exception_global_handler_stub
%endmacro

NOT_ERROR_STUB		0
NOT_ERROR_STUB		1
NOT_ERROR_STUB		2
NOT_ERROR_STUB		3
NOT_ERROR_STUB		4
NOT_ERROR_STUB		5
NOT_ERROR_STUB		6
NOT_ERROR_STUB		7
ERROR_STUB			8
NOT_ERROR_STUB		9
ERROR_STUB			10
ERROR_STUB			11
ERROR_STUB			12
ERROR_STUB			13
ERROR_STUB			14
NOT_ERROR_STUB		15
NOT_ERROR_STUB		16
ERROR_STUB			17
NOT_ERROR_STUB		18
NOT_ERROR_STUB		19
NOT_ERROR_STUB		20
ERROR_STUB			21
NOT_ERROR_STUB		22
NOT_ERROR_STUB		23
NOT_ERROR_STUB		24
NOT_ERROR_STUB		25
NOT_ERROR_STUB		26
NOT_ERROR_STUB		27
NOT_ERROR_STUB		28
ERROR_STUB			29
ERROR_STUB			30
NOT_ERROR_STUB		31

global exception_global_handler_stub
exception_global_handler_stub:
	pusha
	push ds
	push es
	push fs
	push gs

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov eax, esp
	push esp
	call exception_global_handler
	pop eax

	pop gs
	pop fs
	pop es
	pop ds
	popa

	add esp, 8
	iret