#include <e820.h>

static e820_ard_t __TMP_ARD;

EXTERN_C bool LOADERCALL __e820_get_next_entry(uint32_t ebx, uint16_t di, uint32_t* size, uint32_t* next);

static inline mem_phys_reg_type_t __e820_ard_type_to_mem_phys_reg_type(uint32_t type) {
	switch(type) {
		case E820_ARD_TYPE_MEM:			return MEM_PHYS_REG_TYPE_NORMAL;
		case E820_ARD_TYPE_RESERVED:	return MEM_PHYS_REG_TYPE_RESERVED;
		case E820_ARD_TYPE_ACPI:		return MEM_PHYS_REG_TYPE_ACPI;
		case E820_ARD_TYPE_NVS:			return MEM_PHYS_REG_TYPE_NVS;
		case E820_ARD_TYPE_UNUSABLE:	return MEM_PHYS_REG_TYPE_UNUSABLE;
		case E820_ARD_TYPE_DISABLED:	return MEM_PHYS_REG_TYPE_DISABLED;
		case E820_ARD_TYPE_PERSISTENT:	return MEM_PHYS_REG_TYPE_PERSISTENT;
		case E820_ARD_TYPE_UNACCEPTED:	return MEM_PHYS_REG_TYPE_UNACCEPTED;
		default:						return MEM_PHYS_REG_TYPE_UNKNOWN;
	}
}

bool e820_get_map(mem_phys_reg_t* buffer, size_t max_len, size_t* out_len) {
	uint32_t size = 0, next = 0;
	bool ok = __e820_get_next_entry(0, (uint16_t)(((uintptr_t)&__TMP_ARD) & 0xffff), &size, &next);
	if (!ok) return false;

	size_t clength = 0;
	while (clength < max_len) {
		if (size < 20) __TMP_ARD.type = E820_ARD_TYPE_RESERVED;
		else if (size < 24) __TMP_ARD.ea = 1;
		else if (!(__TMP_ARD.ea & 1)) __TMP_ARD.type = E820_ARD_TYPE_RESERVED;

		buffer[clength].base = __TMP_ARD.base;
		buffer[clength].length = __TMP_ARD.length;
		buffer[clength].type = __e820_ard_type_to_mem_phys_reg_type(__TMP_ARD.type);
		clength += 1;

		if (!next) break;
		ok = __e820_get_next_entry(next, (uint16_t)(((uintptr_t)&__TMP_ARD) & 0xffff), &size, &next);
		if (!ok) break;
	}

	if (out_len) *out_len = clength;
	return true;
}