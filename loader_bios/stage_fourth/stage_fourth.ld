ENTRY(stage_fourth_startup)
OUTPUT_ARCH(i386)
OUTPUT_FORMAT(binary)
SECTIONS {
	__PTR_BASE__ = 0x00010000;
	. = __PTR_BASE__;

	.Header : {
		LONG(0x5a4c444c);
		LONG(__PTR_BASE__);
		LONG(0);					/* the fourth stage length in sectors (will be set via shell) */
		LONG(stage_fourth_startup);
		LONG(800);					/* preferred video mode width */
		LONG(600);					/* preferred video mode height */
		LONG(32);					/* preferred video mode depth */
	}

	. = ALIGN(8);

	.text : {
		*(.text)
	}

	. = ALIGN(8);

	.data : {
		*(.data)
	}

	. = ALIGN(8);

	.bss : {
		*(.bss)
	}

	. = ALIGN(8);

	.rodata : {
		*(.rodata)
	}

	__PTR_END__ = .;
}