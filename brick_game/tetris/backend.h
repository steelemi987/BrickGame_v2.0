#ifndef BACKEND_H
#define BACKEND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "structures.h"

#define NO_ACTION 10
#define DELAY 9999999
#define DATA_DIR "games/record_tetris.txt"
#define KEY_ESC 27
#define MAX_SCORE 999999999
#define MAX_TICKS 100

void userInput(UserAction_t action, bool hold);
GameInfo_t updateCurrentState();

GameInfo_t* allocate_memory_game();
void create_game(GameInfo_t* gi, Figure_and_Info_t* fig, int record);
void gameinfo_free(GameInfo_t* gi);
void figure_free(Figure_and_Info_t* fig);
Figure_and_Info_t* allocate_memory_figure();
void random_fig(GameInfo_t* gi);
void start(GameInfo_t* gi, Figure_and_Info_t* fig, int record);
void spawn_figure(Figure_and_Info_t* fig, GameInfo_t* gi);
int abroad(GameInfo_t* gi, Figure_and_Info_t* fig);
void rotate_fig(GameInfo_t* gi, Figure_and_Info_t* fig);
int attaching(GameInfo_t* gi, Figure_and_Info_t* fig);
void write_fig_in_field(GameInfo_t* gi, Figure_and_Info_t* fig);
int set_pause_status(GameInfo_t* gi);
void move_left(GameInfo_t* gi, Figure_and_Info_t* fig);
void move_right(GameInfo_t* gi, Figure_and_Info_t* fig);
void move_down(GameInfo_t* gi, Figure_and_Info_t* fig);
void are_the_lines_filled(GameInfo_t* gi);
int is_rich_high_board(GameInfo_t* gi);
void set_level(GameInfo_t* gi);
void sum_score(GameInfo_t* gi, int count_filled_lines);
void relevant_high_score(GameInfo_t* gi);
GameInfo_t* update_GameInfo(GameInfo_t* cur_game);
Figure_and_Info_t* update_Figure(Figure_and_Info_t* cur_fig);
void game_step(GameInfo_t* gi, Figure_and_Info_t* fig);

int get_score();
int record_write(int record);
void pause_game(GameInfo_t* gi, Figure_and_Info_t* fig);

#ifdef __cplusplus
}
#endif

#endif
