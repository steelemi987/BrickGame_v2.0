#include "backend.h"

int fig_sample[] = {
    0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 4,

    0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 4,

    1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3,

    0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3,

    0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3,

    0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,

    1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3,
};

/** @brief The function allocates memory for the structure GameInfo_t.
 *
 * The function allocates memory for the structure. And passes the address of
 * the allocated memory.
 *
 * @return pointer to the address of allocated memory.
 *
 */

GameInfo_t *allocate_memory_game() {
  GameInfo_t *gi = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  gi->field = (int **)malloc(20 * sizeof(int *));
  for (int i = 0; i < 20; i++) {
    gi->field[i] = (int *)malloc(10 * sizeof(int));
  }
  gi->next = (int **)malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    gi->next[i] = (int *)malloc(4 * sizeof(int));
  }
  return gi;
}

/** @brief The function initializes a new game.
 *
 * The function fills two game structures with initial data for a further game
 * session.
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
 *
 * @param record contains information about the record.
 *
 */

void create_game(GameInfo_t *gi, Figure_and_Info_t *fig, int record) {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) gi->field[i][j] = 0;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) gi->next[i][j] = 1;
  }
  fig->ticks_left = 0;
  gi->score = 0;
  gi->high_score = record;
  gi->level = 1;
  gi->speed = 1;
  gi->pause = 0;
}

/** @brief The function frees the allocated memory.
 *
 * The function frees memory allocated for the structure GameInfo_t to eliminate
 * unwanted memory leaks.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 */

void gameinfo_free(GameInfo_t *gi) {
  for (int i = 0; i < 20; i++) {
    free(gi->field[i]);
  }
  free(gi->field);
  for (int i = 0; i < 4; i++) {
    free(gi->next[i]);
  }
  free(gi->next);
  free(gi);
}

/** @brief The function frees the allocated memory.
 *
 * The function frees memory allocated for the structure Figure_and_Info_t to
 * eliminate unwanted memory leaks.
 *
 * Has no specific values to be returned.
 *
 * @param fig A structure containing information about the game and the current
 * piece (piece coordinates, piece size, game status, current piece state,
 * number of game ticks).
 *
 */

void figure_free(Figure_and_Info_t *fig) {
  for (int i = 0; i < 4; i++) {
    free(fig->fig_image[i]);
  }
  free(fig->fig_image);
  free(fig);
}

/** @brief The function allocates memory for the structure Figure_and_Info_t.
 *
 * The function allocates memory for the structure Figure_and_Info_t. And passes
 * the address of the allocated memory.
 *
 * @return pointer to the address of allocated memory.
 *
 */

Figure_and_Info_t *allocate_memory_figure() {
  Figure_and_Info_t *fig =
      (Figure_and_Info_t *)malloc(sizeof(Figure_and_Info_t));
  fig->fig_image = (int **)malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    fig->fig_image[i] = (int *)malloc(4 * sizeof(int));
  }
  return fig;
}

/** @brief The function passes a random figure to the structure GameInfo_t.
 *
 * The function selects a random figure from a pre-created template and copies
 * it to the next field of the structure GameInfo_t.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 */

void random_fig(GameInfo_t *gi) {
  int fig_num = rand() % 7;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      gi->next[i][j] = fig_sample[fig_num * 16 + i * 4 + j];
    }
  }
}

/** @brief The function start or restart the game.
 *
 * The function fills in the necessary structures, preparing them for further
 * use.
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
 *
 */

void start(GameInfo_t *gi, Figure_and_Info_t *fig, int record) {
  if (record != ERROR_GAME) {
    fig->status = MOVE;
    create_game(gi, fig, record);
    random_fig(gi);
    spawn_figure(fig, gi);
  } else
    gi->high_score = 0;
}

/** @brief The function creates the current figure.
 *
 * The function copies blocks from the next field of the structure GameInfo_t to
 * the corresponding field of the structure Figure_and_Info_t. Sets the
 * coordinates of the figure to the starting position. Sets the size of the
 * figure. Fills the structure's next field with the next random figure.
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
 *
 */

void spawn_figure(Figure_and_Info_t *fig, GameInfo_t *gi) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      fig->fig_image[i][j] = gi->next[i][j];
    }
  }
  fig->size = gi->next[3][3];
  fig->fig_image[3][3] = 0;
  fig->y = 0;
  fig->x = 3;
  random_fig(gi);
}

