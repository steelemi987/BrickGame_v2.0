#include "model_snake.h"

/**
 * Default constructor. initializes variables to zero.
 *
 */

s21::Node::Node() : x_(0), y_(0) {}

/**
 * Constructor with parameters. Initializes variables with appropriate values.
 *
 * Has no specific values to be returned.
 *
 * @param x x coordinate
 *
 * @param y y coordinate
 *
 */

s21::Node::Node(int x, int y) : x_(x), y_(y) {}

/**
 * Copy Constructor. Initializes variables with values ​​from another
 * object.
 *
 * Has no specific values to be returned.
 *
 * @param other another object.
 *
 */

s21::Node::Node(const Node& other) : x_(other.x_), y_(other.y_) {}

/**
 * Copy constructor. Initializes variables with values ​​from another
 * object.
 *
 * Has no specific values to be returned.
 *
 * @param other another object.
 *
 */

s21::Node::Node(Node&& other) : x_(other.x_), y_(other.y_) {
  other.x_ = 0;
  other.y_ = 0;
}

/**
 * Overloading the assignment operator with copy. Assigns variables the
 * corresponding value from another object.
 *
 * Has no specific values to be returned.
 *
 * @param other another object.
 *
 */

s21::Node& s21::Node::operator=(Node const& other) {
  x_ = other.x_;
  y_ = other.y_;
  return *this;
}

/**
 * Overloading the assignment operator with moving. Assigns variables the
 * corresponding value from another object.
 *
 * Has no specific values to be returned.
 *
 * @param other another object.
 *
 */

s21::Node& s21::Node::operator=(Node&& other) {
  x_ = other.x_;
  y_ = other.y_;
  other.x_ = 0;
  other.y_ = 0;
  return *this;
}

/**
 * Overloading the comparison operator. Compares the variables of one
 * object with the corresponding variables of another object.
 *
 * @param other another object.
 *
 * @return comparison result. If all variables are equal then the result
 * is true, otherwise false.
 *
 */

bool s21::Node::operator==(const Node& other) const {
  bool res = false;
  if (this->x_ == other.x_ && this->y_ == other.y_) {
    res = true;
  }
  return res;
}

/**
 * Provides access to the variable y_.
 *
 * @return variable value y_.
 *
 */

int s21::Node::get_y() const { return y_; }

/**
 * Provides access to the variable x_.
 *
 * @return variable value x_.
 *
 */

int s21::Node::get_x() const { return x_; }

/**
 * Provides access to the variable y_.
 *
 * Has no specific values to be returned.
 *
 * @param y the value passed to the variable y_ of the object.
 *
 */

void s21::Node::set_y(int y) { y_ = y; }

/**
 * Provides access to the variable x_.
 *
 * Has no specific values to be returned.
 *
 * @param y the value passed to the variable x_ of the object.
 *
 */

void s21::Node::set_x(int x) { x_ = x; }

/**
 * Object constructor. Fills in all the fields necessary to start the game.
 *
 */

s21::Model_Snake::Model_Snake()
    : gameinfo_t_(initial_game()), status_(START_GAME), rotate_(Left) {
  updateCurrentState();
}

/**
 * Class destructor. Frees resources allocated during the process.
 */

s21::Model_Snake::~Model_Snake() {
  free_gameinfo_t_();
  delete snake_;
}

/** @brief Initializes the game.
 *
 * Allocates memory for the main structure of the game. Fills the main
 * structure with initial data, gets information about the record from
 * the text document. Allocates memory for the vector from the base
 * structures that stores the coordinates of the snake's body,
 * initializes it with the initial coordinates. Sets the coordinates
 * of the apple.
 *
 * @return Current state of main game structure.
 */

GameInfo_t* s21::Model_Snake::initial_game() {
  GameInfo_t* game_info_init = new GameInfo_t;
  game_info_init->field = new int* [20] {};
  for (int i = 0; i < 20; i++) {
    game_info_init->field[i] = new int[10]{};
  }
  game_info_init->next = nullptr;
  game_info_init->score = 0;
  game_info_init->high_score = get_record();
  game_info_init->level = 0;
  game_info_init->speed = 0;
  game_info_init->pause = 0;

  snake_ = new std::vector<Node>(4);
  int x = 3;
  for (auto iter{snake_->begin()}; iter != snake_->end(); iter++) {
    *iter = Node(x, 9);
    x++;
  }

  plant_apple(snake_);
  return game_info_init;
}

