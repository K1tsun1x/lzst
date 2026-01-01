#include <sys/sys.h>

extern sys_info_t SYS_INFO;

void sys_set_info(const sys_info_t* buffer) {
	SYS_INFO = *buffer;
}