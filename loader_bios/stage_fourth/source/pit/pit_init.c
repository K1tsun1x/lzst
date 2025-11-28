#include <pit/pit.h>

void pit_init(
	uint8_t operating_mode,
	uint8_t channel,
	uint16_t ms
) {
	uint16_t divisor = pit_calc_divisor(ms);
	outb(PIT_PORT_COMMAND, PIT_COMMAND_BINARY | operating_mode | PIT_COMMAND_ACCESS_BOTH | channel);

	uint16_t port;
	if (channel == PIT_COMMAND_CHNL0) port = PIT_PORT_CHNL0_DATA;
	else if (channel == PIT_COMMAND_CHNL1) port = PIT_PORT_CHNL1_DATA;
	else if (channel == PIT_COMMAND_CHNL2) port = PIT_PORT_CHNL2_DATA;
	else return;
	
	outb(port, (uint8_t)(divisor & 0xff));
	outb(port, (uint8_t)(divisor >> 8));
}