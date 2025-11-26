#include <tty/tty.h>

static const char* __STR_UNSUPPORTED_ATTRIBUTE_TYPE = "[unsupported attribute type]";
static const char* __STR_UNSUPPORTED_ATTRIBUTE = "[unsupported attribute]";
static const char* __STR_MISSING_WIDTH = "[missing width]";
static const char* __STR_UNSUPPORTED_FORMAT_TYPE = "[unsupported format type]";
static const char* __STR_UNSUPPORTED_RADIX = "[unsupported radix]";

extern uint8_t TTY_FRG_RED;
extern uint8_t TTY_FRG_GREEN;
extern uint8_t TTY_FRG_BLUE;
extern uint8_t TTY_BKG_RED;
extern uint8_t TTY_BKG_GREEN;
extern uint8_t TTY_BKG_BLUE;

int tty_vprintf(const char* s, va_list args) {
	gfx_color_t frg_color = GFX_PACK_COLOR(TTY_FRG_RED, TTY_FRG_GREEN, TTY_FRG_BLUE);
	gfx_color_t bkg_color = GFX_PACK_COLOR(TTY_BKG_RED, TTY_BKG_GREEN, TTY_BKG_BLUE);
	char buffer[(sizeof(uint64_t) << 3) + 2];
	size_t printed_chars = 0;
	for (; *s; s++) {
		if (*s == '\x1b') {
			++s;
			if (*s != '[') {
				tty_prints_color(__STR_UNSUPPORTED_ATTRIBUTE_TYPE, GFX_UNPACK_COLOR(frg_color), GFX_UNPACK_COLOR(bkg_color));
				continue;
			}
			
			gfx_color_t tmp_frg = frg_color;
			gfx_color_t tmp_bkg = bkg_color;
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
						tty_prints_color(
							__STR_UNSUPPORTED_ATTRIBUTE,
							GFX_UNPACK_COLOR(frg_color),
							GFX_UNPACK_COLOR(bkg_color)
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
						tty_prints_color(
							__STR_UNSUPPORTED_ATTRIBUTE,
							GFX_UNPACK_COLOR(frg_color),
							GFX_UNPACK_COLOR(bkg_color)
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
						tty_prints_color(
							__STR_UNSUPPORTED_ATTRIBUTE,
							GFX_UNPACK_COLOR(frg_color),
							GFX_UNPACK_COLOR(bkg_color)
						);
						continue;
					}
				}
				else if (*s == '1') {
					++s;
					if (*s != '0') {
						tty_prints_color(
							__STR_UNSUPPORTED_ATTRIBUTE,
							GFX_UNPACK_COLOR(frg_color),
							GFX_UNPACK_COLOR(bkg_color)
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
						tty_prints_color(
							__STR_UNSUPPORTED_ATTRIBUTE,
							GFX_UNPACK_COLOR(frg_color),
							GFX_UNPACK_COLOR(bkg_color)
						);
						continue;
					}
				}
				else {
					tty_prints_color(
						__STR_UNSUPPORTED_ATTRIBUTE,
						GFX_UNPACK_COLOR(frg_color),
						GFX_UNPACK_COLOR(bkg_color)
					);
					continue;
				}

				++s;
			} while(*s == ';');

			if (*s != 'm') {
				tty_prints_color(
					__STR_UNSUPPORTED_ATTRIBUTE_TYPE,
					GFX_UNPACK_COLOR(frg_color),
					GFX_UNPACK_COLOR(bkg_color)
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
			tty_putchar_color(
				(int)*s,
				GFX_UNPACK_COLOR(frg_color),
				GFX_UNPACK_COLOR(bkg_color)
			);

			++printed_chars;
			continue;
		}

		s++;
		if (*s == '%') {
			tty_putchar_color(
				'%',
				GFX_UNPACK_COLOR(frg_color),
				GFX_UNPACK_COLOR(bkg_color)
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
			else if (*s < '0' || *s > '9') tty_prints_color(
				__STR_MISSING_WIDTH,
				GFX_UNPACK_COLOR(frg_color),
				GFX_UNPACK_COLOR(bkg_color)
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
		else tty_prints_color(
			__STR_UNSUPPORTED_FORMAT_TYPE,
			GFX_UNPACK_COLOR(frg_color),
			GFX_UNPACK_COLOR(bkg_color)
		);
		
		size_t tmp_len = 0;
		if (is_number) {
			if (!is_unsigned && signed_number < 0) {
				tty_putchar_color(
					'-',
					GFX_UNPACK_COLOR(frg_color),
					GFX_UNPACK_COLOR(bkg_color)
				);

				tmp_len += 1;
				is_unsigned = true;
				unsigned_number = (unsigned long)(-(unsigned long)signed_number);
			}

			if (flag_hash) {
				if (radix == 16) {
					tty_prints_color(
						"0x",
						GFX_UNPACK_COLOR(frg_color),
						GFX_UNPACK_COLOR(bkg_color)
					);
					tmp_len += 2;
				}
				else if (radix == 8) {
					tty_putchar_color(
						'0',
						GFX_UNPACK_COLOR(frg_color),
						GFX_UNPACK_COLOR(bkg_color)
					);

					tmp_len += 1;
				}
				else if (radix == 2) {
					tty_prints_color(
						"0b",
						GFX_UNPACK_COLOR(frg_color),
						GFX_UNPACK_COLOR(bkg_color)
					);

					tmp_len += 2;
				}
				else if (radix != 10) tty_prints_color(
					__STR_UNSUPPORTED_RADIX,
					GFX_UNPACK_COLOR(frg_color),
					GFX_UNPACK_COLOR(bkg_color)
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

			for (; tmp_len < width; tmp_len++) tty_putchar_color(
				c,
				GFX_UNPACK_COLOR(frg_color),
				GFX_UNPACK_COLOR(bkg_color)
			);
		}

		if (is_char) tty_putchar_color(
			buffer[0],
			GFX_UNPACK_COLOR(frg_color),
			GFX_UNPACK_COLOR(bkg_color)
		);
		else tty_prints_color(
			buffer,
			GFX_UNPACK_COLOR(frg_color),
			GFX_UNPACK_COLOR(bkg_color)
		);

		printed_chars += tmp_len;
	}

	return printed_chars;
}