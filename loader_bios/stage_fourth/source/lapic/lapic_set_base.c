#include <lapic/lapic.h>

bool lapic_set_base(uintptr_t base) {
	if (base & 0xfff) return false;

	uint64_t value = (uint64_t)(base | LAPIC_MSR_IA32_APIC_BASE_FLAG_ENABLE);
	wrmsr(LAPIC_MSR_IA32_APIC_BASE, value);
	return true;
}