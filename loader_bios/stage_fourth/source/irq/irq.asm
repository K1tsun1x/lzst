bits 32

extern irq_global_handler

%macro IRQ					1
global irq_stub%+%1
irq_stub%+%1:
	push dword 0
	push dword %1+32
	jmp irq_global_handler_stub
%endmacro

IRQ					0
IRQ					1
IRQ					2
IRQ					3
IRQ					4
IRQ					5
IRQ					6
IRQ					7
IRQ					8
IRQ					9
IRQ					10
IRQ					11
IRQ					12
IRQ					13
IRQ					14
IRQ					15

irq_global_handler_stub:
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
	call irq_global_handler
	pop eax

	pop gs
	pop fs
	pop es
	pop ds
	popa

	add esp, 8
	iret