/** @brief The method is responsible for the movement of the snake.
 *
 * The method creates a buffer vector that reflects the next step
 * of the game. This vector is checked for going beyond the field
 * boundary. Then it is checked for being eaten, if the apple is
 * eaten by the snake's head, the vector increases its size by one
 * element with the corresponding coordinates, a new apple is generated,
 * and the points are recalculated. At the end of the method, the
 * buffer vector is written to the vector snake_.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Model_Snake::move_body() {
  std::vector<Node> check_body = *snake_;
  Node check_head = check_body.front();
  move_head(&check_head);
  if (check_collision(&check_body, check_head)) {
    status_ = GAME_OVER;
  } else {
    if (check_for_eating(check_head)) {
      check_body.push_back(*snake_->rbegin());
      check_body.front() = check_head;
      snake_->push_back(Node());
      if (check_body.size() == 200) {
        status_ = WIN_GAME;
      } else {
        plant_apple(&check_body);
      }
      process_score();
    }
    check_body.front() = check_head;
    auto curr{snake_->begin()};
    for (auto check{check_body.begin()}; check != check_body.end();
         check++, curr++) {
      *curr = *check;
    }
  }
}

/**
 * The method moves the snake's head by changing the coordinates
 * depending on the direction of the snake's movement.
 *
 * Has no specific values to be returned.
 *
 * @param check_head snake head pointer.
 *
 */

void s21::Model_Snake::move_head(Node* check_head) const {
  switch (rotate_) {
    case Left:
      check_head->set_x(check_head->get_x() - 1);
      break;
    case Right:
      check_head->set_x(check_head->get_x() + 1);
      break;
    case Down:
      check_head->set_y(check_head->get_y() + 1);
      break;
    case Up:
      check_head->set_y(check_head->get_y() - 1);
      break;
  }
}

/** @brief The method counts points and level.
 *
 * The method increases the player's current points. Updates the
 * record points and writes them to a file. Updates the speed and
 * level parameter depending on the points received.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Model_Snake::process_score() {
  gameinfo_t_->score++;
  if (gameinfo_t_->score > gameinfo_t_->high_score) {
    gameinfo_t_->high_score = gameinfo_t_->score;
    write_record(gameinfo_t_->high_score);
  }
  int scale = gameinfo_t_->score / SCALE_POINT;
  if (scale <= MAX_LEVEL && scale > gameinfo_t_->level) {
    gameinfo_t_->level = scale;
    gameinfo_t_->speed = scale;
  }
}

/**
 * Provides access to the variable status_.
 *
 * @return variable value status_.
 *
 */

int s21::Model_Snake::get_status() const { return status_; }

/**
 * Provides access to the variable status_.
 *
 * @param status the value passed to the variable status_ of the object.
 *
 */

void s21::Model_Snake::set_status(int status) { status_ = status; }

/**
 * Provides access to the variable pause.
 *
 * @param status the value passed to the variable pause of the object.
 *
 */

void s21::Model_Snake::set_pause(int status) { gameinfo_t_->pause = status; }

/**
 * Provides access to the variable speed.
 *
 * @return variable value speed.
 *
 */

int s21::Model_Snake::get_speed() const { return gameinfo_t_->speed; }

/** @brief Recreates the game.
 *
 * Frees previously allocated resources. Fills the model fields with
 * initial values ​​to start a new game.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Model_Snake::restart() {
  free_gameinfo_t_();
  delete snake_;
  gameinfo_t_ = initial_game();
  status_ = MOVE;
  rotate_ = Left;
}

/**
 * Provides access to the variable gameinfo_t_.
 *
 * @return pointer to structure gameinfo_t_.
 *
 */

GameInfo_t* s21::Model_Snake::mod_get_gameinfo_t() const { return gameinfo_t_; }

/** @brief Method to process user input taken in get_input function
 *
 * The function defines the changes in private variables, vector
 * according to user input placed in action.
 *
 * Has no specific values to be returned.
 *
 * @param action code of the key pressed by the user from the structure
 * UserAction_t.
 *
 * @param hold Points if the key is hold by user. In snake it's value is always
 * true
 */

void s21::Model_Snake::userInput(UserAction_t action, bool hold) {
  if (hold) {
    switch (action) {
      case Left:
        rotate_left();
        break;
      case Right:
        rotate_right();
        break;
      case Down:
        rotate_down();
        break;
      case Up:
        rotate_up();
        break;
      case Action:
        move_body();
        break;
      case Start:
        status_ = MOVE;
        break;
      case Pause:
        if (status_ == MOVE) {
          status_ = PAUSE_GAME;
        } else if (status_ == PAUSE_GAME) {
          status_ = MOVE;
        }
        break;
      case Terminate:
        status_ = EXIT_GAME;
        break;
    }
  }
}

