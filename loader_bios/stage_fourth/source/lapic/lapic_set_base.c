#include <lapic/lapic.h>

volatile uint32_t* LAPIC_REGS = NULL;

bool lapic_set_base(uintptr_t base) {
	if (base & 0xfff) return false;

	LAPIC_REGS = (volatile uint32_t*)base;
	
	uint64_t value = (uint64_t)(base | LAPIC_MSR_IA32_APIC_BASE_FLAG_ENABLE);
	wrmsr(LAPIC_MSR_IA32_APIC_BASE, value);
	return true;
}