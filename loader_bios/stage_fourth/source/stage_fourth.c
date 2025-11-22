#include <bootloader_info.h>
#include <gfx.h>
#include <tty.h>
#include <cpuid486.h>
#include <fpu.h>

static bootloader_info_t BOOTLOADER_INFO;

void stage_fourth_startup(bootloader_info_t* bootloader_info) {
	BOOTLOADER_INFO = *bootloader_info;
	gfx_init(&BOOTLOADER_INFO.video_mode);

	bool cpuid_prsnt = cpuid486_present();
	bool fpu_prsnt = false;
	size_t sse_version = 0;
	if (cpuid_prsnt) {
		BOOTLOADER_INFO.cpuid_present = true;

		uint32_t features = cpuid486_get_features();
		fpu_prsnt = (features & CPUID486_FEATURE_FPU) != 0;
		if (features & CPUID486_FEATURE_SSE2) sse_version = 2;
		else if (features & CPUID486_FEATURE_SSE) sse_version = 1;
	}
	else {
		BOOTLOADER_INFO.cpuid_present = false;

		// not implemented yet...
	}

	BOOTLOADER_INFO.sse_version = sse_version;
	BOOTLOADER_INFO.fpu_present = fpu_prsnt;
	if (fpu_prsnt) {
		fpu_init(sse_version != 0, sse_version != 0, sse_version != 0);
		const size_t w = BOOTLOADER_INFO.video_mode.width;
		const size_t h = BOOTLOADER_INFO.video_mode.height;
		const float aspect = (float)w / (float)h;

		size_t num_chars_per_line = w / 16;
		size_t num_lines = h / 16;

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
	
	tty_putchar(U'Б', 0xff, 0xff, 0);
	tty_print_ustring(U"БВbbAA33  - ?\n", 0xff, 0x7f, 0x00);
	tty_print_string("bob!\nVVV", 0xff, 0xff, 0);
	__asm__ __volatile__("jmp ."::"a"(BOOTLOADER_INFO.video_mode.framebuffer));
}