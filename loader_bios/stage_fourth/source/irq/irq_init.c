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
}