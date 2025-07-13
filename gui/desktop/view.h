#ifndef VIEW_H
#define VIEW_H

#include <QApplication>
#include <QKeyEvent>
#include <QLCDNumber>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "../../controller/snake/controller_snake.h"

#define FIELD_W 400
#define FIELD_H 800
#define LABEL_X 440
#define LABEL_W 100
#define LABEL_H 50
#define NUMB_X 550
#define NUMB_W 150
#define NUMB_H 50
#define PIXEL_SIZE 40
#define START_DELAY 400
#define SCALE_DELAY 30

namespace s21 {

/**
 * The class represents the main playing field, along which the snake
 * moves and on which the apple is located. The class also has widgets
 * with messages about the game status for the player.
 *
 */

class Field : public QWidget {
  Q_OBJECT

 public:
  explicit Field(QWidget* parent = nullptr, GameInfo_t* gameinfo_t = nullptr);
  ~Field();
  void paintEvent(QPaintEvent* event);
  void start_text_hide() const;
  void game_over_text_show() const;
  void win_text_show() const;
  void pause_text_show() const;
  void pause_text_hide() const;

 private:
  GameInfo_t* gameinfo_t_;  ///< structure for rendering in the view
  QLabel* start_text;       ///< Start Message Widget
  QLabel* game_over_text;   ///< Loss Message Widget
  QLabel* pause_text;       ///< Pause Message Widget
  QLabel* win_text;         ///< Win Message Widget
};

/** @brief The class acts as a View in MVC pattern.
 *
 * The class contains widgets with information about
 * the game for the player, a widget with a game field,
 * a timer with a slot connected to it, which sets the
 * game in motion. The class contains methods for working
 * with user input, for drawing the field and blocks on it.
 *
 */

class View : public QWidget {
  Q_OBJECT
 public:
  explicit View(QWidget* parent = nullptr, Controller* controller = nullptr);
  ~View();
  void keyPressEvent(QKeyEvent* e);
  void paintEvent(QPaintEvent* event);

 private:
  Controller*
      controller_;  ///< Pointer to class for communication with business logic
  GameInfo_t* gameinfo_t_;  ///< structure with game data
  QLCDNumber*
      high_score_num;     ///< Pointer to the widget displaying the high_score
  QLCDNumber* score_num;  ///< Pointer to the widget displaying the score
  QLCDNumber* level_num;  ///< Pointer to the widget displaying the level
  QLCDNumber* speed_num;  ///< Pointer to the widget displaying the speed
  Field* field;  ///< Pointer to a widget displaying the game field and in-game
                 ///< messages
  QLabel* high_score_text;  ///< Pointer to the widget displaying the
                            ///< corresponding text
  QLabel*
      score_text;  ///< Pointer to the widget displaying the corresponding text
  QLabel*
      level_text;  ///< Pointer to the widget displaying the corresponding text
  QLabel*
      speed_text;  ///< Pointer to the widget displaying the corresponding text
  QLabel* next_figure_text;  ///< Pointer to the widget displaying the
                             ///< corresponding text
  QTimer* timer;             ///< Pointer to a structure containing a timer.
  void create_number();
  void create_text();
  void pause_timer() const;
  void restart_timer() const;
  void paint_next_figure(QPainter* painter);
  void process_model();

 private slots:
  void time_to_move();
};

/**
 * The class contains a main window with the ability to select a game.
 */

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  QWidget* central;  ///< Pointer to the widget containing the container window.
  View* game;        ///< Pointer to the widget containing the game window.
  QVBoxLayout* layout;  ///< Pointer to a container containing buttons.
  QPushButton*
      snake_btn_;  ///< Pointer to the button that starts the snake game.
  QPushButton*
      tetris_btn_;  ///< Pointer to the button that starts the tetris game.
 private slots:
  void load_snake();
  void load_tetris();
};

}  // namespace s21

#endif  // VIEW_H
