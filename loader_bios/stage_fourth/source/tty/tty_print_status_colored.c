#include <tty/tty.h>

static const struct {
	status_t		status;
	const char*		repr;
} STATUS_REPRESENTATIONS[] = {
	{ STATUS_UNREACHABLE, "unreachable" },
	{ STATUS_INVALID_PARAMETER_14 , "invalid parameter (14)" },
	{ STATUS_INVALID_PARAMETER_13 , "invalid parameter (13)" },
	{ STATUS_INVALID_PARAMETER_12 , "invalid parameter (12)" },
	{ STATUS_INVALID_PARAMETER_11 , "invalid parameter (11)" },
	{ STATUS_INVALID_PARAMETER_10 , "invalid parameter (10)" },
	{ STATUS_INVALID_PARAMETER_9 , "invalid parameter (9)" },
	{ STATUS_INVALID_PARAMETER_8 , "invalid parameter (8)" },
	{ STATUS_INVALID_PARAMETER_7 , "invalid parameter (7)" },
	{ STATUS_INVALID_PARAMETER_6 , "invalid parameter (6)" },
	{ STATUS_INVALID_PARAMETER_5 , "invalid parameter (5)" },
	{ STATUS_INVALID_PARAMETER_4 , "invalid parameter (4)" },
	{ STATUS_INVALID_PARAMETER_3 , "invalid parameter (3)" },
	{ STATUS_INVALID_PARAMETER_2 , "invalid parameter (2)" },
	{ STATUS_INVALID_PARAMETER_1 , "invalid parameter (1)" },
	{ STATUS_INVALID_PARAMETER, "invalid parameter" },
	{ STATUS_INVALID_HEADER, "invalid header" },
	{ STATUS_NOT_FOUND, "not found" },
	{ STATUS_NO_MEMORY, "no memory" },
	{ STATUS_OK, "ok" }
};

int tty_print_status_colored(
	status_t status,
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b
) {
	const size_t len = sizeof(STATUS_REPRESENTATIONS) / sizeof(STATUS_REPRESENTATIONS[0]);
	size_t index = SIZE_MAX;
	for (size_t i = 0; i < len; i++) {
		if (STATUS_REPRESENTATIONS[i].status == status) {
			index = i;
			break;
		}
	}

	if (index == SIZE_MAX) return 0;

	return tty_prints_color(
		STATUS_REPRESENTATIONS[index].repr,
		frg_r, frg_g, frg_b,
		bkg_r, bkg_g, bkg_b
	);
}