#include <critical-section/critical-section.h>

__volatile__ size_t __CRITICAL_SECTION_CALLS = 0;
__volatile__ irq_flags_t __CRITICAL_SECTION_IRQ_FLAGS = 0;

void __critical_section_enter(void) {
	if (!__CRITICAL_SECTION_CALLS) __CRITICAL_SECTION_IRQ_FLAGS = irq_disable();
	__CRITICAL_SECTION_CALLS += 1;
}