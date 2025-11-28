#include <lapic/lapic.h>

uintptr_t lapic_get_base(void) {
	uint64_t msr = rdmsr(LAPIC_MSR_IA32_APIC_BASE);
	return (uintptr_t)(msr & 0xffffff000ULL);
}