#include "../../gui/cli/frontend.h"

/** @brief Entrypoint
 *
 * Main fuction that starts tetris game.
 *
 * Console interface is to be initialized, datafile to be opened and
 * main structure of the game to be created here.
 *
 * It needs no arguments and has no specific output values except standart error
 * codes.
 */

int main(void) {
  WIN_INIT
  COLOR
  GameInfo_t *gi = allocate_memory_game();
  Figure_and_Info_t *fig = allocate_memory_figure();
  update_GameInfo(gi);
  update_Figure(fig);
  int record = 0;
  fig->status = start_screen(gi);
  struct timespec rem;
  struct timespec req = {0, DELAY};
  while (fig->status != EXIT_GAME && record != ERROR_GAME) {
    if (fig->status == START_GAME) {
      record = get_score();
      start(gi, fig, record);
    } else if (fig->status == MOVE) {
      nanosleep(&req, &rem);
      userInput(get_input(), TRUE);
      game_step(gi, fig);
      print_game_screen(updateCurrentState());
      refresh();
    } else if (fig->status == PAUSE_GAME) {
      pause_game(gi, fig);
    } else if (fig->status == GAME_OVER) {
      userInput(game_over(gi, fig->status), TRUE);
      record_write(gi->high_score);
    }
  }
  if (record == ERROR_GAME) {
    print_error();
  }
  record_write(gi->high_score);
  if (gi) gameinfo_free(gi);
  if (fig) figure_free(fig);
  endwin();

  return 0;
}

/** @brief The function pauses the game.
 *
 * The function pauses the game waiting for user input.
 * Depending on the keyboard key pressed, it either exits the game or continues
 * it.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 * @param fig A structure containing information about the game and the current
 * piece (piece coordinates, piece size, game status, current piece state,
 * number of game ticks).
 *
 * Has no specific values to be returned.
 *
 */

void pause_game(GameInfo_t *gi, Figure_and_Info_t *fig) {
  int ch = 0;
  nodelay(stdscr, FALSE);
  while (ch != 'p' && ch != KEY_ESC) {
    ch = getch();
  }
  nodelay(stdscr, TRUE);
  if (ch == 'p') {
    fig->status = MOVE;
    gi->pause = START_GAME;
  } else {
    fig->status = EXIT_GAME;
  }
}