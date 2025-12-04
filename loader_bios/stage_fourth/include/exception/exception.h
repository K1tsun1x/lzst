#pragma once
#ifndef __EXCEPTION_H
#define __EXCEPTION_H

#include <isr/isr.h>
#include <idt/idt.h>
#include <tty/tty.h>
#include <asm.h>

#define NUM_EXCEPTIONS							32

/**
 * Divide Error
 * Error code: -
 */
#define EXCEPTION_DE							0

/**
 * Debug Exception
 * Error code: -
 */
#define EXCEPTION_DB							1

/**
 * NMI
 * Error code: -
 */
#define EXCEPTION_NMI							2

/**
 * Breakpoint
 * Error code: -
 */
#define EXCEPTION_BP							3

/**
 * Overflow
 * Error code: -
 */
#define EXCEPTION_OF							4

/**
 * Bound Range Exceeded
 * Error code: -
 */
#define EXCEPTION_BR							5

/**
 * Undefined Opcode
 * Error code: -
 */
#define EXCEPTION_UD							6

/**
 * No Math Coprocessor
 * Error code: -
 */
#define EXCEPTION_NM							7

/**
 * Double Fault
 * Error code: +
 */
#define EXCEPTION_DF							8

/**
 * Invalid TSS
 * Error code: +
 */
#define EXCEPTION_TS							10

/**
 * Segment Not Present
 * Error code: +
 */
#define EXCEPTION_NP							11

/**
 * Stack-Segment Fault
 * Error code: +
 */
#define EXCEPTION_SS							12

/**
 * General Protection Fault
 * Error code: +
 */
#define EXCEPTION_GP							13

/**
 * Page Fault
 * Error code: +
 */
#define EXCEPTION_PF							14

/**
 * Math Fault
 * Error code: -
 */
#define EXCEPTION_MF							16

/**
 * Alignment Check
 * Error code: +
 */
#define EXCEPTION_AC							17

/**
 * Machine Check
 * Error code: -
 */
#define EXCEPTION_MC							18

/**
 * SIMD Floating-Point Exception
 * Error code: -
 */
#define EXCEPTION_XM							19

/**
 * Virtualization Exception
 * Error code: -
 */
#define EXCEPTION_VE							20

/**
 * Control Protection Exception
 * Error code: +
 */
#define EXCEPTION_CP							21

bool exception_set(size_t index, isr_t isr);
bool exception_get(size_t index, isr_t* isr);
void exceptions_init(void);

EXTERN_C void exception_global_handler(isr_data_t* data);

#endif