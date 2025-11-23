#include <bootloader_info.h>
#include <gfx.h>
#include <tty.h>
#include <cpuid486.h>
#include <fpu.h>
#include <asm.h>

static bootloader_info_t BOOTLOADER_INFO;

void stage_fourth_startup(bootloader_info_t* bootloader_info) {
	BOOTLOADER_INFO = *bootloader_info;
	gfx_init(&BOOTLOADER_INFO.video_mode);

	bool cpuid_prsnt = cpuid486_present();
	bool fpu_prsnt = false;
	bool avx_prsnt = false;
	size_t sse_version = 0;
	if (cpuid_prsnt) {
		BOOTLOADER_INFO.cpuid_present = true;

		uint32_t ecx;
		uint32_t edx;
		cpuid486_get_features(&ecx, &edx);
		
		fpu_prsnt = (edx & CPUID486_EDX_FEATURE_FPU) != 0;
		if (ecx & CPUID486_ECX_FEATURE_SSE4_2) sse_version = 0x42;
		else if (ecx & CPUID486_ECX_FEATURE_SSE4_1) sse_version = 0x41;
		else if (ecx & CPUID486_ECX_FEATURE_SSE3) sse_version = 0x03;
		else if (edx & CPUID486_EDX_FEATURE_SSE2) sse_version = 0x02;
		else if (edx & CPUID486_EDX_FEATURE_SSE) sse_version = 0x01;

		if (fpu_prsnt) fpu_init(sse_version != 0, sse_version != 0, ecx & CPUID486_ECX_FEATURE_OSXSAVE);

		cpuid486_get_features(&ecx, &edx);
		if (fpu_prsnt && (ecx & CPUID486_ECX_FEATURE_OSXSAVE)) {
			uint32_t low;
			uint32_t high;
			xgetbv(0, &low, &high);
			low |= 0b111;			// x87 FPU + SSE + AVX
			xsetbv(0, low, high);
		}
		
		cpuid486_get_features(&ecx, &edx);
		if (ecx & CPUID486_ECX_FEATURE_AVX) {
			avx_prsnt = true;
			if (sse_version < 0x42) sse_version = 0x42;
		}
	}
	else {
		BOOTLOADER_INFO.cpuid_present = false;
		// FIXME: not implemented yet...
	}

	BOOTLOADER_INFO.fpu_present = fpu_prsnt;
	BOOTLOADER_INFO.sse_version = sse_version;
	BOOTLOADER_INFO.avx_present = avx_prsnt;
	if (fpu_prsnt) {
		const size_t w = BOOTLOADER_INFO.video_mode.width;
		const size_t h = BOOTLOADER_INFO.video_mode.height;
		const float aspect = (float)w / (float)h;

		size_t num_chars_per_line = w / 14;
		size_t num_lines = h / 14;

		if (aspect > 1.6f && num_chars_per_line < 100) num_chars_per_line = 100;
		if (aspect < 1.3f && num_chars_per_line > 80) num_chars_per_line = 80;

		// very small screen
		if (w < 640 || h < 480) {
			if (num_chars_per_line > 40) num_chars_per_line = 40;
			if (num_lines > 20) num_lines = 20;
		}

		tty_init(num_chars_per_line, num_lines, 2, 2, 0x10, 0x10, 0x10);
	}
	else tty_init(80, 25, 2, 2, 0x10, 0x10, 0x10);

	const color_t tty_frg_color = COLOR_LIGHT_GRAY;

	tty_puts("Welcome to LZST bootloader!", 0xff, 0x7f, 0);

	tty_printf("Boot drive:\t\t\t\x1b[96m%#x\x1b[0m\n", BOOTLOADER_INFO.boot_drive);

	tty_print_string("VGA:\t\t\t\t", tty_frg_color.r, tty_frg_color.g, tty_frg_color.b);
	if (BOOTLOADER_INFO.vga_present) tty_printf("\x1b[92m[PRESENT]\x1b[0m");
	else tty_printf("\x1b[91m[NOT PRESENT]\x1b[0m");
	
	tty_print_string("\nVBE:\t\t\t\t", tty_frg_color.r, tty_frg_color.g, tty_frg_color.b);
	if (BOOTLOADER_INFO.vbe_present) tty_printf("\x1b[92m[PRESENT]\x1b[0m");
	else tty_printf("\x1b[91m[NOT PRESENT]\x1b[0m");
	
	tty_print_string("\ni8042 controller:\t", tty_frg_color.r, tty_frg_color.g, tty_frg_color.b);
	if (BOOTLOADER_INFO.i8042_present) tty_printf("\x1b[92m[PRESENT]\x1b[0m");
	else tty_printf("\x1b[91m[NOT PRESENT]\x1b[0m");
	
	tty_print_string("\nCPUID:\t\t\t\t", tty_frg_color.r, tty_frg_color.g, tty_frg_color.b);
	if (BOOTLOADER_INFO.cpuid_present) tty_printf("\x1b[92m[PRESENT]\x1b[0m");
	else tty_printf("\x1b[91m[NOT PRESENT]\x1b[0m");
	
	tty_print_string("\nFPU:\t\t\t\t", tty_frg_color.r, tty_frg_color.g, tty_frg_color.b);
	if (BOOTLOADER_INFO.fpu_present) tty_printf("\x1b[92m[PRESENT]\x1b[0m");
	else tty_printf("\x1b[91m[NOT PRESENT]\x1b[0m");
	
	tty_print_string("\nSSE version:\t\t", tty_frg_color.r, tty_frg_color.g, tty_frg_color.b);
	if (!BOOTLOADER_INFO.sse_version) tty_printf("\x1b[91m[NONE]\x1b[0m");
	else {
		if (BOOTLOADER_INFO.sse_version < 0x10) tty_printf("\x1b[92m%u\x1b[0m", BOOTLOADER_INFO.sse_version);
		else {
			if (BOOTLOADER_INFO.sse_version == 0x41) tty_printf("\x1b[92m4.1\x1b[0m");
			else if (BOOTLOADER_INFO.sse_version == 0x42) tty_printf("\x1b[92m4.2\x1b[0m");
			else tty_printf("\x1b[92m4.2+\x1b[0m");
		}
	}
	
	tty_print_string("\nAVX:\t\t\t\t", tty_frg_color.r, tty_frg_color.g, tty_frg_color.b);
	if (BOOTLOADER_INFO.avx_present) tty_printf("\x1b[92m[PRESENT]\x1b[0m");
	else tty_printf("\x1b[91m[NOT PRESENT]\x1b[0m");
	
	tty_printf(
		"\nVideo:\t\t\t\tmode=\x1b[96m%xh\x1b[0m (\x1b[96m%u\x1b[0mx\x1b[96m%u\x1b[0m \x1b[94m%ubpp\x1b[0m)\n",
		BOOTLOADER_INFO.video_mode.number,
		BOOTLOADER_INFO.video_mode.width,
		BOOTLOADER_INFO.video_mode.height,
		BOOTLOADER_INFO.video_mode.depth
	);

	tty_puts("Memory map:", tty_frg_color.r, tty_frg_color.g, tty_frg_color.b);
	for (size_t i = 0; i < BOOTLOADER_INFO.memory_map_length; i++) {
		tty_printf(
			"%u)\tBase=\x1b[96m%#010x%08x\x1b[0m, Length=\x1b[96m%#010x%08x\x1b[0m, Type=\x1b[94m%u\x1b[0m\n",
			i + 1,
			BOOTLOADER_INFO.memory_map[i].base_high,
			BOOTLOADER_INFO.memory_map[i].base_low,
			BOOTLOADER_INFO.memory_map[i].length_high,
			BOOTLOADER_INFO.memory_map[i].length_low,
			BOOTLOADER_INFO.memory_map[i].type
		);
	}
	
	__asm__ __volatile__("jmp ."::"a"(BOOTLOADER_INFO.video_mode.framebuffer));
}