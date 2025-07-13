#include "test.h"

TEST(Constructor, Without_param) {
  s21::Node A;
  EXPECT_EQ(A.get_y(), 0);
  EXPECT_EQ(A.get_x(), 0);
}

TEST(Constructor, With_param) {
  s21::Node A(1, 3);
  EXPECT_EQ(A.get_x(), 1);
  EXPECT_EQ(A.get_y(), 3);
}

TEST(Constructor, Copy) {
  s21::Node B(3, 3);
  s21::Node A(B);
  EXPECT_EQ(A.get_x(), 3);
  EXPECT_EQ(A.get_y(), 3);
}

TEST(Constructor, Move) {
  s21::Node B(3, 3);
  s21::Node A((std::move(B)));
  EXPECT_EQ(A.get_x(), 3);
  EXPECT_EQ(A.get_y(), 3);
}

TEST(Operator, Copy) {
  s21::Node B(2, 2);
  s21::Node A(3, 3);
  A = B;
  EXPECT_EQ(A.get_x(), 2);
  EXPECT_EQ(A.get_y(), 2);
}

TEST(Operator, Move) {
  s21::Node B(2, 2);
  s21::Node A(3, 3);
  A = std::move(B);
  EXPECT_EQ(A.get_x(), 2);
  EXPECT_EQ(A.get_y(), 2);
  EXPECT_EQ(B.get_x(), 0);
  EXPECT_EQ(B.get_y(), 0);
}

TEST(Operator, Equal_1) {
  s21::Node B(2, 2);
  s21::Node A(3, 3);
  EXPECT_FALSE(A == B);
}

TEST(Operator, Equal_2) {
  s21::Node B(2, 2);
  s21::Node A(2, 2);
  EXPECT_TRUE(A == B);
}

TEST(Method, set_y) {
  s21::Node A(2, 2);
  A.set_y(0);
  EXPECT_EQ(A.get_y(), 0);
}

TEST(Method, set_x) {
  s21::Node A(2, 2);
  A.set_x(0);
  EXPECT_EQ(A.get_x(), 0);
}

TEST(Constructor, Standard) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  EXPECT_TRUE(test.test_game_info(test_model));
  EXPECT_TRUE(test.test_snake_(test_model));
  EXPECT_TRUE(test_model.get_status() == START_GAME);
  EXPECT_TRUE(test.test_rotate_(test_model));
}

TEST(Method, Move_body_1) {
  s21::Model_Snake test_model;
  test_model.move_body();
  s21::TestClass test;
  EXPECT_TRUE(test.test_move_body_1(test_model));
}

TEST(Method, Move_body_2) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  EXPECT_TRUE(test.test_move_body_2(test_model));
}

TEST(Method, Move_body_3) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  EXPECT_TRUE(test.test_move_body_3(test_model));
}

TEST(Method, Move_body_4) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  EXPECT_TRUE(test.test_move_body_4(test_model));
}

TEST(Method, Move_head_1) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  EXPECT_TRUE(test.test_move_head_1(test_model));
}

TEST(Method, Move_head_2) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  EXPECT_TRUE(test.test_move_head_2(test_model));
}

TEST(Method, Process_score) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  EXPECT_TRUE(test.test_process_score(test_model));
}

TEST(Method, Get_status) {
  s21::Model_Snake test_model;
  EXPECT_EQ(test_model.get_status(), START_GAME);
}

TEST(Method, Set_status) {
  s21::Model_Snake test_model;
  test_model.set_status(2);
  EXPECT_EQ(test_model.get_status(), 2);
}

TEST(Method, Set_pause) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  test_model.set_pause(2);
  EXPECT_EQ(test.test_set_pause(test_model), 2);
}

TEST(Method, Get_speed) {
  s21::Model_Snake test_model;
  EXPECT_EQ(test_model.get_speed(), 0);
}

TEST(Method, Restart) {
  s21::Model_Snake test_model;
  test_model.restart();
  s21::TestClass test;
  EXPECT_TRUE(test.test_game_info(test_model));
  EXPECT_TRUE(test.test_snake_(test_model));
  EXPECT_TRUE(test_model.get_status() == MOVE);
  EXPECT_TRUE(test.test_rotate_(test_model));
}

TEST(Method, Mod_get_gameinfo_t) {
  s21::Model_Snake test_model;
  GameInfo_t* game_info = test_model.mod_get_gameinfo_t();
  s21::TestClass test;
  EXPECT_TRUE(test.test_mod_get_gameinfo_t(game_info));
}