/** @brief The function checks for going beyond the boundaries of the figure.
 *
 * The function checks whether the blocks of the current figure go beyond the
 * boundaries of the playing field, as well as whether the blocks of the current
 * figure fit into the blocks of the field.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 * @param fig A structure containing information about the game and the current
 * piece (piece coordinates, piece size, game status, current piece state,
 * number of game ticks).
 *
 * @return returns 1 if there was an out of bounds or block fit. Returns 0
 * otherwise.
 */

int abroad(GameInfo_t *gi, Figure_and_Info_t *fig) {
  int flag = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (fig->fig_image[i][j] == 1) {
        if ((fig->x + j) > 9 || (fig->x + j) < 0 || (fig->y + i) < 0 ||
            (fig->y + i) > 19 || 1 == gi->field[i + fig->y][j + fig->x])
          flag = 1;
      }
    }
  }
  return flag;
}

/** @brief The function rotate figure.
 *
 * The function creates a temporary field for writing a figure into. Changes the
 * configuration of the current figure as if it were rotated clockwise and
 * writes it to a temporary field. Then it checks using the abroad function to
 * see if such a configuration is possible in the current field. If possible, it
 * writes the temporary configuration into the field with the current figure.
 * Frees temporary field memory.
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
 *
 */

void rotate_fig(GameInfo_t *gi, Figure_and_Info_t *fig) {
  Figure_and_Info_t *new_fig = allocate_memory_figure();
  new_fig->x = fig->x;
  new_fig->y = fig->y;
  int s = fig->size;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      new_fig->fig_image[i][j] = 0;
    }
  }
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      new_fig->fig_image[i][j] = fig->fig_image[s - 1 - j][i];
    }
  }
  int flag = abroad(gi, new_fig);
  for (int i = 0; i < 4 && !flag; i++) {
    for (int j = 0; j < 4; j++) {
      fig->fig_image[i][j] = new_fig->fig_image[i][j];
    }
  }
  figure_free(new_fig);
}

/** @brief The function checks for contacts with the bottom border of the field
 * and with a block on the field.
 *
 * The function checks for contact between the current figure block and the
 * bottom border of the field and with the field block located under the figure
 * block.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 * @param fig A structure containing information about the game and the current
 * piece (piece coordinates, piece size, game status, current piece state,
 * number of game ticks).
 *
 * @return returns 1 if contacts. Returns 0 otherwise.
 */

int attaching(GameInfo_t *gi, Figure_and_Info_t *fig) {
  int flag = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (fig->fig_image[i][j] == 1) {
        if ((fig->y + i) == 19 || 1 == gi->field[i + 1 + fig->y][j + fig->x])
          flag = 1;
      }
    }
  }
  return flag;
}

/** @brief The function writes a figure to a field.
 *
 * The function writes the blocks of the current figure from the structure
 * Figure_and_Info_t to the structure GameInfo_t field according to the
 * coordinates of the figure.
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
 *
 */

void write_fig_in_field(GameInfo_t *gi, Figure_and_Info_t *fig) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (fig->fig_image[i][j] == 1) {
        gi->field[i + fig->y][j + fig->x] = 1;
      }
    }
  }
}

/** @brief The function sets the pause status.
 *
 * The function sets the pause status to the structure GameInfo_t and returns
 * the pause status.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 * @return returns the pause status.
 */

int set_pause_status(GameInfo_t *gi) {
  int status;  // = MOVE
  if (gi->pause != PAUSE_GAME) {
    gi->pause = PAUSE_GAME;
    status = PAUSE_GAME;
  }
  return status;
}

/** @brief The function moves the figure to the left.
 *
 * The function moves the figure to the left by changing the coordinate in the
 * structure Figure_and_Info_t if this is possible according to the rules of the
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
 *
 */

void move_left(GameInfo_t *gi, Figure_and_Info_t *fig) {
  fig->x -= 1;
  if (abroad(gi, fig)) {
    fig->x += 1;
  }
}

/** @brief The function moves the figure to the right.
 *
 * The function moves the figure to the right by changing the coordinate in the
 * structure Figure_and_Info_t if this is possible according to the rules of the
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
 *
 */

