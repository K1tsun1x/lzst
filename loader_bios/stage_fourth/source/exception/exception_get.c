#include <exception/exception.h>

extern isr_t EXCEPTION_HANDLERS[NUM_EXCEPTIONS];

bool exception_get(size_t index, isr_t* isr) {
	if (index >= NUM_EXCEPTIONS || !isr) return false;

	*isr = EXCEPTION_HANDLERS[index];
	return true;
}