TEST(Method, Test_rotate_left) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  test.test_set_apple(test_model);
  test_model.userInput(Left, true);
  EXPECT_EQ(test.test_get_rotate_(test_model), Left);
}

TEST(Method, Test_rotate_right) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  test.test_set_apple(test_model);
  test_model.userInput(Up, true);
  test_model.move_body();
  test_model.userInput(Right, true);
  EXPECT_EQ(test.test_get_rotate_(test_model), Right);
}

TEST(Method, Test_rotate_down) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  test.test_set_apple(test_model);
  test_model.userInput(Down, true);
  EXPECT_EQ(test.test_get_rotate_(test_model), Down);
}

TEST(Method, Test_rotate_up) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  test.test_set_apple(test_model);
  test_model.userInput(Up, true);
  EXPECT_EQ(test.test_get_rotate_(test_model), Up);
}

TEST(Method, Test_userInput_1) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  test.test_set_apple(test_model);
  test_model.userInput(Action, true);
  EXPECT_TRUE(test.test_move_body_1(test_model));
}

TEST(Method, Test_userInput_2) {
  s21::Model_Snake test_model;
  test_model.userInput(Start, true);
  EXPECT_EQ(test_model.get_status(), MOVE);
}

TEST(Method, Test_userInput_3) {
  s21::Model_Snake test_model;
  test_model.userInput(Terminate, true);
  EXPECT_EQ(test_model.get_status(), EXIT_GAME);
}

TEST(Method, Test_userInput_4) {
  s21::Model_Snake test_model;
  test_model.set_status(MOVE);
  test_model.userInput(Pause, true);
  EXPECT_EQ(test_model.get_status(), PAUSE_GAME);
}

TEST(Method, Test_userInput_5) {
  s21::Model_Snake test_model;
  test_model.set_status(PAUSE_GAME);
  test_model.userInput(Pause, true);
  EXPECT_EQ(test_model.get_status(), MOVE);
}

TEST(Method, Test_updateCurrentState) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  test.test_set_apple(test_model);
  test_model.updateCurrentState();
  EXPECT_TRUE(test.test_updateCurrentState(test_model));
}

