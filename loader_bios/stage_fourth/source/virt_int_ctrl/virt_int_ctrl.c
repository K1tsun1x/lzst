#include <virt-int-ctrl/virt-int-ctrl.h>

pvirt_int_ctrl_mask_irq virt_int_ctrl_mask_irq = NULL;
pvirt_int_ctrl_unmask_irq virt_int_ctrl_unmask_irq = NULL;
pvirt_int_ctrl_mask_all_irqs virt_int_ctrl_mask_all_irqs = NULL;
pvirt_int_ctrl_unmask_all_irqs virt_int_ctrl_unmask_all_irqs = NULL;
pvirt_int_ctrl_eoi virt_int_ctrl_eoi = NULL;