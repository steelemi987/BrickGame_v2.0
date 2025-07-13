#include "view.h"

/** @brief Constructor with parametrs
 *
 * The main game structure is transferred to the private field. Memory
 * is allocated for the necessary widgets. The widget content is set
 * as text. The visual design is set.
 *
 * @param parent parent widget
 *
 * @param gameinfo_t A structure containing information about the game (field
 * state, next piece, current score, record score, current level, current game
 * speed, pause).
 *
 */

s21::Field::Field(QWidget* parent, GameInfo_t* gameinfo_t)
    : QWidget{parent}, gameinfo_t_(gameinfo_t) {
  start_text = new QLabel("PRESS <R> TO START GAME", this);
  start_text->setGeometry(10, 70, 380, LABEL_H);
  game_over_text = new QLabel("GAME OVER", this);
  game_over_text->setGeometry(10, 70, 380, LABEL_H);
  game_over_text->hide();
  pause_text = new QLabel("GAME ON PAUSE, PRESS P TO CONTINUE", this);
  pause_text->setGeometry(10, 70, 380, LABEL_H);
  pause_text->hide();
  win_text = new QLabel("CONGRATULATIONS ON YOUR VICTORY!!!", this);
  win_text->setGeometry(10, 70, 380, LABEL_H);
  win_text->hide();
  this->setStyleSheet(
      "QLabel {"
      "border-style: solid;"
      "border-width: 1px;"
      "border-color: black; "
      "background-color:white;"
      "}");
}

/**
 * Class destructor. Frees resources allocated during the process.
 */

s21::Field::~Field() {
  delete start_text;
  delete game_over_text;
  delete pause_text;
  delete win_text;
}

/** @brief Method for drawing
 *
 * The method draws the game field. Draws a grid using vertical and horizontal
 * dotted lines. Draws colored blocks on the fields according to their
 * coordinates stored in a special structure of the private field of the class
 * itself.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Field::paintEvent(QPaintEvent*) {
  QPen pen;
  pen.setStyle(Qt::DotLine);
  pen.setWidth(1);
  pen.setColor("black");

  QPainter painter;
  painter.begin(this);
  painter.setPen(pen);
  for (int i = 0; i <= 10; i++) {
    painter.drawLine(PIXEL_SIZE * i, 0, PIXEL_SIZE * i, FIELD_H);
  }
  for (int i = 0; i <= 20; i++) {
    painter.drawLine(0, PIXEL_SIZE * i, FIELD_W, PIXEL_SIZE * i);
  }
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      if (gameinfo_t_->field[i][j] == 1) {
        painter.fillRect(j * 40, i * 40, 40, 40, QBrush{"#2980b9"});
      }
      if (gameinfo_t_->field[i][j] == 2) {
        painter.fillRect(j * 40, i * 40, 40, 40, QBrush{"limegreen"});
      }
    }
  }
  painter.end();
}

/**
 * Hides the text widget.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Field::start_text_hide() const { start_text->hide(); }

/**
 * Shows the text widget.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Field::game_over_text_show() const { game_over_text->show(); }

/**
 * Shows the text widget.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Field::win_text_show() const { win_text->show(); }

/**
 * Shows the text widget.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Field::pause_text_show() const { pause_text->show(); }

/**
 * Hides the text widget.
 *
 * Has no specific values to be returned.
 *
 */

void s21::Field::pause_text_hide() const { pause_text->hide(); }

/** @brief Constructor with parametrs.
 *
 * The main game structure is transferred to the private field. A pointer to the
 * controller is passed to a private field. Memory is allocated for the
 * necessary widgets. The widget content is set as text. The visual design is
 * set. Connects the timer signal to the corresponding slot.
 *
 * @param parent parent widget
 *
 * @param controller pointer to controller for communication with business logic
 *
 */

s21::View::View(QWidget* parent, Controller* controller)
    : QWidget{parent},
      controller_(controller),
      gameinfo_t_(controller_->get_gameinfo_t()) {
  create_number();
  field = new Field(this, gameinfo_t_);
  field->setGeometry(10, 10, 401, 801);
  create_text();
  this->setStyleSheet(
      "QLabel {"
      "background-color:white;"
      "border-style: solid;"
      "border-width: 1px;"
      "border-color: black; "
      "}");
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(time_to_move()));
}

/**
 * Class destructor. Frees resources allocated during the process.
 */

