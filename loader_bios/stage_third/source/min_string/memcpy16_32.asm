bits 16

extern gdt_switch_to16
extern gdt_switch_to32

; void LOADERCALL memcpy16_32(uint32_t src, uint32_t dst, uint32_t count)
global memcpy16_32
memcpy16_32:
	push dword [esp + 4]
	pop dword [.tmp_src]
	push dword [esp + 8]
	pop dword [.tmp_dst]
	push dword [esp + 12]
	pop dword [.tmp_cnt]

	push dword .mode32
	call dword gdt_switch_to32
.mode32:
bits 32
	push ax
	push ecx
	push esi
	push edi
	push es
	push ds

	mov ax, 0
	mov ds, ax
	mov esi, [.tmp_src]
	mov es, ax
	mov edi, [.tmp_dst]
	mov ecx, [.tmp_cnt]
	rep movsb

	pop ds
	pop es
	pop edi
	pop esi
	pop ecx
	pop ax

	push dword .mode16
	call dword gdt_switch_to16
.mode16:
bits 16
	retd
.tmp_src:			dd 0
.tmp_dst:			dd 0
.tmp_cnt:			dd 0