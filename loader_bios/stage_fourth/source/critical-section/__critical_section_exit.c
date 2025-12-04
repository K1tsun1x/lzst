#include <critical-section/critical-section.h>

extern size_t __CRITICAL_SECTION_CALLS;
extern irq_flags_t __CRITICAL_SECTION_IRQ_FLAGS;

void __critical_section_exit(void) {
	if (!__CRITICAL_SECTION_CALLS) return;

	__CRITICAL_SECTION_CALLS -= 1;
	if (!__CRITICAL_SECTION_CALLS) irq_restore(__CRITICAL_SECTION_IRQ_FLAGS);
}