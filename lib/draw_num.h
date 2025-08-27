#ifndef DRAW_NUM_H_
#define DRAW_NUM_H_
void add_colours_if_applicable(bool want_colours, bool *graphics_mode, const char *);

void draw_digit(WINDOW *, int, int, int);
void draw_zero(WINDOW *win, int i, int j, int size, int x, int y);
void draw_one(WINDOW *win, int i, int j, int size, int x, int y);
void draw_two(WINDOW *win, int i, int j, int size, int x, int y);
void draw_three(WINDOW *win, int i, int j, int size, int x, int y);
void draw_four(WINDOW *win, int i, int j, int size, int x, int y);
void draw_five(WINDOW *win, int i, int j, int size, int x, int y);
void draw_six(WINDOW *win, int i, int j, int size, int x, int y);
void draw_seven(WINDOW *win, int i, int j, int size, int x, int y);
void draw_eight(WINDOW *win, int i, int j, int size, int x, int y);
void draw_nine(WINDOW *win, int i, int j, int size, int x, int y);
void draw_colon(WINDOW *win, int i, int j, int size, int x, int y);

#endif