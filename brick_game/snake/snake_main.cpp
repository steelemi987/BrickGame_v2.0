#include "../../gui/cli/frontend.h"
#include "model_snake.h"

void pause_game_snake(s21::Model_Snake* model);

/** @brief Entrypoint
 *
 * Main fuction that starts snake game.
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
  s21::Model_Snake model;
  UserAction_t action;
  model.set_status(start_screen(model.mod_get_gameinfo_t()));
  struct timespec rem;
  struct timespec req = {0, DELAY};
  int ticks_left = 0;
  while (model.get_status() != EXIT_GAME) {
    if (model.get_status() == START_GAME) {
      model.restart();
    } else if (model.get_status() == MOVE) {
      nanosleep(&req, &rem);
      model.userInput(get_input(), true);
      if (ticks_left >= (MAX_TICKS - model.get_speed() * 6)) {
        model.move_body();
        ticks_left = 0;
      } else {
        ticks_left++;
      }
      print_game_screen(model.updateCurrentState());
      refresh();
    } else if (model.get_status() == PAUSE_GAME) {
      pause_game_snake(&model);
    } else if (model.get_status() == GAME_OVER ||
               model.get_status() == WIN_GAME) {
      action = game_over(model.mod_get_gameinfo_t(), model.get_status());
      if (action == Terminate) {
        model.set_status(EXIT_GAME);
      } else if (action == Start) {
        model.set_status(START_GAME);
      }
    }
  }
  endwin();

  return 0;
}

/** @brief The function pauses the game.
 *
 * The function pauses the game waiting for user input.
 * Depending on the keyboard key pressed, it either exits the game or continues
 * it.
 *
 * @param model A class object containing information about the game and methods
 * are working with them.
 *
 * Has no specific values to be returned.
 *
 */

void pause_game_snake(s21::Model_Snake* model) {
  int ch = 0;
  nodelay(stdscr, FALSE);
  while (ch != 'p' && ch != KEY_ESC) {
    ch = getch();
  }
  nodelay(stdscr, TRUE);
  if (ch == 'p') {
    model->set_status(MOVE);
    model->set_pause(START_GAME);
  } else {
    model->set_status(EXIT_GAME);
  }
}