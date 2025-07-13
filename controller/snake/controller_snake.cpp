#include "controller_snake.h"

/**
 * Virtual destructor
 *
 */
s21::Controller::~Controller() {}

/**
 * Constructor with one parametr
 *
 */

s21::Controller_snake::Controller_snake(Model_Snake* model) : model_(model) {}

/**
 * Class destructor. Frees resources allocated during the process.
 */

s21::Controller_snake::~Controller_snake() { delete model_; }

/**
 * The method returns a structure with game data stored in an object
 * of the class with business logic.
 *
 * @return Current state of main game structure
 */

GameInfo_t* s21::Controller_snake::get_gameinfo_t() const {
  return model_->mod_get_gameinfo_t();
}

/** @brief The method processes user input.
 *
 * The method controls the transmission of user input depending
 * on the game state.
 *
 * Has no specific values to be returned.
 *
 * @param action code of the key pressed by the user from the structure
 * UserAction_t.
 *
 */

void s21::Controller_snake::get_Input(UserAction_t action) {
  if (con_get_status() == START_GAME) {
    if (action == Start) {
      model_->userInput(action, true);
    }
  } else if (con_get_status() == PAUSE_GAME) {
    if (action == Pause) {
      model_->userInput(action, true);
    }
  } else if (con_get_status() == GAME_OVER || con_get_status() == WIN_GAME) {
    model_->userInput((UserAction_t)NO_ACTION, true);
  } else {
    model_->userInput(action, true);
    model_->updateCurrentState();
  }
}

/**
 * The method sets the game in motion. Updates the state of the game board.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Controller_snake::move_model() {
  model_->move_body();
  model_->updateCurrentState();
}

/**
 * The method returns the current status of the game.
 *
 * @return game status code
 *
 */

int s21::Controller_snake::con_get_status() const {
  return model_->get_status();
}

/**
 * Constructor without parametrs. Initializes the game with initial data.
 *
 */

s21::Controller_tetris::Controller_tetris() {
  gi = allocate_memory_game();
  fig = allocate_memory_figure();
  update_GameInfo(gi);
  update_Figure(fig);
  fig->status = START_GAME;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) gi->field[i][j] = 0;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) gi->next[i][j] = 1;
  }
}

/**
 * Class destructor. Frees resources allocated during the process.
 */

s21::Controller_tetris::~Controller_tetris() {
  gameinfo_free(gi);
  figure_free(fig);
}

/**
 * The method returns a structure with game data stored in an object
 * of the class with business logic.
 *
 * @return Current state of main game structure
 */

GameInfo_t* s21::Controller_tetris::get_gameinfo_t() const { return gi; }

/** @brief The method processes user input.
 *
 * The method controls the transmission of user input depending
 * on the game state.
 *
 * Has no specific values to be returned.
 *
 * @param action code of the key pressed by the user from the structure
 * UserAction_t.
 *
 */

void s21::Controller_tetris::get_Input(UserAction_t action) {
  if (con_get_status() == START_GAME) {
    if (action == Start) {
      start(gi, fig, get_score());
    }
  } else if (con_get_status() == PAUSE_GAME) {
    if (action == Pause) {
      fig->status = MOVE;
      gi->pause = START_GAME;
    }
  } else if (con_get_status() != GAME_OVER) {
    userInput(action, true);
    process_changes();
    updateCurrentState();
  }
  record_write(gi->high_score);
}

/**
 * The method sets the game in motion. Updates the state of the game board.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Controller_tetris::move_model() {
  if (con_get_status() != GAME_OVER) {
    move_down(gi, fig);
    process_changes();
  }
  updateCurrentState();
}

/**
 * The method returns the current status of the game.
 *
 * @return game status code
 *
 */

int s21::Controller_tetris::con_get_status() const { return fig->status; }

/**
 * The method processes changes after the figure moves down. If the falling
 * figure collides with a block on the field, the figure is written to the
 * field, a new figure is spawned. If the line on the field is completely
 * filled with blocks, they are removed, and the player is awarded points.
 * There is a check for blocks reaching the upper boundary of the field.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Controller_tetris::process_changes() {
  if (attaching(gi, fig)) {
    write_fig_in_field(gi, fig);
    spawn_figure(fig, gi);
    are_the_lines_filled(gi);
  }
  if (is_rich_high_board(gi)) {
    fig->status = GAME_OVER;
  }
}
