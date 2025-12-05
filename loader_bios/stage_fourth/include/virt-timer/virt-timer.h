#pragma once
#ifndef __VIRT_TIMER_H
#define __VIRT_TIMER_H

#include <typedefs.h>
#include <isr/isr.h>
#include <virt-int-ctrl/virt-int-ctrl.h>
#include <asm.h>

void virt_timer_set_tick_ms(uint16_t tick_ms);
void virt_timer_wait_irq(void);
void virt_timer_delay(size_t ms);
void virt_timer_irq_handler(isr_data_t* data);

extern __volatile__ size_t VIRT_TIMER_TICKS;

#endif