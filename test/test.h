#ifndef TEST_H
#define TEST_H

#include <gtest/gtest.h>

#include "../brick_game/snake/model_snake.h"

namespace s21 {

class TestClass {
 public:
  TestClass() {}
  ~TestClass() = default;
  bool test_game_info(s21::Model_Snake const& test_model);
  bool test_snake_(s21::Model_Snake const& test_model);
  bool test_rotate_(s21::Model_Snake const& test_model);
  bool test_move_body_1(s21::Model_Snake const& test_model);
  bool test_move_body_2(s21::Model_Snake& test_model);
  bool test_move_body_3(s21::Model_Snake& test_model);
  bool test_move_body_4(s21::Model_Snake& test_model);
  bool test_move_head_1(s21::Model_Snake& test_model);
  bool test_move_head_2(s21::Model_Snake& test_model);
  bool test_process_score(s21::Model_Snake& test_model);
  int test_set_pause(s21::Model_Snake& test_model);
  bool test_mod_get_gameinfo_t(GameInfo_t* game_info);
  void test_set_apple(s21::Model_Snake& test_model);
  int test_get_rotate_(s21::Model_Snake& test_model);
  bool test_updateCurrentState(s21::Model_Snake const& test_model);
  bool test_check_collision(s21::Model_Snake& test_model);
};

}  // namespace s21

#endif  // TEST_H