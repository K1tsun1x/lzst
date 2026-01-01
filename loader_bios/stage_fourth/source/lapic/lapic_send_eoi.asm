bits 32

%define LAPIC_REG_EOI				0xb0

extern LAPIC_REGS

; void lapic_send_eoi(uint8_t index)
global lapic_send_eoi
lapic_send_eoi:
	push ebx
	mov ebx, LAPIC_REG_EOI
	add ebx, [LAPIC_REGS]
	mov dword [ebx], 0
	pop ebx
	ret