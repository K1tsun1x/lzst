bits 32

%define SYS_INFO_OFFSET_FPU_PRESENT					0x34

extern SYS_INFO

; bool LOADERCALL sys_fpu_present(void)
global sys_fpu_present
sys_fpu_present:
	mov al, [SYS_INFO + SYS_INFO_OFFSET_FPU_PRESENT]
	ret