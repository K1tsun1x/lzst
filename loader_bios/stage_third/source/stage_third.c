#include <min_stdio.h>
#include <boot_info.h>
#include <vga.h>
#include <a20.h>
#include <i8042.h>
#include <e820.h>
#include <vbe.h>
#include <drive.h>
#include <gdt.h>
#include <gdt_descriptor.h>

extern uintptr_t __PTR_BASE__[];
extern uintptr_t __PTR_END__[];

static vbe_info_t VBE_INFO;
static boot_info_t BOOT_INFO = {
	.vga_present = false,
	.vbe_present = false,
	.i8042_present = false,
	
	.video_mode = {
		.number = 0x03,
		.type = VIDEO_MODE_TYPE_TEXT,
		.indexed = true,
		.width = 80,
		.height = 25,
		.depth = 8,
		.pitch = 160,
		.bits_red = 0,
		.shift_red = 0,
		.bits_green = 0,
		.shift_green = 0,
		.bits_blue = 0,
		.shift_blue = 0,
		.bits_reserved = 0,
		.shift_reserved = 0,
		.framebuffer = 0xb8000
	}
};

static uint8_t FOURTH_STAGE_HEADER_BUFFER[DRIVE_SECTOR_SIZE];

static gdt32_t ALIGNED(16) GDT_FOURTH_STAGE[] = {
	GDT32_STATIC(0, 0, 0, 0),
	GDT32_STATIC(
		0xfffff,
		0,
		GDT_ACCESS_READABLE_WRITEABLE | GDT_ACCESS_EXECUTABLE | GDT_ACCESS_NOT_SYSTEM | GDT_ACCESS_PRESENT,
		GDT_FLAG_SIZE | GDT_FLAG_GRANULARITY
	),
	GDT32_STATIC(
		0xfffff,
		0,
		GDT_ACCESS_READABLE_WRITEABLE | GDT_ACCESS_NOT_SYSTEM | GDT_ACCESS_PRESENT,
		GDT_FLAG_SIZE | GDT_FLAG_GRANULARITY
	)
};

static gdt_descriptor32_t ALIGNED(16) GDT_DESCRIPTOR_FOURTH_STAGE = GDT_DESCRIPTOR_STATIC(
	sizeof(GDT_FOURTH_STAGE),
	GDT_FOURTH_STAGE
);

