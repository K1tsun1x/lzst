#pragma once
#ifndef __PIC_H
#define __PIC_H

#include <asm.h>

#define PIC_PORT_MASTER_COMMAND				0x20
#define PIC_PORT_MASTER_DATA				0x21
#define PIC_PORT_SLAVE_COMMAND				0xa0
#define PIC_PORT_SLAVE_DATA					0xa1

#define PIC_COMMAND_ICW1_ICW4			0x01
#define PIC_COMMAND_ICW4_UP_MODE		0x01
#define PIC_COMMAND_ICW1_INIT			0x10

// End Of Interrupt
#define PIC_COMMAND_EOI						0x20

void pic_remap(uint8_t master_base, uint8_t slave_base);
void pic_mask_irq(uint8_t index);
void pic_unmask_irq(uint8_t index);
void pic_mask_all_irqs(void);
void pic_unmask_all_irqs(void);
void pic_send_eoi(uint8_t index);

#endif