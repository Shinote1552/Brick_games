#include "view.h"

#include "ui_view.h"

namespace s21 {
View::View(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::View), action_(Start) {
  qDebug() << "Object View Conctructed \n";
  ui->setupUi(this);

  initWindow();
  initGameInfo();
  createSlotSignal();
}

View::~View() {
  qDebug() << "\n\n\n\t\t\t SUCCESS DESTRUCTED! \n";
  freeGameInfo();
  delete ui;
}

void View::initWindow() {
  setWindowTitle("BRICK GAME V2.0");  // заголовок окна
  setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
  resize(windowWight, windowWight);
  setFixedSize(windowWight, windowWight);
   //QColorConstants::Svg::gray
  palette_ = new QPalette();
  palette_->setColor(QPalette::Window, QColorConstants::Svg::gray);
  setPalette(*palette_);
}

void View::initGameInfo() {
  gameInfo_.pause = 0;
  gameInfo_.score = 0;
  gameInfo_.level = 0;
  gameInfo_.speed = 0;
  gameInfo_.high_score = 0;
  pause_ = 0;

  // Field allocate memory
  gameInfo_.field = new int*[GAME_COLS_FIELD_X];
  for (int i = 0; i < GAME_COLS_FIELD_X; i++) {
    gameInfo_.field[i] = new int[GAME_ROWS_FIELD_Y];
    for (int j = 0; j < GAME_ROWS_FIELD_Y; j++) {
      gameInfo_.field[i][j] = 0;
    }
  }
  //
  gameInfo_.next = new int*[SHAPE_MATRIX_SIZE];
  for (int i = 0; i < SHAPE_MATRIX_SIZE; i++) {
    gameInfo_.next[i] = new int[SHAPE_MATRIX_SIZE];
    for (int j = 0; j < SHAPE_MATRIX_SIZE; j++) {
      gameInfo_.next[i][j] = 0;
    }
  }
}

void View::freeGameInfo() {
  for (int i = 0; i < GAME_COLS_FIELD_X; i++) {
    delete[] gameInfo_.field[i];
  }
  delete[] gameInfo_.field;
  for (int i = 0; i < SHAPE_MATRIX_SIZE; i++) {
    delete[] gameInfo_.next[i];
  }
  delete[] gameInfo_.next;
}

void View::createSlotSignal() {
  // Инициализация таймера

  double timerSpeed = 3000 * levelspeeds[gameInfo_.level];
  draw_timer_ = new QTimer(this);
  connect(draw_timer_, &QTimer::timeout, this, &View::updateGame);
  draw_timer_->start(timerSpeed);
}

void View::updateGame() {
  if (pause_ || gameInfo_.pause == PAUSE_MENU) {
    update();
    qDebug() << "gameInfo_.pause == PAUSE_MENU\n";
  } else if (gameInfo_.pause != Terminate) {
    qDebug() << "updateCurrentState\np";
    CALL_BACKEND;  // model
    action_ = Empty_key;
    update();  // view
  }
}

void View::debugValues() { qDebug() << geometry(); }

void View::drawStringWithValue(int x, int y, std::string text, int value) {
  QFont font("Futura", 16);
  QString qText;
  painter_->setFont(font);
  qText = QString::fromStdString(text);

  if (value != 0 || text == "Level: ") {
    qText += QString::number(value);
  }
  painter_->drawText(x, y, qText);
}

// высота и ширина каждого блока массива(49 на 49 чтобы была сетка)
void View::drawingColorsCase(int x, int y, int width, int height, int color) {
  switch (color) {
    case 0:  // FIELD
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::darkgray);
      break;
    case 1:  // WALL
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::black);
      break;
    case 2:  // I_SHAPE
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::blue);
      break;
    case 3:  // J_SHAPE
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::darkblue);
      break;
    case 4:  // L_SHAPE
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::orange);
      break;
    case 5:  // O_SHAPE
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::yellow);
      break;
    case 6:  // S_SHAPE - SNAKE
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::green);
      break;
    case 7:  // T_SHAPE
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::purple);
      break;
    case 8:  // Z_SHAPE
      painter_->fillRect(x, y, width, height, QColorConstants::Svg::red);
      break;
    default:
      break;
  }
}

