#include <irq/irq.h>

extern isr_t IRQ_HANDLERS[NUM_IRQS];

EXTERN_C void irq_stub0(void);
EXTERN_C void irq_stub1(void);
EXTERN_C void irq_stub2(void);
EXTERN_C void irq_stub3(void);
EXTERN_C void irq_stub4(void);
EXTERN_C void irq_stub5(void);
EXTERN_C void irq_stub6(void);
EXTERN_C void irq_stub7(void);
EXTERN_C void irq_stub8(void);
EXTERN_C void irq_stub9(void);
EXTERN_C void irq_stub10(void);
EXTERN_C void irq_stub11(void);
EXTERN_C void irq_stub12(void);
EXTERN_C void irq_stub13(void);
EXTERN_C void irq_stub14(void);
EXTERN_C void irq_stub15(void);
EXTERN_C void irq_stub192(void);

void irq_init(void* table) {
	idt32_t* idt = (idt32_t*)table;
	init_idt32(&idt[32], (uintptr_t)irq_stub0,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[33], (uintptr_t)irq_stub1,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[34], (uintptr_t)irq_stub2,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[35], (uintptr_t)irq_stub3,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[36], (uintptr_t)irq_stub4,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[37], (uintptr_t)irq_stub5,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[38], (uintptr_t)irq_stub6,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[39], (uintptr_t)irq_stub7,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[40], (uintptr_t)irq_stub8,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[41], (uintptr_t)irq_stub9,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[42], (uintptr_t)irq_stub10,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[43], (uintptr_t)irq_stub11,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[44], (uintptr_t)irq_stub12,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[45], (uintptr_t)irq_stub13,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[46], (uintptr_t)irq_stub14,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[47], (uintptr_t)irq_stub15,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	init_idt32(&idt[LAPIC_TIMER_VECTOR],(uintptr_t)irq_stub192,0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);		// LAPIC Timer
}

irq_info_t IRQ_INFOS[NUM_IRQS] = {
	{ 0, 0, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 1, 1, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 2, 2, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 3, 3, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 4, 4, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 5, 5, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 6, 6, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 7, 7, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 8, 8, IRQ_INFO_TRIGGER_MODE_LEVEL,	IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 9, 9, IRQ_INFO_TRIGGER_MODE_EDGE,		IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 10, 10, IRQ_INFO_TRIGGER_MODE_EDGE,	IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 11, 11, IRQ_INFO_TRIGGER_MODE_EDGE,	IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 12, 12, IRQ_INFO_TRIGGER_MODE_EDGE,	IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 13, 13, IRQ_INFO_TRIGGER_MODE_EDGE,	IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 14, 14, IRQ_INFO_TRIGGER_MODE_EDGE,	IRQ_INFO_POLARITY_ACTIVE_HIGH },
	{ 15, 15, IRQ_INFO_TRIGGER_MODE_EDGE,	IRQ_INFO_POLARITY_ACTIVE_HIGH }
};