#include <boot/boot_info.h>

void boot_info_get_features(boot_info_t* boot_info) {
	if (cpuid486_present()) {
		boot_info->cpuid_present = true;

		uint32_t ecx;
		uint32_t edx;
		cpuid486_get_features(&ecx, &edx);

		boot_info->fpu_present = edx & CPUID486_EDX_FEATURE_FPU;
		if (ecx & CPUID486_ECX_FEATURE_SSE4_2) boot_info->sse_version = 0x42;
		else if (ecx & CPUID486_ECX_FEATURE_SSE4_1) boot_info->sse_version = 0x41;
		else if (ecx & CPUID486_ECX_FEATURE_SSE3) boot_info->sse_version = 0x03;
		else if (edx & CPUID486_EDX_FEATURE_SSE2) boot_info->sse_version = 0x02;
		else if (edx & CPUID486_EDX_FEATURE_SSE) boot_info->sse_version = 0x01;
		boot_info->osxsave_present = ecx & CPUID486_ECX_FEATURE_OSXSAVE;

		if (boot_info->fpu_present) fpu_init(
			boot_info->sse_version != 0,
			boot_info->sse_version != 0,
			boot_info->osxsave_present
		);

		cpuid486_get_features(&ecx, &edx);
		boot_info->osxsave_present = ecx & CPUID486_ECX_FEATURE_OSXSAVE;
		if (boot_info->fpu_present && boot_info->osxsave_present) {
			uint32_t low;
			uint32_t high;
			xgetbv(0, &low, &high);
			low |= 0b111;			// x87 FPU + SSE + AVX
			xsetbv(0, low, high);
		}
		
		cpuid486_get_features(&ecx, &edx);
		if (ecx & CPUID486_ECX_FEATURE_AVX) {
			boot_info->avx_present = true;
			if (boot_info->sse_version < 0x42) boot_info->sse_version = 0x42;
		}

		boot_info->apic_present = edx & CPUID486_EDX_FEATURE_APIC;
		boot_info->msr_present = edx & CPUID486_EDX_FEATURE_MSR;
	}
	else {
		boot_info->cpuid_present = false;

		// FIXME: unknown:

		boot_info->fpu_present = false;
		boot_info->sse_version = 0;
		boot_info->osxsave_present = false;
		boot_info->avx_present = false;
		boot_info->apic_present = false;
		boot_info->msr_present = false;
	}
}