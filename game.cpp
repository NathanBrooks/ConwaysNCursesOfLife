#include <unistd.h>
#include <ncurses.h>
#include "life.h"



int main() {
	char c_input;
	WINDOW *main_win;
	
	int StartX, StartY, Height, Width;

	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	
	start_color();
	curs_set(0);

	init_pair(1, COLOR_WHITE, COLOR_BLUE); // controls color of live cell
	init_pair(2, COLOR_BLACK, COLOR_BLACK); // controls color of dead cell
	init_pair(3, COLOR_BLACK, COLOR_CYAN); // controls background of window
	init_pair(4, COLOR_WHITE, COLOR_MAGENTA); // color age warn
	init_pair(5, COLOR_WHITE, COLOR_BLUE); // controls color of outer border

	Height = LINES-2;
	Width = COLS-2;
	StartY = (LINES - Height) / 2;
	StartX = (COLS - Width) / 2;
	attron(COLOR_PAIR(5));
	mvprintw(0,(COLS-20)/2, "CONWAYS GAME OF LIFE");
	attroff(COLOR_PAIR(5));

	refresh();

	main_win = newwin(Height,Width,StartY,StartX);
	wbkgd(stdscr,COLOR_PAIR(5));
	refresh();
	wbkgd(main_win,COLOR_PAIR(3));
	box(main_win,0,0);

	Life MyField = Life(Width, Height, main_win); // this automatically updates the screen square
	c_input = getchar();
	while (c_input != 'c') {
		if (c_input != 'r')
			MyField.UpdateSquare();
		else
			MyField.Reset(COLS-2, LINES-2, main_win); // try to reset
		c_input = getchar();
	}
	endwin();
	return 0;
}
