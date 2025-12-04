#include <virt-timer/virt-timer.h>

__volatile__ uint16_t VIRT_TIMER_TICK_MS = 1;
__volatile__ size_t VIRT_TIMER_TICKS = 0;
__volatile__ bool __VIRT_TIMER_TICK = false;