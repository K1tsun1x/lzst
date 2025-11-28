#pragma once
#ifndef __IOAPIC_H
#define __IOAPIC_H

#include <lapic/lapic.h>

#define IOAPIC_REG_SEL					0x00
#define IOAPIC_REG_WIN					0x10

uint32_t ioapic_read(uint8_t reg);
void ioapic_write(uint8_t reg, uint32_t value);
void ioapic_remap_irq(uint8_t irq, uint8_t vector, bool level, bool active_low);
void ioapic_mask_irq(uint8_t irq);
void ioapic_unmask_irq(uint8_t irq);
void ioapic_mask_all_irqs(void);
void ioapic_unmask_all_irqs(void);

void ioapic_init(uintptr_t base);

extern uintptr_t IOAPIC_BASE;
extern size_t IOAPIC_NUM_PINS;

#endif