TEST(Method, Test_check_collision) {
  s21::Model_Snake test_model;
  s21::TestClass test;
  EXPECT_TRUE(test.test_check_collision(test_model));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

bool s21::TestClass::test_game_info(s21::Model_Snake const& test_model) {
  bool res = true;
  if (test_model.gameinfo_t_->field == nullptr) {
    res = false;
  }
  if (test_model.gameinfo_t_->next != nullptr) {
    res = false;
  }
  if (test_model.gameinfo_t_->score != 0) {
    res = false;
  }
  if (test_model.gameinfo_t_->level != 0) {
    res = false;
  }
  if (test_model.gameinfo_t_->speed != 0) {
    res = false;
  }
  if (test_model.gameinfo_t_->pause != 0) {
    res = false;
  }
  return res;
}

bool s21::TestClass::test_snake_(s21::Model_Snake const& test_model) {
  bool res = true;
  if (test_model.snake_->size() != 4) {
    res = false;
  }
  auto iter{test_model.snake_->begin()};
  if (iter->get_x() != 3 || iter->get_y() != 9) {
    res = false;
  }
  iter++;
  if (iter->get_x() != 4 || iter->get_y() != 9) {
    res = false;
  }
  iter++;
  if (iter->get_x() != 5 || iter->get_y() != 9) {
    res = false;
  }
  iter++;
  if (iter->get_x() != 6 || iter->get_y() != 9) {
    res = false;
  }

  return res;
}

bool s21::TestClass::test_rotate_(s21::Model_Snake const& test_model) {
  bool res = true;
  if (test_model.rotate_ != Left) {
    res = false;
  }
  return res;
}

bool s21::TestClass::test_move_body_1(s21::Model_Snake const& test_model) {
  bool res = true;
  auto iter{test_model.snake_->begin()};
  if (iter->get_x() != 2 || iter->get_y() != 9) {
    res = false;
  }
  iter++;
  if (iter->get_x() != 3 || iter->get_y() != 9) {
    res = false;
  }
  iter++;
  if (iter->get_x() != 4 || iter->get_y() != 9) {
    res = false;
  }
  iter++;
  if (iter->get_x() != 5 || iter->get_y() != 9) {
    res = false;
  }
  return res;
}

bool s21::TestClass::test_move_body_2(s21::Model_Snake& test_model) {
  bool res = true;
  test_model.apple_ = Node(0, 0);
  for (int i = 0; i < 4; i++) {
    test_model.move_body();
  }
  if (test_model.status_ != GAME_OVER) {
    res = false;
  }
  return res;
}

bool s21::TestClass::test_move_body_3(s21::Model_Snake& test_model) {
  bool res = true;
  test_model.apple_ = Node(2, 9);
  test_model.move_body();
  if (test_model.snake_->size() != 5) {
    res = false;
  }
  int x = 2;
  for (auto iter{test_model.snake_->begin()}; iter != test_model.snake_->end();
       iter++) {
    if (!(*iter == Node(x, 9))) {
      res = false;
    }
    x++;
  }
  return res;
}

bool s21::TestClass::test_move_body_4(s21::Model_Snake& test_model) {
  bool res = true;
  delete test_model.snake_;
  test_model.snake_ = new std::vector<Node>(190);
  int x = 0;
  for (auto iter{test_model.snake_->begin()}; iter != test_model.snake_->end();
       iter++) {
    *iter = Node(x % 10, 1 + x / 10);
    x++;
  }
  for (int i = 0; i < 9; i++) {
    test_model.snake_->push_back(Node(i, 0));
  }
  test_model.snake_->front() = Node(8, 0);
  test_model.snake_->back() = Node(0, 1);
  test_model.plant_apple(test_model.snake_);
  test_model.rotate_ = Right;
  test_model.move_body();
  if (test_model.status_ != WIN_GAME) {
    res = false;
  }
  return res;
}

bool s21::TestClass::test_move_head_1(s21::Model_Snake& test_model) {
  bool res = true;
  test_model.rotate_ = Down;
  Node check_head = Node(3, 3);
  test_model.move_head(&check_head);
  if (!(check_head == Node(3, 4))) {
    res = false;
  }
  return res;
}

bool s21::TestClass::test_move_head_2(s21::Model_Snake& test_model) {
  bool res = true;
  test_model.rotate_ = Up;
  Node check_head = Node(3, 3);
  test_model.move_head(&check_head);
  if (!(check_head == Node(3, 2))) {
    res = false;
  }
  return res;
}

bool s21::TestClass::test_process_score(s21::Model_Snake& test_model) {
  bool res = true;
  test_model.gameinfo_t_->score = 5;
  test_model.gameinfo_t_->high_score = 0;
  test_model.process_score();
  if (test_model.gameinfo_t_->high_score != 6) {
    res = false;
  }
  if (test_model.gameinfo_t_->level != 1) {
    res = false;
  }
  if (test_model.gameinfo_t_->speed != 1) {
    res = false;
  }
  return res;
}

int s21::TestClass::test_set_pause(s21::Model_Snake& test_model) {
  return test_model.gameinfo_t_->pause;
}

bool s21::TestClass::test_mod_get_gameinfo_t(GameInfo_t* game_info) {
  bool res = true;
  if (game_info->field == nullptr) {
    res = false;
  }
  if (game_info->next != nullptr) {
    res = false;
  }
  if (game_info->score != 0) {
    res = false;
  }
  if (game_info->level != 0) {
    res = false;
  }
  if (game_info->speed != 0) {
    res = false;
  }
  if (game_info->pause != 0) {
    res = false;
  }
  return res;
}

void s21::TestClass::test_set_apple(s21::Model_Snake& test_model) {
  test_model.apple_ = Node(0, 0);
}

int s21::TestClass::test_get_rotate_(s21::Model_Snake& test_model) {
  return test_model.rotate_;
}

bool s21::TestClass::test_updateCurrentState(
    s21::Model_Snake const& test_model) {
  bool res = true;
  if (test_model.gameinfo_t_->field[0][0] != 2) {
    res = false;
  }
  for (int i = 3; i < 7; i++) {
    if (test_model.gameinfo_t_->field[9][i] != 1) {
      res = false;
    }
  }
  return res;
}

bool s21::TestClass::test_check_collision(s21::Model_Snake& test_model) {
  bool res = true;
  std::vector<s21::Node> check_body;
  s21::Node check_head(4, 9);
  check_body.push_back(Node(4, 8));
  check_body.push_back(Node(3, 8));
  check_body.push_back(Node(3, 9));
  check_body.push_back(Node(4, 9));
  check_body.push_back(Node(5, 9));
  res = test_model.check_collision(&check_body, check_head);
  return res;
}