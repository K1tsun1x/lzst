#pragma once
#ifndef __SPINLOCK_H
#define __SPINLOCK_H

#include <stdatomic.h>
#include <asm.h>

#define SPINLOCK_INIT				ATOMIC_FLAG_INIT

typedef atomic_flag	spinlock_t;

static inline void spinlock_acquire(spinlock_t* lock) {
	while(atomic_flag_test_and_set_explicit(lock, memory_order_acquire)) cpu_relax();
}

static inline void spinlock_release(spinlock_t* lock) {
	atomic_flag_clear_explicit(lock, memory_order_release);
}

#endif