s21::View::~View() {
  delete high_score_num;
  delete score_num;
  delete level_num;
  delete speed_num;
  delete high_score_text;
  delete score_text;
  delete level_text;
  delete speed_text;
  delete next_figure_text;
  delete timer;
  delete field;
  delete controller_;
}

/** @brief The method creates widgets.
 *
 * Widgets created in the method output digital information in the form of a
 * dial. Memory is allocated for the necessary widgets. The visual design is
 * set.
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::create_number() {
  high_score_num = new QLCDNumber(this);
  high_score_num->setSegmentStyle(QLCDNumber::Flat);
  high_score_num->setGeometry(NUMB_X, 10, NUMB_W, NUMB_H);
  score_num = new QLCDNumber(this);
  score_num->setSegmentStyle(QLCDNumber::Flat);
  score_num->setGeometry(NUMB_X, 70, NUMB_W, NUMB_H);
  level_num = new QLCDNumber(this);
  level_num->setSegmentStyle(QLCDNumber::Flat);
  level_num->setGeometry(NUMB_X, 130, NUMB_W, NUMB_H);
  speed_num = new QLCDNumber(this);
  speed_num->setSegmentStyle(QLCDNumber::Flat);
  speed_num->setGeometry(NUMB_X, 190, NUMB_W, NUMB_H);
}

/** @brief The method creates widgets.
 *
 * Rectangles with text are created. Memory is allocated for the necessary
 * widgets. The widget content is set as text. The visual design is set.
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::create_text() {
  high_score_text = new QLabel("HIGH SCORE", this);
  high_score_text->setGeometry(LABEL_X, 10, LABEL_W, LABEL_H);
  score_text = new QLabel("SCORE", this);
  score_text->setGeometry(LABEL_X, 70, LABEL_W, LABEL_H);
  level_text = new QLabel("LEVEL", this);
  level_text->setGeometry(LABEL_X, 130, LABEL_W, LABEL_H);
  speed_text = new QLabel("SPEED", this);
  speed_text->setGeometry(LABEL_X, 190, LABEL_W, LABEL_H);
  next_figure_text = new QLabel("NEXT FIGURE", this);
  next_figure_text->setGeometry(LABEL_X, 250, LABEL_W, LABEL_H);
  if (gameinfo_t_->next == nullptr) {
    next_figure_text->hide();
  }
}

/** @brief Method for drawing
 *
 * The method draws the field with figure.
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::paintEvent(QPaintEvent*) {
  QPen pen;
  pen.setStyle(Qt::DotLine);
  pen.setWidth(1);
  pen.setColor("grey");

  QPainter painter;
  painter.begin(this);
  painter.setPen(pen);
  if (gameinfo_t_->next != nullptr) {
    paint_next_figure(&painter);
  }
  painter.end();
}

/** @brief The method processes user input.
 *
 * The method captures the user pressing buttons. Translates the button code
 * into the structure UserAction_t button code. When the corresponding buttons
 * are pressed, it displays messages, starts the timer, pauses the game, and
 * closes the current game window. Transfers the button code to the controller
 * for further processing in the business logic code. The received information
 * is output to the interface, updating the game state.
 *
 * @param e code of the button pressed by the user
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::keyPressEvent(QKeyEvent* e) {
  UserAction_t action = (UserAction_t)NO_ACTION;
  switch (e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
      action = Up;
      break;
    case Qt::Key_Down:
    case Qt::Key_S:
      action = Down;
      break;
    case Qt::Key_Left:
    case Qt::Key_A:
      action = Left;
      break;
    case Qt::Key_Right:
    case Qt::Key_D:
      action = Right;
      break;
    case Qt::Key_R:
      action = Start;
      if (controller_->con_get_status() == START_GAME) {
        field->start_text_hide();
        timer->start(START_DELAY);
      }
      break;
    case Qt::Key_P:
      action = Pause;
      if (controller_->con_get_status() == MOVE) {
        pause_timer();
      } else if (controller_->con_get_status() == PAUSE_GAME) {
        restart_timer();
      }
      break;
    case Qt::Key_Escape:
      action = Terminate;
      this->close();
      break;
    case Qt::Key_Space:
      action = Action;
      break;
  }
  controller_->get_Input(action);
  process_model();
}

/**
 * The method is a slot that is triggered when the timer expires. This causes
 * the controller method to be called, which sets the game in motion. The
 * received information is output to the interface, updating the game state.
 * The timer is set according to the current level of the game.
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::time_to_move() {
  controller_->move_model();
  process_model();
  timer->setInterval(START_DELAY - gameinfo_t_->speed * SCALE_DELAY);
}

/**
 * The method stops the timer.
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::pause_timer() const {
  int remain_time = timer->remainingTime();
  timer->stop();
  timer->setInterval(remain_time);
}

/**
 * The method starts a timer.
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::restart_timer() const { timer->start(); }

/** @brief The method displays the following figure.
 *
 * The method draws a field for a figure in the form of a grid of dotted
 * lines. Fills this field with blocks that form figures.
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::paint_next_figure(QPainter* painter) {
  for (int i = 0; i <= 4; i++) {
    painter->drawLine(PIXEL_SIZE * i + LABEL_X, 310, PIXEL_SIZE * i + LABEL_X,
                      470);
  }
  for (int i = 0; i <= 4; i++) {
    painter->drawLine(LABEL_X, PIXEL_SIZE * i + 310, LABEL_X + 160,
                      PIXEL_SIZE * i + 310);
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (gameinfo_t_->next[i][j] == 1) {
        painter->fillRect(j * PIXEL_SIZE + LABEL_X, i * PIXEL_SIZE + 310,
                          PIXEL_SIZE, PIXEL_SIZE, QBrush{"#2980b9"});
      }
    }
  }
}

/**
 * The method displays information obtained from the business model
 * and manages in-game messages. Calls the method responsible for
 * drawing the game field.
 *
 * Has no specific values to be returned.
 *
 */

