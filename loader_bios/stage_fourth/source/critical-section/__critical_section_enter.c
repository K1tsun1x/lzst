#include <critical-section/critical-section.h>

volatile size_t __CRITICAL_SECTION_CALLS = 0;
volatile irq_flags_t __CRITICAL_SECTION_IRQ_FLAGS = 0;

void __critical_section_enter(void) {
	if (!__CRITICAL_SECTION_CALLS) __CRITICAL_SECTION_IRQ_FLAGS = irq_disable();
	__CRITICAL_SECTION_CALLS += 1;
}