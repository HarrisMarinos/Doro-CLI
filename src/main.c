#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "draw_num.h"

#define LOWER_CASE_Q_KEY 'q'
#define UPPER_CASE_Q_KEY 'Q'

const char *get_applicable_colour(const char *);

bool time_changed(int, int);
int main(int argc, char *argv[])
{
	const int DEFAULT_MINUTES = 15;
	const int BREAK_MINUTES = 5;
	const char *DEFAULT_COLOUR = "white";
	const char *colour_str;
	int i, ch;
	int total_seconds, minutes = 0, seconds = 0;
	bool want_colours = true, graphics_mode, border = true;
	struct timeval tv;
	struct timezone tz;
	struct winsize w;
	int row, col;

	// Argument initialization
	if (argc == 1)
	{
		minutes = DEFAULT_MINUTES; // default value for now
		colour_str = (char *)DEFAULT_COLOUR;
	}

	if (argc == 2)
	{

		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
		{
			printf("Open Source CLI-POMODORO\n");
			printf("- Set Minutes and Seconds : \n\tdoro -m minutes -s seconds\n");
			printf("- Add no border : \n\tdoro --no-border\n");
			printf("- Both : \n\tdoro -m minutes -s seconds --no-border\n");
			printf("- Break (default is 5) : \n\tdoro --break or doro -b\n");
			printf("- Set Specific colour : \n\tdoro -m 30 --colour red\n");

			printf("The Default Values are 15 : 00\n");
			printf("\n************More Features COMING SOON (check README)************\n\n");
			exit(0);
		}
	}

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{

			if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) // set minutes
			{
				minutes = atoi(argv[++i]);
			}
			else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) // set seconds
			{
				seconds = atoi(argv[++i]);
			}
			else if (strcmp(argv[i], "--colour") == 0 && i + 1 < argc)
			{
				colour_str = get_applicable_colour(argv[++i]);
			}
			else if (strcmp(argv[i], "--no-border") == 0)
			{
				border = false;
			}
			else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--break") == 0)
			{
				minutes = BREAK_MINUTES;
			}
			else
			{
				printf("Not enough or invalid arguments, please try again.\n");
				exit(0);
			}
		}
	}

	if (minutes < 0 || seconds < 0)
	{
		printf("Minutes or Seconds cannot be negative\n");
		exit(0);
	}
	else if (minutes > 99 || seconds > 59)
	{
		printf("More Time is under construction.\n");
		exit(0);
	}
	if (seconds == 0 && minutes == 0)
	{
		minutes = DEFAULT_MINUTES;
	}
	total_seconds = (60 * minutes) + seconds;

	gettimeofday(&tv, &tz);

	// initialize ncurses
	initscr();
	/*All ncurses colours
	- COLOR_BLACK
	- COLOR_RED
	- COLOR_GREEN
	- COLOR_YELLOW
	- COLOR_BLUE
	- COLOR_MAGENTA
	- COLOR_CYAN
	- COLOR_WHITE
	*/

	add_colours_if_applicable(want_colours, &graphics_mode, colour_str);

	// getting size of terminal

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// initialize window
	WINDOW *win = newwin(w.ws_row, w.ws_col, 0, 0);
	if (win == NULL)
	{
		printf("Window is too small...\n");
		exit(0);
	}
	refresh();
	nodelay(win, true);

	//  prevent characters to appear
	noecho();
	// remove cursor
	curs_set(0);
	getmaxyx(win, row, col);
	// Pomodoro Counter

	char msg[100];
	int initial_seconds = tv.tv_sec;

	ch = wgetch(win);

	while (total_seconds >= 0 && (ch != LOWER_CASE_Q_KEY && ch != UPPER_CASE_Q_KEY))
	{

		werase(win);

		minutes = total_seconds / 60;
		seconds = total_seconds % 60;
		getmaxyx(win, row, col);
		if (border)
			box(win, 0, 0);
		sprintf(msg, "%02d : %02d", minutes, seconds);

		int size = 0;

		if (col >= 44 && row >= 9) // BIG FONT
		{
			size = 7;
			graphics_mode = true;
		}
		else if (row > 6) // SMALL FONT
		{
			size = 5;
			graphics_mode = true;
		}
		else // NO FONT - JUST TEXT
		{
			graphics_mode = false;
		}
		if (graphics_mode)
		{
			for (i = 0; i < strlen(msg); i++)
			{
				draw_digit(win, msg[i], i, size);
			}
		}
		else
		{
			mvwprintw(win, (row / 2), (col / 2) - (strlen(msg) / 2), "%s", msg);
		}
		if (border)
			box(win, 0, 0);
		gettimeofday(&tv, &tz);
		if (initial_seconds != tv.tv_sec)
		{
			initial_seconds = tv.tv_sec;
			total_seconds--;
		}

		wrefresh(win);

		ch = wgetch(win);
	}
	const char *time_passed = "Time passed! Good Job!";
	const char *quit_msg = "(Press (Q|q) to quit)";
	while ((ch != LOWER_CASE_Q_KEY && ch != UPPER_CASE_Q_KEY))
	{
		werase(win);
		if (border)
			box(win, 0, 0);
		// Needs a way to quit
		getmaxyx(win, row, col);

		mvwprintw(win, (row / 2), (col / 2) - (strlen(time_passed) / 2), "%s", time_passed);
		mvwprintw(win, (row / 2) + 1, (col / 2) - (strlen(quit_msg) / 2), "%s", quit_msg);
		if (border)
			box(win, 0, 0);
		wrefresh(win);

		ch = wgetch(win);
	}
	endwin();
	return 0;
}
bool time_changed(int minutes, int seconds)
{
	if (minutes == 0 && seconds == 0)
	{
		return false;
	}
	return true;
}

const char *get_applicable_colour(const char *colour_str)
{
	int i;
	const char *DEFAULT_COLOUR = "white";
	const char *ALL_COLOURS[] = {"red", "black", "green", "yellow", "blue", "magenta", "cyan", "white"};
	const int ALL_COLOUR_SIZE = sizeof(ALL_COLOURS) / sizeof(char *);
	for (i = 0; i < ALL_COLOUR_SIZE; i++)
	{
		if (strcmp(ALL_COLOURS[i], colour_str) == 0)
		{
			return ALL_COLOURS[i];
		}
	}
	return DEFAULT_COLOUR;
}