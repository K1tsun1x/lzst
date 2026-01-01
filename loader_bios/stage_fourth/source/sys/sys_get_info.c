#include <sys/sys.h>

extern sys_info_t SYS_INFO;

void sys_get_info(sys_info_t* buffer) {
	if (buffer) *buffer = SYS_INFO;
}