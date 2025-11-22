bits 32

; void LOADERCALL __cpuid486_call(
; 	uint32_t leaf,
; 	uint32_t sub_leaf,
; 	uint32_t* eax,
; 	uint32_t* ecx,
; 	uint32_t* edx,
; 	uint32_t* ebx
; );
global __cpuid486_call
__cpuid486_call:
	push ebp
	mov ebp, esp
	push eax
	push ecx
	push edx
	push ebx
	push edi

	mov eax, [ebp + 8]
	mov ecx, [ebp + 12]
	cpuid

.save_eax:
	mov edi, [ebp + 16]
	test edi, edi
	jz .save_ecx
	mov [edi], eax
.save_ecx:
	mov edi, [ebp + 20]
	test edi, edi
	jz .save_edx
	mov [edi], ecx
.save_edx:
	mov edi, [ebp + 24]
	test edi, edi
	jz .save_ebx
	mov [edi], edx
.save_ebx:
	mov edi, [ebp + 28]
	test edi, edi
	jz .fin
	mov [edi], ebx
.fin:
	pop edi
	pop ebx
	pop edx
	pop ecx
	pop eax
	pop ebp
	ret