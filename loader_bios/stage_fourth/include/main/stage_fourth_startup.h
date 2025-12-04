#pragma once
#ifndef __STAGE_FOURTH_STARTUP_H
#define __STAGE_FOURTH_STARTUP_H

#include <boot/boot_info.h>
#include <asm.h>
#include <cpuid486/cpuid486.h>
#include <gfx/gfx.h>
#include <tty/tty.h>
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

extern uint32_t __PTR_BASE__[];
extern uint32_t __PTR_END__[];

extern boot_info_t BOOT_INFO;
extern gfx_video_mode_t GFX_VIDEO_MODE;

extern gdt32_t ALIGNED(16) GDT[3];
extern gdtr32_t ALIGNED(16) GDTR;

extern paging_pde_t ALIGNED(0x1000) PDE[PAGING_NUM_DIRECTORY_ENTRIES];

#endif