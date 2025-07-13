#ifndef CONTROLLER_SNAKE_H
#define CONTROLLER_SNAKE_H

#include "../../brick_game/snake/model_snake.h"
#include "../../brick_game/tetris/backend.h"

namespace s21 {

/**
 * An abstract class that provides the relationship between
 * the view and the business logic.
 *
 */

class Controller {
 public:
  Controller() {}
  virtual ~Controller() = 0;
  virtual GameInfo_t* get_gameinfo_t() const = 0;
  virtual void get_Input(UserAction_t action) = 0;
  virtual void move_model() = 0;
  virtual int con_get_status() const = 0;
};

/**
 * An class that provides the relationship between
 * the view and the business logic snake game. The methods of
 * this class mainly call methods of the class Model_Snake that
 * contain the logic of the snake game, providing communication
 * with the user interface.
 *
 */

class Controller_snake : public Controller {
 public:
  Controller_snake(Model_Snake* model);
  ~Controller_snake() override;
  GameInfo_t* get_gameinfo_t() const override;
  void get_Input(UserAction_t action) override;
  void move_model() override;
  int con_get_status() const override;

 private:
  Model_Snake* model_;  ///< object of class with business logic.
};

/**
 * An class that provides the relationship between
 * the view and the business logic tetris game. The methods of
 * this class mainly call functions that contain the logic of
 * the tetris game, providing communication
 * with the user interface.
 *
 */

class Controller_tetris : public Controller {
 public:
  Controller_tetris();
  ~Controller_tetris();
  GameInfo_t* get_gameinfo_t() const;
  void get_Input(UserAction_t action);
  void move_model();
  int con_get_status() const;
  void process_changes();

 private:
  GameInfo_t* gi;          ///< structure with game data
  Figure_and_Info_t* fig;  ///< structure with game data
};
}  // namespace s21

#endif  // CONTROLLER_SNAKE_H
