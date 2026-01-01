#include <sys/sys.h>

XTRN_ONLY_CPP sys_info_t SYS_INFO = { 0 };

void sys_init(
	// e820_reg_t* memory_map,
	// size_t memory_map_length,
	gfx_video_mode_t* video_mode,
	bool vga_present,
	bool vbe_present,
	bool i8042_present
) {
	// SYS_INFO.memory_map = memory_map;
	// SYS_INFO.memory_map_length = memory_map_length;

	if (video_mode) SYS_INFO.video_mode = *video_mode;
	SYS_INFO.vga_present = vga_present;
	SYS_INFO.vbe_present = vbe_present;
	SYS_INFO.i8042_present = i8042_present;

	// CPUID

	SYS_INFO.cpuid_present = cpuid486_present();
	if (SYS_INFO.cpuid_present) {
		uint32_t ecx;
		uint32_t edx;
		cpuid486_get_features(&ecx, &edx);

		SYS_INFO.fpu_present = edx & CPUID486_EDX_FEATURE_FPU;
		if (ecx & CPUID486_ECX_FEATURE_SSE4_2) SYS_INFO.sse_version = 0x42;
		else if (ecx & CPUID486_ECX_FEATURE_SSE4_1) SYS_INFO.sse_version = 0x41;
		else if (ecx & CPUID486_ECX_FEATURE_SSE3) SYS_INFO.sse_version = 0x03;
		else if (edx & CPUID486_EDX_FEATURE_SSE2) SYS_INFO.sse_version = 0x02;
		else if (edx & CPUID486_EDX_FEATURE_SSE) SYS_INFO.sse_version = 0x01;
		SYS_INFO.osxsave_present = ecx & CPUID486_ECX_FEATURE_OSXSAVE;
		SYS_INFO.xsave_present = ecx & CPUID486_ECX_FEATURE_XSAVE;

		if (SYS_INFO.fpu_present) fpu_init(
			SYS_INFO.sse_version != 0,
			SYS_INFO.sse_version != 0,
			SYS_INFO.osxsave_present
		);

		cpuid486_get_features(&ecx, &edx);
		SYS_INFO.osxsave_present = ecx & CPUID486_ECX_FEATURE_OSXSAVE;
		if (SYS_INFO.fpu_present && SYS_INFO.osxsave_present) {
			uint32_t low;
			uint32_t high;
			xgetbv(0, &low, &high);
			low |= 0b111;			// x87 FPU + SSE + AVX
			xsetbv(0, low, high);
		}
		
		cpuid486_get_features(&ecx, &edx);
		if (ecx & CPUID486_ECX_FEATURE_AVX) {
			SYS_INFO.avx_present = true;
			if (SYS_INFO.sse_version < 0x42) SYS_INFO.sse_version = 0x42;
		}

		SYS_INFO.apic_present = edx & CPUID486_EDX_FEATURE_APIC;
		SYS_INFO.msr_present = edx & CPUID486_EDX_FEATURE_MSR;
	}
	else {
		// FIXME: not implemented yet
		memset(&SYS_INFO, 0, sizeof(SYS_INFO));
	}

	// ACPI tables

	// status_t status = sys_parse_acpi(&SYS_INFO);
	// UNREFERENCED_PARAMETER(status);
}