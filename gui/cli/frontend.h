#ifndef FRONTEND_H
#define FRONTEND_H

#define _POSIX_C_SOURCE 199309

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/tetris/backend.h"

#define WIN_INIT           \
  {                        \
    initscr();             \
    noecho();              \
    curs_set(0);           \
    keypad(stdscr, TRUE);  \
    nodelay(stdscr, TRUE); \
  }
#define COLOR                                 \
  {                                           \
    start_color();                            \
    init_pair(1, COLOR_WHITE, COLOR_CYAN);    \
    init_pair(2, COLOR_GREEN, COLOR_GREEN);   \
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   \
    init_pair(4, COLOR_RED, COLOR_CYAN);      \
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW); \
  }

void print_game_screen(GameInfo_t gi);
void print_field(GameInfo_t gi);
void print_next_fig(int y, int x, GameInfo_t gi);
UserAction_t game_over(GameInfo_t* gi, int status);
void print_error();
int start_screen(GameInfo_t* gi);
UserAction_t get_input();

#endif