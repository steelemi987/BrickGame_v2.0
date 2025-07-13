#include "frontend.h"

/**
 * @brief Function to update the state of user interface in console.
 *
 * The function prints on screen the current state of the game for user
 * interface to be up to date in real time.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 */

void print_game_screen(GameInfo_t gi) {
  print_field(gi);
  attron(COLOR_PAIR(C_STATUS));
  mvprintw(0, 24, "SCORE:          ");
  mvprintw(0, 24, "SCORE: %d", gi.score);
  mvprintw(2, 24, "HIGH_SCORE: %d", gi.high_score);
  mvprintw(4, 24, "LEVEL: %d", gi.level);
  if (gi.next != NULL) {
    mvprintw(6, 24, "NEXT:");
  }
  attroff(COLOR_PAIR(C_STATUS));
  if (gi.next != NULL) {
    print_next_fig(7, 24, gi);
  }
  if (gi.pause) {
    attron(COLOR_PAIR(C_STATUS));
    mvprintw(11, 24, "PAUSE");
    attroff(COLOR_PAIR(C_STATUS));
  } else {
    mvprintw(11, 24, "     ");
  }
}

/**
 * @brief Function to update the state of field.
 *
 * The function prints on screen the current state of the field for user
 * interface to be up to date in real time.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 */

void print_field(GameInfo_t gi) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      int sym = C_FIELD;
      if (gi.field[i][j] == 1) {
        sym = C_BLOCK;
      } else if (gi.field[i][j] == 2) {
        sym = C_YELLOW;
      }
      attron(COLOR_PAIR(sym));
      mvaddstr(i, 2 * j, "  ");
      attroff(COLOR_PAIR(sym));
    }
  }
}

/**
 * @brief Function to update the state of next figure.
 *
 * The function prints on screen the current state of the next figure for user
 * interface to be up to date in real time.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 */

void print_next_fig(int y, int x, GameInfo_t gi) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int sym = C_FIELD;
      if (gi.next[i][j] == 1) {
        sym = C_BLOCK;
      }
      attron(COLOR_PAIR(sym));
      mvaddstr(y + i, x + 2 * j, "  ");
      attroff(COLOR_PAIR(sym));
    }
  }
}

/**
 * @brief Function to print GameOver screen of user interface when the game is
 * over
 *
 * When the game's state is GAME_OVER, this function is called to print GameOver
 * screen. The function waits for user input to restart the game or exit the
 * game.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 * @param fig A structure containing information about the game and the current
 * piece (piece coordinates, piece size, game status, current piece state,
 * number of game ticks).
 */

UserAction_t game_over(GameInfo_t* gi, int status) {
  attron(COLOR_PAIR(C_SYMB));
  if (status == GAME_OVER) {
    mvprintw(1, 0, "GAME OVER");
    mvprintw(3, 0, "YOUR SCORE");
    mvprintw(5, 0, "%d", gi->score);
    mvprintw(7, 0, "PRESS R");
    mvprintw(9, 0, "TO RESTART");
  }
  if (status == WIN_GAME) {
    mvprintw(1, 0, "CONGRATULATIONS");
    mvprintw(3, 0, "ON YOUR");
    mvprintw(5, 0, "VICTORY");
    mvprintw(7, 0, "PRESS R");
    mvprintw(9, 0, "TO RESTART");
  }
  attroff(COLOR_PAIR(C_SYMB));
  refresh();
  UserAction_t ch = Pause;
  nodelay(stdscr, FALSE);
  while (ch != Start && ch != Terminate) {
    ch = get_input();
  }
  nodelay(stdscr, TRUE);
  return ch;
}

/**
 * @brief Function to print error screen of user interface
 *
 * When the game's state is ERROR_GAME, this function is called to print error
 * screen.
 *
 * Needs no arguments.
 *
 * Has no specific values to be returned.
 */

void print_error() {
  mvprintw(0, 0, "File 'data.txt' not found");
  refresh();
  nodelay(stdscr, FALSE);
  getch();
}

/** @brief Function to print start screen of user interface before the game
 * itself is started
 *
 * The function prints start screen and awaits for user to press Start bottom.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 * @return returns the START_GAME status.
 *
 */

int start_screen(GameInfo_t* gi) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) gi->field[i][j] = 0;
  }
  print_field(*gi);
  attron(COLOR_PAIR(C_SYMB));
  mvprintw(3, 0, "PRESS");
  mvprintw(5, 0, "R");
  mvprintw(7, 0, "TO START");
  attroff(COLOR_PAIR(C_SYMB));
  refresh();
  int ch = Pause;
  nodelay(stdscr, FALSE);
  while (ch != Start) {
    ch = get_input();
  }
  nodelay(stdscr, TRUE);

  return START_GAME;
}

/** @brief Function takes user input and returns it as code according to the
 * structure UserAction_t.
 *
 * The function converts the symbol received from the user into structure code
 * for further work.
 *
 * The function takes no parameters.
 *
 * @return action as code according to the structure UserAction_t.
 *
 */

UserAction_t get_input() {
  UserAction_t action;
  int ch = getch();
  switch (ch) {
    case KEY_LEFT:
    case 'a':
      action = Left;
      break;
    case KEY_DOWN:
    case 's':
      action = Down;
      break;
    case KEY_RIGHT:
    case 'd':
      action = Right;
      break;
    case 'r':
      action = Start;
      break;
    case 'p':
      action = Pause;
      break;
    case KEY_ESC:
      action = Terminate;
      break;
    case ' ':
      action = Action;
      break;
    case 'w':
    case KEY_UP:
      action = Up;
      break;
    default:
      action = (UserAction_t)NO_ACTION;
  }
  return action;
}
