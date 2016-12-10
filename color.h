#ifndef _TRI_COLOR_H
#define _TRI_COLOR_H

#include <stdio.h>
#include <string.h>

#define COLOR_END_LEN		4

#define COLOR_START		"\033["
#define COLOR_END		"\033[0m"

#define COLOR_BLACK_STR		"30"
#define COLOR_RED_STR		"31"
#define COLOR_GREEN_STR		"32"
#define COLOR_YELLOW_STR	"33"
#define COLOR_BLUE_STR		"34"
#define COLOR_PURPLE_STR	"35"
#define COLOR_CYAN_STR		"36"
#define COLOR_WHITE_STR		"37"

#define COLOR_ON_BLACK_STR	"40"
#define COLOR_ON_RED_STR	"41"
#define COLOR_ON_GREEN_STR	"42"
#define COLOR_ON_YELLOW_STR	"43"
#define COLOR_ON_BLUE_STR	"44"
#define COLOR_ON_PURPLE_STR	"45"
#define COLOR_ON_CYAN_STR	"46"
#define COLOR_ON_WHITE_STR	"47"

#define COLOR_STYLE_NORMAL	"0"
#define COLOR_BOLD_STR		"1"
#define COLOR_UNDERLINE_STR	"4"
#define COLOR_REVERSE_STR	"7"
#define COLOR_CROSSLINE_STR	"9"

enum fg_color {
	NORMAL,
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	CYAN,
	WHITE,
};

enum bg_color {
	ON_NORMAL,
	ON_BLACK,
	ON_RED,
	ON_GREEN,
	ON_YELLOW,
	ON_BLUE,
	ON_PURPLE,
	ON_CYAN,
	ON_WHITE
};

enum font_style {
	STYLE_NORMAL,
	BOLD,
	UNDERLINE,
	REVERSE,
	CROSSLINE
};

extern const char *end_of_color;
extern const char *fg_color_table[];
extern const char *bg_color_table[];
extern const char *font_style_table[];

static inline int color_string(enum fg_color fg, enum bg_color bg,
			       enum font_style fs, char *buf, int len)
{
	int len_str, len_ret;
	int color_start_len = 0;
	char color_start[11] = {0};

	if (fg == NORMAL && bg == ON_NORMAL && fs == STYLE_NORMAL)
		return 0;

	len_str = strnlen(buf, len);

	snprintf(color_start + color_start_len, 4, "\033[%1s",
		 font_style_table[fs]);
	color_start_len += 3;

	if (fg != NORMAL) {
		snprintf(color_start + color_start_len, 4, ";%2s",
			 fg_color_table[fg]);
		color_start_len += 3;
	}

	if (bg != ON_NORMAL) {
		snprintf(color_start + color_start_len, 4, ";%2s",
			 bg_color_table[bg]);
		color_start_len += 3;
	}

	snprintf(color_start + color_start_len, 2, "m");
	color_start_len += 1;

	len_ret = len_str + color_start_len + COLOR_END_LEN;

	if (len <= len_ret) {
		return -1;
	}



	memcpy(buf + len_str + color_start_len, end_of_color, COLOR_END_LEN);

	for (int i = color_start_len + len_str; i - color_start_len > 0; --i) {
		buf[i - 1] = buf[i - color_start_len - 1];
	}

	memcpy(buf, color_start, color_start_len);

	return 0;
}

#endif /* _TRI_COLOR_H */
