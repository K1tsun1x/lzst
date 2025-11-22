#pragma once
#ifndef __A20_H
#define __A20_H

#include "spinlock.h"

#define A20_PORT_FAST_GATE				0x92

#define A20_FAST_GATE_RESET_CPU			1
#define A20_FAST_GATE_ENABLE			2

EXTERN_C bool LOADERCALL a20_enabled(void);

/**
 * @return Returns true if A20 was changed by this call
 */
bool a20_set_fast_gate_state(bool enabled);

#endif