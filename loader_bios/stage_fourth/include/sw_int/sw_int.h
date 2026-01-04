#pragma once
#ifndef __SW_INT_H
#define __SW_INT_H

#include <idt/idt.h>
#include "sw_int_data.h"

#include "sw_int_scheduler_yield.h"
#include "sw_int_tty.h"

#define NUM_SW_INTS				2

typedef void (*sw_int_handler_t)(bool ring_switch, sw_int_data_t* data);

void sw_int_init(void);

bool sw_int_set(size_t sw_int, sw_int_handler_t handler);
bool sw_int_get(size_t sw_int, sw_int_handler_t* handler);

#endif