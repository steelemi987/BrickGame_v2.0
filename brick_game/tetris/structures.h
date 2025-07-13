#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * @brief UserAction_t enum.
 *
 * Variations of user actions during the game.
 *
 * Start - Starts game
 * Pause - Pauses game
 * Terminate - Stops game
 * Left - Moves figure left
 * Right - Moves figure right
 * Up - Not used
 * Down - Moves figure down
 * Action - Rotates figure
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @brief GameInfo_t structure.
 *
 * A structure containing information about the game (field state, next piece,
 * current score, record score, current level, current game speed, pause).
 */

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/**
 * @brief Figure_and_Info_t structure.
 *
 * A structure containing information about the game and the current piece
 * (piece coordinates, piece size, game status, current piece state, number of
 * game ticks).
 */

typedef struct {
  int y;
  int x;
  int size;
  int status;
  int **fig_image;
  int ticks_left;
} Figure_and_Info_t;

/**
 * @brief Status_t enum.
 *
 * Variations of status during the game.
 */

typedef enum {
  ERROR_GAME = -1,
  START_GAME,
  PAUSE_GAME,
  EXIT_GAME,
  MOVE,
  GAME_OVER,
  WIN_GAME
} Status_t;

/**
 * @brief Color_t enum.
 *
 * Variations of color pair during the game.
 */

typedef enum { C_FIELD = 1, C_BLOCK, C_STATUS, C_SYMB, C_YELLOW } Color_t;

#endif
