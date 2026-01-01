#include <lapic/lapic.h>

uint64_t lapic_get_base(void) {
	uint64_t msr = rdmsr(LAPIC_MSR_IA32_APIC_BASE);
	return msr & 0xffffff000ULL;
}