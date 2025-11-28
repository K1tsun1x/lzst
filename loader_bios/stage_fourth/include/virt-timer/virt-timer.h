#pragma once
#ifndef __VIRT_TIMER_H
#define __VIRT_TIMER_H

#include <typedefs.h>
#include <isr/isr.h>
#include <irq/irq.h>
#include <virt-int-ctrl/virt-int-ctrl.h>

void virt_timer_wait_irq(void);
void virt_timer_sleep(size_t ms);
void virt_timer_irq_handler(isr_data_t* data);

extern size_t VIRT_TIMER_TICKS;

#endif