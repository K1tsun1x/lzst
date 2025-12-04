#include <exception/exception.h>

extern isr_t EXCEPTION_HANDLERS[NUM_EXCEPTIONS];

EXTERN_C void exception_global_handler(isr_data_t* data) {
	if (data->int_index >= NUM_EXCEPTIONS) return;

	if (EXCEPTION_HANDLERS[data->int_index]) EXCEPTION_HANDLERS[data->int_index](data);
	else {
		tty_printf(
			"Error: unhandled exception %#04x (error = %#x)!",
			data->int_index,
			data->error_code
		);

		panic_halt();
	}
}