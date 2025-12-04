#include <exception/exception.h>

extern isr_t EXCEPTION_HANDLERS[NUM_EXCEPTIONS];

bool exception_set(size_t index, isr_t isr) {
	if (index >= NUM_EXCEPTIONS) return false;

	EXCEPTION_HANDLERS[index] = isr;
	return true;
}