EXTERN_C void stage_third_startup(uint8_t drive) {
	const uintptr_t base = (uintptr_t)&__PTR_BASE__;
	const uintptr_t end = (uintptr_t)&__PTR_END__;
	const size_t size = end - base;
	const uint32_t lba_my_start = 2;
	const uint32_t my_length = size / DRIVE_SECTOR_SIZE;

	min_stdio_init();
	if (vga_present()) {
		BOOT_INFO.vga_present = true;
		vga_set_cursor_state(false);
	}
	else BOOT_INFO.vga_present = false;
	
	if (vbe_get_info(&VBE_INFO)) BOOT_INFO.vbe_present = true;
	else {
		*((uint16_t*)((uintptr_t)VBE_INFO.video_mode_ptr[0])) = 0xffff;
		BOOT_INFO.vbe_present = false;
	}

	if (i8042_present()) BOOT_INFO.i8042_present = true;
	else BOOT_INFO.i8042_present = false;
	
	printf(
		"LSZT bootloader 3rd stage:\nBase=%#x, Size=%#x, End=%#x, LBA=%xh\n",
		base,
		size,
		end,
		lba_my_start
	);

	// memcpy16_32(0, 0x200000, 0x500);

	printf("Boot drive:\t\t\t\t\t\x1b[96m%#04x\x1b[0m", drive);

	BOOT_INFO.boot_drive = drive;

	const uint32_t lba_fourth_stage_start = lba_my_start + my_length;
	const uint32_t header_off_fourth_stage = ((uintptr_t)FOURTH_STAGE_HEADER_BUFFER) & 0x0f;
	const uint32_t header_seg_fourth_stage = ((uintptr_t)FOURTH_STAGE_HEADER_BUFFER) >> 4;
	if (!drive_read_sectors_low(
		drive,
		header_off_fourth_stage,
		header_seg_fourth_stage,
		(uint64_t)lba_fourth_stage_start,
		1
	)) {
		printf("\n\x1b[91;107mError: failed to read the fourth stage header\x1b[0m\n");
		panic_halt();
	}

	const uint32_t* fourth_stage_header = (uint32_t*)(uintptr_t)FOURTH_STAGE_HEADER_BUFFER;
	if (fourth_stage_header[0] != 0x5a4c444c) {
		printf("\n\x1b[91;107mError: invalid fourth stage header signature\x1b[0m\n");
		panic_halt();
	}
	else if (fourth_stage_header[1] > 0xfffff) {
		printf("\n\x1b[91;107mError: invalid fourth stage base address\x1b[0m\n");
		panic_halt();
	}
	
	const uint32_t base_fourth_stage = fourth_stage_header[1];
	const uint32_t len_fourth_stage = fourth_stage_header[2];
	const uint32_t entry_point_fourth_stage = fourth_stage_header[3];
	const uint32_t size_fourth_stage = len_fourth_stage * DRIVE_SECTOR_SIZE;
	const uint32_t end_fourth_stage = base_fourth_stage + size_fourth_stage;
	
	printf(
		"\nLSZT bootloader 4th stage:\nBase=%#010x, Size=%#x, End=%#x, LBA=%#010x\n",
		base_fourth_stage,
		size_fourth_stage,
		end_fourth_stage,
		lba_fourth_stage_start
	);

	if (!drive_read_sectors_low(
		drive,
		(uint16_t)(base_fourth_stage & 0x0f),
		(uint16_t)(base_fourth_stage >> 4),
		(uint64_t)lba_fourth_stage_start,
		len_fourth_stage
	)) {
		printf("\n\x1b[91;107mError: failed to read the fourth stage\x1b[0m\n");
		panic_halt();
	}

	printf("VGA:\t\t\t\t\t\t");
	if (BOOT_INFO.vga_present) printf("\x1b[92m%s\x1b[0m\n", "[PRESENT]");
	else printf("\x1b[93m%s\x1b[0m\n", "[NOT PRESENT]");
	
	printf("VBE(VESA):\t\t\t\t\t");
	if (BOOT_INFO.vbe_present) printf("\x1b[92m%s\x1b[0m\n", "[PRESENT]");
	else printf("\x1b[93m%s\x1b[0m\n", "[NOT PRESENT]");

	printf("i8042 controller:\t\t\t");
	if (BOOT_INFO.i8042_present) printf("\x1b[92m%s\x1b[0m\n", "[PRESENT]");
	else printf("\x1b[93m%s\x1b[0m\n", "[NOT PRESENT]");

	printf("A20 line:\t\t\t\t\t");
	bool a20_state = a20_enabled();
	if (a20_state) {
		printf("\x1b[92m%s\x1b[0m\n", "[ENABLED]");
	}
	else {
		printf("\x1b[93m%s\x1b[0m\n", "[DISABLED]");

		if (BOOT_INFO.i8042_present) {
			printf("A20 enable via i8042 controller:\t\t");
			i8042_set_a20_state(true);

			a20_state = a20_enabled();
			if (a20_state) {
				printf("\x1b[92m%s\x1b[0m\n", "[SUCCESS]");
			}
			else {
				printf("\x1b[93m%s\x1b[0m\n", "[FAILED]");
			}
		}

		if (!a20_state) {
			printf("A20 enable via fast gate:\t");
			a20_set_fast_gate_state(true);

			a20_state = a20_enabled();
			if (a20_state) {
				printf("\x1b[92m%s\x1b[0m\n", "[SUCCESS]");
			}
			else {
				printf("\x1b[93m%s\x1b[0m\n", "[FAILED]");
			}
		}
		
		if (!a20_state) {
			printf("\x1b[91;107mError: failed to enable A20 line\x1b[0m\n");
			panic_halt();
		}
	}

	BOOT_INFO.memory_map = (boot_mem_reg_t*)(end + 0x1000);

	printf("Memory map:\t\t\t\t\t");
	if (!e820_get_map(BOOT_INFO.memory_map, 100, &BOOT_INFO.memory_map_length)) {
		printf("\x1b[93m%s\x1b[0m\n", "[UNAVAILABLE]");
		printf("\x1b[91;107mError: failed to retrieve memory map\x1b[0m\n");
		panic_halt();
	}
	
	printf("\x1b[92m%s\x1b[0m\n", "[AVAILABLE]");
	for (size_t i = 0; i < BOOT_INFO.memory_map_length; i++) {
		printf(
			"% 2u) Base: \x1b[96m%#010x%08x\x1b[0m, Length: \x1b[96m%#010x%08x\x1b[0m",
			i + 1,
			BOOT_INFO.memory_map[i].base_high,
			BOOT_INFO.memory_map[i].base_low,
			BOOT_INFO.memory_map[i].length_high,
			BOOT_INFO.memory_map[i].length_low
		);

		printf(", Type: \x1b[94m%#04x\x1b[0m\n",BOOT_INFO.memory_map[i].type);
	}

	if (BOOT_INFO.vbe_present) {
		const size_t preferred_width = fourth_stage_header[4];
		const size_t preferred_height = fourth_stage_header[5];
		const size_t preferred_depth = fourth_stage_header[6];
		vbe_find_best_video_mode(
			&VBE_INFO,
			preferred_width,
			preferred_height,
			preferred_depth,
			&BOOT_INFO.video_mode
		);
	}

	printf(
		"Video mode:\t\t\t\t\t\x1b[94m%u\x1b[0mx\x1b[94m%u\x1b[0mx\x1b[94m%u\x1b[0m (\x1b[96m#%xh\x1b[0m)\n",
		BOOT_INFO.video_mode.width,
		BOOT_INFO.video_mode.height,
		BOOT_INFO.video_mode.depth,
		BOOT_INFO.video_mode.number
	);

	// puts("GDT:\n");
	// for (size_t i = 0; i < sizeof(GDT_FOURTH_STAGE); i++) printf("%02x ", ((uint8_t*)&GDT_FOURTH_STAGE)[i]);
	// puts("");
	// panic_halt();

	bool video_mode_set;
	if (BOOT_INFO.vbe_present) {
		BOOT_INFO.video_mode.indexed = false;
		video_mode_set = vbe_set_video_mode(0x4000 | BOOT_INFO.video_mode.number);
	}
	else {
		if (BOOT_INFO.video_mode.number == 0x13) BOOT_INFO.video_mode.indexed = true;
		video_mode_set = vga_set_video_mode((uint8_t)BOOT_INFO.video_mode.number);
	}

	if (!video_mode_set) {
		printf("\x1b[91;107mError: failed to set video mode #%xh\x1b[0m\n", BOOT_INFO.video_mode.number);
		panic_halt();
	}

	gdt_load(&GDT_DESCRIPTOR_FOURTH_STAGE, entry_point_fourth_stage, base_fourth_stage, (uintptr_t)&BOOT_INFO);
	
	panic_halt();
}