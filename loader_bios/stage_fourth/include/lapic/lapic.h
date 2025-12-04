#pragma once
#ifndef __LAPIC_H
#define __LAPIC_H

#include <asm.h>
#include <typedefs.h>
#include <pit/pit.h>

#define LAPIC_MSR_IA32_APIC_BASE				0x1b

#define LAPIC_MSR_IA32_APIC_BASE_FLAG_ENABLE	(1 << 11)

// ID Register (RW)
#define LAPIC_REG_ID							0x20
// Version Register (R)
#define LAPIC_REG_VERSION						0x30
// Task Priority Register (RW)
#define LAPIC_REG_TPR							0x80
// Arbitration Priority Register (R)
#define LAPIC_REG_APR							0x90
// Processor Priority Register (R)
#define LAPIC_REG_PPR							0xa0
// End Of Interrupt Register (W)
#define LAPIC_REG_EOI							0xb0
// Remote Read Register (R)
#define LAPIC_REG_RRD							0xc0
// Logical Destination Register (RW)
#define LAPIC_REG_LDR							0xd0
// Destination Format Register (RW)
#define LAPIC_REG_DFR							0xe0
// Spurious Interrupt Vector Register (RW)
#define LAPIC_REG_SVR							0xf0
// Error Status Register (R)
#define LAPIC_REG_ESR							0x280
// LVT Corrected Machine Check Interrupt Register (RW)
#define LAPIC_REG_LVT_CMCI						0x2f0
// Interrupt Command Register 0 (RW)
#define LAPIC_REG_ICR0							0x300
// Interrupt Command Register 1 (RW)
#define LAPIC_REG_ICR1							0x310
// LVT Timer Register (RW)
#define LAPIC_REG_LVT_TIMER						0x320
// LVT Thermal Sensor Register (RW)
#define LAPIC_REG_LVT_THERMAL_SENSOR			0x330
// LVT Performance Monitoring Counters Register (RW)
#define LAPIC_REG_LVT_PMC						0x340
// LVT LINT0 Register (RW)
#define LAPIC_REG_LVT_LINT0						0x350
// LVT LINT1 Register (RW)
#define LAPIC_REG_LVT_LINT1						0x360
// LVT Error Register (RW)
#define LAPIC_REG_LVT_ERROR						0x370
// Initial Count Register for timer (RW)
#define LAPIC_REG_INITIAL_COUNT					0x380
// Current Count Register for timer (R)
#define LAPIC_REG_CCR							0x390
// Divide Configuration Register for timer (RW)
#define LAPIC_REG_DCR							0x3e0

uintptr_t lapic_get_base(void);
bool lapic_set_base(uintptr_t base);
uint32_t lapic_read(uint32_t index);
void lapic_write(uint32_t index, uint32_t value);
void lapic_eoi(uint8_t index);
uint32_t lapic_timer_calibrate(void);

void lapic_init(void);
uint32_t lapic_timer_init(uint8_t vector, uint16_t tick_ms);

static inline void lapic_enable_svr(uint8_t index) {
	lapic_write(LAPIC_REG_SVR, index | 0x100);
}

static inline void lapic_set_tpr(uint8_t value) {
	lapic_write(LAPIC_REG_TPR, value);
}

extern uint32_t LAPIC_TICKS_PER_MS;

#endif