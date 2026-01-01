#pragma once
#ifndef __MAIN_H
#define __MAIN_H

#include <boot/boot_info.h>
#include <asm.h>
#include <gfx/gfx.h>
#include <tty/tty.h>
#include <sys/sys.h>
#include <pmm/pmm.h>
#include <fpu/fpu.h>
#include <paging/paging.h>
#include <acpi/acpi.h>
#include <gdt/gdt.h>
#include <idt/idt.h>
#include <exception/exception.h>
#include <irq/irq.h>
#include <pic/pic.h>
#include <virt-int-ctrl/virt-int-ctrl.h>
#include <msr/msr.h>
#include <acpi/acpi_madt_ioapic.h>
#include <acpi/acpi_madt_lapic.h>
#include <lapic/lapic.h>
#include <ioapic/ioapic.h>
#include <dynarr/dynarr.h>

#define TIMER_TICK_MS				1

extern void task1(void);
extern void task2(void);

extern uint32_t __PTR_BASE__[];
extern uint32_t __PTR_END__[];

extern gfx_video_mode_t GFX_VIDEO_MODE;

extern gdt32_t ALIGNED(16) GDT[3];
extern gdtr32_t ALIGNED(16) GDTR;

extern paging_pde_t ALIGNED(0x1000) PDE[PAGING_NUM_DIRECTORY_ENTRIES];

#endif