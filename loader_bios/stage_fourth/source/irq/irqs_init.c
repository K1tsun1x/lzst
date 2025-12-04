#include <irq/irq.h>

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

void irqs_init(void) {
	idt32_set_entry(32,					(uint32_t)irq_stub0,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(33,					(uint32_t)irq_stub1,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(34,					(uint32_t)irq_stub2,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(35,					(uint32_t)irq_stub3,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(36,					(uint32_t)irq_stub4,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(37,					(uint32_t)irq_stub5,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(38,					(uint32_t)irq_stub6,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(39,					(uint32_t)irq_stub7,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(40,					(uint32_t)irq_stub8,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(41,					(uint32_t)irq_stub9,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(42,					(uint32_t)irq_stub10,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(43,					(uint32_t)irq_stub11,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(44,					(uint32_t)irq_stub12,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(45,					(uint32_t)irq_stub13,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(46,					(uint32_t)irq_stub14,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(47,					(uint32_t)irq_stub15,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
	idt32_set_entry(LAPIC_TIMER_VECTOR,	(uint32_t)irq_stub192,	0x08, IDT_TYPE_INT32, IDT_FLAG_PRESENT);
}