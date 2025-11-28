#include <ioapic/ioapic.h>

void ioapic_remap_irq(uint8_t irq, uint8_t vector, bool level, bool active_low) {
	uint32_t low_index = 0x10 + (irq << 1);
	uint32_t high_index = low_index + 1;
	uint32_t lapic_id = lapic_read(LAPIC_REG_ID) >> 24;

	uint32_t low = 0;
    low |= vector;
    low |= (0 << 8);					// delivery mode = fixed
    low |= (0 << 11);					// dest mode = physical
    low |= ((active_low != false) << 13);	// polarity
    low |= ((level != false) << 15);	// trigger mode
    low |= (0 << 16);					// mask = 0 = enabled

    ioapic_write(low_index, low);

	uint32_t high = ioapic_read(high_index);
	high &= 0xffffff;
	high |= lapic_id << 24;
    ioapic_write(high_index, high);
}