bits 32

global TEST_TASK2_START
TEST_TASK2_START:

ALIGN(0x1000)
global test_task2
test_task2:
	push dword 0x0000444E			; 'ND'
	push dword 0x4F434553			; 'SECO'
	mov eax, 1
	mov ecx, esp
	int 0x41
	add esp, 8
	jmp test_task2

global TEST_TASK2_END
TEST_TASK2_END: