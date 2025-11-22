bits 32

%define CR0_MP				(1 << 1)
%define CR0_EM				(1 << 2)
%define CR0_TS				(1 << 3)

%define CR4_OSFXSR			(1 << 9)
%define CR4_OSXMMEXCPT		(1 << 10)
%define CR4_OSXSAVE			(1 << 18)

; void LOADERCALL fpu_init(bool osfxsr, bool osxmmexcpt, bool osxsave);
global fpu_init
fpu_init:
	push ebp
	mov ebp, esp
	push eax
	push ecx

	mov eax, cr0
	and eax, ~(CR0_EM | CR0_TS)
	or eax, CR0_MP
	mov cr0, eax
	
	mov eax, cr4
.osfxsr:
	mov cl, [ebp + 8]
	test cl, cl
	jz .osxmmexcpt

	or eax, CR4_OSFXSR
.osxmmexcpt:
	mov cl, [ebp + 12]
	test cl, cl
	jz .osxsave

	or eax, CR4_OSXMMEXCPT
.osxsave:
	mov cl, [ebp + 16]
	test cl, cl
	jz .after_cr4

	or eax, CR4_OSXSAVE
.after_cr4:
	mov cr4, eax

	test eax, CR4_OSFXSR
	jz .fin
	ldmxcsr [mxcsr]
.fin:
	fninit
	pop ecx
	pop eax
	pop ebp
	ret

align(16)
mxcsr:		dd 0x1f80