bits 32

%define PIC_PORT_MASTER_COMMAND				0x20
%define PIC_PORT_SLAVE_COMMAND				0xa0

%define PIC_COMMAND_EOI						0x20

; void pic_send_eoi(uint8_t index)
global pic_send_eoi
pic_send_eoi:
	push eax
	mov al, PIC_COMMAND_EOI
	out PIC_PORT_MASTER_COMMAND, al
	pop eax

	cmp byte [esp + 4], 7
	jna .fin

	push eax
	mov al, PIC_COMMAND_EOI
	out PIC_PORT_SLAVE_COMMAND, al
	pop eax
.fin:
	ret