void View::keyPressEvent(QKeyEvent* event) {
  qDebug() << "Key pressed\n";
  if (event->key() == Qt::Key_P) {
    pause_ = !pause_;
    return;
  }
  if (pause_) {
    if (event->key() == Qt::Key_Q || event->key() == Qt::Key_Escape) {
      action_ = Terminate;
    }
  } else {
    switch (event->key()) {
      case Qt::Key_W:
      case Qt::Key_Up:
        action_ = Up;
        break;
      case Qt::Key_S:
      case Qt::Key_Down:
        action_ = Down;
        break;
      case Qt::Key_A:
      case Qt::Key_Left:
        action_ = Left;
        break;
      case Qt::Key_D:
      case Qt::Key_Right:
        action_ = Right;
        break;
      case Qt::Key_Space:
        action_ = Action;
        break;
      case Qt::Key_Enter:
        action_ = Start;
        break;
      case Qt::Key_Escape:
      case Qt::Key_Q:
        action_ = Terminate;
        break;
      default:
        break;
    }
  }
  if (action_ == Terminate) {
    qDebug() << "\n\t Terminate";
    QApplication::quit();
  }
  updateGame();
  double timerSpeed = 3000 * levelspeeds[gameInfo_.level];
  draw_timer_->setInterval(timerSpeed);
}

void View::drawGameScene() {
  int cellWidthBlock = gameBlockSize - 1;  // размер блока
  int cellHeightBlock = gameBlockSize - 1;
  int textPositionX = (GAME_COLS_FIELD_X+2) * gameBlockSize;
  int textPositionY = 4 * gameBlockSize - 10;

  drawStringWithValue(textPositionX, textPositionY,
                      "HightScore: ", gameInfo_.high_score);
  drawStringWithValue(textPositionX, textPositionY + 3 * gameBlockSize,
                      "Score: ", gameInfo_.score);
  drawStringWithValue(textPositionX, textPositionY + 6 * gameBlockSize,
                      "Level: ", gameInfo_.level);

  // drawing field with objects
  for (int i = 0; i < GAME_COLS_FIELD_X; i++) {
    for (int j = 0; j < GAME_ROWS_FIELD_Y; j++) {
      int coordX = (i + 1) * gameBlockSize;
      int coordY = (j + 1) * gameBlockSize;
      drawingColorsCase(coordX, coordY, cellWidthBlock, cellHeightBlock,
                        gameInfo_.field[i][j]);
    }
  }

  // drawing next shape field
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 2; ++j) {
      int coordX = (i + GAME_COLS_FIELD_X+2) * gameBlockSize;
      int coordY = (j + 12) * gameBlockSize;
      drawingColorsCase(coordX, coordY, cellWidthBlock, cellHeightBlock,
                        gameInfo_.next[i][j]);
      if (gameInfo_.next[i][j] == 0) {
        // QColor colorBackground(50, 50, 50);
        painter_->fillRect(coordX, coordY, cellWidthBlock, cellHeightBlock,
                            QColorConstants::Svg::gray);
      }
    }
  }
}

void View::drawGamePause() {
  int textPositionX = 6 * gameBlockSize;
  int textPositionY = 6 * gameBlockSize - 10;
  QColor color(50, 50, 50);
  painter_->fillRect(444, 414, 444, 444, color);

  // Draw the Pause message
  drawStringWithValue(textPositionX, textPositionY, "PAUSED", 0);
  drawStringWithValue(textPositionX, textPositionY + gameBlockSize,
                      "Score: ", gameInfo_.score);
  drawStringWithValue(textPositionX, textPositionY + 2 * gameBlockSize,
                      "Press P to Continue", 0);
}
void View::drawGameOver() {
  int textPositionX = 6 * gameBlockSize;
  int textPositionY = 6 * gameBlockSize - 10;

  drawStringWithValue(textPositionX, textPositionY, "GAME OVER!", 0);
  drawStringWithValue(textPositionX, textPositionY + gameBlockSize,
                      "Score: ", gameInfo_.score);
}

void View::drawGameWin() {
  int textPositionX = 6 * gameBlockSize;
  int textPositionY = 6 * gameBlockSize - 10;

  drawStringWithValue(textPositionX, textPositionY, "GAME WINNER!", 0);
  drawStringWithValue(textPositionX, textPositionY + gameBlockSize,
                      "Score: ", gameInfo_.score);
}

void View::drawGameWindow() {
  if (pause_ && gameInfo_.pause == START_MENU) {
    qDebug() << "\n\t PAUSE";
    drawGamePause();
  } else if (gameInfo_.pause == GAME_OVER_MENU ||
             gameInfo_.pause == TERMINATE_MENU) {
    qDebug() << "\n\t GAME_OVER_MENU";
    drawGameOver();
  } else if (gameInfo_.pause == GAME_WIN) {
    qDebug() << "\n\t GAME_WIN";
    drawGameWin();
  } else {
    qDebug() << "\n\t drawGameScene";
    drawGameScene();
  }
}

// updating with rePaint();
void View::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  painter_ = new QPainter(this);
  painter_->begin(this);
  qDebug() << "\t\t\t\t\t\t\t PaintEvent\n";
  drawGameWindow();
  painter_->end();
  delete painter_;
}
}  // namespace s21
