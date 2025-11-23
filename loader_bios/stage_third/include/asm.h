#pragma once
#ifndef __ASM_H
#define __ASM_H

#include "typedefs.h"

#if defined(_MSC_VER) && defined(_M_X64)
#include <immintrin.h>
#include <intrin.h>
#endif

#if defined(__GNUC_CLANG__)
#if defined(__x86_64__)
typedef uint64_t					irq_flags_t;
#elif defined(__i386__)
typedef uint32_t					irq_flags_t;
#else
#error Unsupported architecture
typedef uint64_t					irq_flags_t;
#endif
#elif defined(_MSC_VER)
#if defined(_M_X64)
typedef uint64_t					irq_flags_t;
#elif defined(_M_IX86)
typedef uint32_t					irq_flags_t;
#else
#error Unsupported architecture
typedef uint64_t					irq_flags_t;
#endif
#else
#error Unsupported compiler
typedef uint64_t					irq_flags_t;
#endif

static inline uint8_t inb(uint16_t port) {
	uint8_t res;
#if defined(__GNUC_CLANG__)
	__asm__ __volatile__("inb %1, %0":"=a"(res):"d"(port):"memory");
#elif defined(_MSC_VER)
#if defined(_M_X64)
	res = (uint8_t)__inbyte(port);
#elif defined(_M_IX86)
	__asm {
		mov dx, port
		in al, dx
		mov res, al
	}
#else
#error Unsupported architecture
#endif
#else
#error Unsupported compiler
#endif
	return res;
}

static inline uint16_t inw(uint16_t port) {
	uint16_t res;
#if defined(__GNUC_CLANG__)
	__asm__ __volatile__("inw %1, %0":"=a"(res):"d"(port):"memory");
#elif defined(_MSC_VER)
#if defined(_M_X64)
	res = (uint16_t)__inword(port);
#elif defined(_M_IX86)
	__asm {
		mov dx, port
		in ax, dx
		mov res, ax
	}
#else
#error Unsupported architecture
#endif
#else
#error Unsupported compiler
#endif
	return res;
}

static inline uint32_t inl(uint16_t port) {
	uint32_t res;
#if defined(__GNUC_CLANG__)
	__asm__ __volatile__("inl %1, %0":"=a"(res):"d"(port):"memory");
#elif defined(_MSC_VER)
#if defined(_M_X64)
	res = (uint32_t)__indword(port);
#elif defined(_M_IX86)
	__asm {
		mov dx, port
		in eax, dx
		mov res, eax
	}
#else
#error Unsupported architecture
#endif
#else
#error Unsupported compiler
#endif
	return res;
}

static inline void outb(uint16_t port, uint8_t value) {
#if defined(__GNUC_CLANG__)
	__asm__ __volatile__("outb %0, %1"::"a"(value), "d"(port):"memory");
#elif defined(_MSC_VER)
#if defined(_M_X64)
	__outbyte(port, value);
#elif defined(_M_IX86)
	__asm {
		mov dx, port
		mov al, value
		out dx, al
	}
#else
#error Unsupported architecture
#endif
#else
#error Unsupported compiler
#endif
}

static inline void outw(uint16_t port, uint16_t value) {
#if defined(__GNUC_CLANG__)
	__asm__ __volatile__("outw %0, %1"::"a"(value), "d"(port):"memory");
#elif defined(_MSC_VER)
#if defined(_M_X64)
	__outword(port, value);
#elif defined(_M_IX86)
	__asm {
		mov dx, port
		mov ax, value
		out dx, ax
	}
#else
#error Unsupported architecture
#endif
#else
#error Unsupported compiler
#endif
}

static inline void outl(uint16_t port, uint32_t value) {
#if defined(__GNUC_CLANG__)
	__asm__ __volatile__("outl %0, %1"::"a"(value), "d"(port):"memory");
#elif defined(_MSC_VER)
#if defined(_M_X64)
	__outdword(port, value);
#elif defined(_M_IX86)
	__asm {
		mov dx, port
		mov eax, value
		out dx, eax
	}
#else
#error Unsupported architecture
#endif
#else
#error Unsupported compiler
#endif
}

static inline void io_wait(void) {
	outb(0x80, 0);
}

static inline void cpu_relax(void) {
#if defined(__GNUC_CLANG__)
#if defined(__x86_64__) || defined(__i386__)
	__asm__ __volatile__("pause":::"memory");
#else
	__asm__ __volatile__("":::"memory");
#endif
#elif defined(_MSC_VER)
#if defined(_M_X64)
	_mm_pause();
#elif defined(_M_IX86)
	__asm { pause }
#else
	__asm { nop }
#endif
#endif
}

static inline irq_flags_t irq_disable(void) {
	irq_flags_t flags;
#if defined(__GNUC_CLANG__)
#if defined(__x86_64__)
	__asm__ volatile(
		"pushfq\n\t"
		"cli\n\t"
		"popq %0"
		:"=r"(flags)
		::"memory"
	);
#elif defined(__i386__)
	__asm__ volatile(
		"pushfl\n\t"
		"cli\n\t"
		"popl %0"
		:"=r"(flags)
		::"memory"
	);
#else
#error Unsupported architecture
#endif
#elif defined(_MSC_VER)
#if defined(_M_X64)
	flags = __readeflags();
	__writeeflags(flags & (~0x200));
#elif defined(_M_IX86)
	__asm {
		pushfd
		pop eax
		mov flags, eax
		cli
	}
#else
#error Unsupported architecture
#endif
#else
#error Unsupported compiler
#endif
    return flags;
}

static inline void irq_restore(irq_flags_t flags) {
#if defined(__GNUC_CLANG__)
#if defined(__x86_64__)
	__asm__ volatile(
		"pushq %0\n\t"
		"popfq"
		::"r"(flags)
		:"memory"
	);
#elif defined(__i386__)
	__asm__ volatile(
		"pushl %0\n\t"
		"popfl"
		::"r"(flags)
		:"memory"
	);
#else
#error Unsupported architecture
#endif
#elif defined(_MSC_VER)
#if defined(_M_X64)
	__writeeflags(flags);
#elif defined(_M_IX86)
	__asm {
		mov eax, flags
		push eax
		popfd
	}
#else
#error Unsupported architecture
#endif
#else
#error Unsupported compiler
#endif
}

/**
 * Halt the CPU forever
 */
static inline void panic_halt(void) {
	for (;;) {
#if defined(__GNUC_CLANG__)
#if defined(__x86_64__) || defined(__i386__)
		__asm__ __volatile__("jmp .");
#else
		io_wait();
#endif
#elif defined(_MSC_VER)
#if defined(_M_X64) ||  defined(_M_IX86)
	__asm {
		cli
		hlt
	}
#else
		io_wait();
#endif
#else
		io_wait();
#endif
	}
}

#endif