#include <virt-timer/virt-timer.h>

volatile uint16_t VIRT_TIMER_TICK_MS = 1;
volatile size_t VIRT_TIMER_TICKS = 0;
volatile bool __VIRT_TIMER_TICK = false;