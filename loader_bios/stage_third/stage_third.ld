ENTRY(stage_third_startup)
OUTPUT_ARCH(i386)
OUTPUT_FORMAT(binary)
SECTIONS {
	__PTR_BASE__ = 0x1200;
	. = __PTR_BASE__;

	.Header : {
		LONG(0x444c5a4c);
		LONG(0);					/* the third stage length in sectors (will be set via shell) */
		LONG(stage_third_startup);
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
		. = . + 0;
	}

	. = ALIGN(512);

	__PTR_END__ = .;
}