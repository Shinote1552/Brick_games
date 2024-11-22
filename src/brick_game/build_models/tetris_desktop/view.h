#ifndef VIEW_H
#define VIEW_H

#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QResizeEvent>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>

#include "../../../brick_game/common/common.h"
#include "../../../brick_game/tetris/tetris.h"

// TETRIS
#define CALL_BACKEND                          \
  gameInfo_ = updateCurrentState(&gameInfo_); \
  userInput(action_);

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
static const int windowWight = 800;
static const int gameBlockSize = 30;

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget* parent = nullptr);
  ~View();
  void debugValues();

 private:
  Ui::View* ui;
  QPainter* painter_;
  QPalette* palette_;
  QTimer* draw_timer_;
  QTimer* key_timer_;
  GameInfo_t gameInfo_;
  UserAction_t action_;
  int pause_;

  void initGameInfo();
  void freeGameInfo();
  void initWindow();
  void createSlotSignal();
  void drawingColorsCase(int x, int y, int width, int height, int color);
  void keyPressEvent(QKeyEvent* event) override;
  void drawGameWindow();
  void drawStringWithValue(int x, int y, std::string text, int value);
  void drawGamePause();
  void drawGameOver();
  void drawGameWin();
  void drawGameScene();
  void updateGame();
  void keyPressUpdate();

 protected:
  void paintEvent(QPaintEvent* event) override;
};
}  // namespace s21
#endif  // VIEW_H
