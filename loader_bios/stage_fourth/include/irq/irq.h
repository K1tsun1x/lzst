#pragma once
#ifndef __IRQ_H
#define __IRQ_H

#include <isr/isr.h>
#include <idt/idt.h>
#include <asm.h>
#include <virt-timer/virt-timer.h>
#include <virt-int-ctrl/virt-int-ctrl.h>

#define NUM_IRQS						256-32

#define PIT_IRQ							0
#define LAPIC_TIMER_VECTOR				0xe0

#define IRQ_PIT							0
#define IRQ_KBD							1
#define IRQ_CASCADE						2
#define IRQ_COM2						3
#define IRQ_COM1						4
#define IRQ_LPT2						5
#define IRQ_FLOPPY						6
#define IRQ_LPT1						7
#define IRQ_CMOS_RTC					8
#define IRQ_PERIPHERALS0				9
#define IRQ_PERIPHERALS1				10
#define IRQ_PERIPHERALS2				11
#define IRQ_PS2_MOUSE					12
#define IRQ_FPU							13
#define IRQ_PRIMARY_ATA					14
#define IRQ_SECONDARY_ATA				15

#define IRQ_INFO_TRIGGER_MODE_EDGE		0
#define IRQ_INFO_TRIGGER_MODE_LEVEL		1

#define IRQ_INFO_POLARITY_ACTIVE_HIGH	0
#define IRQ_INFO_POLARITY_ACTIVE_LOW	1

typedef struct _irq_info_t {
	uint8_t			irq;
	uint8_t			vector;
	/*
		0 - edge
		1 - level
		IRQ_INFO_TRIGGER_MODE_*
	*/
	uint8_t			trigger_mode;
	/*
		0 - active high
		1 - active low
		IRQ_INFO_POLARITY_*
	*/
	uint8_t			polarity;
} irq_info_t;

EXTERN_C void irq_global_handler(isr_data_t* data);
void irq_init(void* idt);

extern isr_t IRQ_HANDLERS[NUM_IRQS];
extern irq_info_t IRQ_INFOS[NUM_IRQS];

#endif