#	LZST
##	Roadmap
+	[ ] LZST bootloader
	- [x] First stage
		*	[x] Switch to BIOS video mode 3 (80x25 text)
		*	[x] Load the second stage
	- [x] Second stage
		*	[x] Load the third stage
	- [ ] Third stage
		*	[x] Check for VGA presence
		*	[x] Check for VBE presence
		*	[x] Check for i8042 controller presence
		*	[x] Defining logical disk geometry
		*	[x] Loading stage 4 into memory
		*	[ ] ...
		*	[x] Enable the A20 line
			+	[x] Enabling the A20 line via i8042 controller
			+	[x] Enabling the A20 line via fast gate (port 0x92)
		*	[x] Reading memory map via E820
		*	[x] Finding and setting a suitable video mode (VBE or VGA)
		*	[x] Setting up GDT
	- [ ] Fourth stage
		*	[x] Check for CPUID presence
		*	[x] Check for FPU presence
		*	[x] Check for SSE version (not present/1/2)
		*	[x] Initialize FPU and SSE (if present)
		*	[x] Initializing the TTY driver with the appropriate resolution
		*	[ ] ...
+	[ ] LZST kernel
	-	[ ] ...