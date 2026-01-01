bits 32

%define SYS_INFO_OFFSET_OSXSAVE_PRESENT				0x3a

extern SYS_INFO

; bool LOADERCALL sys_osxsave_present(void)
global sys_osxsave_present
sys_osxsave_present:
	mov al, [SYS_INFO + SYS_INFO_OFFSET_OSXSAVE_PRESENT]
	ret