/**
 * The method sets the snake's movement vector to the left if the game rules
 * allow it.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Model_Snake::rotate_left() {
  Node check_head = snake_->front();
  check_head.set_x(check_head.get_x() - 1);
  auto curr{snake_->begin()};
  curr++;
  if (!(check_head == *curr)) {
    rotate_ = Left;
  }
}

/**
 * The method sets the snake's movement vector to the right if the game rules
 * allow it.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Model_Snake::rotate_right() {
  Node check_head = snake_->front();
  check_head.set_x(check_head.get_x() + 1);
  auto curr{snake_->begin()};
  curr++;
  if (!(check_head == *curr)) {
    rotate_ = Right;
  }
}

/**
 * The method sets the snake's movement vector to the down if the game rules
 * allow it.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Model_Snake::rotate_down() {
  Node check_head = snake_->front();
  check_head.set_y(check_head.get_y() + 1);
  auto curr{snake_->begin()};
  curr++;
  if (!(check_head == *curr)) {
    rotate_ = Down;
  }
}

/**
 * The method sets the snake's movement vector to the up if the game rules allow
 * it.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Model_Snake::rotate_up() {
  Node check_head = snake_->front();
  check_head.set_y(check_head.get_y() - 1);
  auto curr{snake_->begin()};
  curr++;
  if (!(check_head == *curr)) {
    rotate_ = Up;
  }
}

/**
 * The method rewrites the apple and the snake's body in the field
 * according to their coordinates. Maintains the current state of
 * the playing field.
 *
 * @return pointer to structure gameinfo_t_.
 *
 */

GameInfo_t s21::Model_Snake::updateCurrentState() {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      gameinfo_t_->field[i][j] = 0;
    }
  }
  gameinfo_t_->field[apple_.get_y()][apple_.get_x()] = 2;

  for (auto iter{snake_->begin()}; iter != snake_->end(); iter++) {
    gameinfo_t_->field[iter->get_y()][iter->get_x()] = 1;
  }
  return *gameinfo_t_;
}

/**
 * The method randomizes the coordinates of the apple by choosing
 * coordinates excluding the coordinates of the snake's body.
 *
 * Has no specific values to be returned.
 *
 * @param check_body The body of the snake, the coordinates of
 * which will not be included in the possible pool for generating
 * the coordinates of the apple.
 *
 */

void s21::Model_Snake::plant_apple(std::vector<Node> const* check_body) {
  int temp_field[20][10] = {{0}};
  for (auto iter{check_body->begin()}; iter != check_body->end(); iter++) {
    temp_field[iter->get_y()][iter->get_x()] = 1;
  }
  std::vector<Node> temp_v;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (temp_field[i][j] == 0) {
        temp_v.push_back(Node(j, i));
      }
    }
  }
  srand(time(NULL));
  apple_ = temp_v[rand() % temp_v.size()];
}

/**
 * The method tells whether the snake's head has eaten the apple.
 *
 * @param check_head snake's head
 *
 * @return true if the snake ate the apple or false if not.
 *
 */

bool s21::Model_Snake::check_for_eating(Node check_head) const {
  bool res = false;
  if (check_head == apple_) {
    res = true;
  }
  return res;
}

/** @brief The method checks the collision of the snake's body with obstacles.
 *
 * The method shifts the coordinates of the snake's body, simulating the snake's
 * movement. Checks the snake's head for going beyond the boundaries of the
 * playing field, collision with the snake's body.
 *
 * @param check_body snake's body
 *
 * @param check_head snake's head
 *
 * @return true if snake's head for going beyond the boundaries of the
 * playing field or collision with the snake's body, false if not.
 *
 */

bool s21::Model_Snake::check_collision(std::vector<Node>* check_body,
                                       Node check_head) const {
  bool res = false;
  auto prev{check_body->rbegin()};
  int i = 1;
  for (auto iter{check_body->rbegin()}; i < (int)check_body->size();
       ++iter, i++) {
    ++prev;
    *iter = Node(*prev);
  }
  int x_head = check_head.get_x();
  int y_head = check_head.get_y();
  if (x_head > 9 || x_head < 0 || y_head > 19 || y_head < 0) {
    res = true;
  }
  auto iter{check_body->begin()};
  iter++;
  for (; iter != check_body->end(); iter++) {
    if (*iter == check_head) {
      res = true;
    }
  }
  return res;
}

/**
 * Reads the highscore stored in a file for display in the game interface.
 *
 * @return highscore.
 *
 */

int s21::Model_Snake::get_record() const {
  int record = 0;
  std::ifstream file(RECORD_DIR);
  if (file.is_open()) {
    file >> record;
  } else {
    throw std::runtime_error("Failed to open file");
  }
  file.close();
  return record;
}

/**
 * The method writes the current highscore to a file for storage
 * and further use between game sessions.
 *
 * Has no specific values to be returned.
 *
 * @param record current highscore
 *
 */

void s21::Model_Snake::write_record(int record) const {
  std::ofstream file(RECORD_DIR);
  if (file.is_open()) {
    file << record;
  } else {
    throw std::runtime_error("Failed to open file");
  }
  file.close();
}

/**
 * The method frees the memory allocated for storing the structure gameinfo_t_.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Model_Snake::free_gameinfo_t_() {
  for (int i = 0; i < 20; i++) {
    delete[] gameinfo_t_->field[i];
  }
  delete[] gameinfo_t_->field;
  delete gameinfo_t_;
}