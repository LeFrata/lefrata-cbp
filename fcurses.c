#include <curses.h>

#include "fcurses.h"

#define PALLETE_SIZE  (COLOR_WHITE - COLOR_BLACK + 1)

void InitScreen(void) {

#ifdef XCURSES
	Xinitscr(argc, argv);
#else
	initscr();
#endif

	if (has_colors()) {

		short int fg = 0, bg = 0;

		start_color();

		for (bg = COLOR_BLACK; bg <= COLOR_WHITE; bg++)
			for (fg = COLOR_BLACK; fg <= COLOR_WHITE; fg++)
				init_pair(bg * PALLETE_SIZE + fg + 1, fg, bg);

	}

	noecho();
	curs_set(0);
	nodelay(stdscr, TRUE);
	timeout(0);
	keypad(stdscr, TRUE);

}

void SetColor(short int fg, short int bg, chtype attr) {

	chtype color = COLOR_PAIR(bg * PALLETE_SIZE + fg + 1);
	color |= attr;
	attrset(color);

}