void s21::View::process_model() {
  if (controller_->con_get_status() == GAME_OVER) {
    field->game_over_text_show();
  }
  if (controller_->con_get_status() == WIN_GAME) {
    field->win_text_show();
    pause_timer();
  }
  if (controller_->con_get_status() == PAUSE_GAME) {
    field->pause_text_show();
  } else {
    field->pause_text_hide();
  }
  repaint();
  high_score_num->display(gameinfo_t_->high_score);
  score_num->display(gameinfo_t_->score);
  level_num->display(gameinfo_t_->level);
  speed_num->display(gameinfo_t_->speed);
}

/** @brief Constructor with parametr.
 *
 * Memory is allocated for the necessary widgets. The visual design
 * is set. The corresponding slots are connected to the buttons.
 *
 */

s21::MainWindow::MainWindow(QWidget* parent) : QMainWindow{parent} {
  this->setWindowTitle("BrickGame");
  this->setFixedSize(300, 200);
  setStyleSheet("background-color:grey;");
  central = new QWidget;
  layout = new QVBoxLayout(central);
  snake_btn_ = new QPushButton("Snake");
  tetris_btn_ = new QPushButton("Tetris");
  snake_btn_->setStyleSheet("background-color: white");
  tetris_btn_->setStyleSheet("background-color: white");
  layout->addWidget(snake_btn_);
  layout->addWidget(tetris_btn_);
  setCentralWidget(central);
  connect(snake_btn_, SIGNAL(clicked()), this, SLOT(load_snake()));
  connect(tetris_btn_, SIGNAL(clicked()), this, SLOT(load_tetris()));
}

/**
 * Class destructor. Frees resources allocated during the process.
 */

s21::MainWindow::~MainWindow() {
  delete tetris_btn_;
  delete snake_btn_;
  delete layout;
  delete central;
}

/** @brief The method launches a window with the game.
 *
 * The method creates a class object containing business logic,
 * a controller class object, and a presentation class object.
 * Sets up the game window.
 *
 * Has no specific values to be returned.
 *
 */

void s21::MainWindow::load_snake() {
  s21::Model_Snake* Model = new s21::Model_Snake();
  s21::Controller_snake* Contr_ = new s21::Controller_snake(Model);
  game = new s21::View(nullptr, Contr_);
  game->setWindowTitle("Snake");
  game->setFixedSize(720, 855);
  game->setAttribute(Qt::WA_DeleteOnClose);
  game->setWindowModality(Qt::WindowModality::WindowModal);
  game->show();
}

/** @brief The method launches a window with the game.
 *
 * The method creates a controller class object, and a
 * presentation class object. Sets up the game window.
 *
 * Has no specific values to be returned.
 *
 */

void s21::MainWindow::load_tetris() {
  s21::Controller_tetris* Contr_ = new s21::Controller_tetris();
  game = new s21::View(nullptr, Contr_);
  game->setWindowTitle("Tetris");
  game->setFixedSize(720, 855);
  game->setAttribute(Qt::WA_DeleteOnClose);
  game->setWindowModality(Qt::WindowModality::WindowModal);
  game->show();
}
