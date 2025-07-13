#ifndef MODEL_SNAKE_H
#define MODEL_SNAKE_H

#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../../brick_game/tetris/structures.h"

#define NO_ACTION 10
#define MAX_LEVEL 10
#define SCALE_POINT 5
#define MAX_TICKS 100
#define KEY_ESC 27
#define RECORD_DIR "games/record_snake.txt"

namespace s21 {

/**
 *  Class containing coordinates and methods working with them
 *
 */

class Node {
 public:
  Node();
  explicit Node(int x, int y);
  Node(const Node& other);
  Node(Node&& other);
  Node& operator=(Node const& other);
  Node& operator=(Node&& other);
  ~Node() = default;
  bool operator==(const Node& other) const;
  int get_y() const;
  int get_x() const;
  void set_y(int y);
  void set_x(int x);

 private:
  int x_;  ///< x coordinate of a point on the field
  int y_;  ///< y coordinate of a point on the field
};

/** @brief Main class for implementing business logic
 *
 * The class contains a structure with the coordinates
 * of the apple, a vector containing the body of the snake,
 * and a structure with information about the state of the game.
 * And also methods that process user input, implementing the
 * main mechanics of the game: the movement of the snake,
 * the appearance of an apple, the increase in the length of
 * the snake after "eating" the apple, scoring, reflecting
 * changes in a special structure.
 *
 */

class Model_Snake {
 public:
  Model_Snake();
  ~Model_Snake();
  GameInfo_t* mod_get_gameinfo_t() const;
  void userInput(UserAction_t action, bool hold);
  GameInfo_t updateCurrentState();
  GameInfo_t* initial_game();
  void move_body();
  int get_status() const;
  void set_status(int status);
  void set_pause(int status);
  int get_speed() const;
  void restart();
  friend class TestClass;

 private:
  Node apple_;  ///< structure containing the coordinates of an apple
  std::vector<Node>* snake_;  ///< vector with coordinates of the snake's body
  GameInfo_t* gameinfo_t_;    ///< structure for rendering in the view
  int status_;                ///< code of one of the possible game statuses
  int rotate_;                ///< direction of movement of the snake

  void plant_apple(std::vector<Node> const* check_body);
  void move_head(Node* check_head) const;
  void process_score();
  void rotate_left();
  void rotate_right();
  void rotate_down();
  void rotate_up();
  bool check_collision(std::vector<Node>* check_body, Node check_head) const;
  bool check_for_eating(Node check_head) const;
  int get_record() const;
  void write_record(int record) const;
  void free_gameinfo_t_();
};

}  // namespace s21

#endif  // MODEL_SNAKE_H
