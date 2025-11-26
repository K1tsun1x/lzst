#pragma once
#ifndef __ISR_H
#define __ISR_H

#include "isr_data.h"

typedef void (*isr_t)(isr_data_t* data);

#endif