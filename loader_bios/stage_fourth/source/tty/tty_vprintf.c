#include <tty.h>

int tty_vprintf(const char* s, va_list a) {
	char buffer[(sizeof(uint64_t) << 3) + 2];
	color_t color = COLOR_LIGHT_GRAY;
	size_t printed_chars = 0;
	color_t frg;
	for (; *s; s++) {
		if (*s == '\x1b') {
			++s;
			if (*s != '[') {
				tty_print_string("[unsupported attribute type]", color.r, color.g, color.b);
				continue;
			}
			
			color_t tmp_color = color;
			do {
				++s;
				if (*s == '0') tmp_color = COLOR_LIGHT_GRAY;
				else if (*s == '3') {
					++s;
					if (*s == '0') frg = COLOR_BLACK;
					else if (*s == '1') frg = COLOR_RED;
					else if (*s == '2') frg = COLOR_GREEN;
					else if (*s == '3') frg = COLOR_BROWN;
					else if (*s == '4') frg = COLOR_BLUE;
					else if (*s == '5') frg = COLOR_MAGENTA;
					else if (*s == '6') frg = COLOR_CYAN;
					else if (*s == '7') frg = COLOR_DARK_GRAY;
					else {
						tty_print_string("[unsupported attribute]", color.r, color.g, color.b);
						continue;
					}

					tmp_color = frg;
				}
				else if (*s == '9') {
					++s;
					if (*s == '0') frg = COLOR_LIGHT_GRAY;
					else if (*s == '1') frg = COLOR_LIGHT_RED;
					else if (*s == '2') frg = COLOR_LIGHT_GREEN;
					else if (*s == '3') frg = COLOR_YELLOW;
					else if (*s == '4') frg = COLOR_LIGHT_BLUE;
					else if (*s == '5') frg = COLOR_LIGHT_MAGENTA;
					else if (*s == '6') frg = COLOR_LIGHT_CYAN;
					else if (*s == '7') frg = COLOR_WHITE;
					else {
						tty_print_string("[unsupported attribute]", color.r, color.g, color.b);
						continue;
					}

					tmp_color = frg;
				}
				/*
				else if (*s == '4') {
					++s;
					if (*s == '0') bkg = COLOR_BLACK;
					else if (*s == '1') bkg = COLOR_RED;
					else if (*s == '2') bkg = COLOR_GREEN;
					else if (*s == '3') bkg = COLOR_BROWN;
					else if (*s == '4') bkg = COLOR_BLUE;
					else if (*s == '5') bkg = COLOR_MAGENTA;
					else if (*s == '6') bkg = COLOR_CYAN;
					else if (*s == '7') bkg = COLOR_DARK_GRAY;
					else {
						tty_print_string("[unsupported attribute]", color.r, color.g, color.b);
						continue;
					}

					tmp_color = (bkg << 4) | (tmp_color & 0x0f);
				}
				else if (*s == '1') {
					++s;
					if (*s != '0') {
						tty_print_string("[unsupported attribute]", color.r, color.g, color.b);
						continue;
					}

					++s;
					if (*s == '0') bkg = COLOR_DARK_GRAY;
					else if (*s == '1') bkg = COLOR_LIGHT_RED;
					else if (*s == '2') bkg = COLOR_LIGHT_GREEN;
					else if (*s == '3') bkg = COLOR_YELLOW;
					else if (*s == '4') bkg = COLOR_LIGHT_BLUE;
					else if (*s == '5') bkg = COLOR_LIGHT_MAGENTA;
					else if (*s == '6') bkg = COLOR_LIGHT_CYAN;
					else if (*s == '7') bkg = COLOR_WHITE;
					else {
						__min_stdio_print_colored_string(__STR_UNSUPPORTED_ATTRIBUTE, color);
						continue;
					}

					tmp_color = (bkg << 4) | (tmp_color & 0x0f);
				}
				*/
				else {
					tty_print_string("[unsupported attribute]", color.r, color.g, color.b);
					continue;
				}

				++s;
			} while(*s == ';');

			if (*s != 'm') {
				tty_print_string("[unsupported attribute type]", color.r, color.g, color.b);
				--s;
			}
			else color = tmp_color;
			continue;
		}
		
		if (*s != '%') {
			tty_putchar(*s, color.r, color.g, color.b);
			++printed_chars;
			continue;
		}

		s++;
		if (*s == '%') {
			tty_putchar('%', color.r, color.g, color.b);
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
				width = (size_t)va_arg(a, unsigned long);
				++s;
			}
			else if (*s < '0' || *s > '9') tty_print_string("[missing width]", color.r, color.g, color.b);
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
			signed_number = va_arg(a, long);
		}
		else if (*s == 'u') {
			is_number = true;
			radix = 10;
			unsigned_number = va_arg(a, unsigned long);
		}
		else if (*s == 'x') {
			is_number = true;
			radix = 16;
			unsigned_number = va_arg(a, unsigned long);
		}
		else if (*s == 'o') {
			is_number = true;
			radix = 8;
			unsigned_number = va_arg(a, unsigned long);
		}
		else if (*s == 'b') {
			is_number = true;
			radix = 2;
			unsigned_number = va_arg(a, unsigned long);
		}
		else if (*s == 's') is_string = true;
		else if (*s == 'c') is_char = true;
		else tty_print_string("[unsupported format type]", color.r, color.g, color.b);
		
		size_t tmp_len = 0;
		if (is_number) {
			if (!is_unsigned && signed_number < 0) {
				tty_putchar('-', color.r, color.g, color.b);
				tmp_len += 1;

				is_unsigned = true;
				unsigned_number = (unsigned long)(-(signed_number + 1)) + 1;
			}

			if (flag_hash) {
				if (radix == 16) {
					tty_print_string("0x", color.r, color.g, color.b);
					tmp_len += 2;
				}
				else if (radix == 8) {
					tty_putchar('0', color.r, color.g, color.b);
					tmp_len += 1;
				}
				else if (radix == 2) {
					tty_print_string("0b", color.r, color.g, color.b);
					tmp_len += 2;
				}
				else if (radix != 10) tty_print_string("[unsupported radix]", color.r, color.g, color.b);
			}

			ultoa(unsigned_number, buffer, radix);
			tmp_len += strlen(buffer);
		}
		else if (is_char) {
			buffer[0] = (char)va_arg(a, int);
			tmp_len += 1;
		}
		else if (is_string) {
			char* tmp_str = va_arg(a, char*);
			size_t tmp_str_len = strlen(tmp_str);
			memcpy(buffer, tmp_str, tmp_str_len + 1);
			tmp_len += tmp_str_len;
		}

		if (width_type != WIDTH_TYPE_UNKNOWN) {
			char c = '\0';
			if (width_type == WIDTH_TYPE_SPACES) c = ' ';
			else if (width_type == WIDTH_TYPE_ZEROS) c = '0';

			for (; tmp_len < width; tmp_len++) tty_putchar(c, color.r, color.g, color.b);
		}

		if (is_char) tty_putchar(buffer[0], color.r, color.g, color.b);
		else tty_print_string(buffer, color.r, color.g, color.b);

		printed_chars += tmp_len;
	}

	return printed_chars;
}