void move_right(GameInfo_t *gi, Figure_and_Info_t *fig) {
  fig->x += 1;
  if (abroad(gi, fig)) {
    fig->x -= 1;
  }
}

/** @brief The function moves the figure to the down.
 *
 * The function moves the figure to the down by changing the coordinate in the
 * structure Figure_and_Info_t if this is possible according to the rules of the
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
 *
 */

void move_down(GameInfo_t *gi, Figure_and_Info_t *fig) {
  fig->y += 1;
  if (abroad(gi, fig)) {
    fig->y -= 1;
  }
}

/** @brief The function checks for filled lines and makes appropriate changes.
 *
 * The function checks whether the lines in the “field” array of the structure
 * GameInfo_t are completely filled with blocks. If there are such lines, it
 * resets them to zero and shifts the higher lines down. Counts the number of
 * such lines. In accordance with the number of complete lines, it updates the
 * score, level, and record in the main game structures.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 */

void are_the_lines_filled(GameInfo_t *gi) {
  int line_is_filled = 0;
  int count_filled_lines = 0;
  for (int i = 0; i < 20; i++) {
    line_is_filled = 0;
    for (int j = 0; j < 10; j++) {
      if (gi->field[i][j] == 1) {
        line_is_filled++;
      }
    }
    if (line_is_filled == 10) {
      count_filled_lines++;
      for (int j = 0; j < 10; j++) {
        gi->field[i][j] = 0;
      }
      for (int new_i = i; new_i > 0; new_i--) {
        for (int j = 0; j < 10; j++) {
          gi->field[new_i][j] = gi->field[new_i - 1][j];
        }
      }
      for (int j = 0; j < 10; j++) {
        gi->field[0][j] = 0;
      }
    }
  }

  if (count_filled_lines) {
    sum_score(gi, count_filled_lines);
    set_level(gi);
    relevant_high_score(gi);
  }
}

/** @brief The function checks for the presence of blocks in the top line.
 *
 * The function checks for the presence of blocks in the top row of the "field"
 * array of the structure GameInfo_t.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 * @return returns 1 if it finds a block, 0 if there are no such blocks.
 */

int is_rich_high_board(GameInfo_t *gi) {
  int flag = 0;
  for (int j = 0; j < 10; j++) {
    if (gi->field[0][j] == 1) flag = 1;
  }
  return flag;
}

/** @brief The function sets the game level and speed.
 *
 * The function updates the game level based on the number of points the player
 * has scored. Every 600 points add 1 level. The maximum possible level of the
 * game is 10, so there is a check for this condition. Sets the game speed to
 * level.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 */

void set_level(GameInfo_t *gi) {
  if (gi->level < 10) {
    while (gi->level * 600 <= gi->score) {
      gi->level++;
    }
    if (gi->level > 10) gi->level = 10;
    gi->speed = gi->level;
  }
}

/** @brief The function updates the game score.
 *
 * The function updates the game score by adding the number of points in
 * accordance with the number of filled lines on the playing field. The maximum
 * number of points is limited to 999999999.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 * @param count_filled_lines the number of filled lines on the playing field.
 */

void sum_score(GameInfo_t *gi, int count_filled_lines) {
  switch (count_filled_lines) {
    case 1:
      gi->score += 100;
      break;
    case 2:
      gi->score += 300;
      break;
    case 3:
      gi->score += 700;
      break;
    case 4:
      gi->score += 1500;
      break;
  }
  if (gi->score > MAX_SCORE) {
    gi->score = MAX_SCORE;
  }
}

/** @brief The function updates the record.
 *
 * The function updates the record in real time. If the current score exceeds
 * the record, it is recorded in the high_score structure GameInfo_t.
 *
 * Has no specific values to be returned.
 *
 * @param gi A structure containing information about the game (field state,
 * next piece, current score, record score, current level, current game speed,
 * pause).
 *
 */

void relevant_high_score(GameInfo_t *gi) {
  if (gi->score > gi->high_score) {
    gi->high_score = gi->score;
  }
}

/** @brief Function that contains static exemple of main game structure
 *
 * @param cur_game Main game structure
 * @return Current state of main game structure
 */

GameInfo_t *update_GameInfo(GameInfo_t *cur_game) {
  static GameInfo_t *game;
  if (cur_game != NULL) {
    game = cur_game;
  }
  return game;
}

