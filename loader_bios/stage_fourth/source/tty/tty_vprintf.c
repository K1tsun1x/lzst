#include <tty/tty.h>

static const char* __STR_UNSUPPORTED_ATTRIBUTE_TYPE = "[unsupported attribute type]";
static const char* __STR_UNSUPPORTED_ATTRIBUTE = "[unsupported attribute]";
static const char* __STR_MISSING_WIDTH = "[missing width]";
static const char* __STR_UNSUPPORTED_FORMAT_TYPE = "[unsupported format type]";
static const char* __STR_UNSUPPORTED_RADIX = "[unsupported radix]";

int tty_vprintf(
	uint8_t frg_r, uint8_t frg_g, uint8_t frg_b,
	uint8_t bkg_r, uint8_t bkg_g, uint8_t bkg_b,
	bool fill_bkg,
	const char* s, va_list args
) {
	char buffer[(sizeof(uint64_t) << 3) + 2];
	size_t printed_chars = 0;
	gfx_color_t frg_color = GFX_PACK_COLOR(frg_r, frg_g, frg_b);
	gfx_color_t bkg_color = GFX_PACK_COLOR(bkg_r, bkg_g, bkg_b);
	gfx_color_t tmp_frg;
	gfx_color_t tmp_bkg;
	for (; *s; s++) {
		if (*s == '\x1b') {
			++s;
			if (*s != '[') {
				tty_prints(
					__STR_UNSUPPORTED_ATTRIBUTE_TYPE,
					frg_color.r, frg_color.g, frg_color.b,
					bkg_color.r, bkg_color.g, bkg_color.b,
					fill_bkg
				);

				continue;
			}
			
			tmp_frg = frg_color;
			tmp_bkg = bkg_color;
			do {
				++s;
				if (*s == '0') tmp_frg = GFX_COLOR_LIGHT_GRAY;
				else if (*s == '3') {
					++s;
					if (*s == '0') tmp_frg = GFX_COLOR_BLACK;
					else if (*s == '1') tmp_frg = GFX_COLOR_RED;
					else if (*s == '2') tmp_frg = GFX_COLOR_GREEN;
					else if (*s == '3') tmp_frg = GFX_COLOR_BROWN;
					else if (*s == '4') tmp_frg = GFX_COLOR_BLUE;
					else if (*s == '5') tmp_frg = GFX_COLOR_MAGENTA;
					else if (*s == '6') tmp_frg = GFX_COLOR_CYAN;
					else if (*s == '7') tmp_frg = GFX_COLOR_DARK_GRAY;
					else {
						tty_prints(
							__STR_UNSUPPORTED_ATTRIBUTE,
							frg_color.r, frg_color.g, frg_color.b,
							bkg_color.r, bkg_color.g, bkg_color.b,
							fill_bkg
						);

						continue;
					}
				}
				else if (*s == '9') {
					++s;
					if (*s == '0') tmp_frg = GFX_COLOR_LIGHT_GRAY;
					else if (*s == '1') tmp_frg = GFX_COLOR_LIGHT_RED;
					else if (*s == '2') tmp_frg = GFX_COLOR_LIGHT_GREEN;
					else if (*s == '3') tmp_frg = GFX_COLOR_YELLOW;
					else if (*s == '4') tmp_frg = GFX_COLOR_LIGHT_BLUE;
					else if (*s == '5') tmp_frg = GFX_COLOR_LIGHT_MAGENTA;
					else if (*s == '6') tmp_frg = GFX_COLOR_LIGHT_CYAN;
					else if (*s == '7') tmp_frg = GFX_COLOR_WHITE;
					else {
						tty_prints(
							__STR_UNSUPPORTED_ATTRIBUTE,
							frg_color.r, frg_color.g, frg_color.b,
							bkg_color.r, bkg_color.g, bkg_color.b,
							fill_bkg
						);

						continue;
					}
				}
				else if (*s == '4') {
					++s;
					if (*s == '0') tmp_bkg = GFX_COLOR_BLACK;
					else if (*s == '1') tmp_bkg = GFX_COLOR_RED;
					else if (*s == '2') tmp_bkg = GFX_COLOR_GREEN;
					else if (*s == '3') tmp_bkg = GFX_COLOR_BROWN;
					else if (*s == '4') tmp_bkg = GFX_COLOR_BLUE;
					else if (*s == '5') tmp_bkg = GFX_COLOR_MAGENTA;
					else if (*s == '6') tmp_bkg = GFX_COLOR_CYAN;
					else if (*s == '7') tmp_bkg = GFX_COLOR_DARK_GRAY;
					else {
						tty_prints(
							__STR_UNSUPPORTED_ATTRIBUTE,
							frg_color.r, frg_color.g, frg_color.b,
							bkg_color.r, bkg_color.g, bkg_color.b,
							fill_bkg
						);

						continue;
					}
				}
				else if (*s == '1') {
					++s;
					if (*s != '0') {
						tty_prints(
							__STR_UNSUPPORTED_ATTRIBUTE,
							frg_color.r, frg_color.g, frg_color.b,
							bkg_color.r, bkg_color.g, bkg_color.b,
							fill_bkg
						);

						continue;
					}

					++s;
					if (*s == '0') tmp_bkg = GFX_COLOR_DARK_GRAY;
					else if (*s == '1') tmp_bkg = GFX_COLOR_LIGHT_RED;
					else if (*s == '2') tmp_bkg = GFX_COLOR_LIGHT_GREEN;
					else if (*s == '3') tmp_bkg = GFX_COLOR_YELLOW;
					else if (*s == '4') tmp_bkg = GFX_COLOR_LIGHT_BLUE;
					else if (*s == '5') tmp_bkg = GFX_COLOR_LIGHT_MAGENTA;
					else if (*s == '6') tmp_bkg = GFX_COLOR_LIGHT_CYAN;
					else if (*s == '7') tmp_bkg = GFX_COLOR_WHITE;
					else {
						tty_prints(
							__STR_UNSUPPORTED_ATTRIBUTE,
							frg_color.r, frg_color.g, frg_color.b,
							bkg_color.r, bkg_color.g, bkg_color.b,
							fill_bkg
						);

						continue;
					}
				}
				else {
					tty_prints(
						__STR_UNSUPPORTED_ATTRIBUTE,
						frg_color.r, frg_color.g, frg_color.b,
						bkg_color.r, bkg_color.g, bkg_color.b,
						fill_bkg
					);
					
					continue;
				}

				++s;
			} while(*s == ';');

			if (*s != 'm') {
				tty_prints(
					__STR_UNSUPPORTED_ATTRIBUTE_TYPE,
					frg_color.r, frg_color.g, frg_color.b,
					bkg_color.r, bkg_color.g, bkg_color.b,
					fill_bkg
				);

				--s;
			}
			else {
				frg_color = tmp_frg;
				bkg_color = tmp_bkg;
			}

			continue;
		}
		
		if (*s != '%') {
			tty_putchar(
				(int)*s,
				frg_color.r, frg_color.g, frg_color.b,
				bkg_color.r, bkg_color.g, bkg_color.b,
				fill_bkg
			);
			
			++printed_chars;
			continue;
		}

		s++;
		if (*s == '%') {
			tty_putchar(
				(int)'%',
				frg_color.r, frg_color.g, frg_color.b,
				bkg_color.r, bkg_color.g, bkg_color.b,
				fill_bkg
			);

			++printed_chars;
			continue;
		}

		bool flag_hash = false;
		for (; *s == '#'; s++) {
			if (*s == '#') flag_hash = true;
		}

		enum { WIDTH_TYPE_UNKNOWN, WIDTH_TYPE_SPACES, WIDTH_TYPE_ZEROS } width_type = WIDTH_TYPE_UNKNOWN;
		size_t width = 0; 
		if (*s == '0') width_type = WIDTH_TYPE_ZEROS;
		else if (*s == ' ') width_type = WIDTH_TYPE_SPACES;

		if (width_type != WIDTH_TYPE_UNKNOWN) {
			++s;
			if (*s == '*') {
				width = (size_t)va_arg(args, unsigned long);
				++s;
			}
			else if (*s < '0' || *s > '9') tty_prints(
				__STR_MISSING_WIDTH,
				frg_color.r, frg_color.g, frg_color.b,
				bkg_color.r, bkg_color.g, bkg_color.b,
				fill_bkg
			);
			else for (; *s >= '0' && *s <= '9'; ++s) width = width * 10 + (size_t)(*s - '0');
		}

		bool is_char = false;
		bool is_string = false;
		bool is_number = false;
		bool is_unsigned = false;
		size_t radix = 0;
		long signed_number = 0;
		unsigned long unsigned_number = 0;
		if (*s == 'd') {
			is_number = true;
			radix = 10;
			signed_number = va_arg(args, long);
		}
		else if (*s == 'u') {
			is_number = true;
			radix = 10;
			unsigned_number = va_arg(args, unsigned long);
		}
		else if (*s == 'x') {
			is_number = true;
			radix = 16;
			unsigned_number = va_arg(args, unsigned long);
		}
		else if (*s == 'o') {
			is_number = true;
			radix = 8;
			unsigned_number = va_arg(args, unsigned long);
		}
		else if (*s == 'b') {
			is_number = true;
			radix = 2;
			unsigned_number = va_arg(args, unsigned long);
		}
		else if (*s == 's') is_string = true;
		else if (*s == 'c') is_char = true;
		else tty_prints(
			__STR_UNSUPPORTED_FORMAT_TYPE,
			frg_color.r, frg_color.g, frg_color.b,
			bkg_color.r, bkg_color.g, bkg_color.b,
			fill_bkg
		);
		
		size_t tmp_len = 0;
		if (is_number) {
			if (!is_unsigned && signed_number < 0) {
				tty_putchar(
					'-',
					frg_color.r, frg_color.g, frg_color.b,
					bkg_color.r, bkg_color.g, bkg_color.b,
					fill_bkg
				);

				tmp_len += 1;
				is_unsigned = true;
				unsigned_number = (unsigned long)(-(unsigned long)signed_number);
			}

			if (flag_hash) {
				if (radix == 16) {
					tty_prints(
						"0x",
						frg_color.r, frg_color.g, frg_color.b,
						bkg_color.r, bkg_color.g, bkg_color.b,
						fill_bkg
					);

					tmp_len += 2;
				}
				else if (radix == 8) {
					tty_putchar(
						'0',
						frg_color.r, frg_color.g, frg_color.b,
						bkg_color.r, bkg_color.g, bkg_color.b,
						fill_bkg
					);

					tmp_len += 1;
				}
				else if (radix == 2) {
					tty_prints(
						"0b",
						frg_color.r, frg_color.g, frg_color.b,
						bkg_color.r, bkg_color.g, bkg_color.b,
						fill_bkg
					);
					
					tmp_len += 2;
				}
				else if (radix != 10) tty_prints(
					__STR_UNSUPPORTED_RADIX,
					frg_color.r, frg_color.g, frg_color.b,
					bkg_color.r, bkg_color.g, bkg_color.b,
					fill_bkg
				);
			}

			ultoa(unsigned_number, buffer, radix);
			tmp_len += strlen(buffer);
		}
		else if (is_char) {
			buffer[0] = (char)va_arg(args, int);
			tmp_len += 1;
		}
		else if (is_string) {
			char* tmp_str = va_arg(args, char*);
			size_t tmp_str_len = strlen(tmp_str);
			memcpy(buffer, tmp_str, tmp_str_len + 1);
			tmp_len += tmp_str_len;
		}

		if (width_type != WIDTH_TYPE_UNKNOWN) {
			char c = '\0';
			if (width_type == WIDTH_TYPE_SPACES) c = ' ';
			else if (width_type == WIDTH_TYPE_ZEROS) c = '0';

			for (; tmp_len < width; tmp_len++) tty_putchar(
				c,
				frg_color.r, frg_color.g, frg_color.b,
				bkg_color.r, bkg_color.g, bkg_color.b,
				fill_bkg
			);
		}

		if (is_char) tty_putchar(
			buffer[0],
			frg_color.r, frg_color.g, frg_color.b,
			bkg_color.r, bkg_color.g, bkg_color.b,
			fill_bkg
		);
		else tty_prints(
			buffer,
			frg_color.r, frg_color.g, frg_color.b,
			bkg_color.r, bkg_color.g, bkg_color.b,
			fill_bkg
		);

		printed_chars += tmp_len;
	}

	return printed_chars;
}