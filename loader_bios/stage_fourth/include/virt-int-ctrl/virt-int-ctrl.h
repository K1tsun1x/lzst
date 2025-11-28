#pragma once
#ifndef __VIRT_INT_CTRL_H
#define __VIRT_INT_CTRL_H

#include <typedefs.h>

typedef void (*pvirt_int_ctrl_mask_irq)(uint8_t index);
typedef void (*pvirt_int_ctrl_unmask_irq)(uint8_t index);
typedef void (*pvirt_int_ctrl_mask_all_irqs)(void);
typedef void (*pvirt_int_ctrl_unmask_all_irqs)(void);
typedef void (*pvirt_int_ctrl_eoi)(uint8_t index);

extern pvirt_int_ctrl_mask_irq virt_int_ctrl_mask_irq;
extern pvirt_int_ctrl_unmask_irq virt_int_ctrl_unmask_irq;
extern pvirt_int_ctrl_mask_all_irqs virt_int_ctrl_mask_all_irqs;
extern pvirt_int_ctrl_unmask_all_irqs virt_int_ctrl_unmask_all_irqs;
extern pvirt_int_ctrl_eoi virt_int_ctrl_eoi;

#endif