/** @brief Function that updates current game state
 *
 * @return Current state of game info
 */

GameInfo_t updateCurrentState() {
  GameInfo_t *gi = update_GameInfo(NULL);
  Figure_and_Info_t *fig = update_Figure(NULL);
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (gi->field[i][j] == 2) {
        gi->field[i][j] = 0;
      }
    }
  }
  int y = fig->y;
  int x = fig->x;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (fig->fig_image[i][j] == 1) {
        gi->field[y + i][x + j] = 2;
      }
    }
  }
  return *update_GameInfo(NULL);
}

/** @brief Function that contains static exemple of game structure
 * Figure_and_Info_t.
 *
 * @param cur_game  game structure Figure_and_Info_t
 * @return Current state of game structure Figure_and_Info_t.
 */

Figure_and_Info_t *update_Figure(Figure_and_Info_t *cur_fig) {
  static Figure_and_Info_t *fig;
  if (cur_fig != NULL) {
    fig = cur_fig;
  }
  return fig;
}

/** @brief Function to process user input taken in get_input function
 *
 * The function defines the changes in main game structures GameInfo_t and
 * Figure_and_Info_t, including game field, game state, and figure position,
 * according to user input placed in action.
 *
 * Has no specific values to be returned.
 *
 * @param action code of the key pressed by the user from the structure
 * UserAction_t.
 * @param hold Points if the key is hold by user. In tetris it's value is always
 * true
 */

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *gi = update_GameInfo(NULL);
  Figure_and_Info_t *fig = update_Figure(NULL);
  if (hold) {
    switch (action) {
      case Left:
        move_left(gi, fig);
        break;
      case Right:
        move_right(gi, fig);
        break;
      case Down:
        move_down(gi, fig);
        break;
      case Action:
        rotate_fig(gi, fig);
        break;
      case Start:
        if (fig->status == GAME_OVER) {
          fig->status = START_GAME;
        }
        break;
      case Pause:
        fig->status = set_pause_status(gi);
        break;
      case Terminate:
        fig->status = EXIT_GAME;
        break;
      case Up:
        break;
    }
  }
}

/** @brief The function reflects changes in the game after a key is pressed.
 *
 * The function moves the figure to the down if the number of game ticks has
 * reached the limit value. If the blocks of the figure have reached the bottom
 * border or are in contact with the blocks of the field, then the function
 * transfers the blocks of the figure to the field, creates a new figure, and
 * processes the filled lines of the field. Changes the game status if there are
 * blocks in the top line of the field.
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
 *
 */

void game_step(GameInfo_t *gi, Figure_and_Info_t *fig) {
  if (fig->ticks_left >= (MAX_TICKS - gi->speed * 6)) {
    move_down(gi, fig);
    fig->ticks_left = 0;
  } else {
    fig->ticks_left++;
  }

  if (attaching(gi, fig)) {
    write_fig_in_field(gi, fig);
    spawn_figure(fig, gi);
    are_the_lines_filled(gi);
  }
  if (is_rich_high_board(gi)) {
    fig->status = GAME_OVER;
  }
}

/** @brief Function takes record.
 *
 * The function opens a file containing a record about the record and transfers
 * it to the game. If the file is empty, pass 0 as the record. If the file does
 * not exist, returns an error code.
 *
 * The function takes no parameters.
 *
 * @return record or an error code.
 *
 */

int get_score() {
  FILE *fp;
  int record = 0;
  if ((fp = fopen(DATA_DIR, "r")) == NULL) {
    record = ERROR_GAME;
  } else {
    fscanf(fp, "%d", &record);
  }
  if (fp != NULL) fclose(fp);
  return record;
}

/** @brief The function saves the record.
 *
 * The function writes the current record to a file. If the write fails, it
 * returns an error code.
 *
 * @param record contains information about the record.
 *
 * @return an error code or status of game.
 *
 */

int record_write(int record) {
  FILE *fp;
  int status = GAME_OVER;
  if ((fp = fopen(DATA_DIR, "w")) == NULL) {
    status = ERROR_GAME;
  } else {
    fprintf(fp, "%d", record);
  }
  if (fp != NULL) fclose(fp);
  return status;
}
