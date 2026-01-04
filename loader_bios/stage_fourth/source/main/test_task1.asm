bits 32

global TEST_TASK1_START
TEST_TASK1_START:

ALIGN(0x1000)
global test_task1
test_task1:
	push dword 0x00000054			; 'T'
	push dword 0x53524946			; 'FIRS'
	mov eax, 1
	mov ecx, esp
	int 0x41
	add esp, 8
	jmp test_task1

global TEST_TASK1_END
TEST_TASK1_END: