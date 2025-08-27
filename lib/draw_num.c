#include <ncurses.h>
#include <string.h>

#include "draw_num.h"
void draw_digit(WINDOW *win, int digit, int index, int size)
{
    int row, col;
    int i, j;
    getmaxyx(win, row, col);
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            int y = (row / 2) + i - (size / 2);
            int x;
            int spacing = 2;
            int gap = 10;
            int center = col / 2;
            switch (index)
            {
            case 0:
                x = center - (size * 2 + spacing + gap / 2) + j;
                break;
            case 1:
                x = center - (size + gap / 2) + j;

                break;
            case 3:
                x = center + j - (size / 2);
                break;
            case 5:
                x = center + (gap / 2) + j;
                break;
            case 6:
                x = center + (size + spacing + gap / 2) + j;

                break;
            default:
                x = -1;
                break;
            }
            switch (digit)
            {
            case '0':
                draw_zero(win, i, j, size, x, y);
                break;
            case '1':
                draw_one(win, i, j, size, x, y);
                break;
            case '2':
                draw_two(win, i, j, size, x, y);
                break;
            case '3':
                draw_three(win, i, j, size, x, y);
                break;
            case '4':
                draw_four(win, i, j, size, x, y);
                break;
            case '5':
                draw_five(win, i, j, size, x, y);
                break;
            case '6':
                draw_six(win, i, j, size, x, y);
                break;
            case '7':
                draw_seven(win, i, j, size, x, y);
                break;
            case '8':
                draw_eight(win, i, j, size, x, y);
                break;
            case '9':
                draw_nine(win, i, j, size, x, y);
                break;
            default:
                draw_colon(win, i, j, size, x, y);
            }
        }
    }
}
void add_colours_if_applicable(bool want_colours, bool *graphics_mode, const char *colour)
{

    // add colours (if applicable)
    if (has_colors() && want_colours)
    {

        start_color();
        if (strcmp(colour, "white") == 0)
        {
            init_pair(1, COLOR_WHITE, COLOR_WHITE);
        }
        if (strcmp(colour, "red") == 0)
        {
            init_pair(1, COLOR_RED, COLOR_RED);
        }
        if (strcmp(colour, "black") == 0)
        {
            init_pair(1, COLOR_BLACK, COLOR_BLACK);
        }
        if (strcmp(colour, "green") == 0)
        {
            init_pair(1, COLOR_GREEN, COLOR_GREEN);
        }
        if (strcmp(colour, "yellow") == 0)
        {
            init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
        }
        if (strcmp(colour, "blue") == 0)
        {
            init_pair(1, COLOR_BLUE, COLOR_BLUE);
        }
        if (strcmp(colour, "magenta") == 0)
        {
            init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA);
        }
        if (strcmp(colour, "cyan") == 0)
        {
            init_pair(1, COLOR_CYAN, COLOR_CYAN);
        }
        *graphics_mode = true;
    }
}

void draw_zero(WINDOW *win, int i, int j, int size, int x, int y)
{
    if (i == 0 || j == 0 || i == size - 1 || j == size - 1)
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_one(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (j == size - 1)
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_two(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (i == 0 || i == size / 2 || i == size - 1 || (i > 0 && i < size / 2 && j == size - 1) || (i > size / 2 && i < size - 1 && j == 0))
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_three(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (i == 0 || i == size / 2 || i == size - 1 || j == size - 1)
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_four(WINDOW *win, int i, int j, int size, int x, int y)
{

    if ((i < size / 2 && j == 0) || i == size / 2 || j == size - 1)
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_five(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (i == 0 || i == size / 2 || i == size - 1 || (i > 0 && i < size / 2 && j == 0) || (i > size / 2 && i < size - 1 && j == size - 1))
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_six(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (j == 0 || i == size - 1 || i == size / 2 || (i > size / 2 && i < size - 1 && j == size - 1))
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_seven(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (i == 0 || j == size - 1)
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_eight(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (i == 0 || j == 0 || i == size - 1 || j == size - 1 || i == size / 2)
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}
void draw_nine(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (i == 0 || j == size - 1 || i == size / 2 || (i > 0 && i < size / 2 && j == 0))
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
    else
    {
        mvwprintw(win, y, x, " ");
    }
}

void draw_colon(WINDOW *win, int i, int j, int size, int x, int y)
{

    if (j == 0 || j == size - 1 || i == size / 2)
    {
        mvwprintw(win, y, x, " ");
    }
    else
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, y, x, "O");
        wattroff(win, COLOR_PAIR(1));
    }
}